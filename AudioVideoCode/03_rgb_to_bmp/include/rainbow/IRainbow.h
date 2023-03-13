#ifndef IRAINBOW_H
#define IRAINBOW_H
#include "./Config.h"
#include "../bmp/BitmapFileHeader.h"
#include "../bmp/BitmapInfoHeader.h"

/**
 * @brief 彩虹抽象类
 *
 */
class IRainbow
{
private:
public:
    virtual ~IRainbow() = default;
    /**
     * @brief 写入彩虹数据:纯虚函数,子类必须实现
     *
     * @param outputFile 文件名
     * @param width 宽
     * @param height 高
     * @return true 写入数据成功
     * @return false 写入数据成功
     */
    virtual bool writeRainbow(const char *outputFile, int width, int height) = 0;

    /**
     * @brief 写入彩虹数据:纯虚函数,子类必须实现
     *
     * @param outputFile 文件名
     * @param width 宽
     * @param height 高
     * @return true 写入数据成功
     * @return false 写入数据成功
     */
    virtual bool writeRainbow2(const char *outputFile, int width, int height) = 0;

    /**
     * @brief 写入bmp位图文件头
     *
     * @param bmpHeader
     * @param fp
     */
    virtual void writeBmpFileHeader(BitmapFileHeader *bmpHeader, FILE *fp) = 0;

    /**
     * @brief 写入bmp位图信息头
     *
     * @param bmpInfoHeader
     * @param fp
     */
    virtual void writeBmpInfoHeader(BitmapInfoHeader *bmpInfoHeader, FILE *fp) = 0;

    /**
     * @brief 交换bmp位图文件头大端字节序
     *
     * @param bmpHeader
     */
    virtual void bmpHeaderSwapEndianess(BitmapFileHeader *bmpHeader) = 0;

    /**
     * @brief 交换bmp位图信息头大端字节序
     *
     * @param bmpInfoHeader
     */
    virtual void bmpInfoHeaderSwapEndianess(BitmapInfoHeader *bmpInfoHeader) = 0;
};

#endif