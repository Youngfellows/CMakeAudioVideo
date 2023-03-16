#include <iostream>
#include <cstring>
// #include <string.h>

using namespace std;

#define GIF_STAMP "GIFVER" /* First chars in file - GIF stamp.  */
#define GIF_STAMP_LEN sizeof(GIF_STAMP) - 1
typedef unsigned char *GifRowType; // 指针

/**
 * @brief RGB像素信息结构体
 *
 */
typedef struct
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
} RGBPixel;

/**
 * @brief 学生信息对象
 *
 */
class Student
{
private:
    std::string name;
    int age;
    double salary;
    char sex;

public:
    Student(std::string name, int age);
    ~Student();
};

Student::Student(std::string name, int age)
{
    // std::cout << "Student::Student()构造函数" << std::endl;
    this->name = name;
    this->age = age;
}

Student::~Student()
{
    // std::cout << "Student::~Student()析构函数" << std::endl;
}

int main(int arg, char *argv[])
{
    const char *TAG = "DemoSizeof";
    printf("%s::main::\n", TAG);

    // 6
    printf("GIF_STAMP_LEN: %lu\n", GIF_STAMP_LEN); // 使用宏求字符串长度

    const char *name = "binglingziyu"; // 指针，指向一个字符串

    // 8
    printf("sizeOf name: %lu\n", sizeof(name)); // 求指针地址的大小为8

    // 13
    printf("sizeOf string: %lu\n", sizeof("binglingziyu")); // 求字符串的长短

    // 12
    printf("strlen name: %lu\n", strlen(name)); // 使用库函数求字符串长度

    // 8
    printf("sizeOf point GifRowType: %lu\n", sizeof(GifRowType)); // 字符指针的长度也是8

    // 8
    Student *student = new Student("杨过", 18);
    printf("sizeOf class Student: %lu\n", sizeof(Student)); // 类的长度不固定
    printf("sizeOf Student: %lu\n", sizeof(student));       // 指针的长度都是8

    // 3
    RGBPixel pixel = RGBPixel{111, 222, 123};
    printf("sizeOf struct RGBPixel: %lu\n", sizeof(pixel)); // 结构体的长度为各元素长度的和，3

    // 8
    RGBPixel *pPixel = &pixel;
    printf("sizeOf point RGBPixel: %lu\n", sizeof(pPixel)); // 指针的长度都是8

    // 释放内存
    delete student;
    return 0;
}