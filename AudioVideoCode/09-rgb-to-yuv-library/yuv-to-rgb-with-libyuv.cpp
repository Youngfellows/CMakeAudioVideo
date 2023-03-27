//
// Created by hubin on 2019/9/19.
//

#include <stdio.h>
#include <stdint.h>
#include "libyuv.h"
#include <iostream>

using namespace libyuv;

void libyuv_I444_to_Rgb(char *srcFileName, char *dstFileName, int width, int height)
{
    FILE *src_file = fopen(srcFileName, "rb");
    FILE *dst_file = fopen(dstFileName, "wb");

    int size_src = width * height * 3;
    int size_dest = width * height * 4;
    char *buffer_src = (char *)malloc(size_src);
    char *buffer_dest = (char *)malloc(size_dest);

    fread(buffer_src, 1, size_src, src_file);

    I444ToARGB((const uint8_t *)buffer_src, width,
               (const uint8_t *)(buffer_src + width * height), width,
               (const uint8_t *)(buffer_src + 2 * width * height), width,
               (uint8_t *)buffer_dest, width * 4,
               width, height);

    fwrite(buffer_dest, 1, size_dest, dst_file);

    free(buffer_src);
    free(buffer_dest);
    fclose(dst_file);
    fclose(src_file);
}

int main(int arg, char **argv)
{
    const char *TAG = "yuv-to-rgb-with-libyuv";
    std::cout << TAG << __FUNCTION__ << ",Line " << __LINE__ << ",arg:" << arg << std::endl;
    if (arg < 3)
    {
        std::cout << TAG << __FUNCTION__ << ",Line " << __LINE__ << ",使用: " << argv[0] << " 宽 高" << std::endl;
        std::cout << TAG << __FUNCTION__ << ",Line " << __LINE__ << ",使用: " << argv[0] << " 711 711" << std::endl;
        return 1;
    }
    // uint32_t width = atof(argv[1]);  // 宽
    // uint32_t height = atof(argv[2]); // 高

    int width = 700, height = 700;
    libyuv_I444_to_Rgb("/Users/hubin/Desktop/rainbow-yuv444p.yuv", "/Users/hubin/Desktop/rainbow-yuv444p-to-rgb32-libyuv.yuv", width, height);
    return 0;
}