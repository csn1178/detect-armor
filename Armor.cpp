#include "Armor.h"
#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;
void drawframe(vector<RotatedRect> rec,Mat img);
bool Armor::camerared()
{
    capture.open("C:\\Users\\20887\\CLionProjects\\robomaster2\\78.mov");
    if(!capture.isOpened())
    {
        cout<<"fail to open video\n";
        return false;
    }
    else
    {
        return true;
    }

}

void Armor::pre()
{
    capture>>frame;
    Mat HsvImage;
    Mat afterImage;
    double Max;
    cvtColor(frame,HsvImage,COLOR_BGR2HSV);//转换成HSV效果更好
    split(HsvImage,channels);
    //imshow("pre",channels[2]);
    if(enemyCO=="RED")//敌我识别
    {
        channels[2]=channels[2]-channels[0];
        channels[2]=channels[2]-channels[0];
        channels[2]=channels[2]-channels[0];
       // imshow("after",channels[2]);
    }
    else
    {
        channels[2]=channels[0]-channels[2];
        channels[2]=channels[0]-channels[2];
        channels[2]=channels[0]-channels[2];
    }
    minMaxLoc(channels[2],NULL,&Max,NULL,NULL);
    threshold(channels[2],channels[2],Max*0.60,255,THRESH_BINARY);//二值化
    Mat element= getStructuringElement(MORPH_RECT,elementSize);
    medianBlur(channels[2],channels[2],3);//中值滤波
    morphologyEx(channels[2],channels[2],MORPH_DILATE,element,Point(-1,-1),1);
    HsvImage.copyTo(afterImage,channels[2]);
    imshow("二值化",channels[2]);
}
cv::RotatedRect& adjustRec(cv::RotatedRect& rec)//修正角度
{
    using std::swap;
    float& width = rec.size.width;
    float& height = rec.size.height;
    float& angle = rec.angle;
    while (angle >= 90.0)
    {
        angle -= 180.0;
    }
    while (angle < -90.0)
    {
        angle += 180.0;
    }
    if (angle >= 45.0)
    {
        swap(width, height);
        angle -= 90.0;
    }
    else if (angle < -45.0)
    {
        swap(width, height);
        angle += 90.0;
    }
    return rec;
}

void Armor::find()
{
    vector<vector<Point>>conturs;
   // vector<RotatedRect>light;//符合的灯条
    float x,y;
    findContours(channels[2].clone(),conturs,RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);//找灯条轮廓
    /*Mat drawingImg = Mat::zeros(frame.size(), CV_8UC3);//调试
    for (int i = 0; i < conturs.size(); i++)
    {
        drawContours(drawingImg, conturs, i, Scalar(0, 255, 0));
    }
    imshow("Contours Image",drawingImg);*/
    for(const auto& contur:conturs)
    {
        float lightarea= contourArea(contur);
        if(contur.size()<=5||lightarea<10)//初筛
        {
            continue;
        }
        RotatedRect lightRec= fitEllipse(contur);//找旋转矩形
        adjustRec(lightRec);//调整
        x=lightRec.center.x-lightRec.size.width;
        y=lightRec.center.y-lightRec.size.height;
        if((lightRec.size.width/lightRec.size.height)>0.8||x<0||y<0)//宽高比和凸度筛选灯条
        {
            continue;
        }
        if((lightRec.size.width/lightRec.size.height)>1.0||(lightarea/lightRec.size.area())<0.5)//按照变换后筛选需要的灯条
        {
            continue;
        }
        lightRec.size.height*=1.1;//扩大面积
        lightRec.size.width*=1.1;
        if ((lightRec.size.height > 10 && (lightRec.size.height < 150) && (lightRec.angle < 45 || lightRec.angle>135)))
        {
            light.push_back(lightRec);//合适的灯条压入栈中
        }
    }
    /*Mat drawingImg = Mat::zeros(frame.size(), CV_8UC3);//调试
    for (int i = 0; i < light.size(); i++)
    {
       // drawContours(frame, conturs, i, Scalar(0, 255, 0));
        drawframe(light,frame);
    }
    //imshow("Contours Image",drawingImg);*/
    conturs.clear();
}
void drawframe(vector<RotatedRect> rec,Mat img)//划出框架
{
    for (int i = 0; i < rec.size(); i++)
    {
        Point2f p[4];
        rec[i].points(p);
        line(img, p[0], p[1], Scalar(0, 0, 255), 1, 8, 0);
        line(img, p[1], p[2], Scalar(0, 0, 255), 1, 8, 0);
        line(img, p[2], p[3], Scalar(0, 0, 255), 1, 8, 0);
        line(img, p[3], p[0], Scalar(0, 0, 255), 1, 8, 0);
        line(img,p[0],p[2],Scalar(0,255,0),1);
        line(img,p[1],p[3],Scalar(0,255,0),1);
    }
}


