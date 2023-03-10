#include "../include/array/MyArray.h"

/**
 * @brief 实现为一个二维数组赋值
 *
 * @param lines 数组行数
 * @param container 数组首地址
 */
void wrap_content(int lines, uint8_t container[][64])
{
    srand(time(0));
    const char *letter = "abcdefghijklmnopqrstuvwxyz0123456789";
    int len = strlen(letter);
    int index = rand() % (len - 1);        // 获取0-35的随机数
    uint8_t character = *(letter + index); // 获取随机字符
    std::cout << "len:" << len << ",index:" << index << ",character:" << character << std::endl;
    for (int i = 0; i < lines; i++)
    {
        uint8_t *line = container[i]; // 获取一行元素首地址
        for (int j = 0; j < 64; j++)
        {
            index = rand() % (len - 1);    // 获取0-35的随机数
            character = *(letter + index); // 获取随机字符
            line[j] = character;           // 为该位置元素赋值
            uint8_t ele = line[j];
            std::cout << ele;
        }
        std::cout << std::endl;
    }
}

/**
 * @brief 打印二维数组元素值
 *
 * @param lines 数组行数
 * @param container  数组首地址
 */
void print_content(int lines, uint8_t container[][64])
{
    std::cout << "================================================================" << std::endl;
    for (int i = 0; i < lines; i++)
    {
        uint8_t *line = container[i]; // 获取一行元素首地址
        for (int j = 0; j < 64; j++)
        {
            uint8_t ele = line[j];
            std::cout << ele;
        }
        std::cout << std::endl;
    }
}