#ifndef _YUV444P_TO_RGB24_H_
#define _YUV444P_TO_RGB24_H_

#include <iostream>
#include <cmath>
#include "./interfaces/IYUV444ptoRGB24.h"

/**
 * @brief yuv444p转化为rgb24实现类
 *
 */
class YUV444ptoRGB24 : public IYUV444ptoRGB24
{
private:
    FILE *rgb24File;     // rgb24源文件指针变量
    FILE *yuv444pFile;   // yuv444p文件指针变量
    unsigned int width;  // 宽
    unsigned int height; // 高
public:
    YUV444ptoRGB24();
    ~YUV444ptoRGB24();
    virtual bool create(unsigned int width, unsigned int height, const char *yuv444pFilePath, const char *rgp24FilePath) override;
    virtual bool yuv444pToRgb24() override;

private:
    void yuv444pToRgb24(uint8_t *yuv444pData, uint8_t *rgb24Data, int width, int height); // yuv444p转化为rgb24
    uint8_t bound(uint8_t start, int value, uint8_t end);                                 // 边界截取
    void freeResource();                                                                  // 释放资源
};
#endif