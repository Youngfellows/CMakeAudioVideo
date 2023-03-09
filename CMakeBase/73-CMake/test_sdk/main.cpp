#include <iostream>
#include "MathFunctions.h"
#include "Shape.h"

using namespace std;

int main(int argc, char *argv[])
{
    std::cout << "hello cmake ..." << std::endl;
    if (argc < 3)
    {
        std::cout << "使用: " << argv[0] << " 基数 指数" << std::endl;
        return 1;
    }
    int base = atof(argv[1]);           // 基数
    int exponent = atof(argv[2]);       // 指数
    int result = power(base, exponent); // 求幂
    std::cout << base << "的" << exponent << "次方的幕是" << result << std::endl;
    double rArea = area(8, 9);
    std::cout << "面积:" << rArea << std::endl;
    return 0;
}
