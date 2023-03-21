#include "../include/rgb2yuv/RGB24toYUV420p.h"
#include <string>

using namespace std;

//  __LINE__, 行号
//  __FUNCTION__ 函数
int main(int arg, char **argv)
{
    const char *TAG = "SampleRGB24ToYUV420p";
    std::cout << TAG << " " << __FUNCTION__ << " " << __LINE__ << std::endl;
    // const char *rgb24FilePath = "./res/rainbow-bmp-rgb24.rgb";
    // const char *yuv420pFilePath = "./resource/rainbow-rgb24-to-yuv420p.yuv";

    uint32_t width = 711;  // 宽
    uint32_t height = 711; // 高
    std::string rgb24File = "./res/rainbow_" + std::to_string(width) + "x" + std::to_string(height) + "_rgb24.rgb";
    std::string yuv420pFile = "./res/rainbow_" + std::to_string(width) + "x" + std::to_string(height) + "_rgb24_to_yuv420p.yuv";
    const char *rgb24FilePath = rgb24File.c_str();     // string 转化为字符串
    const char *yuv420pFilePath = yuv420pFile.c_str(); // string 转化为字符串

    // RGB24toYUV420p *rgb24toYuv420p = new RGB24toYUV420p();      // 动态申请内存
    IRGB24toYUV420p *rgb24toYuv420p = new RGB24toYUV420p();     // 动态申请内存
    bool isInitSuccess = rgb24toYuv420p->create(width, height); // 初始化
    // bool isInitSuccess = rgb24toYuv420p->create(width, height, rgb24FilePath); // 初始化
    if (isInitSuccess)
    {
        rgb24toYuv420p->rgb24ToYuv420p(yuv420pFilePath); // rgb24转化为yuv420p
    }

    delete rgb24toYuv420p; // 释放内存

    return 0;
}