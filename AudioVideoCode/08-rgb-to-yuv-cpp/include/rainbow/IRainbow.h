#ifndef _IRAINBOW_H
#define _IRAINBOW_H

#include "../entity/RGBPixel.h"

/**
 * @brief 抽象类: 生成彩虹图片像素信息类
 *
 */
class IRainbow
{
public:
    ~IRainbow() = default;

    /**
     * @brief 纯虚函数,抽象接口: 生成彩虹图片的rgb24格式数据
     *
     * @param pixels 图片像素的地址
     * @param width
     * @param height
     */
    virtual void rgb24Data(RGBPixel **pixels, uint32_t width, uint32_t height) = 0;
};

#endif