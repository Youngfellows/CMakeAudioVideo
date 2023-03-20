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
     * @brief 获取rgb24内存数据
     *
     * @return uint8_t*
     */
    virtual uint8_t *rgb24Data() = 0;

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