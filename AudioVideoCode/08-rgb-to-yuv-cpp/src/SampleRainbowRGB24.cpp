#include "../include/rainbow/Rainbow.h"

#include <iostream>
#include <string>

/**
 * @brief 生成彩虹图片的RGB24像素数据
 * @brief 拷贝生成的rgb24图片到指定目录
 *
 * @param arg
 * @param argv
 * @return int
 */
int main(int arg, char **argv)
{
    const char *TAG = "SampleRainbowRGB24::";
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
    std::string rgb24File = "./res/rainbow_" + std::to_string(width) + "x" + std::to_string(height) + "_rgb24.rgb";
    std::string copyRgb24File = "./res/rainbow_" + std::to_string(width) + "x" + std::to_string(height) + "_copy_rgb24.rgb";
    const char *rgb24FilePath = rgb24File.c_str();         // string 转化为字符串
    const char *copyRgb24FilePath = copyRgb24File.c_str(); // string 转化为字符串
    std::cout << TAG << __FUNCTION__ << ",Line " << __LINE__ << ",rgb24FilePath:" << rgb24FilePath << std::endl;
    std::cout << TAG << __FUNCTION__ << ",Line " << __LINE__ << ",copyRgb24FilePath:" << copyRgb24FilePath << std::endl;

    IRainbow *rgb24Rainbow = new Rainbow(); // 动态申请内存,创建Rainbow对象
    bool isCreate = rgb24Rainbow->createRGB24(width, height);
    if (isCreate)
    {
        rgb24Rainbow->createRGB24Pixels();      // 设置rgb24位图像素信息
        rgb24Rainbow->saveRGB24(rgb24FilePath); // 保存到文件
        IRGB24Pixel *rgb24 = new RGB24();       // 创建RGB24对象
        isCreate = rgb24->rgb24Create(rgb24FilePath, width, height);
        if (isCreate)
        {
            rgb24->saveRgb24(copyRgb24FilePath); // 拷贝到文件
        }
    }
    rgb24Rainbow->destory(); // 释放资源
    // delete rgb24Rainbow; // 释放内存
    return 0;
}