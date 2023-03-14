#ifndef RGB_PIXEL_H
#define RGB_PIXEL_H

#include <iostream>

/**
 * @brief 每个像素的三颜色结构体
 *
 */
typedef struct
{
    uint8_t bulue; // 红
    uint8_t green; // 绿
    uint8_t red;   // 蓝
    uint8_t alpha; // 透明度
} RGBPixel;

#endif