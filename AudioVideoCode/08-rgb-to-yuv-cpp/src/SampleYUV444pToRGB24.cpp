#include "../include/rgb2yuv/YUV444ptoRGB24.h"

using namespace std;

//  __LINE__, 行号
//  __FUNCTION__ 函数
int main(int arg, char **argv)
{
    const char *TAG = "SampleRGB24ToYUV444";
    std::cout << TAG << " " << __FUNCTION__ << " " << __LINE__ << std::endl;

    const char *yuv444pFilePath = "./res/rainbow-bmp-yuv444p.yuv";
    const char *rgb24FilePath = "./resource/rainbow-yuv444p-to-rgb24.rgb";
    unsigned int width = 711;
    unsigned int height = 711;

    //YUV444ptoRGB24 *yuv444pToRgb24 = new YUV444ptoRGB24(); // 动态申请内存
    IYUV444ptoRGB24 *yuv444pToRgb24 = new YUV444ptoRGB24();                                     // 动态申请内存
    bool isInitSuccess = yuv444pToRgb24->create(width, height, yuv444pFilePath, rgb24FilePath); // 初始化
    if (isInitSuccess)
    {
        yuv444pToRgb24->yuv444pToRgb24(); // yuv444p转化为rgb24
    }
    delete yuv444pToRgb24; // 释放内存
    return 0;
}