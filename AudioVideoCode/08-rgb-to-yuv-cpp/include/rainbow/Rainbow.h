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

private:
    void destory();                            // 释放资源
    void createBmpPixels(uint8_t *bitmapData); // 设置BMP位图像素信息
};

#endif