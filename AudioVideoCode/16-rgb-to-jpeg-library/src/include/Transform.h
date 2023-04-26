#ifndef _JPEG_TRANSFORM_H_
#define _JPEG_TRANSFORM_H_

#include <iostream>
#include <string>
#include <memory>
// #include <string.h>
#include <cstring>
#include "funset.hpp"

class Transform
{
private:
public:
    Transform();
    ~Transform();

    /**
     * @brief 旋转jpeg图片
     *
     * @param in_image_name jpeg图片路径
     * @param out_image_name 输出旋转后的图片路径
     * @param degree 旋转角度
     * @return true
     * @return false
     */
    bool rotate(const char *in_image_name, const char *out_image_name, int degree);

    /**
     * @brief jpeg图片水平翻转
     *
     * @param in_image_name jpeg图片路径
     * @param out_image_name 输出翻转后的图片路径
     * @return true
     * @return false
     */
    bool flip_horizontal(const char *in_image_name, const char *out_image_name);

    /**
     * @brief jpeg图片垂直翻转
     *
     * @param in_image_name jpeg图片路径
     * @param out_image_name 输出翻转后的图片路径
     * @return true
     * @return false
     */
    bool flip_vertical(const char *in_image_name, const char *out_image_name);

    /**
     * @brief 裁剪jpeg图片
     *
     * @param in_image_name jpeg图片路径
     * @param out_image_name 输出裁剪后的图片路径
     * @return true
     * @return false
     */
    bool crop(const char *in_image_name, const char *out_image_name);
};

#endif