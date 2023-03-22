#include "../include/rgb2yuv/YUV444ptoRGB24.h"

using namespace std;

//  __LINE__, 行号
//  __FUNCTION__ 函数
int main(int arg, char **argv)
{
    const char *TAG = "SampleRGB24ToYUV444";
    std::cout << TAG << " " << __FUNCTION__ << " " << __LINE__ << std::endl;

    std::cout << TAG << __FUNCTION__ << ",Line " << __LINE__ << ",arg:" << arg << std::endl;
    if (arg < 3)
    {
        std::cout << TAG << __FUNCTION__ << ",Line " << __LINE__ << ",使用: " << argv[0] << " 宽 高" << std::endl;
        std::cout << TAG << __FUNCTION__ << ",Line " << __LINE__ << ",使用: " << argv[0] << " 711 711" << std::endl;
        return 1;
    }
    // uint32_t width = 711;            // 宽
    // uint32_t height = 711;           // 高
    uint32_t width = atof(argv[1]);  // 宽
    uint32_t height = atof(argv[2]); // 高

    std::string yuv444pFile = "./res2/rainbow_" + std::to_string(width) + "x" + std::to_string(height) + "_bmp_yuv444p.yuv";
    std::string rgb24File = "./resource/rainbow_" + std::to_string(width) + "x" + std::to_string(height) + "_yuv444p_to_rgb24.rgb";
    const char *rgb24FilePath = rgb24File.c_str();     // string 转化为字符串
    const char *yuv444pFilePath = yuv444pFile.c_str(); // string 转化为字符串

    // YUV444ptoRGB24 *yuv444pToRgb24 = new YUV444ptoRGB24(); // 动态申请内存
    IYUV444ptoRGB24 *yuv444pToRgb24 = new YUV444ptoRGB24();                                     // 动态申请内存
    bool isInitSuccess = yuv444pToRgb24->create(width, height, yuv444pFilePath, rgb24FilePath); // 初始化
    std::cout << TAG << " " << __FUNCTION__ << " " << __LINE__ << "isInitSuccess:" << isInitSuccess << std::endl;
    if (isInitSuccess)
    {
        yuv444pToRgb24->yuv444pToRgb24(); // yuv444p转化为rgb24
    }

    delete yuv444pToRgb24; // 释放内存
    return 0;
}