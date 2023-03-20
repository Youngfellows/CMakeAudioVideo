#ifndef _RGB24_H_
#define _RGB24_H_

#include <iostream>
#include <cstring>
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
    virtual void saveRgb24(const char *rgb24FilePath) override;                                    // 保存rgb24像素数据到文件
    virtual void destory() override;                                                               // 释放内存
    void displayPixels();                                                                          // 打印图片像素信息

private:
    bool mallocPixels();                          // 申请rgb24像素信息内存
    bool mallocRgb24DataBytes();                  // 申请rgb24像素信息内存
    void genRGB24Data();                          // 生成rgb24数据
    void genRGB24Data(const char *rgb24FilePath); // 获取rgb24文件的像素信息
};
#endif