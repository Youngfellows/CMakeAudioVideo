#ifndef FBC_OCR_TEST_LIBJPEG_TURBO_FUNSET_HPP_
#define FBC_OCR_TEST_LIBJPEG_TURBO_FUNSET_HPP_

#include <memory>
#include <chrono>
#include <turbojpeg.h>
#include <jpeglib.h>

class Timer
{
public:
    /**
     * @brief 获取当前系统时间
     *
     * @return long long
     */
    static long long getNowTime()
    { // milliseconds
        auto now = std::chrono::system_clock::now();
        return std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
    }
};

/**
 * @brief 解码jpeg图片文件
 *
 * @return int
 */
int test_libjpeg_turbo_decompress();

/**
 * @brief jpeg图片解码
 *
 * @param image_name jpeg图片路径
 * @param width 宽
 * @param height 高
 * @param channels 位宽,jpeg图片每一个像素占用字节
 * @return std::unique_ptr<unsigned char[]> 返回jpeg图片解码后的rgb数据
 */
std::unique_ptr<unsigned char[]> get_jpeg_decompress_data(const char *image_name, int &width, int &height, int &channels); // jpeg_read_scanlines

/**
 * @brief jpeg图片解码
 *
 * @param image_name jpeg图片路径
 * @param width jpeg图片宽
 * @param height jpeg图片高
 * @param channels jpeg图片每一个像素占用字节
 * @return std::unique_ptr<unsigned char[]>,返回jpeg图片解码后的rgb数据
 */
std::unique_ptr<unsigned char[]> get_jpeg_decompress_data2(const char *image_name, int &width, int &height, int &channels);

/**
 * @brief 压缩jpeg图片数据
 *
 * @return int
 */
int test_libjpeg_turbo();

/**
 * @brief 解码jpeg图片，获取图片信息
 *
 * @param name jpeg图片路径
 * @return int
 */
int parse_jpeg_file(const char *name);

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
int write_jpeg_file(const unsigned char *data, int width, int height, int channels, J_COLOR_SPACE color_space, int quality, const char *name);

int test_libjpeg_turbo_compress();
int get_jpeg_compress_data(const unsigned char *data, int width, int height, int channels, J_COLOR_SPACE color_space, int quality, unsigned char **out_buffer, unsigned long out_buffer_size, unsigned long &free_in_buffer);
int get_jpeg_compress_data2(const unsigned char *data, int width, int height, int pixelFormat, unsigned char **jpegBuf, unsigned long *jpegSize, int jpegSubsamp, int jpegQual, int flags);

#endif // FBC_OCR_TEST_LIBJPEG_TURBO_FUNSET_HPP_