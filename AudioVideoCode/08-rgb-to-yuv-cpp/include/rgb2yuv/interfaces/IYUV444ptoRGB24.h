#ifndef _IYUV444P_TO_RGB24_H_
#define _IYUV444P_TO_RGB24_H_

#include <iostream>

/**
 * @brief rgb24转化为yuv444p抽象接口
 *
 */
class IYUV444ptoRGB24
{
public:
    /**
     * @brief 存虚函数: 初始化
     *
     * @param width 宽
     * @param height 高
     * @param yuv444pFilePath yuv444p文件路径
     * @param rgp24FilePath rgb24文件路径
     */
    virtual bool create(unsigned int width, unsigned int height, const char *yuv444pFilePath, const char *rgp24FilePath) = 0;

    /**
     * @brief yuv444p转化为rgb24
     *
     */
    virtual bool yuv444pToRgb24() = 0;
};

#endif