void Armor::judge()//对灯条进行筛选和匹配
{

    if(light.size()<=1)
    {
        cout<<"NO enough light contours"<<endl;
    }
    sort(light.begin(),light.end(),[](const RotatedRect &ld1,const RotatedRect &ld2)//对灯条以x的大小排序
    {
        return ld1.center.x<ld2.center.x;
    });
    for(int i=0;i<light.size();i++)
    {
        for(int j=i+1;j<light.size();j++)
        {
            const RotatedRect &left=light[i];
            const RotatedRect &right=light[j];
            double heighDiff=abs(left.size.height-right.size.height);
           // double widthDiff=abs(right.size.width-left.size.width);
            double angleDiff=abs(right.angle-left.angle);//角度差
            //计算左右灯条中心距离//
            double dis = sqrt((left.center.x - right.center.x) * (left.center.x - right.center.x) + (left.center.y - right.center.y) * (left.center.y - right.center.y));
            double averheight=(left.size.height+right.size.height)/2;
            //计算左右灯条长度的均值//
            double yDiff=abs(left.center.y-right.center.y);
            //灯条y的差//
            double yDiffRatio=yDiff/averheight;//y差比率
            double xDiff=abs(left.center.x-right.center.x);
            double xDiffRatio=xDiff/averheight;//x差比率
            //灯条的距离与长度的比值（也就是嫌疑装甲板长和宽的比值）//
            double ratio = dis / averheight;
            //计算左灯和右灯的长度差之比（越相近该值越小）//
            double heightDiff_ratio = heighDiff / max(left.size.height, right.size.height);
            //通过阈值筛选灯条//
            if(angleDiff>10||xDiffRatio<0.5||yDiffRatio>0.7||ratio>3||ratio<1)
            {
                continue;
            }
            armor_rect.center.x = (left.center.x + right.center.x) / 2;//灯条匹配成装甲板部分
            armor_rect.center.y = (left.center.y + right.center.y) / 2;
            armor_rect.angle=(left.angle+right.angle)/2;
            if(180-angleDiff<3)
            {
                armor_rect.angle+=90;
            }
            armor_rect.size.height = (left.size.height + right.size.height) / 2;
            armor_rect.size.width = sqrt((left.center.x - right.center.x) * (left.center.x - right.center.x) + (left.center.y - right.center.y) * (left.center.y - right.center.y));
            double newh = armor_rect.size.height;
            double neww = armor_rect.size.width;
            if (newh < neww)
            {
                armor_rect.size.height = newh;
                armor_rect.size.width = neww;
            }
            else
            {
                armor_rect.size.height = neww;
                armor_rect.size.width = newh;
            }
            armorRects.emplace_back(armor_rect);
            armors.push_back(armor_rect);
        }

    }
   // match();//模板匹配
    cout<<armors.size()<<endl;
    if (armors.empty())
    {
        cout << "no armors!" << endl;
    }
    frame.copyTo(afterImage);
   drawframe(armors,afterImage);//绘制框架
    imshow("video",afterImage);
}

void Armor::clean()//清除缓存
{
    armors.clear();
    armorRects.clear();
    channels.clear();
    light.clear();
    finally.clear();
}

