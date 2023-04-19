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

    cinfo.err = jpeg_std_error(&jerr);

    jpeg_create_decompress(&cinfo);

    jpeg_stdio_src(&cinfo, infile);

    jpeg_read_header(&cinfo, TRUE);

    printf("image_width = %d\n", cinfo.image_width);
    printf("image_height = %d\n", cinfo.image_height);
    printf("num_components = %d\n", cinfo.num_components);

    printf("enter scale M/N:\n");

    //    cinfo.out_color_space = JCS_YCbCr;
    printf("scale to : %d/%d\n", cinfo.scale_num, cinfo.scale_denom);

    jpeg_start_decompress(&cinfo);

    // 输出的图象的信息
    printf("output_width = %d\n", cinfo.output_width);
    printf("output_height = %d\n", cinfo.output_height);
    printf("output_components = %d\n", cinfo.output_components);

    int row_stride = cinfo.output_width * cinfo.output_components;
    /* Make a one-row-high sample array that will go away when done with image */
    JSAMPARRAY buffer = (JSAMPARRAY)malloc(sizeof(JSAMPROW));
    buffer[0] = (JSAMPROW)malloc(sizeof(JSAMPLE) * row_stride);

    struct ImageData imageData = {
        .width = cinfo.image_width,
        .height = cinfo.image_height,
        .pixels = malloc(row_stride * cinfo.image_height)};
    long counter = 0;

    //    tjDecompressToYUV()

    while (cinfo.output_scanline < cinfo.output_height)
    {
        jpeg_read_scanlines(&cinfo, buffer, 1);
        memcpy(imageData.pixels + counter, buffer[0], row_stride);
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

    printf("total size: %ld\n", counter);
    fwrite(imageData.pixels, counter, 1, outfile);

    jpeg_finish_decompress(&cinfo);

    jpeg_destroy_decompress(&cinfo);

    fclose(infile);
    fclose(outfile);
    free(imageData.pixels);

    return 0;
}