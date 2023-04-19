#include "TurboJpegHelp.h"

/**
 * @brief yuv转化为jpeg
 *
 * @param argc
 * @param argv
 * @return int
 */
int main(int argc, char *argv[])
{
    const char *TAG = "sample-yuv2jpeg::";
    printf("%s%s():: Line,%d\n", TAG, __FUNCTION__, __LINE__);
    printf("↓↓↓↓↓↓↓↓↓↓ Encode YUV to JPEG ↓↓↓↓↓↓↓↓↓↓\n");
    char *yuv420FileName = "./jepg-resource/ffmpeg-libjpeg-turbo-test-image-yuv420p.yuv";
    FILE *yuv420File = fopen(yuv420FileName, "rb");
    if (!yuv420File)
    {
        printf("%s%s():: Line,%d,open file error:%s\n", TAG, __FUNCTION__, __LINE__, yuv420FileName);
        return 1;
    }

    // int yuv420Width = 1010, yuv420Height = 1324;
    int yuv420Width = 1010, yuv420Height = 1322;
    int yuvSubsample = TJSAMP_420;
    uint8_t *yuv2jpegBuffer;
    unsigned long yuv2JpegSize;

    // 获取yuv420p文件大小
    struct stat yuv420FileStat;
    stat(yuv420FileName, &yuv420FileStat);
    int yuv420FileLen = yuv420FileStat.st_size;
    printf("yuv420 file length: %d\n", yuv420FileLen);

    uint8_t *yuv420Data = (uint8_t *)malloc(yuv420FileLen * sizeof(uint8_t));
    fread(yuv420Data, yuv420FileLen, 1, yuv420File);
    printf("yuv420 read finish!\n");

    tyuv2jpeg(yuv420Data, yuv420FileLen, yuv420Width, yuv420Height, yuvSubsample, &yuv2jpegBuffer, &yuv2JpegSize, 80);
    printf("jpeg data size: %ld\n", yuv2JpegSize);

    FILE *yuv2JpegOutFile = fopen("./resource/libjpeg-turbo-yuv-to-jpeg.jpeg", "wb");
    fwrite(yuv2jpegBuffer, yuv2JpegSize, 1, yuv2JpegOutFile);

    fclose(yuv420File);
    fflush(yuv2JpegOutFile);
    fclose(yuv2JpegOutFile);
    free(yuv420Data);

    printf("↑↑↑↑↑↑↑↑↑↑ Encode YUV to JPEG ↑↑↑↑↑↑↑↑↑↑\n\n");
    return 0;
}