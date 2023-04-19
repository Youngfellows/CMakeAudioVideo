#include "TurboJpegHelp.h"

/**
 * @brief yuv420p转化为jpeg
 *
 * @param yuv_buffer yuv420p内存数据
 * @param yuv_size yuv420p数据大小
 * @param width yuv420p数据宽
 * @param height yuv420p数据高
 * @param subsample 格式/YUV420p,YUV444p
 * @param jpeg_buffer 转化之后的jpeg数据内存
 * @param jpeg_size 转化之后的jpeg数据大小
 * @param quality
 * @return int
 */
int tyuv2jpeg(unsigned char *yuv_buffer, int yuv_size, int width, int height, int subsample, unsigned char **jpeg_buffer, unsigned long *jpeg_size, int quality)
{
    const char *TAG = "yuv2jpeg::";
    printf("%s%s():: Line,%d\n", TAG, __FUNCTION__, __LINE__);

    tjhandle handle = NULL;
    int flags = 0;
    int padding = 1; // 1或4均可，但不能是0
    int need_size = 0;
    int ret = 0;

    printf("%s%s():: Line,%d\n", TAG, __FUNCTION__, __LINE__);
    handle = tjInitCompress();
    printf("%s%s():: Line,%d\n", TAG, __FUNCTION__, __LINE__);

    flags |= 0;
    printf("%s%s():: Line,%d\n", TAG, __FUNCTION__, __LINE__);
    need_size = tjBufSizeYUV2(width, padding, height, subsample);
    printf("%s%s():: Line,%d\n", TAG, __FUNCTION__, __LINE__);

    if (need_size != yuv_size)
    {
        printf("we detect yuv size: %d, but you give: %d, check again.\n", need_size, yuv_size);
        return 0;
    }
    printf("%s%s():: Line,%d\n", TAG, __FUNCTION__, __LINE__);
    ret = tjCompressFromYUV(handle, yuv_buffer, width, padding, height, subsample, jpeg_buffer, jpeg_size, quality, flags);
    if (ret < 0)
    {
        printf("compress to jpeg failed: %s\n", tjGetErrorStr());
    }
    printf("%s%s():: Line,%d\n", TAG, __FUNCTION__, __LINE__);
    tjDestroy(handle);
    printf("%s%s():: Line,%d\n", TAG, __FUNCTION__, __LINE__);
    return ret;
}