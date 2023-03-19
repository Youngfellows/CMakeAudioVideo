#ifndef _RGB_PIXEL_H_
#define _RGB_PIXEL_H_

#include <iostream>

/**
 * @brief 每一个像素的RGB颜色信息
 *
 */
class RGBPixel
{
public:
    uint32_t red;   // 红色分量
    uint32_t green; // 绿色分量
    uint32_t bulue; // 蓝色分量

public:
    RGBPixel() = default;
    RGBPixel(uint32_t r, uint32_t g, uint32_t b);
    ~RGBPixel() = default;
};

#endif