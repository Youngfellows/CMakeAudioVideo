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

using namespace std;

/**
 * @brief BMP具体实现类
 *
 */
class Bitmap : public IBitmap
{
private:
    uint32_t rainbowColors[7]; // 彩虹的七种颜色

public:
    Bitmap();
    ~Bitmap();
    virtual void bmpCreate(uint32_t width, uint32_t height, uint32_t depth) override;
    virtual bool bmpSetPixel(uint32_t x, uint32_t y, RGBPixel pixel) override;
    virtual bool save(const char *outputFile, int width, int height) override;           // 覆写writeRainbow()函数
    virtual bool save2(const char *outputFile, int width, int height) override;          // 覆写writeRainbow2()函数
    virtual void writeBmpFileHeader(BitmapFileHeader *bmpHeader, FILE *fp) override;     // 覆写writeBmpFileHeader()函数
    virtual void writeBmpInfoHeader(BitmapInfoHeader *bmpInfoHeader, FILE *fp) override; // 覆写writeBmpInfoHeader()函数
    virtual void bmpHeaderSwapEndianess(BitmapFileHeader *bmpHeader) override;
    virtual void bmpInfoHeaderSwapEndianess(BitmapInfoHeader *bmpInfoHeader) override;
    virtual void bmpDestroy() override;

private:
    void initRainbowColors(); // 初始化彩虹颜色
    bool isBigEndian(void);   // 是否大端字节序
};
#endif