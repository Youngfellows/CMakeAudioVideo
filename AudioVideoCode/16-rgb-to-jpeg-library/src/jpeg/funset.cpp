#include <string>
#include <memory>
// #include <string.h>
#include <cstring>

#include "funset.hpp"
// #include <opencv2/opencv.hpp>

/**
 * @brief Blog: https://blog.csdn.net/fengbingchun/article/details/102837111
 * @brief jpeg文件解码为rgb数据
 *
 * @return int
 */
int test_libjpeg_turbo_decompress()
{
#ifdef _MSC_VER
    std::string image_path{"E:/GitCode/OCR_Test/test_data/"};
#else
    std::string image_path{"./jepg-resource/"}; // 源图片文件目录
    std::string res_image_path{"./resource/"};  // 解码图片文件目录
#endif

    std::string image_name = image_path + "libjpeg-turbo-test-image.jpg"; // jpeg图片路径
    printf("%s():: Line,%d,image_name:%s\n", __FUNCTION__, __LINE__, image_name.c_str());

    // 方式1解码jpeg图片
    int width, height, channels;
    long long t1 = Timer::getNowTime();
    std::unique_ptr<unsigned char[]> data = get_jpeg_decompress_data(image_name.c_str(), width, height, channels);
    long long t2 = Timer::getNowTime();
    if (data == nullptr)
    {
        fprintf(stderr, "fail to decompress: %s\n", image_name.c_str());
        return -1;
    }
    fprintf(stdout, "decompress time 1: %lldms, width: %d, height: %d, channels: %d\n", t2 - t1, width, height, channels);

    std::string result_image = res_image_path + "result_tirg_rgb24.rgb";

    // 把解码后的rgb数据写入文件
    FILE *outfile = fopen(result_image.c_str(), "wb");
    if (outfile == nullptr)
    {
        fprintf(stderr, "open file fail: %s\n", result_image.c_str());
        return -1;
    }
    fwrite(data.get(), width * height * channels, 1, outfile); // 向文件中写入jpeg数据
    fclose(outfile);

    // 方式2解码jpeg图片
    int width2, height2, channels2;
    t1 = Timer::getNowTime();
    std::unique_ptr<unsigned char[]> data2 = get_jpeg_decompress_data2(image_name.c_str(), width2, height2, channels2);
    t2 = Timer::getNowTime();
    if (data2 == nullptr)
    {
        fprintf(stderr, "fail to decompress: %s\n", image_name.c_str());
        return -1;
    }

    fprintf(stdout, "decompress time 2: %lldms, width2: %d, height2: %d, channels2: %d\n", t2 - t1, width2, height2, channels2);
    std::string result_image2 = res_image_path + "result_tirg2_rgb24.rgb";

    // 把解码后的rgb数据写入文件
    FILE *outfile2 = fopen(result_image2.c_str(), "wb");
    if (outfile2 == nullptr)
    {
        fprintf(stderr, "open file fail: %s\n", result_image2.c_str());
        return -1;
    }
    fwrite(data.get(), width * height * 3, 1, outfile2);
    fclose(outfile2);

    return 0;
}

/**
 * @brief jpeg图片解码
 *
 * @param image_name jpeg图片路径
 * @param width jpeg图片宽
 * @param height jpeg图片高
 * @param channels jpeg图片每一个像素占用字节
 * @return std::unique_ptr<unsigned char[]>,返回jpeg图片解码后的rgb数据
 */
std::unique_ptr<unsigned char[]> get_jpeg_decompress_data2(const char *image_name, int &width, int &height, int &channels)
{
    FILE *infile = fopen(image_name, "rb");
    if (infile == nullptr)
    {
        fprintf(stderr, "can't open %s\n", image_name);
        return nullptr;
    }
    fseek(infile, 0, SEEK_END);
    unsigned long srcSize = ftell(infile); // 获取jpeg文件大小

    // 读取jpeg图片信息到srcBuf内存中
    std::unique_ptr<unsigned char[]> srcBuf(new unsigned char[srcSize]);
    fseek(infile, 0, SEEK_SET);
    fread(srcBuf.get(), srcSize, 1, infile);
    fclose(infile);

    tjhandle handle = tjInitDecompress(); // 回调函数
    int subsamp, cs;
    // 获取jpeg文件头信息
    int ret = tjDecompressHeader3(handle, srcBuf.get(), srcSize, &width, &height, &subsamp, &cs);
    if (cs == TJCS_GRAY)
        channels = 1;
    else
        channels = 3;

    int pf = TJCS_RGB;
    int ps = tjPixelSize[pf];
    std::unique_ptr<unsigned char[]> data(new unsigned char[width * height * channels]); // 申请rgb内存空间
    ret = tjDecompress2(handle, srcBuf.get(), srcSize, data.get(), width, width * channels, height, TJPF_RGB, TJFLAG_NOREALLOC);

    tjDestroy(handle);

    return data;
}

