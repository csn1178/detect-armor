#ifndef ROBOMASTER_ARMOR_H
#define ROBOMASTER_ARMOR_H
#include <opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;
class Armor
{
public:
    bool camerared();//读取视频
    void pre();//对视频预处理
    void find();//找到需要的灯条
    void judge();//对灯条进行筛选和匹配
    void clean();//清除缓存信息
    void match();//模板匹配
    Armor();//构造函数

private:
    Mat frame;
    VideoCapture capture;
    Size elementSize=Size(5,5);
    Mat afterImage;
    string enemyCO="RED";//敌我识别
    vector<RotatedRect>light;//符合的灯条
    vector<RotatedRect>armors;
    vector<RotatedRect>armorRects;
    vector<RotatedRect>finally;
    vector<Mat>matcher;
    RotatedRect armor_rect;
    vector<Mat>channels;
};


#endif //ROBOMASTER_ARMOR_H
