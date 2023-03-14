#include "../include/bitmap/Bitmap.h"

Bitmap::Bitmap()
{
    std::cout << "Bitmap::Bitmap()构造函数" << std::endl;
}

/**
 * @brief 创建BMP图片信息
 *
 * @param width
 * @param height
 * @param depth
 */
bool Bitmap::bmpCreate(uint32_t width, uint32_t height, uint32_t depth)
{
    std::cout << "Bitmap::bmpCreate():: width:" << width << ",height:" << height << ",depth:" << depth << std::endl;
    this->bmpFileHeader = new BitmapFileHeader(); // BMP文件信息头
    this->bmpInfoHeader = new BitmapInfoHeader(); // BMP位图信息头
    if ((bmpFileHeader == NULL) || (bmpInfoHeader == NULL))
    {
        return false;
    }

    // 1. 设置bmp图片,文件信息头,一共14个字节
    bmpFileHeader->bfType = 0x4d42; // 文件类型BM
    bmpFileHeader->bfReserved1 = 0;
    bmpFileHeader->bfReserved2 = 0;
    // bmpFileHeader->bfSize = 14 + 40 + width * height * (depth / 8); // 整个 BMP 文件的大小
    bmpFileHeader->bfOffBits = 0x36; // 偏移数54位

    // 4字节对齐
    double bytesPerPixel = (depth * 1.0 / 8.0);
    unsigned int bytesPerLine = (unsigned int)ceil(bytesPerPixel * width);
    if ((bytesPerLine % 4) != 0)
    {
        bytesPerLine += (4 - bytesPerLine % 4);
    }
    bmpFileHeader->bfSize = 14 + 40 + bytesPerLine * height;
    std::cout << "Bitmap::bmpCreate():: bytesPerPixel:" << bytesPerPixel << ",bytesPerLine:" << bytesPerLine << std::endl;

    // 2.设置bmp图片,位图信息头,一共40个字节
    bmpInfoHeader->biSize = sizeof(BitmapInfoHeader);
    bmpInfoHeader->biWidth = width;
    bmpInfoHeader->biHeight = -height;
    bmpInfoHeader->biPlanes = 1;
    bmpInfoHeader->biBitCount = depth;
    bmpInfoHeader->biSizeImage = 0;
    bmpInfoHeader->biCompression = 0;
    bmpInfoHeader->biXPelsPerMeter = 5000;
    bmpInfoHeader->biYPelsPerMeter = 5000;
    bmpInfoHeader->biClrUsed = 0;
    bmpInfoHeader->biClrImportant = 0;
    std::cout << "Bitmap::bmpCreate():: " << sizeof(BitmapFileHeader) << "," << sizeof(BitmapInfoHeader) << "," << bmpFileHeader->bfSize << std::endl;

    // 申请保存图片像素的内存
    bool isMalloc = bmpMallocPixels();
    return isMalloc;
}
/**
 * @brief 申请图片像素信息内存
 *
 * @return true
 * @return false
 */
bool Bitmap::bmpMallocPixels()
{
    std::cout << "Bitmap::bmpMallocPixels():: " << std::endl;
    this->pixels = (RGBPixel **)malloc(sizeof(RGBPixel *) * (abs(bmpInfoHeader->biHeight))); // 申请行(高)数内存
    if (pixels == NULL)
    {
        return false;
    }
    bool isMallocError = false;
    for (int i = 0; i < abs(bmpInfoHeader->biHeight); i++)
    {
        // pixels[i] = (RGBPixel *)malloc(sizeof(RGBPixel) * (bmpInfoHeader->biWidth));  // 申请每一行的宽(列)的内存
        *(pixels + i) = (RGBPixel *)malloc(sizeof(RGBPixel) * (bmpInfoHeader->biWidth)); // 申请每一行的宽(列)的内存
        if (*(pixels + i) == nullptr)
        {
            isMallocError = true;
            break;
        }

        for (int j = 0; j < bmpInfoHeader->biWidth; j++)
        {
            // pixels[i][j].red = 66;
            // pixels[i][j].green = 255;
            // pixels[i][j].bulue = 77;
            pixels[i][j].red = 255;
            pixels[i][j].green = 255;
            pixels[i][j].bulue = 255;
        }
    }

    if (isMallocError)
    {
        return false;
    }
    // 打印图片像素初始颜色信息
    // displayPixels();
    return true;
}

