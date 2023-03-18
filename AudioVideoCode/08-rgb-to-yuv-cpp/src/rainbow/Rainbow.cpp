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
 * @brief 生成彩虹图片的bmp格式像素数据
 *
 * @param size 数据大小
 * @param width 宽
 * @param height 高
 * @return uint8_t* 返回彩虹图片的bmp格式像素数据
 */
uint8_t *Rainbow::bmpData(uint32_t *size, uint32_t width, uint32_t height)
{
    std::cout << "Rainbow::" << __FUNCTION__ << "():: " << __LINE__ << ",width:" << width << ",height:" << height << std::endl;
    *size = width * height;
    bmpDataBytes = (uint8_t *)malloc(sizeof(uint8_t) * (abs(width) * abs(height))); // 动态申请内存
    std::cout << "Rainbow::" << __FUNCTION__ << "():: " << __LINE__ << ",bmpDataBytes sizeof:" << sizeof(bmpDataBytes) << ",bmpDataBytes len:" << (width * height) << ",bmpDataBytes:" << bmpDataBytes << std::endl;
    if (bmpDataBytes == NULL)
    {
        std::cout << "Rainbow::" << __FUNCTION__ << "():: " << __LINE__ << ",bmpDataBytes is null" << std::endl;
    }
    else
    {
        std::cout << "Rainbow::" << __FUNCTION__ << "():: " << __LINE__ << ",bmpDataBytes address:" << &bmpDataBytes << std::endl;
        std::cout << "Rainbow::" << __FUNCTION__ << "():: " << __LINE__ << ",bmpDataBytes address:" << bmpDataBytes + 1 << std::endl;
        printf("Rainbow::%s()::%d,%p,%p,%p\n", __FUNCTION__, __LINE__, bmpDataBytes, bmpDataBytes + 1, bmpDataBytes + 2);
    }
    bmpDataBytes[0] = 'a';
    bmpDataBytes[1] = 'b';
    std::cout << "Rainbow::" << __FUNCTION__ << "():: " << __LINE__ << ",bmpDataBytes:" << bmpDataBytes << std::endl;
    std::cout << "Rainbow::" << __FUNCTION__ << "():: " << __LINE__ << ",bmpDataBytes:" << bmpDataBytes[1] << std::endl;
    std::cout << "Rainbow::" << __FUNCTION__ << "():: " << __LINE__ << ",bmpDataBytes address:" << bmpDataBytes + 1 << std::endl;
    const char *bmpData = "欢迎来到中国深圳,这里是美丽的南山区,SHENZHEN BAI SHI ZHOU";
    std::cout << "Rainbow::" << __FUNCTION__ << "():: " << __LINE__ << ",bmpData size:" << strlen(bmpData) << std::endl;
    memcpy(bmpDataBytes, bmpData, strlen(bmpData)); // 向内存中写入数据
    std::cout << "Rainbow::" << __FUNCTION__ << "():: " << __LINE__ << ",bmpDataBytes:" << bmpDataBytes << std::endl;
    createBmpPixelData(bmpDataBytes, size, width, height); // 生成bmp彩虹图片的像素数据
    return bmpDataBytes;
}

/**
 * @brief 生成mp彩虹图片的位图文件头数据
 *
 * @param bitmapData bmp图片数据内存
 * @param size bmp数据
 * @param width 宽
 * @param height 高
 */
void Rainbow::createBmpFileHeaderDate(uint8_t *bitmapData, uint32_t *size, uint32_t width, uint32_t height)
{
    std::cout << "Rainbow::" << __FUNCTION__ << "():: " << __LINE__ << ",width:" << width << ",height:" << height << std::endl;
    uint32_t headLength = 54; // 头文件的大小
    for (int i = 0; i < height; i++)
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
        // std::cout << "Rainbow::" << __FUNCTION__ << "():: XXXXXXXXX,i:" << i << ",(" << red << "," << green << "," << bulue << "),red sizeof:" << sizeof(red) << std::endl;

        for (int j = 0; j < width; j++)
        {
            RGBPixel rgbPixel(red, green, bulue);
            //   rgbPixel.red = red;     // 右移16位之后,有效数据其实只要1个字节8位,可以赋值
            //   rgbPixel.green = green; // 右移8位之后,有效数据其实只要1个字节8位,可以赋值
            //   rgbPixel.bulue = bulue; // 右移0位之后,有效数据其实只要1个字节8位,可以赋值
            // std::cout << "Rainbow::" << __FUNCTION__ << "():: " << __LINE__ << "(" << i << "," << j << ") 1,ele(" << rgbPixel.red << "," << rgbPixel.green << "," << rgbPixel.bulue << "),red sizeof:" << sizeof(rgbPixel.red) << std::endl;

            uint32_t currentIndex = 3 * (i * height + j);
            uint8_t r = (uint8_t)(rgbPixel.red);
            uint8_t g = (uint8_t)(rgbPixel.green);
            uint8_t b = (uint8_t)(rgbPixel.bulue);
            // std::cout << "r char is:" << r << std::endl;
            // std::cout << "g char is:" << g << std::endl;
            // std::cout << "b char is:" << b << std::endl;

            // memcpy(bitmapData + currentIndex, "987", sizeof(uint8_t));
            memcpy(headLength + bitmapData + currentIndex, &r, sizeof(uint8_t));
            memcpy(headLength + bitmapData + currentIndex + 1, &g, sizeof(uint8_t));
            memcpy(headLength + bitmapData + currentIndex + 2, &b, sizeof(uint8_t));
            // std::cout << "Rainbow::" << __FUNCTION__ << "():: " << __LINE__ << "(" << i << "," << j << ") 2,ele(" << bitmapData + currentIndex + 2 << "," << bitmapData + currentIndex + 1 << "," << bitmapData + currentIndex << "),red sizeof:" << sizeof(rgbPixel.red) << std::endl;
        }
    }
}

