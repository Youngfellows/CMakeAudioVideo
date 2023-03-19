#ifndef _IPIXEL_H
#define _IPIXEL_H

#include "../bitmap/RGBPixel.h"

/**
 * @brief 抽象类: 生成图片像素信息类
 *
 */
class IPixel
{
public:
    ~IPixel() = default;

    /**
     * @brief
    /**
     * @brief 纯虚函数,抽象接口: 生成图片的bmp格式像素数据
     *
     * @param size
     * @param width
     * @param height
     * @return uint8_t*
     */
    virtual uint8_t *bmpData(uint32_t *size, uint32_t width, uint32_t height) = 0;

    /**
     * @brief 纯虚函数,抽象接口: 生成图片的rgb24格式像素数据
     *
     * @param pixels 图片像素的地址
     * @param width
     * @param height
     */
    virtual void rgb24Data(RGBPixel **pixels, uint32_t width, uint32_t height) = 0;
};

#endif