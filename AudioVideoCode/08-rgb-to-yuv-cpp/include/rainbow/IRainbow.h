#ifndef _IRAINBOW_H_
#define _IRAINBOW_H_

#include "../pixel/Bitmap.h"

/**
 * @brief 抽象类: 抽象彩虹图片生成器
 *
 */
class IRainbow
{
protected:
    Bitmap *bitmap; // BMP位图对象

public:
    ~IRainbow() = default;

    /**
     * @brief 创建BMP格式彩虹图片
     *
     * @param width 宽
     * @param height 高
     */
    virtual bool createBitmap(uint32_t width, uint32_t height) = 0;

    /**
     * @brief 创建RGB24格式彩虹图片
     *
     * @param width 宽
     * @param height 高
     */
    virtual bool createRGB24(uint32_t width, uint32_t height) = 0;

    /**
     * @brief 保存BMP位图到文件
     *
     * @param bmpFilePath
     */
    virtual void saveBitmap(const char *bmpFilePath) = 0;

    /**
     * @brief 保存RGB24位图到文件
     *
     * @param rgb24FilePath
     */
    virtual void saveRGB24(const char *rgb24FilePath) = 0;
};
#endif