/**
 * @brief jpeg图片解码
 *
 * @param image_name jpeg图片路径
 * @param width 宽
 * @param height 高
 * @param channels 位宽,jpeg图片每一个像素占用字节
 * @return std::unique_ptr<unsigned char[]> 返回jpeg图片解码后的rgb数据
 */
std::unique_ptr<unsigned char[]> get_jpeg_decompress_data(const char *image_name, int &width, int &height, int &channels)
{
    FILE *infile = fopen(image_name, "rb");
    if (infile == nullptr)
    {
        fprintf(stderr, "can't open %s\n", image_name);
        return nullptr;
    }

    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;

    /* Step 1: allocate and initialize JPEG decompression object */
    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&cinfo); // 分配并初始化JPEG解压缩对象

    /* Step 2: specify data source (eg, a file) */
    jpeg_stdio_src(&cinfo, infile); // 指定jpeg图像数据源

    /* Step 3: read file parameters with jpeg_read_header() */
    jpeg_read_header(&cinfo, TRUE); // 使用jpeg_read_header读取文件参数

    /* Step 4: set parameters for decompression */
    /* Step 5: Start decompressor */
    jpeg_start_decompress(&cinfo); // 启动解压缩程序

    cinfo.out_color_space = JCS_RGB; // JCS_EXT_BGR;

    // 图片每一行占用字节数
    int row_stride = cinfo.output_width * cinfo.output_components;
    // 输出行缓冲区
    /* Output row buffer */
    JSAMPARRAY buffer = (*cinfo.mem->alloc_sarray)((j_common_ptr)&cinfo, JPOOL_IMAGE, row_stride, 1);

    // 获取图片的宽高和每一个像素占用字节数
    width = cinfo.output_width;
    height = cinfo.output_height;
    channels = cinfo.output_components;

    // 申请rgb数据内存空间
    std::unique_ptr<unsigned char[]> data(new unsigned char[width * height * channels]);

    /* Step 6: while (scan lines remain to be read) */
    for (int j = 0; j < cinfo.output_height; ++j)
    {
        jpeg_read_scanlines(&cinfo, buffer, 1);
        unsigned char *p = data.get() + j * row_stride;
        memcpy(p, buffer[0], row_stride); // 拷贝行数据内容到内存
    }

    /* Step 7: Finish decompression */
    jpeg_finish_decompress(&cinfo); // 结束解码jpeg文件

    /* Step 8: Release JPEG decompression object */
    jpeg_destroy_decompress(&cinfo); // 释放JPEG解压缩对象
    fclose(infile);                  // 关闭jpeg文件

    return data;
}

/**
 * @brief Blog: https://blog.csdn.net/fengbingchun/article/details/89715416
 * @brief 解码jpeg图片，获取图片信息
 *
 * @param name jpeg图片路径
 * @return int
 */
