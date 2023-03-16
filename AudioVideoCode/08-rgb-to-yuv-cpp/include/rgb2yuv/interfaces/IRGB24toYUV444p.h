#ifndef _IRGB24_TO_YUV444P_H_
#define _IRGB24_TO_YUV444P_H_

#include <iostream>

/**
 * @brief rgb24转化为yuv444p抽象接口
 *
 */
class IRGB24toYUV444p
{
public:
    //~IRGB24toYUV444p() = default;

    /**
     * @brief 存虚函数: 初始化
     *
     * @param width 宽
     * @param height 高
     * @param rgp24FilePath rgb24文件路径
     * @param yuv444pFilePath yuv444p文件路径
     */
    virtual void create(unsigned int width, unsigned int height, const char *rgp24FilePath, const char *yuv444pFilePath) = 0;

    /**
     * @brief rgb24转化为yuv444p
     *
     */
    virtual void rgb24ToYuv444p() = 0;

    /**
     * @brief 释放内存
     *
     */
    virtual void free() = 0;
};

#endif