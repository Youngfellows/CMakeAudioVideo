#include "../include/rgb2yuv/RGB24toYUV420p.h"

using namespace std;

//  __LINE__, 行号
//  __FUNCTION__ 函数
int main(int arg, char **argv)
{
    const char *TAG = "SampleRGB24ToYUV420p";
    std::cout << TAG << " " << __FUNCTION__ << " " << __LINE__ << std::endl;

    // const char *rgb24FilePath = "./res/rainbow-bmp-rgb24.rgb";
    // const char *yuv444pFilePath = "./resource/rainbow-rgb24-to-yuv444p.yuv";
    // unsigned int width = 711;
    // unsigned int height = 711;

    // // 动态申请内存
    // // RGB24toYUV444p *rgb24toyuv444p = new RGB24toYUV444p();
    // IRGB24toYUV444p *rgb24toyuv444p = new RGB24toYUV444p();
    // bool isInitSuccess = rgb24toyuv444p->create(width, height, rgb24FilePath, yuv444pFilePath); // 初始化
    // if (isInitSuccess)
    // {
    //     rgb24toyuv444p->rgb24ToYuv444p(); // rgb24转化为yuv444p
    // }
    // delete rgb24toyuv444p;
    // std::cout << "11111111111111" << std::endl;
    return 0;
}