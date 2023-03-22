#include "../../include/rainbow/Rainbow.h"

Rainbow::Rainbow()
{
    std::cout << "Rainbow::" << __FUNCTION__ << "():: " << __LINE__ << std::endl;
    this->bitmap = new Bitmap(); // 动态申请内存,创建BMP位图图像
    this->rgb24 = new RGB24();   // 动态申请内存,创建RGB24位图图像
}

Rainbow::~Rainbow()
{
    std::cout << "Rainbow::" << __FUNCTION__ << "():: " << __LINE__ << std::endl;
    destory();
}

/**
 * @brief 创建BMP格式彩虹图片
 *
 * @param width
 * @param height
 */
bool Rainbow::createBitmap(uint32_t width, uint32_t height)
{
    std::cout << "Rainbow::" << __FUNCTION__ << "():: " << __LINE__ << std::endl;
    this->width = abs(width);
    this->height = abs(height);
    uint32_t headLength = 54;                                   // 头文件的大小
    uint8_t *rainbowBmpData = bitmap->bmpCreate(width, height); // 获取bmp格式彩虹图片像素数据
    if (rainbowBmpData == NULL)
    {
        return false;
    }
    uint32_t bmpSize = bitmap->getBmpSize(); // 获取bmp文件大小
    std::cout << "Rainbow::" << __FUNCTION__ << "():: LINE:" << __LINE__ << ",rainbowBmpData len:" << bmpSize << ",rainbowBmpData:" << rainbowBmpData << std::endl;
    std::cout << "Rainbow::" << __FUNCTION__ << "():: LINE:" << __LINE__ << ",bfType:" << bitmap->shortFromBytes(rainbowBmpData, 0) << std::endl;
    std::cout << "Rainbow::" << __FUNCTION__ << "():: LINE:" << __LINE__ << ",bfSize:" << bitmap->intFromBytes(rainbowBmpData, 2) << std::endl;
    uint32_t b = (uint32_t)rainbowBmpData[headLength];
    uint32_t g = (uint32_t)rainbowBmpData[headLength + 1];
    uint32_t r = (uint32_t)rainbowBmpData[headLength + 2];
    std::cout << "Rainbow::" << __FUNCTION__ << "():: LINE:" << __LINE__ << ",rainbowBmpData len:" << bmpSize << ",(" << r << "," << g << "," << b << ")" << std::endl;
    return true;
}

/**
 * @brief 创建RGB24格式彩虹图片
 *
 * @param width
 * @param height
 */
bool Rainbow::createRGB24(uint32_t width, uint32_t height)
{
    std::cout << "Rainbow::" << __FUNCTION__ << "():: " << __LINE__ << std::endl;
    this->width = abs(width);
    this->height = abs(height);
    bool isCreate = rgb24->rgb24Create(width, height); // 创建rgb24文件
    return isCreate;
}

/**
 * @brief 保存BMP位图到文件
 *
 * @param bmpFilePath
 */
void Rainbow::saveBitmap(const char *bmpFilePath)
{
    std::cout << "Rainbow::" << __FUNCTION__ << "():: " << __LINE__ << std::endl;
    if (bitmap != NULL)
    {
        // uint8_t *rainbowBmpData = bitmap->bmpCreate(width, height); // 获取内存中的bmp位图数据
        uint8_t *rainbowBmpData = bitmap->bmpData();              // 获取内存中的bmp位图数据
        createBmpPixels(rainbowBmpData);                          // 设置彩虹图像BMP位图像素信息
        uint32_t bmpSize = bitmap->getBmpSize();                  // 获取bmp文件大小
        bitmap->saveBitmap(bmpFilePath, rainbowBmpData, bmpSize); // 保存bmp数据到文件
        // destory();                                                   // 释放资源
    }
}

/**
 * @brief 保存RGB24位图到文件
 *
 * @param rgb24FilePath
 */
void Rainbow::saveRGB24(const char *rgb24FilePath)
{
    std::cout << "Rainbow::" << __FUNCTION__ << "():: " << __LINE__ << std::endl;
    if (rgb24 != NULL)
    {
        // uint8_t *rgb24Data = rgb24->rgb24Data();
        createRGB24Pixels();             // 设置rgb24彩虹数据
        rgb24->saveRgb24(rgb24FilePath); // 保存rgb24文件
        // destory(); // 释放资源
    }
}

