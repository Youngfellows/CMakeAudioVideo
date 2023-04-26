#include "Transform.h"

Transform::Transform(/* args */)
{
    printf("%s():: Line %d\n", __FUNCTION__, __LINE__);
}

Transform::~Transform()
{
    printf("%s():: Line %d\n", __FUNCTION__, __LINE__);
}

/**
 * @brief 旋转jpeg图片
 *
 * @param in_image_name jpeg图片路径
 * @param out_image_name 输出旋转后的图片路径
 * @param degree 旋转角度
 * @return true
 * @return false
 */
bool Transform::rotate(const char *in_image_name, const char *out_image_name, int degree)
{
    printf("%s():: Line %d,degree:%d\n", __FUNCTION__, __LINE__, degree);
    parse_jpeg_file(in_image_name);

    // 读取jpeg文件到内存
    FILE *infile = fopen(in_image_name, "rb");
    if (infile == nullptr)
    {
        fprintf(stderr, "can't open %s\n", in_image_name);
        return false;
    }
    // 获取jpeg文件大小
    fseek(infile, 0, SEEK_END);
    unsigned long srcSize = ftell(infile);
    printf("%s():: Line %d,jpet size:%ld\n", __FUNCTION__, __LINE__, srcSize);

    // 读取jpeg图片信息到srcBuf内存中
    std::unique_ptr<unsigned char[]> srcBuf(new unsigned char[srcSize]);
    fseek(infile, 0, SEEK_SET);
    fread(srcBuf.get(), srcSize, 1, infile);
    fclose(infile);

    printf("%s():: Line %d\n", __FUNCTION__, __LINE__);
    // 申请旋转后图片的内存空间
    std::unique_ptr<unsigned char[]> desBuf(new unsigned char[srcSize]);
    // tjhandle decompressor = tjInitDecompress(); // jieg图片解码控制器
    tjhandle transformer = tjInitTransform(); // jpeg图片旋转控制器

    // 旋转图片
    tjtransform *transform = new tjtransform();
    if (degree == 90)
    {
        transform->op = TJXOP_ROT90;
    }
    else if (degree == 180)
    {
        transform->op = TJXOP_ROT180;
    }
    else if (degree == 270)
    {
        transform->op = TJXOP_ROT270;
    }
    transform->options = TJXOPT_TRIM;
    unsigned long desSize;
    unsigned char *pSrc = srcBuf.get();
    unsigned char *pDes = desBuf.get();
    // printf("%s():: Line %d\n", __FUNCTION__, __LINE__);
    tjTransform(transformer, pSrc, srcSize, 1, &pDes, &desSize, transform, 0);
    printf("%s():: Line %d,des size:%ld\n", __FUNCTION__, __LINE__, desSize);
    if (desSize > 0)
    {
        // 把旋转后的图片保存到文件
        FILE *outfile = fopen(out_image_name, "wb");
        if (outfile != NULL)
        {
            fwrite(pDes, desSize, 1, outfile);
            fclose(outfile);
        }
    }

    // tjDestroy(decompressor);
    tjDestroy(transformer);
    return true;
}

/**
 * @brief jpeg图片水平翻转
 *
 * @param in_image_name jpeg图片路径
 * @param out_image_name 输出翻转后的图片路径
 * @return true
 * @return false
 */
bool Transform::flip_horizontal(const char *in_image_name, const char *out_image_name)
{
    printf("%s():: Line %d\n", __FUNCTION__, __LINE__);
    parse_jpeg_file(in_image_name);

    // 读取jpeg文件到内存
    FILE *infile = fopen(in_image_name, "rb");
    if (infile == nullptr)
    {
        fprintf(stderr, "can't open %s\n", in_image_name);
        return false;
    }
    // 获取jpeg文件大小
    fseek(infile, 0, SEEK_END);
    unsigned long srcSize = ftell(infile);
    printf("%s():: Line %d,jpet size:%ld\n", __FUNCTION__, __LINE__, srcSize);

    // 读取jpeg图片信息到srcBuf内存中
    std::unique_ptr<unsigned char[]> srcBuf(new unsigned char[srcSize]);
    fseek(infile, 0, SEEK_SET);
    fread(srcBuf.get(), srcSize, 1, infile);
    fclose(infile);

    printf("%s():: Line %d\n", __FUNCTION__, __LINE__);
    // 申请旋转后图片的内存空间
    std::unique_ptr<unsigned char[]> desBuf(new unsigned char[srcSize]);
    // tjhandle decompressor = tjInitDecompress(); // jieg图片解码控制器
    tjhandle transformer = tjInitTransform(); // jpeg图片旋转控制器

    // 水平翻转图片
    tjtransform *transform = new tjtransform();
    transform->op = TJXOP_HFLIP;
    transform->options = TJXOPT_TRIM;
    unsigned long desSize;
    unsigned char *pSrc = srcBuf.get();
    unsigned char *pDes = desBuf.get();
    printf("%s():: Line %d\n", __FUNCTION__, __LINE__);
    tjTransform(transformer, pSrc, srcSize, 1, &pDes, &desSize, transform, 0);
    printf("%s():: Line %d,des size:%ld\n", __FUNCTION__, __LINE__, desSize);
    if (desSize > 0)
    {
        // 把水平翻转后的图片保存到文件
        FILE *outfile = fopen(out_image_name, "wb");
        if (outfile != NULL)
        {
            fwrite(pDes, desSize, 1, outfile);
            fclose(outfile);
        }
    }

    // tjDestroy(decompressor);
    tjDestroy(transformer);
    return true;
}

