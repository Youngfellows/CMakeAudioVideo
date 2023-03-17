#ifndef _RAINBOW_H_
#define _RAINBOW_H_

#include <iostream>
#include "./IRainbow.h"
#include "./RainbowColors.h"

/**
 * @brief 实现类: 彩虹图片像素数据的实现类
 *
 */
class Rainbow : public IRainbow
{
private:
public:
    Rainbow();
    ~Rainbow();
    virtual void rgb24Data(RGBPixel ***pixels, uint32_t width, uint32_t height) override; // 生成彩虹图片的rgb24数据
};
#endif