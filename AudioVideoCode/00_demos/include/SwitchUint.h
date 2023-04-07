#ifndef _SWITCH_UINT_H_
#define _SWITCH_UINT_H_

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <sys/stat.h>

/**
 * @brief 判断是 大端字节序 OR 小端字节序
 *
 * @return true
 * @return false
 */
bool isBigEndianOrder();

/**
 * @brief 16 位字节序转换
 *
 * @param s
 * @return uint16_t
 */
uint16_t switchUint16(uint16_t s);

/**
 * @brief 32 位字节序转换
 *
 * @param i
 * @return uint32_t
 */
uint32_t switchUint32(uint32_t i);

/**
 * @brief 获取32位整数在内存中的4字节数据
 *
 * @param s 32位的4字节整数
 * @param bytes 申请的4字节连续内存空间
 * @return true
 * @return false
 */
bool uint32Bytes(uint32_t s, uint8_t *bytes);

/**
 * @brief 将连续32位4字节，转化为4字节整数
 *
 * @param byte 连续的4字节空间
 * @return uint32_t
 */
uint32_t byteToUint32(uint8_t *byte);

/**
 * @brief 获取文件大小
 *
 * @param fileName
 * @return size_t
 */
size_t getFileSize(const char *fileName);

#endif