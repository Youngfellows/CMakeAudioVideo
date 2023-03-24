#ifndef _I_YUV444P_TO_YUV420P_H_
#define _I_YUV444P_TO_YUV420P_H_

#include <iostream>

/**
 * @brief 抽象类接口:yuv444p转化为yuv420p
 *
 */
class IYUV444ptoYUV420p
{
public:
    ~IYUV444ptoYUV420p() = default;

    /**
     * @brief 默认初始化
     *
     * @param width 宽
     * @param height 高
     * @return true
     * @return false
     */
    virtual bool create(uint32_t width, uint32_t height) = 0;

    /**
     * @brief 从RGB24文件初始化
     *
     * @param rgb24FilePath 从RGB24文件
     * @param width 宽
     * @param height 高
     * @return true
     * @return false
     */
    virtual bool createFromRGB24(const char *rgb24FilePath, uint32_t width, uint32_t height) = 0;

    /**
     * @brief 从YUV444p文件初始化
     *
     * @param yuv444pFilePath YUV444p文件
     * @param width 宽
     * @param height 高
     * @return true
     * @return false
     */
    virtual bool createFromYUV444p(const char *yuv444pFilePath, uint32_t width, uint32_t height) = 0;

    /**
     * @brief yuv444p转化为yuv420p
     *
     * @param yuv420pFilePath 保存的文件路径
     */
    virtual void yuv444pToYuv420p(const char *yuv420pFilePath) = 0;

    /**
     * @brief 释放资源
     *
     */
    virtual void destory() = 0;
};

#endif