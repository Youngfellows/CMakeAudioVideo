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
    IPixel *rainbow = new Rainbow();
    uint32_t bmpSize;                                                    // bmp格式彩虹图片像素数据大小
    uint32_t width = 6;                                                  // 宽
    uint32_t height = 6;                                                 // 高
    uint32_t headLength = 54;                                            // 头文件的大小
    uint8_t *rainbowBmpData = rainbow->bmpData(&bmpSize, width, height); // 获取bmp格式彩虹图片像素数据
    std::cout << TAG << __FUNCTION__ << "():: LINE:" << __LINE__ << ",rainbowBmpData len:" << bmpSize << ",rainbowBmpData:" << rainbowBmpData << std::endl;
    std::cout << TAG << __FUNCTION__ << "():: LINE:" << __LINE__ << ",bfType:" << rainbow->shortFromBytes(rainbowBmpData, 0) << std::endl;
    std::cout << TAG << __FUNCTION__ << "():: LINE:" << __LINE__ << ",bfSize:" << rainbow->intFromBytes(rainbowBmpData, 2) << std::endl;
    uint32_t b = (uint32_t)rainbowBmpData[headLength];
    uint32_t g = (uint32_t)rainbowBmpData[headLength + 1];
    uint32_t r = (uint32_t)rainbowBmpData[headLength + 2];
    std::cout << TAG << __FUNCTION__ << "():: LINE:" << __LINE__ << ",rainbowBmpData len:" << bmpSize << ",(" << r << "," << g << "," << b << ")" << std::endl;

    // 保存bmp数据到内存
    // const char *bmpFilePath = "./resource/rainbow_bitmap_6x6.bmp";
    // const char *data = "111111111111122222222222233333333";
    // uint8_t *rainbowBmpData2 = (uint8_t *)data;
    // rainbow->saveBitmap(bmpFilePath, rainbowBmpData2, strlen(data)); // 保存到文件

    // delete rainbow; // 释放内存
    rainbow->destory(); // 释放内存

    return 0;
}