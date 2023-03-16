#include "../include/rgb2yuv/RGB24toYUV444p.h"

using namespace std;

//  __LINE__, 行号
//  __FUNCTION__ 函数
int main(int arg, char **argv)
{
    const char *TAG = "SampleRGB24ToYUV444";
    std::cout << TAG << " " << __FUNCTION__ << " " << __LINE__ << std::endl;

    const char *rgb24FilePath = "xxxx.rgb24";
    const char *yuv444pFilePath = "yyyy.yuv444";
    unsigned int width = 700;
    unsigned int height = 700;

    // 动态申请内存
    // RGB24toYUV444p *rgb24toyuv444p = new RGB24toYUV444p();
    IRGB24toYUV444p *rgb24toyuv444p = new RGB24toYUV444p();
    rgb24toyuv444p->create(width, height, rgb24FilePath, yuv444pFilePath);

    // 释放内存
    rgb24toyuv444p->free();
    delete rgb24toyuv444p;
    std::cout << "11111111111111" << std::endl;
    return 0;
}