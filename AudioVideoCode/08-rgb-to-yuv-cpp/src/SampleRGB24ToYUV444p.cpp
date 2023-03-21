#include "../include/rgb2yuv/RGB24toYUV444p.h"
#include <string>

using namespace std;

//  __LINE__, 行号
//  __FUNCTION__ 函数
int main(int arg, char **argv)
{
    const char *TAG = "SampleRGB24ToYUV444";
    std::cout << TAG << " " << __FUNCTION__ << " " << __LINE__ << std::endl;

    unsigned int width = 711;
    unsigned int height = 711;
    std::string rgb24File = "./res/rainbow_" + std::to_string(width) + "x" + std::to_string(height) + "_rgb24.rgb";
    std::string yuv444pFile = "./resource/rainbow_" + std::to_string(width) + "x" + std::to_string(height) + "_rgb24_to_yuv444p.yuv";
    const char *rgb24FilePath = rgb24File.c_str();     // string 转化为字符串
    const char *yuv444pFilePath = yuv444pFile.c_str(); // string 转化为字符串

    // 动态申请内存
    // RGB24toYUV444p *rgb24toyuv444p = new RGB24toYUV444p();
    IRGB24toYUV444p *rgb24toyuv444p = new RGB24toYUV444p();
    bool isInitSuccess = rgb24toyuv444p->create(width, height, rgb24FilePath, yuv444pFilePath); // 初始化
    if (isInitSuccess)
    {
        rgb24toyuv444p->rgb24ToYuv444p(); // rgb24转化为yuv444p
    }
    delete rgb24toyuv444p;
    // std::cout << "11111111111111" << std::endl;
    return 0;
}