/**
 * @brief 打印图片像素颜色信息
 *
 */
void Bitmap::displayPixels()
{
    std::cout << "Bitmap::displayPixels()::" << std::endl;
    for (int i = 0; i < abs(bmpInfoHeader->biHeight); i++)
    {
        for (int j = 0; j < bmpInfoHeader->biWidth; j++)
        {
            unsigned int r = (*(*(pixels + i) + j)).red;
            unsigned int g = (*(*(pixels + i) + j)).green;
            unsigned int b = (*(*(pixels + i) + j)).bulue;
            std::cout << "(" << r << "," << g << "," << b << ")"
                      << " ";
        }
        std::cout << std::endl;
    }
}

/**
 * @brief 释放图片像素信息内存
 *
 */
void Bitmap::bmpFreePixels()
{
    std::cout << "Bitmap::bmpFreePixels():: " << std::endl;
}

/**
 * @brief 为每个位置设置像素信息
 *
 * @param x x位置
 * @param y y位置
 * @param pixel 像素信息
 * @return true
 * @return false
 */
bool Bitmap::bmpSetPixel(unsigned int x, unsigned int y, RGBPixel pixel)
{
    // std::cout << "Bitmap::bmpSetPixel():: " << std::endl;
    if ((bmpInfoHeader == NULL) || (pixels == NULL))
    {
        return false;
    }
    // pixels[x][y].red = pixel.red;
    // pixels[x][y].green = pixel.green;
    // pixels[x][y].bulue = pixel.bulue;
    (*(*(pixels + x) + y)).red = pixel.red;
    (*(*(pixels + x) + y)).green = pixel.green;
    (*(*(pixels + x) + y)).bulue = pixel.bulue;

    unsigned int r = (*(*(pixels + x) + y)).red;
    unsigned int g = (*(*(pixels + x) + y)).green;
    unsigned int b = (*(*(pixels + x) + y)).bulue;
    // std::cout << "Bitmap::bmpSetPixel()::(" << r << "," << g << "," << b << ")" << std::endl;
    return true;
}

Bitmap::~Bitmap()
{
    std::cout << "Bitmap::~Bitmap()析构函数" << std::endl;
}

/**
 * @brief 是否是大端字节序
 *
 * @return true
 * @return false
 */
bool Bitmap::isBigEndian(void)
{
    uint16_t value = 0x0001;
    return (*(uint8_t *)&value) != 0x01;
}

void Bitmap::bmpHeaderSwapEndianess(BitmapFileHeader *bmpHeader)
{
    bmpHeader->bfType = UINT32_SWAP_LE_BE_CONSTANT(bmpHeader->bfType);
    bmpHeader->bfSize = UINT32_SWAP_LE_BE_CONSTANT(bmpHeader->bfSize);
    bmpHeader->bfReserved1 = UINT16_SWAP_LE_BE_CONSTANT(bmpHeader->bfReserved1);
    bmpHeader->bfReserved2 = UINT16_SWAP_LE_BE_CONSTANT(bmpHeader->bfReserved2);
    bmpHeader->bfOffBits = UINT32_SWAP_LE_BE_CONSTANT(bmpHeader->bfOffBits);
}

void Bitmap::bmpInfoHeaderSwapEndianess(BitmapInfoHeader *bmpInfoHeader)
{
    std::cout << "Bitmap::bmpInfoHeaderSwapEndianess()::" << std::endl;
}

/**
 * @brief 写入bmp位图文件头
 *
 * @param bmpHeader
 * @param fp
 */
void Bitmap::writeBmpFileHeader(BitmapFileHeader *bmpHeader, FILE *fp)
{
    std::cout << "Bitmap::writeBmpFileHeader():: isBigEndian:" << isBigEndian() << std::endl;
    if (isBigEndian())
    {
        bmpHeaderSwapEndianess(bmpHeader);
    }

    fwrite(&(bmpHeader->bfType), sizeof(bmpHeader->bfType), 1, fp);
    fwrite(&(bmpHeader->bfSize), sizeof(bmpHeader->bfSize), 1, fp);
    fwrite(&(bmpHeader->bfReserved1), sizeof(bmpHeader->bfReserved1), 1, fp);
    fwrite(&(bmpHeader->bfReserved2), sizeof(bmpHeader->bfReserved2), 1, fp);
    fwrite(&(bmpHeader->bfOffBits), sizeof(bmpHeader->bfOffBits), 1, fp);
}

