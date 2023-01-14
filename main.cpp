#include<opencv2/opencv.hpp>
#include"Armor.h"
using namespace cv;
int main()
{
    Armor armor;
    if(!armor.camerared())
    {
        return 0;
    }
    while(1)
    {
        armor.pre();//对视频预处理
        armor.find();//找到需要的灯条
        armor.judge();//对灯条进行筛选和匹配
        armor.clean();//清除缓存信息
        if(waitKey(10)>=0)
        {
            break;
        }
    }
}
/*
cv::Mat binBrightImg;
cvtColor(_roiImg, _grayImg, COLOR_BGR2GRAY, 1);
cv::threshold(_grayImg, binBrightImg, _param.brightness_threshold, 255, cv::THRESH_BINARY);

 // 把一个3通道图像转换成3个单通道图像
split(_roiImg,channels);//分离色彩通道
//预处理删除己方装甲板颜色
if(_enemy_color==RED)
    _grayImg=channels.at(2)-channels.at(0);//Get red-blue image;
 else _grayImg=channels.at(0)-channels.at(2);//Get blue-red image;

 cv::Mat element = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(3, 3));
dilate(binBrightImg, binBrightImg, element);

 vector<vector<Point>> lightContours;
cv::findContours(binBrightImg.clone(), lightContours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

 for(const auto& contour : lightContours)//对每个轮廓都进行处理
		{
    		//得到轮廓的面积//
			float lightContourArea = contourArea(contour);

    		//筛选掉噪声//
			if(contour.size() <= 5 ||
			   lightContourArea < _param.light_min_area) continue;
			//椭圆拟合生成相应的旋转矩形（注：只是用矩形去拟合灯条，方便获取灯条的长宽比等）
			RotatedRect lightRec = fitEllipse(contour);

			adjustRec(lightRec, ANGLE_TO_UP);
			//筛选出需要的灯条//
            if(lightRec.size.width / lightRec.size.height > _param.light_max_ratio ||
			   lightContourArea / lightRec.size.area() < _param.light_contour_min_solidity)
                continue;

			//扩展矩形的长宽//
			lightRec.size.width *= _param.light_color_detect_extend_ratio;
			lightRec.size.height *= _param.light_color_detect_extend_ratio;
    		//获取矩形的外接矩形框//
			Rect lightRect = lightRec.boundingRect();
			const Rect srcBound(Point(0, 0), _roiImg.size());
    		//上面定义的lightRect为灯条的外接矩形，与检测区域srcBound交集。但实际上我不明白这一步有什么用。如果是为了排除检测区域外的灯条，可是轮廓就是提取自一开始的roiImg的吧。//
    		//此处我一开始没反应过来是为了做什么，经过查找才明白：&=操作是将两个矩阵的交集再存放到lightRect中。相类似的操作还有|（并集），+point（a，b）（平移一个point的向量（a，b）位移），+size（a，b）（长和宽分别加上a和b）//
			lightRect &= srcBound;

    		//以后的操作（一直到#ifdef）都是为了颜色处理，特别是关于识别灯条是蓝色还是红色//
    		//但由于操作十分繁琐，所以我参考了网上来自江达小记的做法，请回到顶部//
			Mat lightImg = _roiImg(lightRect);
			Mat lightMask = Mat::zeros(lightRect.size(), CV_8UC1);
			Point2f lightVertexArray[4];
			lightRec.points(lightVertexArray);
			std::vector<Point> lightVertex;
			for(int i = 0; i < 4; i++)
			{
				lightVertex.emplace_back(Point(lightVertexArray[i].x - lightRect.tl().x,
											   lightVertexArray[i].y - lightRect.tl().y));
			}
			fillConvexPoly(lightMask, lightVertex, 255);

            		if(lightImg.size().area() <= 0 || lightMask.size().area() <= 0) continue;
            		cv::dilate(lightMask, lightMask, element);
			const Scalar meanVal = mean(lightImg, lightMask);


			if(((_enemy_color == BLUE) && (meanVal[BLUE] - meanVal[RED] > 20.0)) || (_enemy_color == RED && meanVal[RED] - meanVal[BLUE] > 20.0))
			{
				lightInfos.push_back(LightDescriptor(lightRec));
			}
    		//若使用了两通道值相减的方法，则这里可以直接将结果保存下来。注意放入的是lightrec而不是lightrect的外接矩形信息
			//lightInfos.push_back(LightDescriptor(lightRec));




		//检查是否检测到灯条//
if(lightInfos.empty())
{
return _flag = ARMOR_NO;
}
}//循环结束



{
//用到了C++11的lambda（可简单看作函数对象），设置了ld1和ld2两个参数，依照灯条中心的x坐标从左到右（opencv的坐标轴为横x竖y）。center为point2f类型的。//
sort(lightInfos.begin(), lightInfos.end(), [](const LightDescriptor& ld1, const LightDescriptor& ld2)
{
return ld1.center.x < ld2.center.x;
});
//设一个长为lightInfos.size()，值都为-1的数组//
vector<int> minRightIndices(lightInfos.size(), -1);

//遍历每一种组合//
for(size_t i = 0; i < lightInfos.size(); i++)
{
for(size_t j = i + 1; (j < lightInfos.size()); j++)
{
const LightDescriptor& leftLight  = lightInfos[i];
const LightDescriptor& rightLight = lightInfos[j];

//计算左灯和右灯的角度差//
float angleDiff_ = abs(leftLight.angle - rightLight.angle);
//计算左灯和右灯的长度差之比（越相近该值越小）//
float LenDiff_ratio = abs(leftLight.length - rightLight.length) / max(leftLight.length, rightLight.length);
//通过阈值筛选灯条//
if(angleDiff_ > _param.light_max_angle_diff_ ||
LenDiff_ratio > _param.light_max_height_diff_ratio_)
{
continue;
}


//计算左右灯条中心距离//
float dis = cvex::distance(leftLight.center, rightLight.center);
//计算左右灯条长度的均值//
float meanLen = (leftLight.length + rightLight.length) / 2;
//灯条y的差//
float yDiff = abs(leftLight.center.y - rightLight.center.y);
//y差值的比率//
float yDiff_ratio = yDiff / meanLen;
//同前//
float xDiff = abs(leftLight.center.x - rightLight.center.x);
float xDiff_ratio = xDiff / meanLen;
//灯条的距离与长度的比值（也就是嫌疑装甲板长和宽的比值）//
float ratio = dis / meanLen;
//对上面各量筛选，如果y差太大（y最好越相近越好），或者x差的太小，又或者装甲板长宽比不合适就排除掉。//
if(yDiff_ratio > _param.light_max_y_diff_ratio_ ||
xDiff_ratio < _param.light_min_x_diff_ratio_ ||
              ratio > _param.armor_max_aspect_ratio_ ||
ratio < _param.armor_min_aspect_ratio_)
{
continue;
}

// calculate pairs' info
//通过长宽比来确定是大的还是小的装甲板//
int armorType = ratio > _param.armor_big_armor_ratio ? BIG_ARMOR : SMALL_ARMOR;
// calculate the rotation score
float ratiOff = (armorType == BIG_ARMOR) ? max(_param.armor_big_armor_ratio - ratio, float(0)) : max(_param.armor_small_armor_ratio - ratio, float(0));
float yOff = yDiff / meanLen;
//应该是rotationScore越接近0越好，看后续用处//
float rotationScore = -(ratiOff * ratiOff + yOff * yOff);

//生成相应的装甲板//
ArmorDescriptor armor(leftLight, rightLight, armorType, _grayImg, rotationScore, _param);
//将获得的嫌疑装甲板放到armors中去//
_armors.emplace_back(armor);
break;
}
}

//此处删除debug内容//

//没找到的话。。//
if(_armors.empty())
{
return _flag = ARMOR_NO;
}
}

//此处删除调试信息//

//delete the fake armors
_armors.erase(remove_if(_armors.begin(), _armors.end(), [](ArmorDescriptor& i)
{
    //这里就是识别装甲板的算法了//
    return !(i.isArmorPattern());
}), _armors.end());

//江达小记版本//
_armors.erase(remove_if(_armors.begin(), _armors.end(), [this](ArmorDescriptor& i)
{//lamdba函数判断是不是装甲板，将装甲板中心的图片提取后让识别函数去识别，识别可以用svm或者模板匹配等
    return 0==(i.isArmorPattern(_small_Armor_template,_big_Armor_template,lastEnemy));
} ), _armors.end());

//没有一个是装甲板的情况//
if(_armors.empty())
{
_targetArmor.clear();

//看是目标丢失还是没识别出来//
if(_flag == ARMOR_LOCAL)
{
//cout << "Tracking lost" << endl;
return _flag = ARMOR_LOST;
}
else
{
//cout << "No armor pattern detected." << endl;
return _flag = ARMOR_NO;
}
}

//calculate the final score
for(auto & armor : _armors)
{
armor.finalScore = armor.sizeScore + armor.distScore + armor.rotationScore;
}

//choose the one with highest score, store it on _targetArmor
std::sort(_armors.begin(), _armors.end(), [](const ArmorDescriptor & a, const ArmorDescriptor & b)
{
return a.finalScore > b.finalScore;
});
_targetArmor = _armors[0];

//update the flag status
_trackCnt++;


*/
