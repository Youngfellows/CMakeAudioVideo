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
    uint8_t red;
    uint8_t green;
    uint8_t bulue;

public:
    RGBPixel() = default;
    RGBPixel(uint8_t r, uint8_t g, uint8_t b);
    ~RGBPixel() = default;
};

#endif