#include <iostream>
#include "../include/pixel/RGB24.h"

using namespace std;

int main(int arg, char **argv)
{
    const char *TAG = "RGB24::";
    std::cout << TAG << __FUNCTION__ << ",Line " << __LINE__ << std::endl;
    const char *rgb24FilePath = "./resource/rainbow_711x711_rgb24.rgb24"; // bmp图片保存路径
    uint32_t width = 6;
    uint32_t height = 6;
    RGB24 *rgb24 = new RGB24();
    bool isCreate = rgb24->rgb24Create(width, height);
    if (isCreate)
    {
        rgb24->saveRgb24(rgb24FilePath);
    }
    delete rgb24;

    return 0;
}