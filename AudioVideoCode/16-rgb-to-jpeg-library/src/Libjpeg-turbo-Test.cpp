#include <iostream>
#include "funset.hpp"

int main()
{
    const char *TAG = "Libjpeg-turbo-Test::";
    printf("%s%s():: Line,%d\n", TAG, __FUNCTION__, __LINE__);

    int ret = test_libjpeg_turbo_decompress();

    if (ret == 0)
        fprintf(stdout, "========== test success ==========\n");
    else
        fprintf(stderr, "########## test fail ##########\n");

    return 0;
}