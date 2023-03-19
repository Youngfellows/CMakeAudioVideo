#ifndef _BITMAP_INFO_HEADER_H_
#define _BITMAP_INFO_HEADER_H_

#include <iostream>

/**
 * @brief 位图信息头
 *
 */
class BitmapInfoHeader
{
public:
    BitmapInfoHeader() = default;
    ~BitmapInfoHeader() = default;

public:
    uint32_t biSize;          // 位图信息头的大小，为40,0x28(40)
    uint32_t biWidth;         // 位图的宽度，单位是像素
    uint32_t biHeight;        // 位图的高度，单位是像素
    uint16_t biPlanes;        // 固定值1
    uint16_t biBitCount;      // 每个像素的位数 1-黑白图，4-16色，8-256色，24-真彩色，32-带 alpha 通道,0x18(24)
    uint32_t biCompression;   // 压缩方式，BI_RGB(0)为不压缩,0
    uint32_t biSizeImage;     // 位图全部像素占用的字节数，BI_RGB时可设为0
    uint32_t biXPelsPerMeter; // 水平分辨率(像素/米),0
    uint32_t biYPelsPerMeter; // 垂直分辨率(像素/米),0
    uint32_t biClrUsed;       // 位图使用的颜色数 如果为0，则颜色数为2的biBitCount次方,0
    uint32_t biClrImportant;  // 重要的颜色数，0代表所有颜色都重要,0
};

#endif