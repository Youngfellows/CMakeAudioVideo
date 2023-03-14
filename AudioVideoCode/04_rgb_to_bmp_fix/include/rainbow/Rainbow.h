#ifndef RAINBOW_H
#define RAINBOW_H

#include <iostream>
#include <iomanip>
#include "./IRainbow.h"
#include "./Config.h"
#include <string>
#include <memory>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "../bmp/BitmapFileHeader.h"
#include "../bmp/BitmapInfoHeader.h"

using namespace std;

/**
 * @brief 彩虹类
 *
 */
class Rainbow : public IRainbow
{
private:
    uint32_t rainbowColors[7]; // 彩虹的七种颜色

public:
    Rainbow();
    ~Rainbow();
    virtual bool writeRainbow(const char *outputFile, int width, int height) override;  // 覆写writeRainbow()函数
    virtual bool writeRainbow2(const char *outputFile, int width, int height) override; // 覆写writeRainbow2()函数

private:
    void initRainbowColors(); // 初始化彩虹颜色
    int caculateLineBytes(int width);
};
#endif