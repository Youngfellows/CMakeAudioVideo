#include "../../include/rgb2yuv/YUV420ptoYUV444p.h"

YUV420ptoYUV444p::YUV420ptoYUV444p()
{
    std::cout << TAG << __FUNCTION__ << "():: Line " << __LINE__ << std::endl;
}

YUV420ptoYUV444p::~YUV420ptoYUV444p()
{
    std::cout << TAG << __FUNCTION__ << "():: Line " << __LINE__ << std::endl;
}

/**
 * @brief  初始化,默认使用彩虹图片
 *
 * @param width 宽
 * @param height 高
 * @return true
 * @return false
 */
bool YUV420ptoYUV444p::create(uint32_t width, uint32_t height)
{
    std::cout << TAG << __FUNCTION__ << "():: Line " << __LINE__ << std::endl;
    return true;
}

/**
 * @brief 使用本地rgb24文件初始化,然后再转化为yuv420p
 *
 * @param rgb24FilePath rgb24文件路径
 * @param width 宽
 * @param height 高
 * @return true
 * @return false
 */
bool YUV420ptoYUV444p::createFromRgb24(const char *rgb24FilePath, uint32_t width, uint32_t height)
{
    std::cout << TAG << __FUNCTION__ << "():: Line " << __LINE__ << std::endl;
    return true;
}

/**
 * @brief 使用本地yuv420p文件初始化
 *
 * @param yuv420pFilePath yuv420p文件路径
 * @param width 宽
 * @param height 高
 * @return true
 * @return false
 */
bool YUV420ptoYUV444p::createFromYuv420p(const char *yuv420pFilePath, uint32_t width, uint32_t height)
{
    std::cout << TAG << __FUNCTION__ << "():: Line " << __LINE__ << std::endl;
    return true;
}

/**
 * @brief yuv420p转化为yuv444p
 *
 * @param yuv444pFilePath
 */
void YUV420ptoYUV444p::yuv420pToYuv444p(const char *yuv444pFilePath)
{
    std::cout << TAG << __FUNCTION__ << "():: Line " << __LINE__ << std::endl;
}

/**
 * @brief 释放资源
 *
 */
void YUV420ptoYUV444p::destory()
{
    std::cout << TAG << __FUNCTION__ << "():: Line " << __LINE__ << std::endl;
}

/**
 * @brief yuv420p转化为yuv444p
 *
 */
void YUV420ptoYUV444p::yuv420pToYuv444p()
{
    std::cout << TAG << __FUNCTION__ << "():: Line " << __LINE__ << std::endl;
}

/**
 * @brief 保存yuv444p数据到文件
 *
 * @param yuv444pFilePath
 */
void YUV420ptoYUV444p::saveYuv444p(const char *yuv444pFilePath)
{
    std::cout << TAG << __FUNCTION__ << "():: Line " << __LINE__ << std::endl;
}