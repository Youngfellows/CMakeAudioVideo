#include "../include/rgb2yuv/YUV420ptoYUV444p.h"

using namespace std;

/**
 * @brief yuv420p转化为yuv444p
 *
 * @param arg
 * @param argv
 * @return int
 */
int main(int arg, char **argv)
{
    const std::string TAG = "SampleYUV420pToYUV444p::";
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
    std::string yuv420pFile = "./res2/rainbow_" + std::to_string(width) + "x" + std::to_string(height) + "_bmp_yuv420p.yuv";
    std::string yuv444pFile = "./resource/rainbow_" + std::to_string(width) + "x" + std::to_string(height) + "_yuv420p_to_yuv444p.yuv";
    const char *rgb24FilePath = rgb24File.c_str();     // string 转化为字符串
    const char *yuv420pFilePath = yuv420pFile.c_str(); // string 转化为字符串
    const char *yuv444pFilePath = yuv444pFile.c_str(); // string 转化为字符串
    std::cout << "rgb24FilePath:" << rgb24FilePath << std::endl;
    std::cout << "yuv420pFilePath:" << yuv420pFilePath << std::endl;
    std::cout << "yuv444pFilePath:" << yuv444pFilePath << std::endl;

    // 创建yuv420p到yuv444p转换器
    IYUV420ptoYUV444p *yuv420pToYuv444p = new YUV420ptoYUV444p();
    // bool isCreate = yuv420pToYuv444p->create(width, height); // 初始化
    // bool isCreate = yuv420pToYuv444p->createFromRgb24(rgb24FilePath, width, height);
    bool isCreate = yuv420pToYuv444p->createFromYuv420p(yuv420pFilePath, width, height);
    if (isCreate)
    {
        yuv420pToYuv444p->yuv420pToYuv444p(yuv444pFilePath); // yuv420p转化为yuv444p
    }
    yuv420pToYuv444p->destory(); // 释放资源
    delete yuv420pToYuv444p;

    return 0;
}