#include "./include/TurboJpegHelp.h"

/**
 * @brief rgb24编码为jpeg
 *
 * @param argc
 * @param argv
 * @return int
 */
int main(int argc, char *argv[])
{
    const char *TAG = "sample-encode2-jpeg::";
    printf("%s%s():: Line,%d\n", TAG, __FUNCTION__, __LINE__);
    printf("↓↓↓↓↓↓↓↓↓↓ Encode RGB24 to JPEG ↓↓↓↓↓↓↓↓↓↓\n");
    // int width = 1010, height = 1324;
    int width = 711, height = 711;
    char *inJpegName1 = "./jepg-resource/ffmpeg-libjpeg-turbo-test-image-rgg24.rgb";
    // char *inJpegName1 = "./jepg-resource/libjpeg-turbo-test-image-rgb24.rgb";
    // char *inJpegName1 = "./jepg-resource/rainbow_711x711_bmp_rgb24.rgb";
    char *outJpegName2 = "./resource/ffmpeg-libjpeg-turbo-test-image-rgg24.jpg";
    uint8_t *rgbBuffer = malloc(width * height * 3);
    if (!rgbBuffer)
    {
        printf("rgbBuffer is null");
        return 1;
    }

    // 打开rgb24源文件
    FILE *fileInput = fopen(inJpegName1, "rb");
    if (!fileInput)
    {
        printf("open file error:%s\n", inJpegName1);
        return 2;
    }
    int size = width * height * 3;
    // 读取rgb24源文件
    fread(rgbBuffer, size, 1, fileInput);
    // 关闭文件
    fclose(fileInput);

    // 有bug，不能还原原图片,应该要做大小端转化(猜测的)
    int flag2 = encode_JPEG_file(outJpegName2, rgbBuffer, width, height, 80);
    if (flag2 == 0)
    {
        printf("encode ok!\n");
    }
    else
    {
        printf("encode error!\n");
    }
    free(rgbBuffer);
    printf("↑↑↑↑↑↑↑↑↑↑ Encode RGB24 to JPEG ↑↑↑↑↑↑↑↑↑↑\n\n");
    return 0;
}