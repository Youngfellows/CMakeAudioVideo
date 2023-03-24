#include "../include/rgb2yuv/YUV444ptoYUV420p.h"

#include <iostream>

using namespace std;

/**
 * @brief yuv444p转化为yuv420p
 *
 * @param arg
 * @param argv
 * @return int
 */
int main(int arg, char **argv)
{
    const std::string TAG = "SampleYUV444ptoYUV420p::";
    std::cout << TAG << __FUNCTION__ << "():: Line " << __LINE__ << ",arg:" << arg << std::endl;
    if (arg < 3)
    {
        std::cout << TAG << __FUNCTION__ << ",Line " << __LINE__ << ",使用: " << argv[0] << " 宽 高" << std::endl;
        std::cout << TAG << __FUNCTION__ << ",Line " << __LINE__ << ",使用: " << argv[0] << " 711 711" << std::endl;
        return 1;
    }
    uint32_t width = atof(argv[1]);  // 宽
    uint32_t height = atof(argv[2]); // 高

    std::string rgb24File = "./res2/rainbow_" + std::to_string(width) + "x" + std::to_string(height) + "_bmp_rgb24.rgb";
    // std::string yuv444pFile = rgb24File;
    std::string yuv444pFile = "./res2/rainbow_" + std::to_string(width) + "x" + std::to_string(height) + "_bmp_yuv444p.yuv";
    std::string yuv420pFile = "./resource/rainbow_" + std::to_string(width) + "x" + std::to_string(height) + "_yuv444p_to_yuv420p.yuv";
    const char *rgb24FilePath = rgb24File.c_str();     // string 转化为字符串
    const char *yuv444pFilePath = yuv444pFile.c_str(); // string 转化为字符串
    const char *yuv420pFilePath = yuv420pFile.c_str(); // string 转化为字符串
    std::cout << "rgb24FilePath:" << rgb24FilePath << std::endl;
    std::cout << "yuv444pFilePath:" << yuv444pFilePath << std::endl;
    std::cout << "yuv420pFilePath:" << yuv420pFilePath << std::endl;

    // yuv444p转化为yuv420p转换器
    IYUV444ptoYUV420p *yuv444ptoYuv420p = new YUV444ptoYUV420p();
    // bool isCreate = yuv444ptoYuv420p->create(width, height); // 默认初始化
    // bool isCreate = yuv444ptoYuv420p->createFromRGB24(rgb24FilePath, width, height); // rgb24文件初始化
    bool isCreate = yuv444ptoYuv420p->createFromYUV444p(yuv444pFilePath, width, height); // yuv444文件初始化
    if (isCreate)
    {
        yuv444ptoYuv420p->yuv444pToYuv420p(yuv420pFilePath); // yuv444p转化为yuv420p
    }
    yuv444ptoYuv420p->destory(); // 释放资源
    delete yuv444ptoYuv420p;
    return 0;
}