#include "MyArray.h"

/**
 * @brief 实现为一个二维数组赋值
 *
 * @param lines 数组行数
 * @param container 数组首地址
 */
void wrap_content(int lines, uint8_t container[][64])
{
    const char *TAG = "MyArray::";
    printf("%s%s():: Line %d\n", TAG, __FUNCTION__, __LINE__);
    srand(time(0));
    const char *letter = "abcdefghijklmnopqrstuvwxyz0123456789";
    int len = strlen(letter);
    int index = rand() % (len - 1);        // 获取0-35的随机数
    uint8_t character = *(letter + index); // 获取随机字符
    // std::cout << "len:" << len << ",index:" << index << ",character:" << character << std::endl;
    printf("len:%d,index:%d,character:%c\n", len, index, character);
    for (int i = 0; i < lines; i++)
    {
        uint8_t *line = container[i]; // 获取一行元素首地址
        for (int j = 0; j < 64; j++)
        {
            index = rand() % (len - 1);    // 获取0-35的随机数
            character = *(letter + index); // 获取随机字符
            line[j] = character;           // 为该位置元素赋值
            uint8_t ele = line[j];
            // std::cout << ele;
            printf("%c", ele);
        }
        // std::cout << std::endl;
        printf("\n");
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
    const char *TAG = "MyArray::";
    printf("%s%s():: Line %d\n", TAG, __FUNCTION__, __LINE__);
    // std::cout << "================================================================" << std::endl;
    printf("\n================================================================\n");
    for (int i = 0; i < lines; i++)
    {
        uint8_t *line = container[i]; // 获取一行元素首地址
        for (int j = 0; j < 64; j++)
        {
            uint8_t ele = line[j];
            // std::cout << ele;
            printf("%c", ele);
        }
        printf("\n");
    }
}