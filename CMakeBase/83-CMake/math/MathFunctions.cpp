#include "MathFunctions.h"

/**
 * @brief 求幕函数
 *
 * @param base 基数
 * @param exponent 指数
 * @return int 返回幕
 */
int power(int base, int exponent)
{
    int result = base;
    int i;
    if (exponent == 0)
    {
        return 1;
    }
    for (i = 1; i < exponent; i++)
    {
        result = result * base;
    }
    return result;
}