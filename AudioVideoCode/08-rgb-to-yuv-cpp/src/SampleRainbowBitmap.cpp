#include "../include/rainbow/Rainbow.h"
#include <iostream>

using namespace std;

/**
 * @brief RGB24转化为BMP格式数据
 * @brief RGB24格式和BMP格式的彩虹图片
 *
 * @param arg
 * @param argv
 * @return int
 */
int main(int arg, char **argv)
{
    const char *TAG = "SampleRainbowBitmap::";
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

    // const char *bmpFilePath = "./resource/rainbow_711x711_bitmap.bmp"; // bmp图片保存路径
    std::string bmpFile = "./res/rainbow_" + std::to_string(width) + "x" + std::to_string(height) + "_bitmap.bmp";
    const char *bmpFilePath = bmpFile.c_str(); // string 转化为字符串

    IRainbow *rainbow = new Rainbow();                    // 创建彩虹图片生成器对象
    bool isCreate = rainbow->createBitmap(width, height); // 创建BMP格式彩虹图片
    if (isCreate)
    {
        rainbow->createBmpPixels();       // 设置彩虹图像BMP位图像素信息
        rainbow->saveBitmap(bmpFilePath); // 保存位图
    }
    delete rainbow; // 释放内存
    return 0;
}