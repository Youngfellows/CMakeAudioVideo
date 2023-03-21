#include <iostream>
#include "../include/pixel/RGB24.h"

using namespace std;

int main(int arg, char **argv)
{
    const char *TAG = "RGB24::";
    std::cout << TAG << __FUNCTION__ << ",Line " << __LINE__ << std::endl;
    const char *rgb24FilePath = "./resource/rainbow_711x711_rgb24.rgb";          // bmp图片保存路径
    const char *copyRgb24FilePath = "./resource/rainbow_711x711_rgb24_copy.rgb"; // bmp图片保存路径
    uint32_t width = 6;
    uint32_t height = 6;
    RGB24 *rgb24 = new RGB24();
    bool isCreate = rgb24->rgb24Create(width, height); // 创建rgb24文件
    if (isCreate)
    {
        rgb24->saveRgb24(rgb24FilePath); // 保存rgb24文件

        // 拷贝rgb24数据到指定文件
        width = 6;
        height = 6;
        isCreate = rgb24->rgb24Create(rgb24FilePath, width, height); // 创建rgb24文件
        if (isCreate)
        {
            rgb24->saveRgb24(copyRgb24FilePath); // 保存rgb24到copy文件
        }
    }
    delete rgb24; // 释放内存

    return 0;
}