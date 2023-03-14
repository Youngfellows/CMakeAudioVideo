// #include "./include/rainbow/Rainbow.h"
#include "Bitmap.h"

int main(int arg, char *argv[])
{
    std::cout << "BMP图片:生成彩虹图片" << std::endl;
    // 创建对象,动态申请内存
    IBitmap *rainbow = new Bitmap();
    const char *outputFile1 = "./resource/rainbow-700x700.bmp";  // 保存的文件名
    const char *outputFile2 = "./resource/rainbow2-700x700.bmp"; // 保存的文件名
    rainbow->save(outputFile1, 700, 700);
    rainbow->save2(outputFile2, 600, 600);

    // 释放内存
    delete rainbow;

    return 0;
}