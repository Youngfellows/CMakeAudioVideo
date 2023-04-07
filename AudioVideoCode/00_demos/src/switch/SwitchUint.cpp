#include "SwitchUint.h"
// #include "../../include/SwitchUint.h"

/**
 * @brief 判断是 大端字节序 OR 小端字节序
 *
 * @return true
 * @return false
 */
bool isBigEndianOrder()
{
    int iVal = 1;
    char *pChar = (char *)(&iVal);
    if (*pChar == 1)
        return false; //(0x01000000) Windows 采用的是小端法
    else
        return true; //(0x00000001)  Aix采用的是大端法
}

/**
 * @brief 16 位字节序转换
 *
 * @param s
 * @return uint16_t
 */
uint16_t switchUint16(uint16_t s)
{
    return ((s & 0x00FF) << 8) | ((s & 0xFF00) >> 8);
}

/**
 * @brief 32 位字节序转换
 *
 * @param i
 * @return uint32_t
 */
uint32_t switchUint32(uint32_t i)
{
    return ((i & 0x000000FF) << 24) | ((i & 0x0000FF00) << 8) | ((i & 0x00FF0000) >> 8) | ((i & 0xFF000000) >> 24);
}

/**
 * @brief 获取32位整数在内存中的4字节数据
 *
 * @param s 32位的4字节整数
 * @param bytes 申请的4字节连续内存空间
 * @return true
 * @return false
 */
bool uint32Bytes(uint32_t s, uint8_t *bytes)
{
    const char *TAG = "SwitchUint::";
    if (bytes == NULL)
    {
        return false;
    }
    printf("%s%s():: Line %d,s:%d\n", TAG, __FUNCTION__, __LINE__, s);
    // 获取每个字节的二进制数
    uint8_t byte1 = (s & 0xff000000) >> 24; // 获取4字节中的第1个字节
    uint8_t byte2 = (s & 0x00ff0000) >> 16; // 获取4字节中的第2个字节
    uint8_t byte3 = (s & 0x0000ff00) >> 8;  // 获取4字节中的第3个字节
    uint8_t byte4 = (s & 0x000000ff) >> 0;  // 获取4字节中的第4个字节
    // printf("%s%s():: Line %d,%d\n", TAG, __FUNCTION__, __LINE__, byte1);
    // printf("%s%s():: Line %d,%d\n", TAG, __FUNCTION__, __LINE__, byte2);
    // printf("%s%s():: Line %d,%d\n", TAG, __FUNCTION__, __LINE__, byte3);
    // printf("%s%s():: Line %d,%d\n", TAG, __FUNCTION__, __LINE__, byte4);
    // printf("\n");

    for (int i = 0; i < sizeof(uint32_t); i++)
    {
        if (i == 0)
        {
            // bytes[i] = s & 0xff000000 >> 24; // 获取4字节中的第1个字节
            *(bytes + i) = (s & 0xff000000) >> 24; // 获取4字节中的第1个字节
        }
        else if (i == 1)
        {
            // bytes[i] = (s & 0x00ff0000) >> 16; // 获取4字节中的第2个字节
            *(bytes + i) = (s & 0x00ff0000) >> 16; // 获取4字节中的第2个字节
        }
        else if (i == 2)
        {
            // bytes[i] = (s & 0x0000ff00) >> 8; // 获取4字节中的第3个字节
            *(bytes + i) = (s & 0x0000ff00) >> 8; // 获取4字节中的第3个字节
        }
        else if (i == 3)
        {
            // bytes[i] = (s & 0x000000ff) >> 0; // 获取4字节中的第4个字节
            *(bytes + i) = (s & 0x000000ff) >> 0; // 获取4字节中的第4个字节
        }
        // printf("%s%s():: Line %d,%d,%d\n", TAG, __FUNCTION__, __LINE__, i, *(bytes + i));
    }
    return true;
}

/**
 * @brief 将连续32位4字节，转化为4字节整数
 *
 * @param byte 连续的4字节空间
 * @return uint32_t
 */
uint32_t byteToUint32(uint8_t *byte)
{
    const char *TAG = "SwitchUint::";
    if (byte == NULL)
    {
        return 0;
    }
    uint32_t s1 = (*(byte + 0) & 0xffffffff) << 24; // 依次获取第1个字节
    uint32_t s2 = (*(byte + 1) & 0xffffffff) << 16; // 依次获取第2个字节
    uint32_t s3 = (*(byte + 2) & 0xffffffff) << 8;  // 依次获取第3个字节
    uint32_t s4 = (*(byte + 3) & 0xffffffff) << 0;  // 依次获取第4个字节
    printf("%s%s():: Line %d,%#x\n", TAG, __FUNCTION__, __LINE__, s1);
    printf("%s%s():: Line %d,%#x\n", TAG, __FUNCTION__, __LINE__, s2);
    printf("%s%s():: Line %d,%#x\n", TAG, __FUNCTION__, __LINE__, s3);
    printf("%s%s():: Line %d,%#x\n", TAG, __FUNCTION__, __LINE__, s4);
    uint32_t s = s1 | s2 | s3 | s4; // 按位或转化为4字节整数
    printf("%s%s():: Line %d,%#x,%d\n", TAG, __FUNCTION__, __LINE__, s, s);
    // uint32_t ss = switchUint32(s); // 32 位字节序转换
    // printf("%s%s():: Line %d,%#x,%d\n", TAG, __FUNCTION__, __LINE__, ss, ss);
    return s;
}
/**
 * @brief 获取文件大小
 *
 * @param fileName 文件名
 * @return size_t
 */
size_t getFileSize(const char *fileName)
{
    if (fileName == NULL)
    {
        return 0;
    }
    struct stat statbuf;               // 这是一个存储文件(夹)信息的结构体，其中有文件大小和创建时间、访问时间、修改时间等
    stat(fileName, &statbuf);          // 提供文件名字符串，获得文件属性结构体
    size_t filesize = statbuf.st_size; // 获取文件大小
    return filesize;
}