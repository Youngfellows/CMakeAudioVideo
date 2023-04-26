#include "Transform.h"

int main()
{
    const char *tag = "sample-jpeg-transform()::";
    printf("%s%s():: ssss,Line %d\n", tag, __FUNCTION__, __LINE__);
    std::string image_path{"./jepg-resource/"}; // 源图片文件目录
    std::string out_image_path{"./resource/"};  // 解码图片文件目录

    // 旋转jpeg图片
    // std::string in_image = image_path + "libjpeg-turbo-test-image.jpg";
    std::string in_image = image_path + "shenzhen-eye.jpg";
    std::string out_image = out_image_path + "route-90.jpg";

    Transform *transsform = new Transform();
    transsform->rotate(in_image.c_str(), out_image.c_str(), 90);

    out_image = out_image_path + "route-180.jpg";
    transsform->rotate(in_image.c_str(), out_image.c_str(), 180);

    out_image = out_image_path + "route-270.jpg";
    transsform->rotate(in_image.c_str(), out_image.c_str(), 270);

    //  翻转jpeg图片
    // in_image = image_path + "cat.jpg";
    out_image = out_image_path + "cat-flip-horizontal.jpg";
    transsform->flip_horizontal(in_image.c_str(), out_image.c_str());

    out_image = out_image_path + "cat-flip-vertical.jpg";
    transsform->flip_vertical(in_image.c_str(), out_image.c_str());

    // 剪切jpeg图片
    in_image = image_path + "libjpeg-turbo-test-image.jpg";
    out_image = out_image_path + "meizi-crop.jpg";
    transsform->crop(in_image.c_str(), out_image.c_str());

    delete transsform;
}