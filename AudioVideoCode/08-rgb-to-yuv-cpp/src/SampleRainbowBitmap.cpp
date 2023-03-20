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
    std::cout << TAG << __FUNCTION__ << "():: LINE:" << __LINE__ << std::endl;

    // rgb24或bmp彩虹图片生成器,动态申请内存
    uint32_t width = 711;                                          // 宽
    uint32_t height = 711;                                         // 高
    const char *bmpFilePath = "./resource/rainbow_bitmap_6x6.bmp"; // bmp图片保存路径
    IRainbow *rainbow = new Rainbow();                             // 创建彩虹图片生成器对象
    bool isCreate = rainbow->createBitmap(width, height);          // 创建BMP格式彩虹图片
    if (isCreate)
    {
        rainbow->saveBitmap(bmpFilePath); // 保存位图
    }
    delete rainbow; // 释放内存
    return 0;
}