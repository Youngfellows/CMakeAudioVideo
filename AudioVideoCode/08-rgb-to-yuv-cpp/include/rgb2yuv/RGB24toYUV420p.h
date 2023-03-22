#ifndef _RGB24_TO_YUV420P_H_
#define _RGB24_TO_YUV420P_H_

#include "./interfaces/IRGB24toYUV420p.h"
#include "../pixel/RGB24.h"
#include "../rainbow/Rainbow.h"
#include "../bitmap/RGBPixel.h"

/**
 * @brief 实现类: rgb24转化为yuv420p
 *
 */
class RGB24toYUV420p : public IRGB24toYUV420p
{
private:
    uint32_t width;       // 宽
    uint32_t height;      // 高
    RGB24 *rgb24;         // rgb24像素生成器
    Rainbow *rainbow;     // 彩虹图片像素生成器
    RGBPixel **rgbPixels; // 图片像素信息
    uint8_t *rgb24Data;   // 内存中按字节存储的图片像素信息
    uint8_t *yuv420pData; // 内存中按字节存储的yvu420p像素信息

public:
    RGB24toYUV420p();
    ~RGB24toYUV420p();
    virtual bool create(uint32_t width, uint32_t height) override;                            // 初始化
    virtual bool create(uint32_t width, uint32_t height, const char *rgb24FilePath) override; // 初始化
    virtual void rgb24ToYuv420p(const char *yuv420pFilePath) override;                        // rgb24转化为yuv420p
    virtual void destory() override;                                                          // 释放资源
private:
    bool createRainbowRGB24Pixels();                   // 创建彩虹图片的RGB24图片信息
    bool createRGB24Pixels(const char *rgb24FilePath); // 创建指定路径图片的RGB24图片信息
    bool mallocYuv420pPixels();                        // 申请yuv420p内存空间
    void rgb24ToYuv420p();                             // rgb24转化为yuv420p
    void saveYuv420p(const char *yuv420pFilePath);     // 保存yuv420p到文件
};
#endif