void Armor::match()//模板匹配思路
{
    Mat src;
    Point2f p[4];
    Point MinPoint;
    Point MaxPoint;
    Point FinalPoint;
    double min, max;
    for(int i=0;i<armors.size();i++)
    {
        armors[i].points(p);
        if(p[0].x+armors[i].size.width+150>frame.rows||p[0].y+armors[i].size.width+150>frame.cols)
        {
            continue;
        }
        src=frame(Rect(p[0].x,p[0].y,armors[i].size.width+50,armors[i].size.height+50));
        Point2f *lastItemPointer = (p+sizeof p/sizeof p[0]);
       vector<Point2f> contour(p,lastItemPointer);
        for(int j=0;j<16;j++)
        {
            int width = src.cols - matcher[j].cols + 1;
            int height = src.rows - matcher[j].rows + 1;
            Mat result(Size(width, height), CV_32FC1);
            matchTemplate(src,matcher[j],result,TM_SQDIFF_NORMED);
            minMaxLoc(result, &min, &max, &MinPoint, &MaxPoint);
            FinalPoint=MinPoint;
         /*  if (FinalPoint.x>p[0].x&&FinalPoint.x<p[2].x&&FinalPoint.y>p[0].y&&FinalPoint.y<p[2].y)
            {
                finally.push_back(armors[i]);
            }
            else if ((FinalPoint.x==p[0].x|| FinalPoint.x==p[2].x) &&(FinalPoint.y>=p[0].y&&FinalPoint.y<=p[2].y))
            {
                finally.push_back(armors[i]);
            }
            else if ((FinalPoint.y==p[0].y||FinalPoint.y==p[2].y)&&(FinalPoint.x>=p[0].x&&FinalPoint.x<=p[2].x))
            {
                finally.push_back(armors[i]);
            }*/
           if(pointPolygonTest(contour,FinalPoint, true)>=0)
            {
                finally.push_back(armors[i]);
            }

        }

    }

}

Armor::Armor()//载入装甲板模板图像
{
    //cout<<"fail to open photo!"<<endl;
    Mat src;
    src= imread("C:\\Users\\20887\\CLionProjects\\robomaster2\\1.jpg");
    matcher.push_back(src);
    if(matcher.empty())
    {
        cout<<"fail to open photo!"<<endl;
    }
    cout<<"gfdgdfdgdf"<<endl;
    src= imread("C:\\Users\\20887\\CLionProjects\\robomaster2\\2.jpg");
    matcher.push_back(src);
    src= imread("C:\\Users\\20887\\CLionProjects\\robomaster2\\3.jpg");
    matcher.push_back(src);
    src= imread("C:\\Users\\20887\\CLionProjects\\robomaster2\\4.jpg");
    matcher.push_back(src);
    src= imread("C:\\Users\\20887\\CLionProjects\\robomaster2\\5.jpg");
    matcher.push_back(src);
    src= imread("C:\\Users\\20887\\CLionProjects\\robomaster2\\6.jpg");
    matcher.push_back(src);
    src= imread("C:\\Users\\20887\\CLionProjects\\robomaster2\\7.jpg");
    matcher.push_back(src);
    src= imread("C:\\Users\\20887\\CLionProjects\\robomaster2\\8.jpg");
    matcher.push_back(src);
    src= imread("C:\\Users\\20887\\CLionProjects\\robomaster2\\9.jpg");
    matcher.push_back(src);
    src= imread("C:\\Users\\20887\\CLionProjects\\robomaster2\\10.jpg");
    matcher.push_back(src);
    src= imread("C:\\Users\\20887\\CLionProjects\\robomaster2\\11.jpg");
    matcher.push_back(src);
    src= imread("C:\\Users\\20887\\CLionProjects\\robomaster2\\12.jpg");
    matcher.push_back(src);
    src= imread("C:\\Users\\20887\\CLionProjects\\robomaster2\\13.jpg");
    matcher.push_back(src);
    src= imread("C:\\Users\\20887\\CLionProjects\\robomaster2\\14.jpg");
    matcher.push_back(src);
    src= imread("C:\\Users\\20887\\CLionProjects\\robomaster2\\15.jpg");
    matcher.push_back(src);
    src= imread("C:\\Users\\20887\\CLionProjects\\robomaster2\\16.jpg");
    matcher.push_back(src);
}
