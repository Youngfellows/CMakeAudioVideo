#ifndef _IRGB24_PIXEL_H_
#define _IRGB24_PIXEL_H_

#include "../bitmap/RGBPixel.h"

class IRGB24Pixel
{

public:
    ~IRGB24Pixel() = default;

    /**
     *
     * @brief 纯虚函数,抽象接口: 生成图片的rgb24格式像素数据
     *
     * @param width 宽
     * @param height 高
     */
    virtual bool rgb24Create(uint32_t width, uint32_t height) = 0;

    /**
     * @brief  纯虚函数,抽象接口: 生成图片的rgb24格式像素数据
     *
     * @param rgb24FilePath RGB24图片路径
     * @param width 宽
     * @param height 高
     * @return true
     * @return false
     */
    virtual bool rgb24Create(const char *rgb24FilePath, uint32_t width, uint32_t height) = 0;

    /**
     * @brief 设置RGB24图片每个像素的RGB颜色信息
     *
     * @param color 当前颜色值
     * @param x x位置
     * @param y y位置
     */
    virtual void setRGB24Pixel(uint32_t color, uint32_t x, uint32_t y) = 0;

    /**
     * @brief 打印图片像素信息
     *
     */
    virtual void displayPixels() = 0;

    /**
     * @brief 获取rgb24内存数据
     *
     * @return uint8_t*
     */
    virtual uint8_t *rgb24Data() = 0;

    /**
     * @brief 获取rgb24像素数据字节大小
     *
     * @return uint32_t
     */
    virtual uint32_t rgb24DataSize() = 0;

    /**
     * @brief 保存rgb24像素数据到文件
     *
     * @param path 保存的文件路径
     */
    virtual void saveRgb24(const char *rgb24FilePath) = 0;

    /**
     * @brief 释放资源
     *
     */
    virtual void destory() = 0;
};

#endif