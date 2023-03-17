#include "../../include/rgb2yuv/YUV444ptoRGB24.h"

YUV444ptoRGB24::YUV444ptoRGB24()
{
    std::cout << "YUV444ptoRGB24::YUV444ptoRGB24()" << std::endl;
}

bool YUV444ptoRGB24::create(unsigned int width, unsigned int height, const char *yuv444pFilePath, const char *rgp24FilePath)
{
    std::cout << "YUV444ptoRGB24::" << __FUNCTION__ << "()::" << __LINE__ << ",rgp24FilePath:" << rgp24FilePath << std::endl;
    std::cout << "YUV444ptoRGB24::" << __FUNCTION__ << "()::" << __LINE__ << ",yuv444pFilePath:" << yuv444pFilePath << std::endl;
    this->width = width;
    this->height = height;
    this->yuv444pFile = fopen(yuv444pFilePath, "rb"); // 获取yuv444p输出文件指针
    this->rgb24File = fopen(rgp24FilePath, "wb");     // 获取rgp24输入文件指针
    if (rgb24File == NULL || yuv444pFile == NULL)
    {
        return false;
    }
    return true;
}

bool YUV444ptoRGB24::yuv444pToRgb24()
{
    std::cout << "YUV444ptoRGB24::" << __FUNCTION__ << "()::" << __LINE__ << std::endl;
    std::cout << "YUV444ptoRGB24::" << __FUNCTION__ << "()::" << __LINE__ << ",uint8_t sizoeof:" << sizeof(uint8_t) << std::endl;
    std::cout << "YUV444ptoRGB24::" << __FUNCTION__ << "()::" << __LINE__ << ",uint32_t sizoeof:" << sizeof(uint32_t) << std::endl;
    int bytesPerPixel = 24 * 1.0 / 8.0;
    std::cout << "YUV444ptoRGB24::" << __FUNCTION__ << "()::" << __LINE__ << ",bytesPerPixel:" << bytesPerPixel << std::endl;
    uint8_t rgb24Data[width * height * bytesPerPixel];   // 申请读取rbg24文件内存
    uint8_t yuv444pData[width * height * bytesPerPixel]; // 申请保存yuv444p文件内存

    size_t size = fread(yuv444pData, sizeof(yuv444pData), 1, yuv444pFile); // 读取yuv444p文件到内存
    std::cout << "YUV444ptoRGB24::" << __FUNCTION__ << "()::" << __LINE__ << ",size:" << size << std::endl;
    yuv444pToRgb24(yuv444pData, rgb24Data, width, height); // 把内存中yuv444p转化为内存中rgb24
    fwrite(rgb24Data, sizeof(rgb24Data), 1, rgb24File);    // 把内存中的rgb24数据写入rgb24文件中
    freeResource();                                        // 释放资源
    return true;
}

void YUV444ptoRGB24::yuv444pToRgb24(uint8_t *yuv444pData, uint8_t *rgb24Data, int width, int height)
{
    std::cout << "YUV444ptoRGB24::" << __FUNCTION__ << "()::" << __LINE__ << std::endl;
    uint8_t *srcY = yuv444pData, *srcU = srcY + width * height, *srcV = srcU + width * height;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int currentYUVIndex = i * height + j;
            uint8_t Y = srcY[currentYUVIndex], U = srcU[currentYUVIndex], V = srcV[currentYUVIndex];

            int r_val = (int)round(1.164 * (Y - 16) + 1.596 * (V - 128));
            int g_val = (int)round(1.164 * (Y - 16) - 0.813 * (V - 128) - 0.391 * (U - 128));
            int b_val = (int)round(1.164 * (Y - 16) + 2.018 * (U - 128));

            int currentRGBIndex = 3 * (i * width + j);
            rgb24Data[currentRGBIndex] = bound(0, r_val, 255);
            rgb24Data[currentRGBIndex + 1] = bound(0, g_val, 255);
            rgb24Data[currentRGBIndex + 2] = bound(0, b_val, 255);
        }
    }
}

uint8_t YUV444ptoRGB24::bound(uint8_t start, int value, uint8_t end)
{
    // std::cout << "YUV444ptoRGB24::bound()" << std::endl;
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

YUV444ptoRGB24::~YUV444ptoRGB24()
{
    std::cout << "YUV444ptoRGB24::~YUV444ptoRGB24()" << std::endl;
    freeResource();
}

void YUV444ptoRGB24::freeResource()
{
    std::cout << "YUV444ptoRGB24::freeResource()" << std::endl;
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