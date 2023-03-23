#include "Bitmap.h"
#include "Rainbow.h"

int main(int arg, char *argv[])
{
    const char *TAG = "SampleRainbow::";
    std::cout << TAG << __FUNCTION__ << "(), Line " << __LINE__ << ",生成BMP格式的彩虹图片" << std::endl;
    std::cout << TAG << __FUNCTION__ << "(), Line " << __LINE__ << ",arg:" << arg << std::endl;
    if (arg < 3)
    {
        std::cout << TAG << __FUNCTION__ << "(), Line " << __LINE__ << ",使用: " << argv[0] << " 宽 高" << std::endl;
        std::cout << TAG << __FUNCTION__ << "(), Line " << __LINE__ << ",使用: " << argv[0] << " 711 711" << std::endl;
        return 1;
    }
    // uint32_t width = 711;            // 图片宽
    // uint32_t height = 711;           // 图片高
    uint32_t width = atof(argv[1]);  // 宽
    uint32_t height = atof(argv[2]); // 高

    // const char *rainbowFilePath = "./resource/rainbow-700x700.bmp";   // 要保存的彩虹文件路径
    // const char *rainbowFilePath2 = "./resource/rainbow2-700x700.bmp"; // 要保存的彩虹文件路径

    std::string rainbowFile = "./resource/rainbow_" + std::to_string(width) + "x" + std::to_string(height) + ".bmp";
    const char *rainbowFilePath = rainbowFile.c_str(); // string 转化为字符串
    std::cout << TAG << __FUNCTION__ << ",Line " << __LINE__ << ",rainbowFilePath:" << rainbowFilePath << std::endl;

    IBitmap *bitmap = new Bitmap();                       // 创建BMP对象,动态申请内存
    bool isCreate = bitmap->bmpCreate(width, height, 24); // 初始化BMP图片信息
    if (!isCreate)
    {
        return -1;
    };

    // 2. 向文件中写入颜色数据
    double perHeight = height * 1.0 / 7.0;
    // double perHeight = 100;
    std::cout << TAG << __FUNCTION__ << ",Line " << __LINE__ << ",perHeight:" << perHeight << std::endl;
    unsigned int currentColor = RAINBOW_COLORS[0]; // 当前颜色，默认是红
    for (int i = 0; i < height; i++)
    {
        // unsigned int currentColor = RAINBOW_COLORS[0]; // 当前颜色，默认是红
        if (i < 1 * perHeight)
        {
            // currentColor = RAINBOW_COLORS[0];
            currentColor = *RAINBOW_COLORS;
        }
        else if (i < 2 * perHeight)
        {
            // currentColor = RAINBOW_COLORS[1];
            currentColor = *(RAINBOW_COLORS + 1);
        }
        else if (i < 3 * perHeight)
        {
            // currentColor = RAINBOW_COLORS[2];
            currentColor = *(RAINBOW_COLORS + 2);
        }
        else if (i < 4 * perHeight)
        {
            // currentColor = RAINBOW_COLORS[3];
            currentColor = *(RAINBOW_COLORS + 3);
        }
        else if (i < 5 * perHeight)
        {
            // currentColor = RAINBOW_COLORS[4];
            currentColor = *(RAINBOW_COLORS + 4);
        }
        else if (i < 6 * perHeight)
        {
            // currentColor = RAINBOW_COLORS[5];
            currentColor = *(RAINBOW_COLORS + 5);
        }
        else if (i < 7 * perHeight)
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
    // bitmap->displayPixels();

    // 3. 保存bmp图片
    bitmap->save(rainbowFilePath);
    // bitmap->save2(rainbowFilePath2, 600, 600);

    delete bitmap; // 释放内存
    return 0;
}