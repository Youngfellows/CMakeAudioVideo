#ifndef _RAINBOW_H_
#define _RAINBOW_H_

#include <iostream>
#include "./IRainbow.h"

/**
 * @brief 实现类: 彩虹图片像素数据的实现类
 *
 */
class Rainbow : public IRainbow
{
private:
    uint32_t width;  // 宽
    uint32_t height; // 高

public:
    Rainbow();
    ~Rainbow();
    virtual bool createBitmap(uint32_t width, uint32_t height) override; // 创建BMP格式彩虹图片
    virtual bool createRGB24(uint32_t width, uint32_t height) override;  // 创建RGB24格式彩虹图片
    virtual void saveBitmap(const char *bmpFilePath) override;           // 保存BMP位图到文件
    virtual void saveRGB24(const char *rgb24FilePath) override;          // 保存RGB24位图到文件
    virtual void destory() override;                                     // 释放资源
    virtual void createBmpPixels() override;                             // 设置BMP位图像素信息
    virtual void createRGB24Pixels() override;                           // 设置rgb24位图像素信息
    virtual uint8_t *rainbowBmpData() override;                          // 获取彩虹图片的BMP格式内存数据
    virtual uint8_t *rainbowRGB24Data() override;                        // 获取彩虹图片的RGB24格式内存数据

private:
    void rgb24Destory(); // 释放rgb24位图资源
    void bmpDestory();   // 释放BMP位图资源
};

#endif