/**
 * @brief 写入bmp位图信息头
 *
 * @param bmpInfoHeader
 * @param fp
 */
void Bitmap::writeBmpInfoHeader(BitmapInfoHeader *bmpInfoHeader, FILE *fp)
{
    std::cout << "Bitmap::writeBmpInfoHeader():: " << std::endl;

    if (isBigEndian())
        bmpInfoHeaderSwapEndianess(bmpInfoHeader);

    fwrite(&(bmpInfoHeader->biSize), sizeof(uint32_t), 1, fp);
    fwrite(&(bmpInfoHeader->biWidth), sizeof(uint32_t), 1, fp);
    fwrite(&(bmpInfoHeader->biHeight), sizeof(uint32_t), 1, fp);
    fwrite(&(bmpInfoHeader->biPlanes), sizeof(uint16_t), 1, fp);
    fwrite(&(bmpInfoHeader->biBitCount), sizeof(uint16_t), 1, fp);
    fwrite(&(bmpInfoHeader->biSizeImage), sizeof(uint32_t), 1, fp);
    fwrite(&(bmpInfoHeader->biCompression), sizeof(uint32_t), 1, fp);
    fwrite(&(bmpInfoHeader->biXPelsPerMeter), sizeof(uint32_t), 1, fp);
    fwrite(&(bmpInfoHeader->biYPelsPerMeter), sizeof(uint32_t), 1, fp);
    fwrite(&(bmpInfoHeader->biClrUsed), sizeof(uint32_t), 1, fp);
    fwrite(&(bmpInfoHeader->biClrImportant), sizeof(uint32_t), 1, fp);
}

/**
 * @brief 向文件写入bmp图片像素信息
 *
 * @param pixels 像素信息的二级指针
 * @param fp 文件
 */
void Bitmap::writeBmpPixels(RGBPixel **bmpPixels, FILE *fp)
{
    std::cout << "Bitmap::writeBmpPixels()::" << std::endl;
    for (int i = 0; i < abs(bmpInfoHeader->biHeight); i++)
    {
        for (int j = 0; j < bmpInfoHeader->biWidth; j++)
        {
            unsigned int r = (*(*(bmpPixels + i) + j)).red;
            unsigned int g = (*(*(bmpPixels + i) + j)).green;
            unsigned int b = (*(*(bmpPixels + i) + j)).bulue;
            // std::cout << "(" << r << "," << g << "," << b << ")" << " ";
            fwrite(&(b), sizeof(unsigned char), 1, fp); // 把每个像素的bulue颜色信息写入文件
            fwrite(&(g), sizeof(unsigned char), 1, fp); // 把每个像素的green颜色信息写入文件
            fwrite(&(r), sizeof(unsigned char), 1, fp); // 把每个像素的red颜色信息写入文件
        }
        // std::cout << std::endl;
    }
}

/**
 * @brief 写入彩虹数据到指定文件
 *
 * @param outputFile 文件名
 * @return true 写入数据成功
 * @return false 写入数据成功
 */
bool Bitmap::save(const char *outputFile)
{
    std::cout << "Bitmap::save():: outputFile:" << outputFile << std::endl;
    std::cout << "Bitmap::save():: isBigEndian:" << isBigEndian() << std::endl;
    // 打开文件
    FILE *bitmapFile = fopen(outputFile, "wb+");
    if (bitmapFile == nullptr) //! rgbFile
    {
        std::cout << "创建文件错误:" << outputFile << std::endl;
        return false;
    }
    // 1. 向文件中写入,图片文件信息头,位图信息头
    writeBmpFileHeader(bmpFileHeader, bitmapFile);
    writeBmpInfoHeader(bmpInfoHeader, bitmapFile);

    // 2. 向文件中写入颜色数据
    writeBmpPixels(pixels, bitmapFile);

    // 关闭文件
    fclose(bitmapFile);
    return true;
}

/**
 * @brief 释放资源
 *
 */
void Bitmap::bmpDestroy()
{
    std::cout << "Bitmap::bmpDestroy()" << std::endl;
}