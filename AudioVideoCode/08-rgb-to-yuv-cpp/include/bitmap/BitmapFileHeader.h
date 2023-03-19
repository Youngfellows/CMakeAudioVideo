#ifndef _BITMAP_FILE_HEADER_H_
#define _BITMAP_FILE_HEADER_H_

#include <iostream>

/**
 * @brief BMP图片位图文件头
 *
 */
class BitmapFileHeader
{
public:
    BitmapFileHeader() = default;
    ~BitmapFileHeader() = default;

public:
    uint16_t bfType;      // 标识，就是“BM”
    uint32_t bfSize;      // 整个 BMP 文件的大小
    uint16_t bfReserved1; // 保留字,0
    uint16_t bfReserved2; // 保留字,0
    uint32_t bfOffBits;   // 偏移数，即位图文件头 位图信息头 调色板的大小,0x36(54)
};

#endif