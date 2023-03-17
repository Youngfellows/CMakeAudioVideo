#include "../../include/rainbow/Rainbow.h"

Rainbow::Rainbow()
{
    std::cout << "Rainbow::" << __FUNCTION__ << "():: " << __LINE__ << std::endl;
}

Rainbow::~Rainbow()
{
    std::cout << "Rainbow::" << __FUNCTION__ << "():: " << __LINE__ << std::endl;
}

/**
 * @brief 生成彩虹图片的rgb24格式数据
 *
 * @param pixels 图片像素信息内存空间
 * @param width 宽
 * @param height 高
 */
void Rainbow::rgb24Data(RGBPixel ***pixels, uint32_t width, uint32_t height)
{
    std::cout << "Rainbow::" << __FUNCTION__ << "():: " << __LINE__ << std::endl;
    std::cout << "Rainbow::" << __FUNCTION__ << "():: " << __LINE__ << pixels << std::endl;
    for (int i = 0; i < width; i++)
    {
        uint32_t currentColor = RAINBOW_COLORS[0]; // 获取改行的rgb彩虹颜色
        if (i < 100)
        {
            currentColor = RAINBOW_COLORS[0]; // 赤色
        }
        else if (i < 200)
        {
            currentColor = RAINBOW_COLORS[1]; // 橙色
        }
        else if (i < 300)
        {
            currentColor = RAINBOW_COLORS[2]; // 红色
        }
        else if (i < 400)
        {
            currentColor = RAINBOW_COLORS[3]; // 绿色
        }
        else if (i < 500)
        {
            currentColor = RAINBOW_COLORS[4]; // 青色
        }
        else if (i < 600)
        {
            currentColor = RAINBOW_COLORS[5]; // 蓝色
        }
        else if (i < 700)
        {
            currentColor = RAINBOW_COLORS[6]; // 紫色
        }

        // uint8_t red = (currentColor & 0xFF0000) >> 16;
        //  unsigned int red = (currentColor & 0xFF0000) >> 16;
        uint32_t red = (currentColor & 0xFF0000) >> 16;

        // 获取当前颜色的 G 分量
        // uint8_t green = (currentColor & 0x00FF00) >> 8;
        // unsigned int green = (currentColor & RGB24_MASK_GREEN) >> 8;
        uint32_t green = (currentColor & RGB24_MASK_GREEN) >> 8;

        // 获取当前颜色的 B 分量
        // uint8_t bulue = (currentColor & 0x0000FF);
        // unsigned int bulue = (currentColor & RGB24_MASK_BLUE);
        uint32_t bulue = (currentColor & RGB24_MASK_BLUE);
        std::cout << "Rainbow::" << __FUNCTION__ << "():: " << __LINE__ << " " << i << ",(" << red << "," << green << "," << bulue << "),red sizeof:" << sizeof(red) << std::endl;

        for (int j = 0; j < width; j++)
        {
            RGBPixel rgbPixel;
            rgbPixel.red = red;     // 右移16位之后,有效数据其实只要1个字节8位,可以赋值
            rgbPixel.green = green; // 右移8位之后,有效数据其实只要1个字节8位,可以赋值
            rgbPixel.bulue = bulue; // 右移0位之后,有效数据其实只要1个字节8位,可以赋值
            // bitmap->bmpSetPixel(i, j, rgbPixel); // 设置每一个像素的颜色信息
            std::cout << "Rainbow::" << __FUNCTION__ << "():: " << __LINE__ << " " << j << ",(" << red << "," << rgbPixel.green << "," << rgbPixel.bulue << "),red sizeof:" << sizeof(rgbPixel.red) << std::endl;
        }
    }
}