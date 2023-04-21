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
    const char *TAG = "sample-encode3-jpeg::";
    printf("%s%s():: Line,%d\n", TAG, __FUNCTION__, __LINE__);
    printf("↓↓↓↓↓↓↓↓↓↓ Encode RGB24 to JPEG ↓↓↓↓↓↓↓↓↓↓\n");
    char *inJpegName1 = "./jepg-resource/libjpeg-turbo-test-image.jpg";
    char *outJpegName2 = "./resource/libjpeg-turbo-test-image-rgb24.jpg";
    struct ImageData imageData; // jpeg图片转化为rgb图像信息
    int width;                  // 图片宽
    int height;                 // 图片高
    int flag1 = decode_JPEG_file2(inJpegName1, &imageData);
    if (flag1 == 0)
    {
        printf("decode ok!\n");
    }
    else
    {
        printf("decode error!\n");
    }
    width = imageData.width;
    height = imageData.height;
    int per_pixel_byte = imageData.per_pixel_byte;
    printf("%s%s():: Line,%d,width:%d,height:%d,per_pixel_byte:%d\n", TAG, __FUNCTION__, __LINE__, width, height, per_pixel_byte);
    int size = width * height * per_pixel_byte;
    uint8_t *rgbBuffer = malloc(size); // 申请内存空间
    if (!rgbBuffer)
    {
        printf("rgbBuffer is null");
        return 1;
    }
    // 拷贝内存中的数据
    memcpy(rgbBuffer, imageData.pixels, size);
    free(imageData.pixels); // 释放内存

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