int parse_jpeg_file(const char *name)
{
    FILE *infile = nullptr;
    if ((infile = fopen(name, "rb")) == nullptr)
    {
        fprintf(stderr, "can't open %s\n", name);
        return -1;
    }

    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;
    cinfo.err = jpeg_std_error(&jerr);

    /* Now we can initialize the JPEG decompression object. */
    jpeg_create_decompress(&cinfo);

    /* Step 2: specify data source (eg, a file) */
    jpeg_stdio_src(&cinfo, infile);

    /* Step 3: read file parameters with jpeg_read_header() */
    jpeg_read_header(&cinfo, TRUE);
    fprintf(stdout, "image_width = %d\n", cinfo.image_width);
    fprintf(stdout, "image_height = %d\n", cinfo.image_height);
    fprintf(stdout, "num_components = %d\n", cinfo.num_components);

    /* Step 4: set parameters for decompression */
    cinfo.scale_num = 2;
    cinfo.scale_denom = 4;

    /* Step 5: Start decompressor */
    jpeg_start_decompress(&cinfo);
    fprintf(stdout, "output_width = %d\n", cinfo.output_width);
    fprintf(stdout, "output_height = %d\n", cinfo.output_height);
    fprintf(stdout, "output_components = %d\n", cinfo.output_components);

    /* JSAMPLEs per row in output buffer */
    int row_stride = cinfo.output_width * cinfo.output_components;
    /* Make a one-row-high sample array that will go away when done with image */
    JSAMPARRAY buffer = (*cinfo.mem->alloc_sarray)((j_common_ptr)&cinfo, JPOOL_IMAGE, row_stride, 1);

    /* Step 6: while (scan lines remain to be read) */
    while (cinfo.output_scanline < cinfo.output_height)
    {
        jpeg_read_scanlines(&cinfo, buffer, 1);
    }

    /* Step 7: Finish decompression */
    jpeg_finish_decompress(&cinfo);

    /* Step 8: Release JPEG decompression object */
    jpeg_destroy_decompress(&cinfo);

    fclose(infile);

    return 0;
}

/**
 * @brief 把rgb数据写入jpeg图片
 *
 * @param data rgb数据
 * @param width 图片宽
 * @param height 图片高
 * @param channels 每一个像素占用字节
 * @param color_space 颜色空间
 * @param quality 压缩质量
 * @param name 输出jpeg图片路径
 * @return int
 */
int write_jpeg_file(const unsigned char *data, int width, int height, int channels, J_COLOR_SPACE color_space, int quality, const char *name)
{
    /* Step 1: allocate and initialize JPEG compression object */
    struct jpeg_compress_struct cinfo;
    struct jpeg_error_mgr jerr;
    cinfo.err = jpeg_std_error(&jerr);

    /* Now we can initialize the JPEG compression object. */
    jpeg_create_compress(&cinfo);

    /* Step 2: specify data destination (eg, a file) */
    FILE *outfile = nullptr;
    if ((outfile = fopen(name, "wb")) == nullptr)
    {
        fprintf(stderr, "can't open file: %s\n", name);
        return -1;
    }
    jpeg_stdio_dest(&cinfo, outfile);

    /* Step 3: set parameters for compression */
    cinfo.image_width = width;
    cinfo.image_height = height;
    cinfo.input_components = channels;
    cinfo.in_color_space = color_space;

    jpeg_set_defaults(&cinfo);
    jpeg_set_quality(&cinfo, quality, TRUE);

    /* Step 4: Start compressor */
    jpeg_start_compress(&cinfo, TRUE);

    /* Step 5: while (scan lines remain to be written) */
    int row_stride = width * channels;
    int line = 0;
    JSAMPROW row_pointer[1];

    while (line < cinfo.image_height)
    {
        row_pointer[0] = (JSAMPROW)&data[line * row_stride];
        jpeg_write_scanlines(&cinfo, row_pointer, 1);
        ++line;
    }

    /* Step 6: Finish compression */
    jpeg_finish_compress(&cinfo);
    fclose(outfile);

    /* Step 7: release JPEG compression object */
    jpeg_destroy_compress(&cinfo);

    return 0;
}

