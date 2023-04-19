#include "./include/TurboJpegHelp.h"

/**
 * @brief jpeg格式解码为rgb24
 */
int main(int arg, char **argv)
{
    const char *TAG = "sample-decode-jpeg::";
    printf("%s%s():: Line,%d\n", TAG, __FUNCTION__, __LINE__);
    printf("↓↓↓↓↓↓↓↓↓↓ Decode JPEG to RGB24 ↓↓↓↓↓↓↓↓↓↓\n");
    char *inJpegName1 = "./jepg-resource/libjpeg-turbo-test-image.jpg";
    char *outRgbName1 = "./resource/libjpeg-turbo-test-image-rgb24.rgb";
    int flag1 = decode_JPEG_file(inJpegName1, outRgbName1);
    if (flag1 == 0)
    {
        printf("decode ok!\n");
    }
    else
    {
        printf("decode error!\n");
    }
    printf("↑↑↑↑↑↑↑↑↑↑ Decode JPEG to RGB24 ↑↑↑↑↑↑↑↑↑↑\n\n");
    return 0;
}
