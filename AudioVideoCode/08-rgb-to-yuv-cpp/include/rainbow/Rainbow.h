#ifndef _RAINBOW_H_
#define _RAINBOW_H_

#include <iostream>
#include <cstring>
#include <bitset>
#include "../pixel/IPixel.h"
#include "./RainbowColors.h"

/**
 * @brief 实现类: 彩虹图片像素数据的实现类
 *
 */
class Rainbow : public IPixel
{
private:
    uint8_t *bmpDataBytes; // 虹图片的bmp数据
public:
    Rainbow();
    ~Rainbow();
    virtual void rgb24Data(RGBPixel **pixels, uint32_t width, uint32_t height) override; // 生成彩虹图片的rgb24数据
    virtual uint8_t *bmpData(uint32_t *size, uint32_t width, uint32_t height) override;  // 生成彩虹图片的bmp数据
private:
    void createBmpPixelData(uint8_t *bitmapData, uint32_t *size, uint32_t width, uint32_t height);        // 生成bmp彩虹图片的像素数据
    void createBmpFileHeaderData(uint8_t *bitmapData, uint32_t *size, uint32_t width, uint32_t height);   // 生成mp彩虹图片的位图文件头数据
    void createBmpInfoHeaderData(uint8_t *bitmapData, uint32_t *size, uint32_t width, uint32_t height);   // 生成mp彩虹图片的位图信息头数据
    void createRainbowBmpPixelData(uint8_t *bitmapData, uint32_t *size, uint32_t width, uint32_t height); // 生成bmp彩虹图片的像素数据
};
#endif