#include "../include/TurboJpegHelp.h"

/**
 * @brief jpeg格式解码为rgb24
 *
 * @param inJpegName jpeg格式文件路径
 * @param outRgbName rgb24格式文件路径
 * @return int
 */
int decode_JPEG_file(char *inJpegName, char *outRgbName)
{
    const char *TAG = "decode-jpeg::";
    printf("%s%s():: Line,%d\n", TAG, __FUNCTION__, __LINE__);

    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;

    FILE *infile;
    FILE *outfile;

    if ((infile = fopen(inJpegName, "rb")) == NULL)
    {
        fprintf(stderr, "can't open %s\n", inJpegName);
        return -1;
    }
    if ((outfile = fopen(outRgbName, "wb")) == NULL)
    {
        fprintf(stderr, "can't open %s\n", outRgbName);
        return -1;
    }
    // 设置解码错误回调函数
    cinfo.err = jpeg_std_error(&jerr);

    // 为JPEG对象分配空间并初始化
    jpeg_create_decompress(&cinfo);

    // 设置需要解码的jpeg图片源文件
    jpeg_stdio_src(&cinfo, infile);

    // 获取jepg图片头信息
    jpeg_read_header(&cinfo, TRUE);

    printf("image_width = %d\n", cinfo.image_width);           // jpeg图片宽
    printf("image_height = %d\n", cinfo.image_height);         // jpeg图片高
    printf("num_components = %d\n", cinfo.num_components);     // jpeg图片位深
    printf("jpeg_color_space = %d\n", cinfo.jpeg_color_space); // jpeg图片颜色空间

    printf("enter scale M/N:\n");

    // cinfo.out_color_space = JCS_YCbCr;
    printf("scale to : %d/%d\n", cinfo.scale_num, cinfo.scale_denom);

    jpeg_start_decompress(&cinfo);

    // 输出的图象的信息
    printf("output_width = %d\n", cinfo.output_width);
    printf("output_height = %d\n", cinfo.output_height);
    printf("output_components = %d\n", cinfo.output_components);

    int row_stride = cinfo.output_width * cinfo.output_components; // rgb图片每一行占用字节数
    /* Make a one-row-high sample array that will go away when done with image */
    JSAMPARRAY buffer = (JSAMPARRAY)malloc(sizeof(JSAMPROW)); // 申请一个保存chr *数据的二维数组,char **,用保存每一行的数据
    buffer[0] = (JSAMPROW)malloc(sizeof(JSAMPLE) * row_stride);

    struct ImageData imageData = {
        .width = cinfo.image_width,
        .height = cinfo.image_height,
        .pixels = malloc(row_stride * cinfo.image_height)};
    long counter = 0;

    //    tjDecompressToYUV()
    // 逐行读取jpeg数据
    while (cinfo.output_scanline < cinfo.output_height)
    {
        jpeg_read_scanlines(&cinfo, buffer, 1);
        memcpy(imageData.pixels + counter, buffer[0], row_stride); // 拷贝读取到的数据到rgb内存中
        counter += row_stride;
        //        /* jpeg_read_scanlines expects an array of pointers to scanlines.
        //        * Here the array is only one element long, but you could ask for
        //        * more than one scanline at a time if that's more convenient.
        //        */
        //        jpeg_read_scanlines(&cinfo, buffer, 1);
        //        /* Assume put_scanline_someplace wants a pointer and sample count. */
        //        //put_scanline_someplace(buffer[0], row_stride);
        //
        //        fwrite(buffer, row_stride*cinfo.num_components, 1, outfile);
    }

    // 把读取到的rgb数据写入文件
    printf("total size: %ld\n", counter);
    fwrite(imageData.pixels, counter, 1, outfile);

    // jpeg图片界面结束，释放资源
    jpeg_finish_decompress(&cinfo);

    jpeg_destroy_decompress(&cinfo);

    fclose(infile);
    fclose(outfile);
    free(imageData.pixels);

    return 0;
}