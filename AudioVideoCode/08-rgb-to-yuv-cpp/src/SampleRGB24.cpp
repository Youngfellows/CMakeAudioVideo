#include <iostream>
#include <string>
#include "../include/pixel/RGB24.h"

using namespace std;

/**
 * @brief 拷贝RGB24文件到指定目录
 *
 * @param arg
 * @param argv
 * @return int
 */
int main(int arg, char **argv)
{
    const char *TAG = "RGB24::";
    std::cout << TAG << __FUNCTION__ << ",Line " << __LINE__ << std::endl;
    uint32_t width = 711;  // 宽
    uint32_t height = 711; // 高
    std::string rgb24File = "./res/rainbow_" + std::to_string(width) + "x" + std::to_string(height) + "_rgb24.rgb";
    std::string copyRgb24File = "./res/rainbow_" + std::to_string(width) + "x" + std::to_string(height) + "_copy2_rgb24.rgb";
    const char *rgb24FilePath = rgb24File.c_str();         // string 转化为字符串
    const char *copyRgb24FilePath = copyRgb24File.c_str(); // string 转化为字符串
    std::cout << TAG << __FUNCTION__ << ",Line " << __LINE__ << ",rgb24FilePath:" << rgb24FilePath << std::endl;
    std::cout << TAG << __FUNCTION__ << ",Line " << __LINE__ << ",copyRgb24FilePath:" << copyRgb24FilePath << std::endl;

    RGB24 *rgb24 = new RGB24();                                       // 创建RGB24文件生成器                                                                // 拷贝rgb24数据到指定文件
    bool isCreate = rgb24->rgb24Create(rgb24FilePath, width, height); // 创建rgb24文件
    if (isCreate)
    {
        rgb24->saveRgb24(copyRgb24FilePath); // 拷贝rgb24文件
    }
    delete rgb24; // 释放内存

    return 0;
}