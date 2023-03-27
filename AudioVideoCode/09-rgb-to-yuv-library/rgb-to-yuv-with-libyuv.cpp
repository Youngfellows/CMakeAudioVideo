//
// Created by hubin on 2019/9/19.
//

#include <stdio.h>
#include "libyuv.h"
#include <iostream>

using namespace libyuv;

void libyuv_Rgb24_to_Yuv420p(const char *rgbFileName, const char *yuvFileName, int width, int height)
{
    FILE *rgb_file = fopen(rgbFileName, "rb");
    FILE *yuv_file = fopen(yuvFileName, "wb");

    int size_rgb = width * height * 3;
    int size_yuv = width * height * 3 / 2;
    uint8_t *buffer_rgb = (uint8_t *)malloc(size_rgb);
    uint8_t *buffer_yuv = (uint8_t *)malloc(size_yuv);

    fread(buffer_rgb, 1, size_rgb, rgb_file);

    // RGB to BGR
    //    uint8_t temp;
    //    for(int i = 0; i < size_rgb; i+=3) {
    //        temp = buffer_rgb[i + 0];
    //        buffer_rgb[i + 0] = buffer_rgb[i + 2];
    //        buffer_rgb[i + 2] = temp;
    //    }

    //    RGB24ToI420(
    RAWToI420(
        buffer_rgb, width * 3,
        buffer_yuv, width,
        buffer_yuv + width * height, (width + 1) / 2,
        buffer_yuv + width * height + ((width + 1) / 2) * ((height + 1) / 2), (width + 1) / 2,
        width, height);

    fwrite(buffer_yuv, 1, size_yuv, yuv_file);

    free(buffer_rgb);
    free(buffer_yuv);
    fclose(yuv_file);
    fclose(rgb_file);
}

int main(int arg, char **argv)
{
    const char *TAG = "rgb-to-yuv-with-libyuv::";
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
    std::string rgb24File = "./res/rainbow_" + std::to_string(width) + "x" + std::to_string(height) + "_bmp_rgb24.rgb";
    std::string yuv420pFile = "./resource/rainbow_" + std::to_string(width) + "x" + std::to_string(height) + "_rgb24-to-yuv420p-libyuv.yuv";
    const char *rgb24FilePath = rgb24File.c_str();     // string 转化为字符串
    const char *yuv420pFilePath = yuv420pFile.c_str(); // string 转化为字符串

    libyuv_Rgb24_to_Yuv420p(rgb24FilePath, yuv420pFilePath, width, height);
    return 0;
}