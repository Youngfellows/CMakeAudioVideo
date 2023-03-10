// #include "./include/rainbow/Rainbow.h"
#include "Rainbow.h"

int main(int arg, char *argv[])
{
    std::cout << "RGB拼图:生成彩虹图片" << std::endl;
    // 创建对象,动态申请内存
    IRainbow *rainbow = new Rainbow();
    const char *outputFile1 = "./resource/rainbow-700x700.rgb24";  // 保存的文件名
    const char *outputFile2 = "./resource/rainbow2-700x700.rgb24"; // 保存的文件名
    rainbow->writeRainbow(outputFile1, 700, 700);
    rainbow->writeRainbow2(outputFile2, 600, 600);

    // 释放内存
    delete rainbow;

    return 0;
}