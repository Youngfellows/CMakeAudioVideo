#include "../../include/rgb2yuv/RGB24toYUV420p.h"

RGB24toYUV420p::RGB24toYUV420p()
{
    std::cout << "RGB24toYUV420p::" << __FUNCTION__ << "():: " << __LINE__ << std::endl;
}

RGB24toYUV420p::~RGB24toYUV420p()
{
    std::cout << "RGB24toYUV420p::" << __FUNCTION__ << "():: " << __LINE__ << std::endl;
}

/**
 * @brief 初始化
 *
 * @param width 宽
 * @param height 高
 */
bool RGB24toYUV420p::create(uint32_t width, uint32_t height)
{
    std::cout << "RGB24toYUV420p::" << __FUNCTION__ << "():: " << __LINE__ << std::endl;
    this->width = abs(width);
    this->height = abs(height);
    return true;
}

/**
 * @brief 初始化
 *
 * @param width 宽
 * @param height 高
 * @param rgb24FilePath rgb24文件路径
 */
bool RGB24toYUV420p::create(uint32_t width, uint32_t height, const char *rgb24FilePath)
{
    std::cout << "RGB24toYUV420p::" << __FUNCTION__ << "():: " << __LINE__ << std::endl;
    this->width = abs(width);
    this->height = abs(height);
    return true;
}

/**
 * @brief rgb24转化为yuv420p
 *
 * @param yuv420pFilePath yuv420p文件路径
 */
void RGB24toYUV420p::rgb24ToYuv420p(const char *yuv420pFilePath)
{
    std::cout << "RGB24toYUV420p::" << __FUNCTION__ << "():: " << __LINE__ << std::endl;
}

/**
 * @brief 释放资源
 *
 */
void RGB24toYUV420p::destory()
{
    std::cout << "RGB24toYUV420p::" << __FUNCTION__ << "():: " << __LINE__ << std::endl;
}