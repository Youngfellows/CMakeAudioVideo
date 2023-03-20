#ifndef _BITMAP_H_
#define _BITMAP_H_

#include <iostream>
#include <cstring>
#include <bitset>
#include "../pixel/IBitmapPixel.h"
#include "./RainbowColors.h"
#include "../bitmap/BitmapFileHeader.h"
#include "../bitmap/BitmapInfoHeader.h"

/**
 * @brief 实现类: 彩虹图片像素数据的实现类
 *
 */
class Bitmap : public IBitmapPixel
{
private:
    uint8_t *bmpDataBytes;          // 虹图片的bmp数据
    BitmapFileHeader bmpFHeader;    // 位图文件头
    BitmapInfoHeader bmpInfoHeader; // 位图信息头
    uint32_t width;                 // 图片宽
    uint32_t height;                // 图片高
    uint32_t bmpHeadLength;         // BMP图片都文件大小54个字节
    uint32_t bmpSize;               // 整个BMP图片的大小

public:
    Bitmap();
    ~Bitmap();
    virtual uint8_t *bmpCreate(uint32_t width, uint32_t height) override;                        // 生成彩虹图片的bmp数据
    virtual void setBmpPixel(uint8_t *bmpData, uint32_t color, uint32_t x, uint32_t y) override; // 设置指定位置的rgb像素值
    virtual uint32_t getBmpSize() override;                                                      // 获取BMP文件大小
    virtual uint16_t shortFromBytes(uint8_t *bytes, uint32_t pos) override;                      // 获取内存中指定位置连续2个字节表示的整数
    virtual uint32_t intFromBytes(uint8_t *bytes, uint32_t pos) override;                        // 获取内存中指定位置连续4个字节表示的整数
    virtual void setShortToBytes(uint16_t number, uint8_t *bytes, uint32_t pos) override;        // 设置指定位置连续2个字节表示的整数到内存中
    virtual void setIntToBytes(uint32_t number, uint8_t *bytes, uint32_t pos) override;          // 设置指定位置连续4个字节表示的整数到内存中
    virtual bool saveBitmap(const char *path, uint8_t *data, uint32_t size) override;            // 保存bmp像素数据到文件
    virtual void destory() override;                                                             // 释放内存
    virtual uint8_t *bmpData() override;                                                         // 获取内存中的BMP位图数据

private:
    void createBmpPixelData(uint8_t *bitmapData);      // 生成bmp彩虹图片的像素数据
    void createBmpFileHeaderData(uint8_t *bitmapData); // 生成mp彩虹图片的位图文件头数据
    void createBmpInfoHeaderData(uint8_t *bitmapData); // 生成mp彩虹图片的位图信息头数据
};

#endif