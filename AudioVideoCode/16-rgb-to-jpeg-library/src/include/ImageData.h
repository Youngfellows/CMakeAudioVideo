#ifndef _IMAGE_DATA_H_
#define _IMAGE_DATA_H_

/**
 * @brief rgb图片数据
 *
 */
struct ImageData
{
    unsigned char *pixels; // rgb内存中的数据
    long width;            // 图片宽
    long height;           // 图片高
    int per_pixel_byte;    // 每个像素占用字节数
};

#endif