#ifndef _IPIXEL_H
#define _IPIXEL_H

#include "../bitmap/RGBPixel.h"

/**
 * @brief 抽象类: 生成图片像素信息类
 *
 */
class IPixel
{
public:
    ~IPixel() = default;

    /**
     * @brief
    /**
     * @brief 纯虚函数,抽象接口: 生成图片的bmp格式像素数据
     *
     * @param size
     * @param width
     * @param height
     * @return uint8_t*
     */
    virtual uint8_t *bmpCreate(uint32_t width, uint32_t height) = 0;

    /**
     * @brief 设置指定位置的rgb像素值
     *
     * @param bmpData bmp内存
     * @param color RGB颜色值
     * @param x
     * @param y
     */
    virtual void setBmpPixel(uint8_t *bmpData, uint32_t color, uint32_t x, uint32_t y) = 0;

    /**
     * @brief 获取内存中的bmp位图数据
     *
     * @return uint8_t*
     */
    virtual uint8_t *bmpData() = 0;

    /**
     * @brief 获取BMP图片的大小
     *
     * @return uint32_t
     */
    virtual uint32_t getBmpSize() = 0;

    /**
     * @brief 纯虚函数,抽象接口: 生成图片的rgb24格式像素数据
     *
     * @param pixels 图片像素的地址
     * @param width
     * @param height
     */
    virtual void rgb24Data(RGBPixel **pixels, uint32_t width, uint32_t height) = 0;

    /**
     * @brief 设置指定位置连续2个字节表示的整数到内存中
     *
     * @param number 要设置的数字
     * @param bytes 内存空间
     * @param pos 开始设置的位置
     */
    virtual void setShortToBytes(uint16_t number, uint8_t *bytes, uint32_t pos) = 0;

    /**
     * @brief 设置指定位置连续4个字节表示的整数到内存中
     *
     * @param number 要设置的数字
     * @param bytes 内存空间
     * @param pos 开始设置的位置
     */
    virtual void setIntToBytes(uint32_t number, uint8_t *bytes, uint32_t pos) = 0;

    /**
     * @brief  获取内存中指定位置连续2个字节表示的整数
     *
     * @param bytes 内存空间
     * @param pos 获取的开始位置
     * @return uint16_t 返回short类型数据
     */
    virtual uint16_t shortFromBytes(uint8_t *bytes, uint32_t pos) = 0;

    /**

     * @brief 获取内存中指定位置连续4个字节表示的整数
     *
     * @param bytes 内存空间
     * @param pos 获取的开始位置
     * @return uint32_t 返回int类型数据
     */
    virtual uint32_t intFromBytes(uint8_t *bytes, uint32_t pos) = 0;

    /**
     * @brief 保存rgb24像素数据到文件
     *
     * @param path 保存的文件路径
     * @param data 内存中的数据
     * @param size 保存的数据大小
     */
    virtual bool saveRgb24(const char *path, uint8_t *data, uint32_t size) = 0;

    /**
     * @brief 保存bmp像素数据到文件
     *
     * @param path 保存的文件路径
     * @param data 内存中的数据
     * @param size 保存的数据大小
     */
    virtual bool saveBitmap(const char *path, uint8_t *data, uint32_t size) = 0;

    /**
     * @brief 释放内存
     *
     */
    virtual void destory() = 0;
};

#endif