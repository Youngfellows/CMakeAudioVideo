#include "../../include/ZArchiver.h"
#include <iostream>

using namespace std;

/**
 * @brief zlib压缩,解压缩库使用
 *
 * @param arg
 * @param argv
 * @return int
 */
int main(int arg, char **argv)
{
    const char *TAG = "DemoZLib::";
    std::cout << TAG << __FUNCTION__ << ",LINE " << __LINE__ << std::endl;

    // FILE *inFile = fopen("/Users/hubin/Desktop/0.data", "rb");
    // FILE *outFile = fopen("/Users/hubin/Desktop/0-uncompress.data", "wb");
    FILE *inFile = fopen("./resource/test1.ppm", "rb");
    FILE *outFile = fopen("./resource/un_test1.ppm", "wb");
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
    // uint32_t destLen = 0;
    long unsigned int destLen = 0;

    printf("HERE\n");
    // uncompress(destBuf, &destLen, dataBuf, size);
    unCompress(destBuf, &destLen, dataBuf, size);
    printf("解压后大小：%d\n", destLen);

    printf("HERE\n");
    fwrite(destBuf, destLen, 1, outFile);

    fflush(outFile);
    fclose(inFile);
    fclose(outFile);
    free(dataBuf);

    return 0;
}
