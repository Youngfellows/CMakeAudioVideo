
#include "file_utils.h"

/**
 * @brief 读取文件内容到缓冲区
 *
 * @param filename 文件名
 * @param buffer 缓冲区
 * @param len 要读取长度
 * @return int
 */
int read_file(const char *filename, char **buffer, int *len)
{
    const char *tmp_file = filename;
    FILE *fp = NULL;
    int file_size = 0;
    char *ptr = NULL;
    int real_len = 0;
    int ret = 0;

    fp = fopen(tmp_file, "rb");
    if (fp == NULL)
    {
        printf("=====error open file: %s.\n", tmp_file);
        return -1;
    }

    fseek(fp, 0, SEEK_END); // 文件尾
    file_size = ftell(fp);
    printf("file size: %d = %.1f(KB) = %.1f(MB)\n",
           file_size, file_size / 1024.0, file_size / 1024.0 / 1024.0);

    fseek(fp, 0, SEEK_SET); // 指回文件头

    *buffer = (char *)malloc(file_size);

    if (NULL == *buffer)
    {
        printf("malloc failed!\n");
        return -1;
    }

    //  读文件
    ptr = *buffer;
    real_len = 0;

    while (file_size > 0)
    {
        ret = fread(ptr, 1, file_size, fp);
        if (ret < 0)
        {
            printf("fread failed! real: %d ret: %d\n", file_size, ret);
            *len = 0;
            return -1;
        }
        else if (ret == 0)
        {
            break;
        }
        ptr += ret;
        real_len += ret;
        file_size -= ret;
    }

    *len = real_len;

    printf("read file OK, len: %d!\n", *len);

    return 0;
}

/**
 * @brief 把缓冲区数据写入文件
 *
 * @param filename 文件名
 * @param buffer 缓冲区
 * @param len 要写入数据的长度
 * @return int
 */
int write_file(const char *filename, char *buffer, int len)
{
    const char *tmp_file = filename;
    FILE *fp = NULL;
    int file_size = len;
    char *ptr = NULL;
    int real_len = 0;
    int ret = 0;

    fp = fopen(tmp_file, "ab");
    if (fp == NULL)
    {
        printf("=====error open file: %s.\n", tmp_file);
        return -1;
    }

    //  写文件
    ptr = buffer;
    real_len = 0;

    while (file_size > 0)
    {
        ret = fwrite(ptr, 1, file_size, fp);
        if (ret < 0)
        {
            printf("fwrite failed! real: %d ret: %d\n", file_size, ret);
            return -1;
        }
        else if (ret == 0)
        {
            break;
        }
        ptr += ret;
        real_len += ret;
        file_size -= ret;
    }

    printf("write file OK, len: %d!\n", real_len);

    return 0;
}

/**
 * @brief 获取文件大小
 *
 * @param filename 文件名
 * @return int
 */
int get_filesize(const char *filename)
{
    const char *tmp_file = filename;
    FILE *fp = NULL;
    int file_size = 0;

    fp = fopen(tmp_file, "rb");
    if (fp == NULL)
    {
        printf("=====error open file: %s.\n", tmp_file);
        return -1;
    }

    fseek(fp, 0, SEEK_END); // 文件尾
    file_size = ftell(fp);

    fseek(fp, 0, SEEK_SET); // 指回文件头

    return file_size;
}