int get_jpeg_compress_data(const unsigned char *data, int width, int height, int channels, J_COLOR_SPACE color_space, int quality, unsigned char **out_buffer, unsigned long out_buffer_size, unsigned long &free_in_buffer)
{
    printf("%s():: Line,%d\n", __FUNCTION__, __LINE__);
    /* Step 1: allocate and initialize JPEG compression object */
    struct jpeg_compress_struct cinfo;
    struct jpeg_error_mgr jerr;
    cinfo.err = jpeg_std_error(&jerr);

    /* Now we can initialize the JPEG compression object. */
    jpeg_create_compress(&cinfo);

    printf("%s():: Line,%d\n", __FUNCTION__, __LINE__);
    /* Step 2: specify data destination (eg, a file) */
    jpeg_mem_dest(&cinfo, out_buffer, &out_buffer_size);

    /* Step 3: set parameters for compression */
    cinfo.image_width = width;
    cinfo.image_height = height;
    cinfo.input_components = channels;
    cinfo.in_color_space = color_space;

    printf("%s():: Line,%d\n", __FUNCTION__, __LINE__);
    jpeg_set_defaults(&cinfo);
    jpeg_set_quality(&cinfo, quality, TRUE);

    printf("%s():: Line,%d\n", __FUNCTION__, __LINE__);
    /* Step 4: Start compressor */
    jpeg_start_compress(&cinfo, TRUE);

    /* Step 5: while (scan lines remain to be written) */
    int row_stride = width * channels;
    int line = 0;
    JSAMPROW row_pointer[1];

    printf("%s():: Line,%d\n", __FUNCTION__, __LINE__);
    while (line < cinfo.image_height)
    {
        row_pointer[0] = (JSAMPROW)&data[line * row_stride];
        jpeg_write_scanlines(&cinfo, row_pointer, 1);
        ++line;
    }

    printf("%s():: Line,%d\n", __FUNCTION__, __LINE__);
    /* Step 6: Finish compression */
    jpeg_finish_compress(&cinfo);

    free_in_buffer = cinfo.dest->free_in_buffer;

    /* Step 7: release JPEG compression object */
    jpeg_destroy_compress(&cinfo);

    return 0;
}

int get_jpeg_compress_data2(const unsigned char *data, int width, int height, int pixelFormat, unsigned char **jpegBuf, unsigned long *jpegSize, int jpegSubsamp, int jpegQual, int flags)
{
    tjhandle handle = tjInitCompress();
    int ret = tjCompress2(handle, data, width, 0, height, pixelFormat, jpegBuf, jpegSize, jpegSubsamp, jpegQual, flags);
    tjDestroy(handle);

    return 0;
}

int test_libjpeg_turbo_compress()
{
    printf("%s():: Line,%d\n", __FUNCTION__, __LINE__);
#ifdef _MSC_VER
    std::string image_path{"E:/GitCode/OCR_Test/test_data/"};
#else
    std::string image_path{"./jepg-resource/"}; // 源目录
    std::string out_image_path{"./resource/"};  // 输出目录
#endif
    std::string name = image_path + "libjpeg-turbo-test-image.jpg";

    // 先解码jpeg图片
    int quality = 50; // 压缩质量
    int width;        // 图片宽
    int height;       // 图片高
    int channels;     // 每一个像素占用的字节数
    long long t1 = Timer::getNowTime();
    std::unique_ptr<unsigned char[]> data = get_jpeg_decompress_data(name.c_str(), width, height, channels);
    long long t2 = Timer::getNowTime();
    if (data == nullptr)
    {
        fprintf(stderr, "fail to decompress: %s\n", name.c_str());
        return -1;
    }
    fprintf(stdout, "decompress time 1: %lldms, width: %d, height: %d, channels: %d\n", t2 - t1, width, height, channels);
    unsigned char *p = data.get();
    int length = width * height * channels;

    // 方式1获取压缩图片数据
    std::unique_ptr<unsigned char[]> data1(new unsigned char[length]); // 申请压缩后的内存空间
    unsigned char *p1 = data1.get();
    unsigned long free_in_buffer;

    t1 = Timer::getNowTime();
    get_jpeg_compress_data(p, width, height, 3, JCS_EXT_BGR, quality, &p1, length, free_in_buffer);
    t2 = Timer::getNowTime();
    fprintf(stdout, "compress time1: %lldms\n", t2 - t1);

    // 把压缩后的数据写入文件
    name = out_image_path + "result1_lena.jpg";
    FILE *outfile = nullptr;
    if ((outfile = fopen(name.c_str(), "wb")) == nullptr)
    {
        fprintf(stderr, "can't open file: %s\n", name.c_str());
        return -1;
    }
    fwrite(data1.get(), sizeof(unsigned char), length - free_in_buffer, outfile);
    fclose(outfile);

    // 方式2获取压缩图片数据
    std::unique_ptr<unsigned char[]> data2(new unsigned char[length]);
    unsigned char *p2 = data1.get();
    unsigned long jpegSize = length;

    unsigned char *pp = nullptr;
    t1 = Timer::getNowTime();
    get_jpeg_compress_data2(p, width, height, TJPF_BGR, &p2, &jpegSize, TJSAMP_420, quality, 0);
    // get_jpeg_compress_data2(p, width, height, JCS_RGB, &p2, &jpegSize, TJSAMP_420, quality, 0);
    t2 = Timer::getNowTime();
    fprintf(stdout, "compress time2: %lldms\n", t2 - t1);

    name = out_image_path + "result2_lena.jpg";
    FILE *outfile2 = nullptr;
    if ((outfile2 = fopen(name.c_str(), "wb")) == nullptr)
    {
        fprintf(stderr, "can't open file: %s\n", name.c_str());
        return -1;
    }
    fwrite(p2, sizeof(unsigned char), jpegSize, outfile2);
    fclose(outfile2);

    return 0;
}

