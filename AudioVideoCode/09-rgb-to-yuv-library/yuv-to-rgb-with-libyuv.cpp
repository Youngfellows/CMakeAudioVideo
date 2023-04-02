//
// Created by hubin on 2019/9/19.
//

#include <stdio.h>
#include <stdint.h>
#include "libyuv.h"
#include <iostream>

using namespace libyuv;

void libyuv_I444_to_Rgb(const char *srcFileName, const char *dstFileName, int width, int height)
{
    std::cout << __FUNCTION__ << "()::,Line " << __LINE__ << std::endl;
    FILE *src_file = fopen(srcFileName, "rb");
    FILE *dst_file = fopen(dstFileName, "wb");
    std::cout << __FUNCTION__ << "()::,Line " << __LINE__ << std::endl;

    int size_src = width * height * 3;
    int size_dest = width * height * 4;
    char *buffer_src = (char *)malloc(size_src);
    char *buffer_dest = (char *)malloc(size_dest);

    std::cout << __FUNCTION__ << "()::,Line " << __LINE__ << std::endl;
    fread(buffer_src, 1, size_src, src_file);
    std::cout << __FUNCTION__ << "()::,Line " << __LINE__ << std::endl;

    I444ToARGB((const uint8_t *)buffer_src, width,
               (const uint8_t *)(buffer_src + width * height), width,
               (const uint8_t *)(buffer_src + 2 * width * height), width,
               (uint8_t *)buffer_dest, width * 4,
               width, height);
    std::cout << __FUNCTION__ << "()::,Line " << __LINE__ << std::endl;

    fwrite(buffer_dest, 1, size_dest, dst_file);

    free(buffer_src);
    free(buffer_dest);
    fclose(dst_file);
    fclose(src_file);
}

int main(int arg, char **argv)
{
    const char *TAG = "yuv-to-rgb-with-libyuv::";
    std::cout << TAG << __FUNCTION__ << "()::,Line " << __LINE__ << ",arg:" << arg << std::endl;
    if (arg < 3)
    {
        std::cout << TAG << __FUNCTION__ << "()::,Line " << __LINE__ << ",使用: " << argv[0] << " 宽 高" << std::endl;
        std::cout << TAG << __FUNCTION__ << "()::,Line " << __LINE__ << ",使用: " << argv[0] << " 711 711" << std::endl;
        return 1;
    }
    uint32_t width = atoi(argv[1]);  // 宽
    uint32_t height = atoi(argv[2]); // 高

    std::cout << __FUNCTION__ << "()::,Line " << __LINE__ << std::endl;
    // int width = 700, height = 700;
    std::string yuv444pFile = "./res/rainbow_" + std::to_string(width) + "x" + std::to_string(height) + "_bmp_yuv444p.yuv";
    std::string rgb24File = "./resource/rainbow_" + std::to_string(width) + "x" + std::to_string(height) + "_yuv444p-to-rgb32-libyuv.rgb";
    std::cout << __FUNCTION__ << "()::,Line " << __LINE__ << std::endl;
    const char *rgb24FilePath = rgb24File.c_str();     // string 转化为字符串
    const char *yuv444pFilePath = yuv444pFile.c_str(); // string 转化为字符串
    std::cout << __FUNCTION__ << "()::,Line " << __LINE__ << std::endl;

    libyuv_I444_to_Rgb(yuv444pFilePath, rgb24FilePath, width, height);
    return 0;
}