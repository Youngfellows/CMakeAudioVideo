#ifndef _RAINBOW_COLORS_H_
#define _RAINBOW_COLORS_H_

#include <iostream>

/**
 * @brief  彩虹的七种颜色
 *
 */
const uint32_t RAINBOW_COLORS[] = {
    0XFF0000, // 红
    0XFFA500, // 橙
    0XFFFF00, // 黄
    0X00FF00, // 绿
    0X007FFF, // 青
    0X0000FF, // 蓝
    0X8B00FF  // 紫
};

const unsigned int RGB24_MASK_RED = 0XFF0000;
const unsigned int RGB24_MASK_GREEN = 0x00FF00;
const unsigned int RGB24_MASK_BLUE = 0x0000FF;

#endif