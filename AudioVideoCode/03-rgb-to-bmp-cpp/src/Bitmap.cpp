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
    bmpInfoHeader->biWidth = abs((int)width);
    bmpInfoHeader->biHeight = -abs((int)height);
    bmpInfoHeader->biPlanes = 1;
    bmpInfoHeader->biBitCount = depth;
    bmpInfoHeader->biSizeImage = 0;
    bmpInfoHeader->biCompression = 0;
    bmpInfoHeader->biXPelsPerMeter = 5000;
    bmpInfoHeader->biYPelsPerMeter = 5000;
    bmpInfoHeader->biClrUsed = 0;
    bmpInfoHeader->biClrImportant = 0;
    std::cout << "Bitmap::bmpCreate():: " << sizeof(BitmapFileHeader) << "," << sizeof(BitmapInfoHeader) << "," << bmpFileHeader->bfSize << std::endl;

    bool isMallocPixel = bmpMallocPixels(); // 申请保存图片像素的内存
    if (isMallocPixel)
    {
        bool isBmpDataMalloc = bmpDataMalloc(); // 申请图片像素信息rgb24字节内存
        return isBmpDataMalloc;
    }
    return false;
}

/**
 * @brief 申请图片像素信息rgb24字节内存
 *
 * @return true
 * @return false
 */
bool Bitmap::bmpDataMalloc()
{
    uint32_t bmpHeadLength = 14 + 40; // BMP头文件长度
    uint32_t size = bmpFileHeader->bfSize - bmpHeadLength;
    std::cout << "Bitmap::" << __FUNCTION__ << "():: Line " << __LINE__ << ",size:" << size << std::endl;
    bmpData = (uint8_t *)malloc(sizeof(uint8_t) * size * 3);
    std::cout << "Bitmap::" << __FUNCTION__ << "():: Line " << __LINE__ << ",bmpData:" << bmpData << std::endl;
    if (bmpData == NULL)
    {
        std::cout << "Bitmap::" << __FUNCTION__ << "():: Line " << __LINE__ << ",bmpData is null" << bmpData << std::endl;
        return false;
    }
    return true;
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
    uint32_t color = ((r & 0xff) << 16) | ((g & 0xff) << 8) | ((b & 0xff) << 0);
    // std::cout << "Bitmap::bmpSetPixel()::(" << std::dec << x << "," << y << "),color(" << std::hex << color << ")" << std::endl;
    return true;
}

Bitmap::~Bitmap()
{
    std::cout << "Bitmap::~Bitmap()析构函数" << std::endl;
    bmpDestroy();
}

/**
 * @brief 释放图片像素信息内存
 *
 */
void Bitmap::bmpFreePixels()
{
    std::cout << "Bitmap::bmpFreePixels():: " << std::endl;
    for (int i = 0; i < abs(bmpInfoHeader->biHeight); i++)
    {
        // free(pixels[i]);     // 释放每一行指针
        free(*(pixels + i)); // 释放每一行指针
    }
    free(pixels); // 释放二维数组指针
    pixels = NULL;
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
    // std::cout << "Bitmap::" << __FUNCTION__ << "():: Line" << __LINE__ << " " << bmpData << std::endl;
    uint32_t bmpHeadLength = 14 + 40; // BMP格式图片头文件大小
    if (bmpData == NULL)
    {
        return;
    }
    std::cout << "Bitmap::" << __FUNCTION__ << "():: Line " << __LINE__ << std::endl;
    for (int i = 0; i < abs(bmpInfoHeader->biHeight); i++)
    {
        // std::cout << "Bitmap::" << __FUNCTION__ << "():: Line " << __LINE__ << std::endl;
        for (int j = 0; j < bmpInfoHeader->biWidth; j++)
        {
            uint8_t r = ((*(*(bmpPixels + i) + j)).red) & 0xff;
            uint8_t g = ((*(*(bmpPixels + i) + j)).green) & 0xff;
            uint8_t b = ((*(*(bmpPixels + i) + j)).bulue) & 0xff;
            uint32_t color = ((r & 0xff) << 16) | ((g & 0xff) << 8) | ((b & 0xff) << 0);
            // std::cout << "Bitmap::" << __FUNCTION__ << "():: Line " << __LINE__ << ",color(" << std::hex << color << ")" << std::endl;

            // 可行，只是没有4字节对齐
            // fwrite(&b, sizeof(uint8_t), 1, fp); // 把每个像素的bulue颜色信息写入文件
            // fwrite(&g, sizeof(uint8_t), 1, fp); // 把每个像素的green颜色信息写入文件
            // fwrite(&r, sizeof(uint8_t), 1, fp); // 把每个像素的red颜色信息写入文件

            // 注意要4字节对齐
            // uint32_t pad = (bmpInfoHeader->biWidth * -3UL) & 3; // 4字节对齐
            uint32_t pad = 4 - (bmpInfoHeader->biWidth * 3 % 4);
            uint32_t index = i * (3 * bmpInfoHeader->biWidth + pad) + j * 3;
            // std::cout << "Bitmap::" << __FUNCTION__ << "():: Line " << __LINE__ << std::dec << "(" << i << "," << j << "),index:" << index + bmpHeadLength << ",color(" << std::hex << color << ")" << std::endl;
            uint8_t *pData = bmpData + index;
            memcpy(pData, &b, sizeof(uint8_t));     // 拷贝数据到内存
            memcpy(pData + 1, &g, sizeof(uint8_t)); // 拷贝数据到内存
            memcpy(pData + 2, &r, sizeof(uint8_t)); // 拷贝数据到内存
        }
        // std::cout << std::endl;
    }
    uint32_t size = bmpFileHeader->bfSize - bmpHeadLength;
    fwrite(bmpData, size, 1, fp); // 把内存中的BMP格式rgb数据写入文件
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
    bmpFreePixels();
    if (bmpFileHeader != NULL)
    {
        delete bmpFileHeader;
    }
    bmpFileHeader = NULL;
    if (bmpInfoHeader != NULL)
    {
        delete bmpInfoHeader;
    }
    bmpInfoHeader = NULL;
    if (bmpData != NULL)
    {
        free(bmpData);
    }
    bmpData = NULL;
}