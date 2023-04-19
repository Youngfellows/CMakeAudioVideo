#include "TurboJpegHelp.h"

/**
 * @brief jpeg转化为yuv
 *
 * @param jpeg_buffer jpeg图片数据
 * @param jpeg_size jpeg图片大小
 * @param yuv_buffer yuv数据缓冲区
 * @param yuv_size 返回的yuv数据大小
 * @param yuv_type 返回的yuv数据类型
 * @return int
 */
int tjpeg2yuv(unsigned char *jpeg_buffer, int jpeg_size, unsigned char **yuv_buffer, int *yuv_size, int *yuv_type)
{
    tjhandle handle = NULL;
    int width, height, subsample, colorspace;
    int flags = 0;
    int padding = 1; // 1或4均可，但不能是0
    int ret = 0;

    handle = tjInitDecompress();
    tjDecompressHeader3(handle, jpeg_buffer, jpeg_size, &width, &height, &subsample, &colorspace);

    printf("w: %d h: %d subsample: %d color: %d\n", width, height, subsample, colorspace);

    flags |= 0;

    *yuv_type = subsample;
    // 注：经测试，指定的yuv采样格式只对YUV缓冲区大小有影响，实际上还是按JPEG本身的YUV格式来转换的
    *yuv_size = tjBufSizeYUV2(width, padding, height, subsample);
    *yuv_buffer = (unsigned char *)malloc(*yuv_size);
    if (*yuv_buffer == NULL)
    {
        printf("malloc buffer for rgb failed.\n");
        return -1;
    }
    ret = tjDecompressToYUV2(handle, jpeg_buffer, jpeg_size, *yuv_buffer, width,
                             padding, height, flags);
    if (ret < 0)
    {
        printf("compress to jpeg failed: %s\n", tjGetErrorStr());
    }
    tjDestroy(handle);

    return ret;
}