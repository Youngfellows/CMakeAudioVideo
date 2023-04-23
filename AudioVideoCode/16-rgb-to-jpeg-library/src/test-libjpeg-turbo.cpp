#include <iostream>
#include "funset.hpp"

/**
 * @brief libjpeg-turbo框架使用
 *
 * @return int
 */
int main()
{
    const char *TAG = "test-libjpeg-turbo-decode::";
    printf("%s%s():: Line,%d\n", TAG, __FUNCTION__, __LINE__);

    // 1. 解码jpeg图片文件
    int ret = test_libjpeg_turbo_decompress();
    if (ret == 0)
    {
        fprintf(stdout, "========== decode jpeg test success ==========\n");
    }
    else
    {
        fprintf(stderr, "##########  decode jpeg test fail ##########\n");
    }

    // 2.压缩jpeg图片数据
    ret = test_libjpeg_turbo();
    if (ret == 0)
    {
        fprintf(stdout, "========== compress jpeg test success ==========\n");
    }
    else
    {
        fprintf(stderr, "##########  compress jpeg test fail ##########\n");
    }

    // 3.编码jpeg图片数据
    ret = test_libjpeg_turbo_compress();
    if (ret == 0)
    {
        fprintf(stdout, "========== 1 compress jpeg test success ==========\n");
    }
    else
    {
        fprintf(stderr, "########## 1  compress jpeg test fail ##########\n");
    }
    return 0;
}