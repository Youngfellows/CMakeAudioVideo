//
// Created by hubin on 2019/9/20.
//
#include <stdio.h>
#include <stdint.h>
#include "libyuv.h"
#include <iostream>

using namespace libyuv;

void scale(uint8_t *srcYuvData, uint8_t *dstYuvData, int width, int height, int dstWidth, int dstHeight)
{
    I420Scale(
        srcYuvData,
        width,
        srcYuvData + width * height,
        (width + 1) / 2,
        srcYuvData + width * height + ((width + 1) / 2) * ((height + 1) / 2),
        (width + 1) / 2,
        width,
        height,
        dstYuvData,
        dstWidth,
        dstYuvData + dstWidth * dstWidth,
        (dstWidth + 1) / 2,
        dstYuvData + dstWidth * dstHeight + ((dstWidth + 1) / 2) * ((dstHeight + 1) / 2),
        (dstWidth + 1) / 2,
        dstWidth,
        dstHeight,
        kFilterBox);
}

int main(int arg, char **argv)
{
    const char *TAG = "yuv-scale::";
    std::cout << TAG << __FUNCTION__ << ",Line " << __LINE__ << ",arg:" << arg << std::endl;
    if (arg < 3)
    {
        std::cout << TAG << __FUNCTION__ << ",Line " << __LINE__ << ",使用: " << argv[0] << " 宽 高" << std::endl;
        std::cout << TAG << __FUNCTION__ << ",Line " << __LINE__ << ",使用: " << argv[0] << " 711 711" << std::endl;
        return 1;
    }
    uint32_t width = atoi(argv[1]);  // 宽
    uint32_t height = atoi(argv[2]); // 高

    // int width = 700, height = 700;
    std::string yuv420pFileName = "./res/rainbow_" + std::to_string(width) + "x" + std::to_string(height) + "_bmp_yuv420p.yuv";
    std::string yuvScaleFileName = "./resource/rainbow_" + std::to_string(width) + "x" + std::to_string(height) + "_yuv420p_scale_6.yuv";
    const char *yuv420pFilePath = yuv420pFileName.c_str();   // string 转化为字符串
    const char *yuvScaleFilePath = yuvScaleFileName.c_str(); // string 转化为字符串

    // uint32_t width = 700, height = 700;
    uint32_t dstWidth = 100, dstHeight = 100;
    uint8_t YUV[width * height * 3 / 2];
    uint8_t YUV_SCALE[dstWidth * dstHeight * 3 / 2];

    // FILE *yuv420pFile = fopen("/Users/hubin/Desktop/rainbow-yuv420p.yuv", "rb");
    FILE *yuv420pFile = fopen(yuv420pFilePath, "rb");
    fread(YUV, sizeof(YUV), 1, yuv420pFile);

    scale(YUV, YUV_SCALE, width, height, dstWidth, dstHeight);

    // FILE *yuvScaleFile = fopen("/Users/hubin/Desktop/rainbow-yuv420p-scale-6.yuv", "wb");
    FILE *yuvScaleFile = fopen(yuvScaleFilePath, "wb");
    fwrite(YUV_SCALE, sizeof(YUV_SCALE), 1, yuvScaleFile);

    fclose(yuvScaleFile);
    fclose(yuv420pFile);

    return 0;
}