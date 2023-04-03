/**
 * @file   file_utils.h
 * @author Late Lee <latelee@163.com>
 * @date   Tue May 14 08:56:48 2013
 *
 * @brief  文件操作的一些常用函数
 *
 *
 */
#include <stdio.h>
#include <stdlib.h>

#ifndef _FILE_UTILS_H
#define _FILE_UTILS_H

#ifdef __cplusplus
extern "C"
{
#endif

    /**
     * @brief 通过文件描述符打开文件
     *
     * @param pathname 文件名
     * @param flags 模式
     * @return int 返回打开的文件描述符
     */
    int open_file_fd(const char *pathname, int flags);

    /**
     * @brief 通过文件指针FILE打开文件
     *
     * @param filename 文件名
     * @param mode 模式
     * @return FILE* 返回文件指针
     */
    FILE *open_file(const char *filename, const char *mode);

    /**
     * @brief 读取文件内容到缓冲区
     *
     * @param filename 文件名
     * @param buffer 缓冲区
     * @param len 要读取长度
     * @return int
     */
    int read_file(const char *filename, char **buffer, int *len);

    /**
     * @brief 把缓冲区数据写入文件
     *
     * @param filename 文件名
     * @param buffer 缓冲区
     * @param len 要写入数据的长度
     * @return int
     */
    int write_file(const char *filename, char *buffer, int len);

    /**
     * @brief 获取文件大小
     *
     * @param filename 文件名
     * @return int
     */
    int get_filesize(const char *filename);

#ifdef __cplusplus
}
#endif

#endif
