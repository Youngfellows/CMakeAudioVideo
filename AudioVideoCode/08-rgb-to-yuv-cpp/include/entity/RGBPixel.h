#ifndef _RGB_PIXEL_H_
#define _RGB_PIXEL_H_

#include <iostream>

/**
 * @brief 每一个像素的颜色信息
 *
 */
class RGBPixel
{
public:
    uint32_t red;
    uint32_t green;
    uint32_t bulue;

public:
    RGBPixel() = default;
    RGBPixel(uint32_t r, uint32_t g, uint32_t b);
    ~RGBPixel() = default;
};

#endif