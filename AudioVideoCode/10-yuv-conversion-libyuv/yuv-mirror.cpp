//
// Created by hubin on 2019/9/21.
//
#include <stdio.h>
#include <stdint.h>
#include "libyuv.h"
#include <iostream>

using namespace libyuv;

// const uint8_t* src_y,
// int src_stride_y,
// const uint8_t* src_u,
// int src_stride_u,
// const uint8_t* src_v,
// int src_stride_v,
// uint8_t* dst_y,
// int dst_stride_y,
// uint8_t* dst_u,
// int dst_stride_u,
// uint8_t* dst_v,
// int dst_stride_v,
// int width,
// int height
void mirror(uint8_t *srcYuvData, uint8_t *dstYuvData, int width, int height)
{
    I420Mirror(
        srcYuvData,
        width,
        srcYuvData + width * height,
        (width + 1) / 2,
        srcYuvData + width * height + ((width + 1) / 2) * ((height + 1) / 2),
        (width + 1) / 2,
        dstYuvData,
        width,
        dstYuvData + width * height,
        (width + 1) / 2,
        dstYuvData + width * height + ((width + 1) / 2) * ((height + 1) / 2),
        (width + 1) / 2,
        width,
        height);
}

int main(int arg, char **argv)
{
    const char *TAG = "yuv-mirror::";
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
    std::string yuvRotationFileName = "./resource/rainbow_" + std::to_string(width) + "x" + std::to_string(height) + "_yuv420p_rotation_90_mirror.yuv";
    const char *yuv420pFilePath = yuv420pFileName.c_str();         // string 转化为字符串
    const char *yuvRotationFilePath = yuvRotationFileName.c_str(); // string 转化为字符串

    // uint32_t width = 700, height = 700;
    uint8_t YUV[width * height * 3 / 2];
    uint8_t YUV_MIRROR[width * height * 3 / 2];

    // FILE *yuv420pFile = fopen("/Users/hubin/Desktop/rainbow-yuv420p-rotation-90.yuv", "rb");
    FILE *yuv420pFile = fopen(yuv420pFilePath, "rb");
    fread(YUV, sizeof(YUV), 1, yuv420pFile);

    mirror(YUV, YUV_MIRROR, width, height);

    // FILE *yuvRotationFile = fopen("/Users/hubin/Desktop/rainbow-yuv420p-rotation-90-mirror.yuv", "wb");
    FILE *yuvRotationFile = fopen(yuvRotationFilePath, "wb");
    fwrite(YUV_MIRROR, sizeof(YUV_MIRROR), 1, yuvRotationFile);

    fclose(yuvRotationFile);
    fclose(yuv420pFile);

    return 0;
}