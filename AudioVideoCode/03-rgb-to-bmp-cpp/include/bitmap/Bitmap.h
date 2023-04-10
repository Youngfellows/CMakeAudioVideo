#ifndef BITMAP_H
#define BITMAP_H

#include <iostream>
#include <iomanip>
#include "./IBitmap.h"
#include "./BmpConfig.h"
#include <string>
#include <memory>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <cmath>
#include <cstring>

using namespace std;

/**
 * @brief BMP具体实现类
 *
 */
class Bitmap : public IBitmap
{
private:
    BitmapFileHeader *bmpFileHeader = NULL; // BMP文件信息头
    BitmapInfoHeader *bmpInfoHeader = NULL; // BMP位图信息头
    RGBPixel **pixels;                      // 图片信息内存
    uint8_t *bmpData;                       // BMP图片内存空间

public:
    Bitmap();
    ~Bitmap();
    virtual bool bmpCreate(uint32_t width, uint32_t height, uint32_t depth) override;
    virtual bool bmpSetPixel(uint32_t x, uint32_t y, RGBPixel pixel) override;
    virtual bool save(const char *outputFile) override; // 覆写writeRainbow()函数
    virtual void displayPixels() override;              // 打印图片像素颜色信息

private:
    void writeBmpFileHeader(BitmapFileHeader *bmpHeader, FILE *fp);     // 向文件写入bmp位图文件头
    void writeBmpInfoHeader(BitmapInfoHeader *bmpInfoHeader, FILE *fp); // 向文件写入bmp位图信息头
    void writeBmpPixels(RGBPixel **pixels, FILE *fp);                   // 向文件写入bmp图片像素信息
    void bmpHeaderSwapEndianess(BitmapFileHeader *bmpHeader);
    void bmpInfoHeaderSwapEndianess(BitmapInfoHeader *bmpInfoHeader);
    bool bmpMallocPixels(); // 申请图片像素信息内存
    bool bmpDataMalloc();   // 申请图片像素信息rgb24字节内存
    void bmpDestroy();      // 释放资源
    void bmpFreePixels();   // 释放图片像素信息内存
    bool isBigEndian(void); // 是否大端字节序
};
#endif