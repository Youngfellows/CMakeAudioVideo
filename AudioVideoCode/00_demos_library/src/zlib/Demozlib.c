#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "zlib.h"

int main(int arg, char **argv)
{
    const char *TAG = "Demozlib";
    printf("%s::main::\n", TAG);
    printf("%s()::%d\n", __FUNCTION__, __LINE__);
    // FILE *inFile = fopen("/Users/hubin/Desktop/0.data", "rb");
    // FILE *outFile = fopen("/Users/hubin/Desktop/0-uncompress.data", "wb");
    FILE *inFile = fopen("./resource/build.zip", "rb");
    FILE *outFile = fopen("./resource/my_build.data", "wb");
    printf("%s()::%d\n", __FUNCTION__, __LINE__);

    fseek(inFile, 0L, SEEK_END);
    long size = ftell(inFile);
    fseek(inFile, 0L, SEEK_SET);
    printf("%s()::%d,size:%ld\n", __FUNCTION__, __LINE__, size);

    printf("%s()::%d,size:%ld\n", __FUNCTION__, __LINE__, size);
    // uint8_t dataBuf[size];
    uint8_t *dataBuf = (uint8_t *)malloc(sizeof(uint8_t) * size);
    printf("%s()::%d,dataBuf:%p\n", __FUNCTION__, __LINE__, dataBuf);

    fread(dataBuf, size, 1, inFile);
    printf("压缩文件大小：%ld\n", size);

    uint8_t destBuf[1500000] = {0};
    uint32_t destLen = 0;

    printf("HERE\n");
    uncompress(destBuf, &destLen, dataBuf, size);
    printf("解压后大小：%d\n", destLen);

    printf("HERE\n");
    fwrite(destBuf, destLen, 1, outFile);

    fflush(outFile);
    fclose(inFile);
    fclose(outFile);
    free(dataBuf);

    return 0;
}