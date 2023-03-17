#include "../../include/rgb2yuv/RGB24toYUV444p.h"

RGB24toYUV444p::RGB24toYUV444p()
{
    std::cout << "RGB24toYUV444p::RGB24toYUV444p()构造函数" << std::endl;
}

RGB24toYUV444p::~RGB24toYUV444p()
{
    std::cout << "RGB24toYUV444p::~RGB24toYUV444p()析构函数" << std::endl;
    freeFile();
}

/**
 * @brief 初始化
 *
 * @param width
 * @param height
 * @param rgp24FilePath
 * @param yuv444pFilePath
 */
bool RGB24toYUV444p::create(unsigned int width, unsigned int height, const char *rgp24FilePath, const char *yuv444pFilePath)
{
    std::cout << "RGB24toYUV444p::create()::" << std::endl;
    std::cout << "RGB24toYUV444p::" << __FUNCTION__ << "()::" << __LINE__ << ",rgp24FilePath:" << rgp24FilePath << std::endl;
    std::cout << "RGB24toYUV444p::" << __FUNCTION__ << "()::" << __LINE__ << ",yuv444pFilePath:" << yuv444pFilePath << std::endl;
    this->width = width;
    this->height = height;
    this->rgb24File = fopen(rgp24FilePath, "rb");     // 获取rgp24输入文件指针
    this->yuv444pFile = fopen(yuv444pFilePath, "wb"); // 获取yuv444p输出文件指针
    if (rgb24File == NULL || yuv444pFile == NULL)
    {
        return false;
    }
    return true;
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
    // std::cout << "RGB24toYUV444p::bound()::" << std::endl;
    if (value <= start)
    {
        return start;
    }
    if (value >= end)
    {
        return end;
    }
    return value;
}

/**
 * @brief rgb24转化为yuv444p
 *
 */
bool RGB24toYUV444p::rgb24ToYuv444p()
{
    std::cout << "RGB24toYUV444p::" << __FUNCTION__ << "()::" << __LINE__ << std::endl;
    std::cout << "RGB24toYUV444p::" << __FUNCTION__ << "()::" << __LINE__ << ",uint8_t sizoeof:" << sizeof(uint8_t) << std::endl;
    std::cout << "RGB24toYUV444p::" << __FUNCTION__ << "()::" << __LINE__ << ",uint32_t sizoeof:" << sizeof(uint32_t) << std::endl;
    int bytesPerPixel = 24 * 1.0 / 8.0;
    std::cout << "RGB24toYUV444p::" << __FUNCTION__ << "()::" << __LINE__ << ",bytesPerPixel:" << bytesPerPixel << std::endl;
    uint8_t rgb24Data[width * height * bytesPerPixel];   // 申请读取rbg24文件内存
    uint8_t yuv444pData[width * height * bytesPerPixel]; // 申请保存yuv444p文件内存

    size_t size = fread(rgb24Data, sizeof(rgb24Data), 1, rgb24File); // 读取rgb24文件到内存
    std::cout << "RGB24toYUV444p::" << __FUNCTION__ << "()::" << __LINE__ << ",size:" << size << std::endl;
    rgb24ToYuv444p(rgb24Data, yuv444pData, width, height);    // 把内存中rgb24转化为内存中yuv444p
    fwrite(yuv444pData, sizeof(yuv444pData), 1, yuv444pFile); // 把内存中的yuv444p数据写入yuv444p文件中
    freeFile();
    return true;
}

/**
 * @brief  rgb24转化为yuv444p
 *
 * @param rgb24Data rgb24数据
 * @param yuv444pData yuv444p数据
 * @param width 宽
 * @param height 高
 */
void RGB24toYUV444p::rgb24ToYuv444p(const uint8_t *rgb24Data, uint8_t *yuv444pData, int width, int height)
{
    int8_t yuv_y[width * height];
    int8_t yuv_u[width * height];
    int8_t yuv_v[width * height];

    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            uint8_t Y, U, V;
            uint8_t R, G, B;

            int currentRGBIndex = 3 * (i * height + j);
            R = rgb24Data[currentRGBIndex];
            G = rgb24Data[currentRGBIndex + 1];
            B = rgb24Data[currentRGBIndex + 2];

            rgbToYuv(R, G, B, &Y, &U, &V);

            int currentYUVIndex = i * height + j;
            yuv_y[currentYUVIndex] = Y;
            yuv_u[currentYUVIndex] = U;
            yuv_v[currentYUVIndex] = V;
        }
    }

    // 拷贝到内存
    memcpy(yuv444pData, yuv_y, sizeof(yuv_y));
    memcpy(yuv444pData + sizeof(yuv_y), yuv_u, sizeof(yuv_u));
    memcpy(yuv444pData + sizeof(yuv_y) + sizeof(yuv_u), yuv_v, sizeof(yuv_v));
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
    // std::cout << "RGB24toYUV444p::rgbToYuv()::" << std::endl;
    int y_val = (int)round(0.257 * R + 0.504 * G + 0.098 * B + 16);
    int u_val = (int)round(-0.148 * R - 0.291 * G + 0.439 * B + 128);
    int v_val = (int)round(0.439 * R - 0.368 * G - 0.071 * B + 128);
    *Y = bound(16, y_val, 235);
    *U = bound(16, u_val, 239);
    *V = bound(16, v_val, 239);
}

/**
 * @brief 释放内存
 *
 */
void RGB24toYUV444p::freeFile()
{
    std::cout << "RGB24toYUV444p::freeFile()" << std::endl;
    // 关闭文件指针
    if (rgb24File != NULL)
    {
        fclose(rgb24File);
    }
    if (yuv444pFile != NULL)
    {
        fclose(yuv444pFile);
    }
    rgb24File = NULL;
    yuv444pFile = NULL;
}