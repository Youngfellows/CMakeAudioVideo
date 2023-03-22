#ifndef _RGB24_TO_YUV420P_H_
#define _RGB24_TO_YUV420P_H_

#include "./interfaces/IRGB24toYUV420p.h"

/**
 * @brief 实现类: rgb24转化为yuv420p
 *
 */
class RGB24toYUV420p : public IRGB24toYUV420p
{
private:
    uint32_t width;  // 宽
    uint32_t height; // 高
public:
    RGB24toYUV420p();
    ~RGB24toYUV420p();
    virtual bool create(uint32_t width, uint32_t height) override;                            // 初始化
    virtual bool create(uint32_t width, uint32_t height, const char *rgb24FilePath) override; // 初始化
    virtual void rgb24ToYuv420p(const char *yuv420pFilePath) override;                        // rgb24转化为yuv420p

private:
    void destory(); // 释放资源
};
#endif