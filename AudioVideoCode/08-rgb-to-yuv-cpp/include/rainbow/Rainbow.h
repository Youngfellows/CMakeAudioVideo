#ifndef _RAINBOW_H_
#define _RAINBOW_H_

#include <iostream>
#include <cstring>
#include <bitset>
#include "../pixel/IPixel.h"
#include "./RainbowColors.h"
#include "../bitmap/BitmapFileHeader.h"
#include "../bitmap/BitmapInfoHeader.h"

/**
 * @brief 实现类: 彩虹图片像素数据的实现类
 *
 */
class Rainbow : public IPixel
{
private:
    uint8_t *bmpDataBytes;          // 虹图片的bmp数据
    BitmapFileHeader bmpFHeader;    // 位图文件头
    BitmapInfoHeader bmpInfoHeader; // 位图信息头

public:
    Rainbow();
    ~Rainbow();
    virtual void rgb24Data(RGBPixel **pixels, uint32_t width, uint32_t height) override;  // 生成彩虹图片的rgb24数据
    virtual uint8_t *bmpData(uint32_t *size, uint32_t width, uint32_t height) override;   // 生成彩虹图片的bmp数据
    virtual uint16_t shortFromBytes(uint8_t *bytes, uint32_t pos) override;               // 获取内存中指定位置连续2个字节表示的整数
    virtual uint32_t intFromBytes(uint8_t *bytes, uint32_t pos) override;                 // 获取内存中指定位置连续4个字节表示的整数
    virtual void setShortToBytes(uint16_t number, uint8_t *bytes, uint32_t pos) override; // 设置指定位置连续2个字节表示的整数到内存中
    virtual void setIntToBytes(uint32_t number, uint8_t *bytes, uint32_t pos) override;   // 设置指定位置连续4个字节表示的整数到内存中
    virtual bool saveRgb24(const char *path, uint8_t *data, uint32_t size) override;         // 保存rgb24像素数据到文件
    virtual bool saveBitmap(const char *path, uint8_t *data, uint32_t size) override;        // 保存bmp像素数据到文件
    virtual void destory() override;                                                      // 释放内存
private:
    void createBmpPixelData(uint8_t *bitmapData, uint32_t *size, uint32_t width, uint32_t height);        // 生成bmp彩虹图片的像素数据
    void createBmpFileHeaderData(uint8_t *bitmapData, uint32_t *size, uint32_t width, uint32_t height);   // 生成mp彩虹图片的位图文件头数据
    void createBmpInfoHeaderData(uint8_t *bitmapData, uint32_t *size, uint32_t width, uint32_t height);   // 生成mp彩虹图片的位图信息头数据
    void createRainbowBmpPixelData(uint8_t *bitmapData, uint32_t *size, uint32_t width, uint32_t height); // 生成bmp彩虹图片的像素数据
};

#endif