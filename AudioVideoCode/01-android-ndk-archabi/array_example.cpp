#include <iostream>
#include "./include/array/MyArray.h"

using namespace std;

int main(int arg, char *argv[])
{
    std::cout << "start ..." << std::endl;
    int lines = 5;
    uint8_t blocks[lines][64];    // 定义一个二维数组
    wrap_content(lines, blocks);  // 为二维数组元素赋值
    print_content(lines, blocks); // 打印二维数组元素
    std::cout << "end ..." << std::endl;

    return 0;
}