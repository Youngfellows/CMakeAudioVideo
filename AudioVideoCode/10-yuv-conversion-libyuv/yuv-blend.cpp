//
// Created by hubin on 2019/9/20.
//
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "libyuv.h"
#include <iostream>

using namespace libyuv;

// const uint8_t* src_y0,
// int src_stride_y0,
// const uint8_t* src_u0,
// int src_stride_u0,
// const uint8_t* src_v0,
// int src_stride_v0,
// const uint8_t* src_y1,
// int src_stride_y1,
// const uint8_t* src_u1,
// int src_stride_u1,
// const uint8_t* src_v1,
// int src_stride_v1,
// const uint8_t* alpha,
// int alpha_stride,
// uint8_t* dst_y,
// int dst_stride_y,
// uint8_t* dst_u,
// int dst_stride_u,
// uint8_t* dst_v,
// int dst_stride_v,
// int width,
// int height

void blend(uint8_t *srcYuvData, uint8_t *dstYuvData, int width, int height)
{
    uint8_t YUV_ROTATION[width * height * 3 / 2];
    std::cout << __FUNCTION__ << ",Line " << __LINE__ << std::endl;
    I420Rotate(
        srcYuvData,
        width,
        srcYuvData + width * height,
        (width + 1) / 2,
        srcYuvData + width * height + ((width + 1) / 2) * ((height + 1) / 2),
        (width + 1) / 2,
        YUV_ROTATION,
        width,
        YUV_ROTATION + width * height,
        (width + 1) / 2,
        YUV_ROTATION + width * height + ((width + 1) / 2) * ((height + 1) / 2),
        (width + 1) / 2,
        width,
        height,
        kRotate90);

    std::cout << __FUNCTION__ << ",Line " << __LINE__ << std::endl;
    uint8_t alpha[width * height];
    memset(alpha, 0X88, width * height);

    std::cout << __FUNCTION__ << ",Line " << __LINE__ << std::endl;

    I420Blend(
        srcYuvData,
        width,
        srcYuvData + width * height,
        (width + 1) / 2,
        srcYuvData + width * height + ((width + 1) / 2) * ((height + 1) / 2),
        (width + 1) / 2,
        YUV_ROTATION,
        width,
        YUV_ROTATION + width * height,
        (width + 1) / 2,
        YUV_ROTATION + width * height + ((width + 1) / 2) * ((height + 1) / 2),
        (width + 1) / 2,
        alpha,
        width,
        dstYuvData,
        width,
        dstYuvData + width * height,
        (width + 1) / 2,
        dstYuvData + width * height + ((width + 1) / 2) * ((height + 1) / 2),
        (width + 1) / 2,
        width,
        height);

    //    I420Interpolate()
}

int main(int arg, char **argv)
{
    const char *TAG = "yuv-blend::";
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
    std::string yuvBlendFileName = "./resource/rainbow_" + std::to_string(width) + "x" + std::to_string(height) + "_yuv420p-blend.yuv";
    const char *yuv420pFilePath = yuv420pFileName.c_str();   // string 转化为字符串
    const char *yuvBlendFilePath = yuvBlendFileName.c_str(); // string 转化为字符串

    // uint32_t width = 700, height = 700;

    uint8_t YUV[width * height * 3 / 2];       // 申请内存
    uint8_t YUV_BLEND[width * height * 3 / 2]; // 申请内存

    // FILE *yuv420pFile = fopen("/Users/hubin/Desktop/rainbow-yuv420p.yuv", "rb");
    FILE *yuv420pFile = fopen(yuv420pFilePath, "rb");
    std::cout << TAG << __FUNCTION__ << ",Line " << __LINE__ << std::endl;
    fread(YUV, sizeof(YUV), 1, yuv420pFile);

    std::cout << TAG << __FUNCTION__ << ",Line " << __LINE__ << std::endl;
    blend(YUV, YUV_BLEND, width, height);
    std::cout << TAG << __FUNCTION__ << ",Line " << __LINE__ << std::endl;

    // FILE *yuvBlendFile = fopen("/Users/hubin/Desktop/rainbow-yuv420p-blend.yuv", "wb");
    FILE *yuvBlendFile = fopen(yuvBlendFilePath, "wb");
    fwrite(YUV_BLEND, sizeof(YUV_BLEND), 1, yuvBlendFile);

    fclose(yuvBlendFile);
    fclose(yuv420pFile);

    return 0;
}