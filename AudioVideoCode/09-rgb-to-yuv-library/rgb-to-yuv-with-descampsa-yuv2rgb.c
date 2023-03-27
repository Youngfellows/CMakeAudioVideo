//
// Created by hubin on 2019/9/19.
//
#include <stdio.h>
#include "yuv_rgb.h"

void rgb24ToYuv420p(uint8_t *RGB, uint8_t *YUV, uint32_t width, uint32_t height)
{
    const YCbCrType yuv_format = YCBCR_601;
    //    const YCbCrType yuv_format = YCBCR_709;
    // const YCbCrType yuv_format = YCBCR_JPEG;

    rgb24_yuv420_std(
        width,
        height,
        RGB,
        width * 3,
        YUV,
        YUV + width * height,
        YUV + width * height + ((width + 1) / 2) * ((height + 1) / 2),
        width,
        width / 2,
        yuv_format);
}

int main(int arg, char **argv)
{
    const char *TAG = "rgb-to-yuv-with-descampsa-yuv2rgb";
    // printf("\n%s::%s():: Line:%d,arg:%d\n", __FILE__, __FUNCTION__, __LINE__, arg);
    printf("\n%s::%s():: Line:%d,arg:%d\n", TAG, __FUNCTION__, __LINE__, arg);
    if (arg < 3)
    {
        printf("n%s::%s():: Line:%d,使用:%s 宽 高\n", TAG, __FUNCTION__, __LINE__, argv[0]);
        printf("n%s::%s():: Line:%d,使用:%s 711 711\n", TAG, __FUNCTION__, __LINE__, argv[0]);
        return 1;
    }
    // uint32_t width = atoi(argv[1]);  // 宽
    // uint32_t height = atoi(argv[2]); // 高
    // printf("width:%d,height:%d\n", width, height);

    uint32_t width = 700, height = 700;
    uint8_t RGB[width * height * 3];
    uint8_t YUV[width * height * 3 / 2];

    FILE *rgb24File = fopen("/Users/hubin/Desktop/rainbow-rgb24.rgb", "rb");
    fread(RGB, sizeof(RGB), 1, rgb24File);

    rgb24ToYuv420p(RGB, YUV, width, height);

    FILE *yuvFile = fopen("/Users/hubin/Desktop/rainbow-rgb24-to-yuv420p-descampsa.yuv", "wb");
    fwrite(YUV, sizeof(YUV), 1, yuvFile);

    fclose(rgb24File);
    fclose(yuvFile);
    return 0;
}