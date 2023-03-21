#ifndef _RGB24_H_
#define _RGB24_H_

#include <iostream>
#include <cstring>
#include <sys/stat.h>
#include "./IRGB24Pixel.h"
#include "../bitmap/RGBPixel.h"
#include "../rainbow/RainbowColors.h"

/**
 * @brief RGB24格式图图片像素生成器
 *
 */
class RGB24 : public IRGB24Pixel
{
private:
    RGBPixel **pixels;       // rgb24像素信息
    uint8_t *rgb24DataBytes; // rgb24内存数据
    uint32_t width;          // 宽
    uint32_t height;         // 高

public:
    RGB24();
    ~RGB24();
    virtual bool rgb24Create(uint32_t width, uint32_t height) override;                            // 初始化rgb24数据
    virtual bool rgb24Create(const char *rgb24FilePath, uint32_t width, uint32_t height) override; // 初始化rgb24数据
    virtual uint8_t *rgb24Data() override;                                                         // 获取rgb24内存数据
    virtual uint32_t rgb24DataSize() override;                                                     // 获取rgb24像素数据字节大小
    virtual void saveRgb24(const char *rgb24FilePath) override;                                    // 保存rgb24像素数据到文件
    virtual void destory() override;                                                               // 释放内存
    virtual void displayPixels() override;                                                         // 打印图片像素信息
    virtual void setRGB24Pixel(uint32_t color, uint32_t x, uint32_t y) override;                   // 设置每个像素位置的rgb颜色信息

private:
    bool mallocPixels();                               // 按像素,申请rgb24像素信息内存
    bool mallocRgb24DataBytes();                       // 按字节,申请rgb24像素信息内存
    bool genRGB24Data(const char *rgb24FilePath);      // 获取rgb24文件的像素信息
    uint8_t *readRgb24Data(const char *rgb24FilePath); // 读取rgb24文件字节数据
    size_t getFileSize(const char *filePath);          // 获取文件大小
    bool reMalloc();                                   // 重新申请内存空间
};
#endif