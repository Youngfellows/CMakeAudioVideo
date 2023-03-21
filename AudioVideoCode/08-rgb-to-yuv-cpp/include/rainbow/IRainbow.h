#ifndef _IRAINBOW_H_
#define _IRAINBOW_H_

#include "../pixel/Bitmap.h"
#include "../pixel/RGB24.h"

/**
 * @brief 抽象类: 抽象彩虹图片生成器
 *
 */
class IRainbow
{
protected:
    IBitmapPixel *bitmap; // BMP位图对象
    IRGB24Pixel *rgb24;   // rgb24位图图像

public:
    ~IRainbow() = default;

    /**
     * @brief 创建BMP格式彩虹图片
     *
     * @param width 宽
     * @param height 高
     */
    virtual bool createBitmap(uint32_t width, uint32_t height) = 0;

    /**
     * @brief 创建RGB24格式彩虹图片
     *
     * @param width 宽
     * @param height 高
     */
    virtual bool createRGB24(uint32_t width, uint32_t height) = 0;

    /**
     * @brief 保存BMP位图到文件
     *
     * @param bmpFilePath
     */
    virtual void saveBitmap(const char *bmpFilePath) = 0;

    /**
     * @brief 保存RGB24位图到文件
     *
     * @param rgb24FilePath
     */
    virtual void saveRGB24(const char *rgb24FilePath) = 0;

    /**
     * @brief 释放资源
     *
     */
    virtual void destory() = 0;
};
#endif