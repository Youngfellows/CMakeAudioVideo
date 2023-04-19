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
    const char *TAG = "sample-encode-jpeg::";
    printf("%s%s():: Line,%d\n", TAG, __FUNCTION__, __LINE__);
    printf("↓↓↓↓↓↓↓↓↓↓ Encode RGB24 to JPEG ↓↓↓↓↓↓↓↓↓↓\n");
    int width = 700, height = 700;
    char *outJpegName2 = "./resource/rainbow-rgb24.jpeg";
    // uint8_t rgbBuffer[width*height*3];
    uint8_t *rgbBuffer = malloc(width * height * 3);
    genRGB24Data(rgbBuffer, width, height);
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
}