/**
 * @brief 生成mp彩虹图片的位图信息头数据
 *
 * @param bitmapData bmp图片数据内存
 * @param size bmp数据
 * @param width 宽
 * @param height 高
 */
void Rainbow::createBmpInfoHeaderDate(uint8_t *bitmapData, uint32_t *size, uint32_t width, uint32_t height)
{
    std::cout << "Rainbow::" << __FUNCTION__ << "():: " << __LINE__ << ",width:" << width << ",height:" << height << std::endl;
}

/**
 * @brief 生成彩虹图片的bmp数据
 *
 * @param bitmapData bmp图片数据内存
 * @param size bmp数据
 * @param width 宽
 * @param height 高
 */
void Rainbow::createBmpPixelData(uint8_t *bitmapData, uint32_t *size, uint32_t width, uint32_t height)
{
    std::cout << "Rainbow::" << __FUNCTION__ << "():: " << __LINE__ << ",width:" << width << ",height:" << height << std::endl;
    createBmpFileHeaderDate(bitmapData, size, width, height); // 生成mp彩虹图片的位图文件头数据
    createBmpInfoHeaderDate(bitmapData, size, width, height); // 生成mp彩虹图片的位图信息头数据
}

/**
 * @brief 生成彩虹图片的rgb24格式数据
 *
 * @param pixels 图片像素信息内存空间
 * @param width 宽
 * @param height 高
 */
void Rainbow::rgb24Data(RGBPixel **pixels, uint32_t width, uint32_t height)
{
    std::cout << "Rainbow::" << __FUNCTION__ << "():: " << __LINE__ << std::endl;
    std::cout << "Rainbow::" << __FUNCTION__ << "():: " << __LINE__ << pixels << std::endl;
    for (int i = 0; i < height; i++)
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
        std::cout << "Rainbow::" << __FUNCTION__ << "():: ssssssss,i:" << i << ",(" << red << "," << green << "," << bulue << "),red sizeof:" << sizeof(red) << "," << (pixels + i) << std::endl;

        for (int j = 0; j < width; j++)
        {
            RGBPixel rgbPixel(red, green, bulue);
            // rgbPixel.red = red;     // 右移16位之后,有效数据其实只要1个字节8位,可以赋值
            // rgbPixel.green = green; // 右移8位之后,有效数据其实只要1个字节8位,可以赋值
            // rgbPixel.bulue = bulue; // 右移0位之后,有效数据其实只要1个字节8位,可以赋值

            std::cout << "Rainbow::" << __FUNCTION__ << "():: " << __LINE__ << "(" << i << "," << j << ") ele(" << red << "," << rgbPixel.green << "," << rgbPixel.bulue << "),red sizeof:" << sizeof(rgbPixel.red) << std::endl;
            // pixels[i][j] = rgbPixel;
            // pixels[i][j].red = 66;
            // pixels[i][j].green = 255;
            // pixels[i][j].bulue = 77;
            //(*(pixels + i) + j)->red = rgbPixel.red; // 为元素赋值
            *(*(pixels + i) + j) = rgbPixel; // 为每一个像素赋值rgb颜色值

            RGBPixel ele = *(*(pixels + i) + j);
            std::cout << "Rainbow::" << __FUNCTION__ << "():: " << __LINE__ << "(" << i << "," << j << ") ele(" << ele.red << "," << ele.green << "," << ele.bulue << "),red sizeof:" << sizeof(ele.red) << std::endl;
        }
    }
}