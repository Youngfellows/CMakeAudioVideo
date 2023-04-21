#include "TurboJpegHelp.h"

/**
 * @brief jpeg转化为yuv
 *
 * @param argc
 * @param argv
 * @return int
 */
int main(int argc, char *argv[])
{
    const char *TAG = "sample-jpeg2yuv::";
    printf("%s%s():: Line,%d\n", TAG, __FUNCTION__, __LINE__);
    printf("↓↓↓↓↓↓↓↓↓↓ Decode JPEG to YUV ↓↓↓↓↓↓↓↓↓↓\n");
    char *inJpegName3 = "./jepg-resource/libjpeg-turbo-test-image.jpg";

    FILE *jpegFile = fopen(inJpegName3, "rb");
    printf("%s%s():: Line,%d\n", TAG, __FUNCTION__, __LINE__);
    fseek(jpegFile, 0, SEEK_END);   // 定位到文件末
    long fileLen = ftell(jpegFile); // 文件长度
    fseek(jpegFile, 0, SEEK_SET);
    printf("fileLength1: %ld\n", fileLen);

    // 获取文件大小有bug，不准确
    struct stat statbuf;
    stat(inJpegName3, &statbuf);
    fileLen = statbuf.st_size;
    printf("fileLength2: %ld\n", fileLen);

    // uint8_t jpegData[fileLen];
    printf("%s%s():: Line,%d,sizeof(uint8_t):%d\n", TAG, __FUNCTION__, __LINE__, sizeof(uint8_t));
    uint8_t *jpegData = (uint8_t *)malloc(sizeof(uint8_t) * fileLen);
    printf("%s%s():: Line,%d,jpegData:%p\n", TAG, __FUNCTION__, __LINE__, jpegData);
    if (jpegData == NULL)
    {
        printf("%s%s():: Line,%d,jpegData is null\n", TAG, __FUNCTION__, __LINE__);
        return 1;
    }

    fread(jpegData, fileLen, 1, jpegFile);
    printf("%s%s():: Line,%d\n", TAG, __FUNCTION__, __LINE__);
    fclose(jpegFile);
    printf("%s%s():: Line,%d\n", TAG, __FUNCTION__, __LINE__);

    uint8_t *yuvData;
    int yuvSize;
    int yuvType;
    printf("%s%s():: Line,%d\n", TAG, __FUNCTION__, __LINE__);
    tjpeg2yuv(jpegData, fileLen, &yuvData, &yuvSize, &yuvType);
    printf("%s%s():: Line,%d\n", TAG, __FUNCTION__, __LINE__);
    printf("size: %d; type: %d\n", yuvSize, yuvType);

    char *yuvSuffix;
    if (yuvType == TJSAMP_444)
    {
        yuvSuffix = "-yuv444";
    }
    else if (yuvType == TJSAMP_422)
    {
        yuvSuffix = "-yuv422";
    }
    else if (yuvType == TJSAMP_420)
    {
        yuvSuffix = "-yuv420";
    }
    else if (yuvType == TJSAMP_GRAY)
    {
        yuvSuffix = "-yuv-gray";
    }
    else if (yuvType == TJSAMP_440)
    {
        yuvSuffix = "-yuv440";
    }
    else if (yuvType == TJSAMP_411)
    {
        yuvSuffix = "-yuv411";
    }
    else
    {
        printf("Unsupported type!");
        return -1;
    }
    printf("yuv samp: %s\n", yuvSuffix);
    char yuvFileName[100];
    sprintf(yuvFileName, "./resource/libjpeg-turbo-test-image%s.yuv", yuvSuffix);
    FILE *yuvFile = fopen(yuvFileName, "wb");
    fwrite(yuvData, yuvSize, 1, yuvFile);

    free(jpegData);
    free(yuvData);
    fflush(yuvFile);
    fclose(yuvFile);
    printf("↑↑↑↑↑↑↑↑↑↑ Decode JPEG to YUV ↑↑↑↑↑↑↑↑↑↑\n\n");
}