/**
 * @brief jpeg图片垂直翻转
 *
 * @param in_image_name jpeg图片路径
 * @param out_image_name 输出翻转后的图片路径
 * @return true
 * @return false
 */
bool Transform::flip_vertical(const char *in_image_name, const char *out_image_name)
{
    printf("%s():: Line %d\n", __FUNCTION__, __LINE__);
    parse_jpeg_file(in_image_name);

    // 读取jpeg文件到内存
    FILE *infile = fopen(in_image_name, "rb");
    if (infile == nullptr)
    {
        fprintf(stderr, "can't open %s\n", in_image_name);
        return false;
    }
    // 获取jpeg文件大小
    fseek(infile, 0, SEEK_END);
    unsigned long srcSize = ftell(infile);
    printf("%s():: Line %d,jpet size:%ld\n", __FUNCTION__, __LINE__, srcSize);

    // 读取jpeg图片信息到srcBuf内存中
    std::unique_ptr<unsigned char[]> srcBuf(new unsigned char[srcSize]);
    fseek(infile, 0, SEEK_SET);
    fread(srcBuf.get(), srcSize, 1, infile);
    fclose(infile);

    printf("%s():: Line %d\n", __FUNCTION__, __LINE__);
    // 申请旋转后图片的内存空间
    std::unique_ptr<unsigned char[]> desBuf(new unsigned char[srcSize]);
    // tjhandle decompressor = tjInitDecompress(); // jieg图片解码控制器
    tjhandle transformer = tjInitTransform(); // jpeg图片旋转控制器

    // 垂直翻转图片
    tjtransform *transform = new tjtransform();
    transform->op = TJXOP_VFLIP;
    transform->options = TJXOPT_TRIM;

    unsigned long desSize;
    unsigned char *pSrc = srcBuf.get();
    unsigned char *pDes = desBuf.get();
    printf("%s():: Line %d\n", __FUNCTION__, __LINE__);
    tjTransform(transformer, pSrc, srcSize, 1, &pDes, &desSize, transform, 0);
    printf("%s():: Line %d,des size:%ld\n", __FUNCTION__, __LINE__, desSize);
    if (desSize > 0)
    {
        // 把 垂直翻转后的图片保存到文件
        FILE *outfile = fopen(out_image_name, "wb");
        if (outfile != NULL)
        {
            fwrite(pDes, desSize, 1, outfile);
            fclose(outfile);
        }
    }

    // tjDestroy(decompressor);
    tjDestroy(transformer);
    return true;
}

/**
 * @brief 裁剪jpeg图片
 *
 * @param in_image_name jpeg图片路径
 * @param out_image_name 输出裁剪后的图片路径
 * @return true
 * @return false
 */
bool Transform::crop(const char *in_image_name, const char *out_image_name)
{
    printf("%s():: Line %d\n", __FUNCTION__, __LINE__);
    parse_jpeg_file(in_image_name);

    // 读取jpeg文件到内存
    FILE *infile = fopen(in_image_name, "rb");
    if (infile == nullptr)
    {
        fprintf(stderr, "can't open %s\n", in_image_name);
        return false;
    }
    // 获取jpeg文件大小
    fseek(infile, 0, SEEK_END);
    unsigned long srcSize = ftell(infile);
    printf("%s():: Line %d,jpet size:%ld\n", __FUNCTION__, __LINE__, srcSize);

    // 读取jpeg图片信息到srcBuf内存中
    std::unique_ptr<unsigned char[]> srcBuf(new unsigned char[srcSize]);
    fseek(infile, 0, SEEK_SET);
    fread(srcBuf.get(), srcSize, 1, infile);
    fclose(infile);

    printf("%s():: Line %d\n", __FUNCTION__, __LINE__);
    // 申请旋转后图片的内存空间
    std::unique_ptr<unsigned char[]> desBuf(new unsigned char[srcSize]);
    // tjhandle decompressor = tjInitDecompress(); // jieg图片解码控制器
    tjhandle transformer = tjInitTransform(); // jpeg图片旋转控制器

    // 裁剪图片
    int left = 198;
    int top = 203;
    int width = 300;
    int height = 400;
    tjtransform *transform = new tjtransform();
    tjregion cropRegion;
    cropRegion.x = left - (left % 16);
    cropRegion.y = top - (top % 16);
    cropRegion.w = width;
    cropRegion.h = height;
    transform->r = cropRegion;
    transform->options = TJXOPT_CROP;

    unsigned long desSize;
    unsigned char *pSrc = srcBuf.get();
    unsigned char *pDes = desBuf.get();
    printf("%s():: Line %d\n", __FUNCTION__, __LINE__);
    tjTransform(transformer, pSrc, srcSize, 1, &pDes, &desSize, transform, 0);
    printf("%s():: Line %d,des size:%ld\n", __FUNCTION__, __LINE__, desSize);
    if (desSize > 0)
    {
        // 把裁剪后的图片保存到文件
        FILE *outfile = fopen(out_image_name, "wb");
        if (outfile != NULL)
        {
            fwrite(pDes, desSize, 1, outfile);
            fclose(outfile);
        }
    }

    // tjDestroy(decompressor);
    tjDestroy(transformer);
    return true;
}
