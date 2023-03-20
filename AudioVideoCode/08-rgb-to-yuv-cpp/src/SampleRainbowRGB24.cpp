#include <iostream>
#include "../include/pixel/RGB24.h"

using namespace std;

int main(int arg, char **argv)
{
    const char *TAG = "RGB24::";
    std::cout << TAG << __FUNCTION__ << ",Line " << __LINE__ << std::endl;
    RGB24 *rgb24 = new RGB24();

    return 0;
}