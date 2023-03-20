#include "../../include/rainbow/Rainbow.h"

Rainbow::Rainbow()
{
    std::cout << "Rainbow::" << __FUNCTION__ << "():: " << __LINE__ << std::endl;
    this->bitmap = new Bitmap(); // 动态申请内存
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
    this->width = width;
    this->height = height;
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
    return true;
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
        uint8_t *rainbowBmpData = bitmap->bmpCreate(width, height); // 获取内存中的bmp位图数据
        createBmpPixels(rainbowBmpData);                            // 设置彩虹图像BMP位图像素信息
        uint32_t bmpSize = bitmap->getBmpSize();                    // 获取bmp文件大小
        bitmap->saveBitmap(bmpFilePath, rainbowBmpData, bmpSize);   // 保存bmp数据到文件
        destory();                                                  // 释放资源
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
}

/**
 * @brief 释放资源
 *
 */
void Rainbow::destory()
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
    for (int i = 0; i < height; i++)
    {
        uint32_t currentColor = RAINBOW_COLORS[0]; // 获取该行的rgb彩虹颜色
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
        for (int j = 0; j < width; j++)
        {
            bitmap->setBmpPixel(bmpData, currentColor, j, i); // 设置指定位置的rgb像素值
        }
    }
}