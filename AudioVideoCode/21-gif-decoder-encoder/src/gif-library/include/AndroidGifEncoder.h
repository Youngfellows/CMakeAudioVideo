#pragma once
#include <stdint.h>
#include <cstring>
#include "GifEncoder.h"
#include "EncodingType.h"

/**
 * @brief Gif编码
 *
 */
class AndroidGifEncoder
{
private:
    GifEncoder *gifEncoder; // Gif编码器

private:
    /* data */
    void setThreadCount(uint32_t threadCount); // 设置线程数量
public:
    AndroidGifEncoder(/* args */);
    ~AndroidGifEncoder();
    bool initialize(uint32_t width, uint32_t height, const char *filePath,
                    EncodingType encodingType, uint32_t threadCount); // 初始化Gif编码器
    void setDither(bool useDither);                                   // 设置使用抖动
    bool encodeFrame(uint8_t *pixels, uint32_t delayMs);              // 编码帧数据
    void destory();                                                   // 释放资源
};
