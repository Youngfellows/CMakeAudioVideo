#ifndef _TURBO_JPEG_HELPER_H_
#define _TURBO_JPEG_HELPER_H_
#include <stdio.h>
#include <setjmp.h>
#include <string.h>
#include <stdlib.h>
#include <jpeglib.h>
#include <stdbool.h>
#include <turbojpeg.h>
#include <sys/stat.h>
#include "util.h"
#include "ImageData.h"

/**
 * @brief jpeg格式解码为rgb24
 *
 * @param inJpegName jpeg格式文件路径
 * @param outRgbName rgb24格式文件路径
 * @return int
 */
int decode_JPEG_file(char *inJpegName, char *outRgbName);

/**
 * @brief jpeg格式解码为rgb格式
 *
 * @param inJpegName jpeg格式文件路径
 * @param imageData 返回的rgb图片信息
 * @return int
 */
int decode_JPEG_file2(char *inJpegName, struct ImageData *imageData);

/**
 * @brief rgb24编码为jpeg图片格式
 *
 * @param strImageName jpeg文件路径
 * @param image_buffer rgb24数据
 * @param image_height 图片高
 * @param image_width 图片宽
 * @param quality 图片质量
 * @return int
 */
int encode_JPEG_file(char *strImageName, uint8_t *image_buffer, int image_height, int image_width, int quality);

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
int tjpeg2yuv(unsigned char *jpeg_buffer, int jpeg_size, unsigned char **yuv_buffer, int *yuv_size, int *yuv_type);

int tyuv2jpeg(unsigned char *yuv_buffer, int yuv_size, int width, int height, int subsample, unsigned char **jpeg_buffer, unsigned long *jpeg_size, int quality);

#endif