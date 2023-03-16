#ifndef _RGB24_TO_YUV444P_H_
#define _RGB24_TO_YUV444P_H_

#include <iostream>
#include "./interfaces/IRGB24toYUV444p.h"

using namespace std;

/**
 * @brief rgb24转换为yuv444
 *
 */
class RGB24toYUV444p : public IRGB24toYUV444p
{
private:
    FILE *rgb24File;     // rgb24源文件指针变量
    FILE *yuv444pFile;   // yuv444p文件指针变量
    unsigned int width;  // 宽
    unsigned int height; // 高

public:
    RGB24toYUV444p();
    ~RGB24toYUV444p();
    virtual void create(unsigned int width, unsigned int height, const char *rgp24FilePath, const char *yuv444pFilePath) override;
    virtual void rgb24ToYuv444p() override;
    virtual void free() override; // 释放内存
private:
    uint8_t bound(uint8_t start, int value, uint8_t end);                               // 截取
    void rgbToYuv(uint8_t R, uint8_t G, uint8_t B, uint8_t *Y, uint8_t *U, uint8_t *V); // rgb24转化为yuv444p
};
#endif