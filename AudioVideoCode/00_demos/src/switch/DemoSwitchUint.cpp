#include "SwitchUint.h"

#include <stdio.h>
#include <stdlib.h>

/**
 * @brief 1.  判断是 大端字节序 OR 小端字节序
 * @brief 2.  16 位字节序转换
 * @brief 3.  32 位字节序转换
 *
 * @param arg
 * @param argv
 * @return int
 */
int main(int arg, char **argv)
{
    const char *TAG = "DemoSwitchUint::";
    printf("%s%s():: Line %d\n", TAG, __FUNCTION__, __LINE__);

    // 1. 查看字节序
    if (isBigEndianOrder())
    {
        printf("%s%s():: Line %d,大端字节序\n", TAG, __FUNCTION__, __LINE__);
    }
    else
    {
        printf("%s%s():: Line %d,小端字节序\n", TAG, __FUNCTION__, __LINE__);
    }

    // 2. 查看一个int整数的4个字节在内存中的二进制(或者十六进制)
    // （1）在C语言中使用格式说明符%d表示输出十进制，%o表示输出八进制，%x或%X表示输出十六进制。
    // （2）如果要带有前缀的输出八进制或十六进制，需要在格式说明符中加#。

    int width = 711;
    int size = sizeof(width);
    printf("%s%s():: Line %d,size:%d\n", TAG, __FUNCTION__, __LINE__, size);
    uint8_t *dataBytes = (uint8_t *)malloc(sizeof(uint8_t) * size); // 申请内存
    uint32Bytes(width, dataBytes);                                  // 获取32位4字节整数的二进制数
    for (int i = 0; i < size; i++)
    {
        uint8_t byte = *(dataBytes + i);
        // uint8_t byte = dataBytes[i];
        printf("%s%s():: Line %d,i:%d,八进制:%#o,十六进制:%#x\n", TAG, __FUNCTION__, __LINE__, i, byte, byte);
    }
    free(dataBytes); // 释放内存

    // 3. 将一个整数按字节转化后保存到文件
    const char *filePath = "./resource/numer_711.data"; // 文件路径
    FILE *fp = fopen(filePath, "wb");                   // 打开文件
    if (!fp)
    {
        printf("%s%s():: Line %d,打开文件错误:%s\n", TAG, __FUNCTION__, __LINE__, filePath);
        return -1;
    }
    uint32_t number = switchUint32(width); // 将4字节整数,32位字节序转换
    printf("%s%s():: Line %d,width:%d,number:%d\n", TAG, __FUNCTION__, __LINE__, width, number);
    fwrite(&number, 1, sizeof(number), fp); // 将4字节整数711写入文件,ok::  00 00 02 c7
    fclose(fp);                             // 关闭文件

    // 4. 读取文件中的4字节数据并转化位4字节整数
    FILE *file = fopen(filePath, "rb"); // 打开文件
    int length = getFileSize(filePath); // 获取文件大小
    printf("%s%s():: Line %d,文件大小:%d\n", TAG, __FUNCTION__, __LINE__, length);
    if (length < 4)
    {
        perror("文件是损坏了的\n");
        printf("%s%s():: Line %d,文件是损坏了的:%s\n", TAG, __FUNCTION__, __LINE__, filePath);
        return -2;
    }
    uint8_t *buffer = (uint8_t *)malloc(length);  // 申请length长度连续内存空间
    int readNum = fread(buffer, 1, length, file); // 读取文件内容到内存
    if (readNum != length)
    {
        perror("读取文件错误\n");
        printf("%s%s():: Line %d,读取文件错误:%s\n", TAG, __FUNCTION__, __LINE__, filePath);
        return -3;
    }
    printf("%s%s():: Line %d,读取文件成功:%s\n", TAG, __FUNCTION__, __LINE__, buffer);

    // 将读取到4字节数据转化为整数
    for (int i = 0; i < sizeof(uint32_t); i++)
    {
        // uint8_t byte = buffer[i];
        uint8_t byte = *(buffer + i);
        printf("%s%s():: Line %d,i:%d,八进制:%#o,十六进制:%#x\n", TAG, __FUNCTION__, __LINE__, i, byte, byte);
    }
    uint32_t numData = byteToUint32(buffer); // 将读取到4字节数据转化为整数
    printf("%s%s():: Line %d,转化4字节为整数成功:%d\n", TAG, __FUNCTION__, __LINE__, numData);
    fclose(file); // 关闭文件
    free(buffer); // 释放内存
    return 0;
}