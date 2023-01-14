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
