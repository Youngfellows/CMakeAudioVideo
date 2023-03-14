#ifndef CONFIG_H
#define CONFIG_H

#include <iostream>

const unsigned int RGB24_MASK_RED = 0XFF0000;
const unsigned int RGB24_MASK_GREEN = 0x00FF00;
const unsigned int RGB24_MASK_BLUE = 0x0000FF;

#define RGB24_MASK_RED_1 0xFF0000
#define RGB24_MASK_GREEN_1 0x00FF00
#define RGB24_MASK_BLUE_1 0x0000FF

/**
 * @brief 2字节大小端字节序转化
 *
 */
#define UINT16_SWAP_LE_BE_CONSTANT(val)            \
    ((uint16_t)((uint16_t)((uint16_t)(val) >> 8) | \
                (uint16_t)((uint16_t)(val) << 8)))

/**
 * @brief 4字节大小端字节序转化
 *
 */
#define UINT32_SWAP_LE_BE_CONSTANT(val)                             \
    ((uint32_t)((((uint32_t)(val) & (uint32_t)0x000000ffU) << 24) | \
                (((uint32_t)(val) & (uint32_t)0x0000ff00U) << 8) |  \
                (((uint32_t)(val) & (uint32_t)0x00ff0000U) >> 8) |  \
                (((uint32_t)(val) & (uint32_t)0xff000000U) >> 24)))

#endif