/**
 * @brief 压缩jpeg图片数据
 *
 * @return int
 */
int test_libjpeg_turbo()
{
    printf("%s():: Line,%d\n", __FUNCTION__, __LINE__);

#ifdef _MSC_VER
    std::string image_path{"E:/GitCode/OCR_Test/test_data/"};
#else
    std::string image_path{"./jepg-resource/"}; // 源文件目录
    std::string out_image_path{"./resource/"};  // 输出文件目录
#endif
    std::string name1 = image_path + "libjpeg-turbo-test-image.jpg";

    parse_jpeg_file(name1.c_str()); // 获取jpeg图片信息

    std::string name2 = out_image_path + "lena.png";
    std::string name3 = out_image_path + "lena.jpg";

    // 解码jpeg图片
    int width;
    int height;
    int channels;
    long long t1 = Timer::getNowTime();
    std::unique_ptr<unsigned char[]> data = get_jpeg_decompress_data(name1.c_str(), width, height, channels);
    long long t2 = Timer::getNowTime();
    if (data == nullptr)
    {
        fprintf(stderr, "fail to decompress: %s\n", name1.c_str());
        return -1;
    }
    fprintf(stdout, "decompress time 1: %lldms, width: %d, height: %d, channels: %d\n", t2 - t1, width, height, channels);
    unsigned char *p = data.get();

    int quality = 80; // 压缩质量

    // 把rgb图片数据按BGR写入jpeg图片
    write_jpeg_file(p, width, height, 3, JCS_EXT_BGR, quality, name3.c_str()); // bgr data

    // 把rgb图片数据按RGB写入jpeg图片
    name3 = out_image_path + "lena2.jpg";
    write_jpeg_file(p, width, height, 3, JCS_RGB, quality, name3.c_str()); // rgb data
    printf("%s():: Line,%d\n", __FUNCTION__, __LINE__);

    // 把rgb图片数据按BGR写入jpeg图片,会抛出异常 “Bogus input colorspace”
    name3 = out_image_path + "lena3.jpg";
    printf("%s():: Line,%d\n", __FUNCTION__, __LINE__);
    // write_jpeg_file(p, width, height, 3, JCS_GRAYSCALE, quality, name3.c_str()); // gray data
    printf("%s():: Line,%d\n", __FUNCTION__, __LINE__);

    // 获取压缩后的jpeg图片数据,然后保存为jpeg图片
    int length = width * height * 3;
    std::unique_ptr<unsigned char[]> data2(new unsigned char[length]);
    unsigned char *p1 = data2.get();
    unsigned long free_in_buffer;

    // 获取压缩后的jpeg图片数据,然后保存为jpeg图片,会抛出异常 “Bogus input colorspace”
    // get_jpeg_compress_data(p, width, height, 3, JCS_GRAYSCALE, quality, &p1, length, free_in_buffer);
    get_jpeg_compress_data(p, width, height, 3, JCS_RGB, quality, &p1, length, free_in_buffer);

    name3 = out_image_path + "lena4.jpg";
    FILE *outfile = nullptr;
    if ((outfile = fopen(name3.c_str(), "wb")) == nullptr)
    {
        fprintf(stderr, "can't open file: %s\n", name3.c_str());
        return -1;
    }
    fwrite(p1, sizeof(unsigned char), length - free_in_buffer, outfile);
    fclose(outfile);

    return 0;
}