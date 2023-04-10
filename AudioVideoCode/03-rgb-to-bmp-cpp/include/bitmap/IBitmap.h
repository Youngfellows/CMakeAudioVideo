#ifndef IBITMAP_H
#define IBITMAP_H
#include "../bmpsturct/BitmapFileHeader.h"
#include "../bmpsturct/BitmapInfoHeader.h"
#include "../bmpsturct/RGBPixel.h"

/**
 * @brief BMP图片抽象类
 *
 */
class IBitmap
{
public:
    virtual ~IBitmap() = default;

    /**
     * @brief 初始化bmp图片,创建图片信息
     *
     * @param width 图片宽
     * @param height 图片高
     * @param depth 每个像素的位数，默认是24位，占3个字节
     */
    virtual bool bmpCreate(uint32_t width, uint32_t height, uint32_t depth) = 0;

    /**
     * @brief 为每个位置设置像素信息
     *
     * @param x x位置
     * @param y y位置
     * @param pixel 像素信息
     * @return true
     * @return false
     */
    virtual bool bmpSetPixel(unsigned int x, unsigned int y, RGBPixel pixel) = 0;

    /**
     * @brief 写入彩虹数据:纯虚函数,子类必须实现
     *
     * @param outputFile 文件名
     * @return true 写入数据成功
     * @return false 写入数据成功
     */
    virtual bool save(const char *outputFile) = 0;

    /**
     * @brief 打印图片像素颜色信息
     *
     */
    virtual void displayPixels() = 0;
};

#endif