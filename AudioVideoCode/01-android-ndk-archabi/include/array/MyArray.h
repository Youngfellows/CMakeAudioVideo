#ifndef MY_ARRAY_H
#define MY_ARRAY_H

// #include <cstdint>
// #include <iostream>
// #include <string.h>
// #include <ctime>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

// using namespace std;

/**
 * @brief 为一个二维数组赋值
 *
 * @param lines 数组行数
 * @param container 数组首地址
 */
void wrap_content(int lines, uint8_t container[][64]);

/**
 * @brief 打印二维数组元素值
 *
 * @param lines 数组行数
 * @param container  数组首地址
 */
void print_content(int lines, uint8_t container[][64]);

#endif