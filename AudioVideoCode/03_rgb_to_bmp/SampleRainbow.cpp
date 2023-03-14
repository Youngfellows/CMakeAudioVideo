#include "Bitmap.h"
#include "Rainbow.h"

int main(int arg, char *argv[])
{
    std::cout << "main:: BMP图片:生成彩虹图片" << std::endl;
    const char *rainbowFilePath = "./resource/rainbow-700x700.bmp";   // 要保存的彩虹文件路径
    const char *rainbowFilePath2 = "./resource/rainbow2-700x700.bmp"; // 要保存的彩虹文件路径
    uint32_t width = 11;                                              // 图片宽
    uint32_t height = 11;                                             // 图片高
    IBitmap *bitmap = new Bitmap();                                   // 创建BMP对象,动态申请内存
    bool isCreate = bitmap->bmpCreate(width, height, 24);             // 初始化BMP图片信息
    if (!isCreate)
    {
        return -1;
    };

    // 2. 向文件中写入颜色数据
    for (int i = 0; i < height; i++)
    {
        unsigned int currentColor = RAINBOW_COLORS[0]; // 当前颜色，默认是红
        if (i < 100)
        {
            // currentColor = RAINBOW_COLORS[0];
            currentColor = *RAINBOW_COLORS;
        }
        else if (i < 200)
        {
            // currentColor = RAINBOW_COLORS[1];
            currentColor = *(RAINBOW_COLORS + 1);
        }
        else if (i < 300)
        {
            // currentColor = RAINBOW_COLORS[2];
            currentColor = *(RAINBOW_COLORS + 2);
        }
        else if (i < 400)
        {
            // currentColor = RAINBOW_COLORS[3];
            currentColor = *(RAINBOW_COLORS + 3);
        }
        else if (i < 500)
        {
            // currentColor = RAINBOW_COLORS[4];
            currentColor = *(RAINBOW_COLORS + 4);
        }
        else if (i < 600)
        {
            // currentColor = RAINBOW_COLORS[5];
            currentColor = *(RAINBOW_COLORS + 5);
        }
        else if (i < 700)
        {
            // currentColor = RAINBOW_COLORS[6];
            currentColor = *(RAINBOW_COLORS + 6);
        }

        // uint8_t r = (currentColor & 0xFF0000) >> 16;
        unsigned int r = (currentColor & 0xFF0000) >> 16;

        // 获取当前颜色的 G 分量
        // uint8_t g = (currentColor & 0x00FF00) >> 8;
        unsigned int g = (currentColor & RGB24_MASK_GREEN) >> 8;

        // 获取当前颜色的 B 分量
        // uint8_t b = (currentColor & 0x0000FF);
        unsigned int b = (currentColor & RGB24_MASK_BLUE);
        // std::cout << "main:: currentColor:" << currentColor << ",(" << r << "," << g << "," << b << ")" << std::endl;

        for (int j = 0; j < width; j++)
        {
            RGBPixel rgbPixel;
            rgbPixel.red = r;
            rgbPixel.green = g;
            rgbPixel.bulue = b;
            bitmap->bmpSetPixel(i, j, rgbPixel); // 设置每一个像素的颜色信息
        }
    }

    // 打印图片像素信息
    bitmap->displayPixels();

    // 3. 保存bmp图片
    bitmap->save(rainbowFilePath);
    // bitmap->save2(rainbowFilePath2, 600, 600);

    delete bitmap; // 释放内存
    return 0;
}