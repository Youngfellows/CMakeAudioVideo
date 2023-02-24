#include <iostream>
#include "config.h"

#ifdef USE_MY_MATH
// 如果定义了 USE_MY_MATH，导入 "MathFunctions.h"
#include "MathFunctions.h"
#else
// 如果 USE_MY_MATH 未定义，导入 <cmath>
#include <cmath>
#endif

using namespace std;

int main(int argc, char *argv[])
{
    std::cout << "hello cmake ..." << std::endl;
    if (argc < 3)
    {
        std::cout << "使用: " << argv[0] << " 基数 指数" << std::endl;
        return 1;
    }
    int base = atof(argv[1]);     // 基数
    int exponent = atof(argv[2]); // 指数
    int result = 0;
    // int result = power(base, exponent); // 求幂
    // std::cout << base << "的" << exponent << "次方的幕是" << result << std::endl;

#ifdef USE_MY_MATH
    std::cout << "定义了USE_MY_MATH ..." << std::endl;
    result = power(base, exponent); // 求幂
#else
    std::cout << "未定义USE_MY_MATH ..." << std::endl;
    result = pow(base, exponent); // 求幂
#endif
    std::cout << base << "的" << exponent << "次方的幕是" << result << std::endl;

#ifdef TEST_DEBUG
    std::cout << "定义了TEST_DEBUG" << std::endl;
#else
    std::cout << "未定义了TEST_DEBUG" << std::endl;
#endif

#ifdef TEST_RELEASE
    std::cout << "定义了TEST_RELEASE" << std::endl;
#else
    std::cout << "未定义了TEST_RELEASE" << std::endl;
#endif

    return 0;
}