/**
 * @brief 释放资源
 *
 */
void Rainbow::destory()
{
    std::cout << "Rainbow::" << __FUNCTION__ << "():: " << __LINE__ << std::endl;
    bmpDestory();
    rgb24Destory();
}

/**
 * @brief 设置rgb24位图像素信息
 *
 */
void Rainbow::createRGB24Pixels()
{
    double perHeight = height * 1.0 / 7.0;
    std::cout << "Rainbow::" << __FUNCTION__ << "():: " << __LINE__ << ",perHeight:" << perHeight << std::endl;
    for (int i = 0; i < height; i++)
    {
        uint32_t currentColor = RAINBOW_COLORS[0]; // 获取改行的rgb彩虹颜色
        if (i < 1 * perHeight)
        {
            currentColor = RAINBOW_COLORS[0]; // 赤色
        }
        else if (i < 2 * perHeight)
        {
            currentColor = RAINBOW_COLORS[1]; // 橙色
        }
        else if (i < 3 * perHeight)
        {
            currentColor = RAINBOW_COLORS[2]; // 红色
        }
        else if (i < 4 * perHeight)
        {
            currentColor = RAINBOW_COLORS[3]; // 绿色
        }
        else if (i < 5 * perHeight)
        {
            currentColor = RAINBOW_COLORS[4]; // 青色
        }
        else if (i < 6 * perHeight)
        {
            currentColor = RAINBOW_COLORS[5]; // 蓝色
        }
        else if (i < 7 * perHeight)
        {
            currentColor = RAINBOW_COLORS[6]; // 紫色
        }

        for (int j = 0; j < width; j++)
        {
            rgb24->setRGB24Pixel(currentColor, i, j); // 设置RGB24图片每个像素的RGB颜色信息
        }
    }
}

/**
 * @brief 释放rgb24位图资源
 *
 */
void Rainbow::rgb24Destory()
{
    std::cout << "Rainbow::" << __FUNCTION__ << "():: " << __LINE__ << std::endl;
    if (rgb24 != NULL)
    {
        rgb24->destory();
    }
    rgb24 = NULL;
}

/**
 * @brief 释放BMP位图资源
 *
 */
void Rainbow::bmpDestory()
{
    std::cout << "Rainbow::" << __FUNCTION__ << "():: " << __LINE__ << std::endl;
    if (bitmap != NULL)
    {
        bitmap->destory(); // 释放内存
    }
    bitmap = NULL;
}

/**
 * @brief 设置彩虹图像BMP位图像素信息
 *
 * @param bitmapData bmp位图内存空间
 */
void Rainbow::createBmpPixels(uint8_t *bitmapData)
{
    std::cout << "Rainbow::" << __FUNCTION__ << "():: " << __LINE__ << ",width:" << width << ",height:" << height << std::endl;
    if (bitmap == NULL)
    {
        return;
    }
    uint8_t *bmpData = bitmapData; // bmp内存
    double perHeight = height * 1.0 / 7.0;
    std::cout << "Rainbow::" << __FUNCTION__ << "():: " << __LINE__ << ",perHeight:" << perHeight << std::endl;
    for (int i = 0; i < height; i++)
    {
        uint32_t currentColor = RAINBOW_COLORS[0]; // 获取该行的rgb彩虹颜色
        if (i < 1 * perHeight)
        {
            currentColor = RAINBOW_COLORS[0]; // 赤色
        }
        else if (i < 2 * perHeight)
        {
            currentColor = RAINBOW_COLORS[1]; // 橙色
        }
        else if (i < 3 * perHeight)
        {
            currentColor = RAINBOW_COLORS[2]; // 红色
        }
        else if (i < 4 * perHeight)
        {
            currentColor = RAINBOW_COLORS[3]; // 绿色
        }
        else if (i < 5 * perHeight)
        {
            currentColor = RAINBOW_COLORS[4]; // 青色
        }
        else if (i < 6 * perHeight)
        {
            currentColor = RAINBOW_COLORS[5]; // 蓝色
        }
        else if (i < 7 * perHeight)
        {
            currentColor = RAINBOW_COLORS[6]; // 紫色
        }
        for (int j = 0; j < width; j++)
        {
            bitmap->setBmpPixel(bmpData, currentColor, j, i); // 设置指定位置的rgb像素值
        }
    }
}