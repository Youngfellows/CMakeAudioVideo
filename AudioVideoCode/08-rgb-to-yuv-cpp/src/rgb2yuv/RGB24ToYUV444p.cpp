#include "../../include/rgb2yuv/RGB24toYUV444p.h"

RGB24toYUV444p::RGB24toYUV444p()
{
    std::cout << "RGB24toYUV444p::RGB24toYUV444p()构造函数" << std::endl;
}

RGB24toYUV444p::~RGB24toYUV444p()
{
    std::cout << "RGB24toYUV444p::~RGB24toYUV444p()析构函数" << std::endl;
}

/**
 * @brief 初始化
 *
 * @param width
 * @param height
 * @param rgp24FilePath
 * @param yuv444pFilePath
 */
void RGB24toYUV444p::create(unsigned int width, unsigned int height, const char *rgp24FilePath, const char *yuv444pFilePath)
{
    std::cout << "RGB24toYUV444p::create()::" << std::endl;
}

/**
 * @brief 截取
 *
 * @param start
 * @param value
 * @param end
 * @return uint8_t
 */
uint8_t RGB24toYUV444p::bound(uint8_t start, int value, uint8_t end)
{
    std::cout << "RGB24toYUV444p::bound()::" << std::endl;
    return 0;
}

/**
 * @brief rgb24转化为yuv444p
 *
 */
void RGB24toYUV444p::rgb24ToYuv444p()
{
    std::cout << "RGB24toYUV444p::rgb24ToYuv444p()::" << std::endl;
}

/**
 * @brief rgb24转化为yuv444p
 *
 * Y = 0.257*R + 0.504*G + 0.098*B + 16;
 * U = -0.148*R - 0.291*G + 0.439*B + 128;
 * V = 0.439*R - 0.368*G - 0.071*B + 128;
 *
 * @param R
 * @param G
 * @param B
 * @param Y
 * @param U
 * @param V
 */
void RGB24toYUV444p::rgbToYuv(uint8_t R, uint8_t G, uint8_t B, uint8_t *Y, uint8_t *U, uint8_t *V)
{
    std::cout << "RGB24toYUV444p::rgbToYuv()::" << std::endl;
}

/**
 * @brief 释放内存
 *
 */
void RGB24toYUV444p::free()
{
    std::cout << "RGB24toYUV444p::free()" << std::endl;
}