#pragma once

#include "GifDecoder.h"

/**
 * @brief Gif解码器封装
 *
 */
class AndroidGifDecoder
{
private:
    GifDecoder *gifDecoder;         // Gif解码器
    BitmapIterator *bitmapIterator; // 迭代器

public:
    AndroidGifDecoder(/* args */);
    ~AndroidGifDecoder();
    bool initialize();                            // 初始化Gif解码器
    bool load(const char *filePath);              // 加载Gif动画
    bool loadUsingIterator(const char *filePath); // 加载Gif动画
    bool bitmapIteratorHasNext();                 // 获取是否有下一帧
    GifFrame *bitmapIteratornext();               // 获取下一帧数据
    uint32_t getFrameCount();                     // 获取Gif动画帧数
    uint32_t getDelay(uint32_t index);            // 获取每一帧延时时长
    GifFrame *getFrame(uint32_t index);           // 获取每一帧数据
    uint32_t getWidth();                          // 获取Gif图片宽
    uint32_t getHeight();                         // 获取Gif图片高
    void destory();                               // 销毁Gif解码器资源
};