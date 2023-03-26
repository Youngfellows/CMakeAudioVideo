#ifndef _I_YUV420P_TO_YUV444P_H_
#define _I_YUV420P_TO_YUV444P_H_

#include <iostream>

/**
 * @brief 抽象类接口: yuv420p转化为yuv444p
 *
 */
class IYUV420ptoYUV444p
{
public:
    ~IYUV420ptoYUV444p() = default;

    /**
     * @brief 默认初始化,
     * @brief 使用默认的彩虹图片rgb24数据，先转化为yuv420，然后再转化为yuv420p
     *
     * @param width 宽
     * @param height 高
     * @return true
     * @return false
     */
    virtual bool create(uint32_t width, uint32_t height) = 0;

    /**
     * @brief 初始化
     * @brief 使用本地rgb24文件初始化,然后再转化为yuv420p
     *
     * @param rgb24FilePath 本地rgb24文件
     * @param width
     * @param height
     * @return true
     * @return false
     */
    virtual bool createFromRgb24(const char *rgb24FilePath, uint32_t width, uint32_t height) = 0;

    /**
     * @brief 初始化
     * @brief 使用本地yuv420p文件初始化
     *
     * @param yuv420pFilePath 本地yuv420p文件
     * @param width
     * @param height
     * @return true
     * @return false
     */
    virtual bool createFromYuv420p(const char *yuv420pFilePath, uint32_t width, uint32_t height) = 0;

    /**
     * @brief yuv420p转化为yuv444p
     *
     * @param yuv444pFilePath 要保存的yuv444p地址
     */
    virtual void yuv420pToYuv444p(const char *yuv444pFilePath) = 0;

    /**
     * @brief 释放资源
     *
     */
    virtual void destory() = 0;
};

#endif