#ifndef _I_RGB24_TO_YUV420P_H_
#define _I_RGB24_TO_YUV420P_H_

#include <iostream>

/**
 * @brief 抽象类: rgb24转化为yuv420p接口
 *
 */
class IRGB24toYUV420p
{
public:
    ~IRGB24toYUV420p() = default;

    /**
     * @brief 纯虚函数,抽象接口: 初始化
     *
     * @param width 宽
     * @param height 高
     */
    virtual bool create(uint32_t width, uint32_t height) = 0;

    /**
     * @brief 纯虚函数,抽象接口: 初始化
     *
     * @param width 宽
     * @param height 高
     * @param rgb24FilePath rgb24文件路径
     */
    virtual bool create(uint32_t width, uint32_t height, const char *rgb24FilePath) = 0;

    /**
     * @brief 纯虚函数,抽象接口: rgb24转化为yuv420p
     *
     * @param yuv420pFilePath yuv420p文件路径
     */
    virtual void rgb24ToYuv420p(const char *yuv420pFilePath) = 0;

    /**
     * @brief 释放资源
     *
     */
    virtual void destory() = 0;
};

#endif