#include "../include/TurboJpegHelp.h"

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
int encode_JPEG_file(char *strImageName, uint8_t *image_buffer, int image_height, int image_width, int quality)
{

    struct jpeg_compress_struct cinfo;

    struct jpeg_error_mgr jerr;
    /* More stuff */
    FILE *outfile;           /* target file */
    JSAMPROW row_pointer[1]; /* pointer to JSAMPLE row[s] */
    int row_stride;          /* physical row width in image buffer */

    cinfo.err = jpeg_std_error(&jerr);
    /* Now we can initialize the JPEG compression object. */
    jpeg_create_compress(&cinfo);

    if ((outfile = fopen(strImageName, "wb")) == NULL)
    {
        fprintf(stderr, "can't open %s\n", strImageName);
        // exit(1);
        return -1;
    }
    jpeg_stdio_dest(&cinfo, outfile);

    cinfo.image_width = image_width; /* image width and height, in pixels */
    cinfo.image_height = image_height;
    cinfo.input_components = 3;     /* # of color components per pixel */
    cinfo.in_color_space = JCS_RGB; /* colorspace of input image */

    jpeg_set_defaults(&cinfo);

    jpeg_set_quality(&cinfo, quality, TRUE /* limit to baseline-JPEG values */);

    jpeg_start_compress(&cinfo, TRUE);

    row_stride = image_width * 3; /* JSAMPLEs per row in image_buffer */

    int line = 0;
    while (line < cinfo.image_height)
    {

        // row_pointer[0] = &image_buffer[cinfo.next_scanline * row_stride];
        row_pointer[0] = &image_buffer[line * row_stride];
        jpeg_write_scanlines(&cinfo, row_pointer, 1);

        line++;
    }

    /* Step 6: Finish compression */
    jpeg_finish_compress(&cinfo);
    /* After finish_compress, we can close the output file. */
    fclose(outfile);

    /* Step 7: release JPEG compression object */
    /* This is an important step since it will release a good deal of memory. */
    jpeg_destroy_compress(&cinfo);

    return 0;
}