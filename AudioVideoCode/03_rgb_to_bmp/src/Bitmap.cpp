#include "../include/bitmap/Bitmap.h"

Bitmap::Bitmap()
{
    std::cout << "Bitmap::Bitmap()构造函数" << std::endl;
    this->initRainbowColors();
}

/**
 * @brief 创建BMP图片信息
 *
 * @param width
 * @param height
 * @param depth
 */
void Bitmap::bmpCreate(uint32_t width, uint32_t height, uint32_t depth)
{
    std::cout << "Bitmap::bmpCreate():: " << std::endl;
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
bool Bitmap::bmpSetPixel(uint32_t x, uint32_t y, RGBPixel pixel)
{
    std::cout << "Bitmap::bmpSetPixel():: " << std::endl;
    return true;
}

void Bitmap::initRainbowColors()
{
    std::cout << "Bitmap::initRainbowColors():: ..." << std::endl;
    int size = sizeof(rainbowColors) / sizeof(uint32_t);
    std::cout << "size:" << size << std::endl;
    // 彩虹的七种颜色
    uint32_t colors[] = {
        0XFF0000, // 赤
        0XFFA500, // 橙
        0XFFFF00, // 黄
        0X00FF00, // 绿
        0X007FFF, // 青
        0X0000FF, // 蓝
        0X8B00FF  // 紫
    };

    for (int i = 0; i < size; i++)
    {
        *(rainbowColors + i) = *(colors + i); // 为数组元素赋值
        // rainbowColors[i] = *(colors + i);     // 为数组元素赋值
        // rainbowColors[i] = colors[i];         // 为数组元素赋值
    }

    // 按照16进制输出
    for (int i = 0; i < size; i++)
    {
        uint32_t color = *(rainbowColors + i); // 获取数组元素
        std::cout << i << "::" << std::uppercase << std::hex << std::setfill('0') << std::setw(6) << color << std::endl;
    }
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
    /**
     *
        dib->header_sz = UINT32_SWAP_LE_BE_CONSTANT(dib->header_sz);
        dib->width = UINT32_SWAP_LE_BE_CONSTANT(dib->width);
        dib->height = UINT32_SWAP_LE_BE_CONSTANT(dib->height);
        dib->nplanes = UINT16_SWAP_LE_BE_CONSTANT(dib->nplanes);
        dib->depth = UINT16_SWAP_LE_BE_CONSTANT(dib->depth);
        dib->compress_type = UINT32_SWAP_LE_BE_CONSTANT(dib->compress_type);
        dib->bmp_bytesz = UINT32_SWAP_LE_BE_CONSTANT(dib->bmp_bytesz);
        dib->hres = UINT32_SWAP_LE_BE_CONSTANT(dib->hres);
        dib->vres = UINT32_SWAP_LE_BE_CONSTANT(dib->vres);
        dib->ncolors = UINT32_SWAP_LE_BE_CONSTANT(dib->ncolors);
        dib->nimpcolors = UINT32_SWAP_LE_BE_CONSTANT(dib->nimpcolors);
     */
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
 * @brief 写入彩虹数据到指定文件
 *
 * @param outputFile 文件名
 * @param width 宽
 * @param height 高
 * @return true 写入数据成功
 * @return false 写入数据成功
 */
bool Bitmap::save(const char *outputFile, int width, int height)
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

    // 设置bmp图片,文件信息,一共14个字节
    // uint16_t bfType = 0x4d42;    // 文件类型BM
    BitmapFileHeader fileHeader; // 图片文件头
    fileHeader.bfType = 0x4d42;  // 文件类型BM
    fileHeader.bfReserved1 = 0;
    fileHeader.bfReserved2 = 0;
    fileHeader.bfSize = sizeof(BitmapFileHeader) + sizeof(BitmapInfoHeader) + width * height * 3;
    std::cout << sizeof(BitmapFileHeader) << "," << sizeof(BitmapInfoHeader) << "," << fileHeader.bfSize << std::endl;
    fileHeader.bfOffBits = 0x36; // 偏移数54位

    // 设置bmp图片,位图信息头,一共40个字节
    BitmapInfoHeader infoHeader;
    infoHeader.biSize = sizeof(BitmapFileHeader);
    infoHeader.biWidth = width;
    // infoHeader.biHeight = height;
    infoHeader.biHeight = -height;
    infoHeader.biPlanes = 1;
    infoHeader.biBitCount = 24;
    infoHeader.biSizeImage = 0;
    infoHeader.biCompression = 0;
    infoHeader.biXPelsPerMeter = 5000;
    infoHeader.biYPelsPerMeter = 5000;
    infoHeader.biClrUsed = 0;
    infoHeader.biClrImportant = 0;

    // 向文件中写入,图片文件信息头,位图信息头
    // fwrite(&bfType, sizeof(bfType), 1, bitmapFile);
    // fwrite(&fileHeader, 1, sizeof(fileHeader), bitmapFile);
    // fwrite(&infoHeader, 1, sizeof(infoHeader), bitmapFile);
    writeBmpFileHeader(&fileHeader, bitmapFile);
    writeBmpInfoHeader(&infoHeader, bitmapFile);

    // 向文件中写入颜色数据
    uint32_t currentColor = rainbowColors[0]; // 当前颜色，默认是红
    for (int i = 0; i < width; i++)
    {
        if (i < 100)
        {
            currentColor = rainbowColors[0];
            // currentColor = *rainbowColors;
        }
        else if (i < 200)
        {
            currentColor = rainbowColors[1];
            // currentColor = *(rainbowColors + 1);
        }
        else if (i < 300)
        {
            currentColor = rainbowColors[2];
            // currentColor = *(rainbowColors + 2);
        }
        else if (i < 400)
        {
            currentColor = rainbowColors[3];
            // currentColor = *(rainbowColors + 3);
        }
        else if (i < 500)
        {
            currentColor = rainbowColors[4];
            // currentColor = *(rainbowColors + 4);
        }
        else if (i < 600)
        {
            currentColor = rainbowColors[5];
            // currentColor = *(rainbowColors + 5);
        }
        else if (i < 700)
        {
            currentColor = rainbowColors[6];
            // currentColor = *(rainbowColors + 6);
        }

        // 获取当前颜色的 R 分量
        // uint8_t r = (currentColor & 0xFF0000) >> 16;
        uint8_t r = (currentColor & RGB24_MASK_RED) >> 16;

        // 获取当前颜色的 G 分量
        // uint8_t g = (currentColor & 0x00FF00) >> 16;
        uint8_t g = (currentColor & RGB24_MASK_GREEN) >> 8;

        // 获取当前颜色的 B 分量
        // uint8_t b = (currentColor & 0x0000FF);
        uint8_t b = (currentColor & RGB24_MASK_BLUE);

        // 按 BGR 顺序写入一个像素 RGB24 到文件中
        for (int j = 0; j < height; j++)
        {
            // 按 BGR 顺序写入一个像素 RGB24 到文件中
            // fputc(b, bitmapFile);
            // fputc(g, bitmapFile);
            // fputc(r, bitmapFile);
            fwrite(&b, 1, 1, bitmapFile);
            fwrite(&g, 1, 1, bitmapFile);
            fwrite(&r, 1, 1, bitmapFile);
        }
    }

    // 关闭文件
    fclose(bitmapFile);
    return true;
}

/**
 * @brief 写入彩虹数据到指定文件
 *
 * @param outputFile 文件名
 * @param width 宽
 * @param height 高
 * @return true 写入数据成功
 * @return false 写入数据成功
 */
bool Bitmap::save2(const char *outputFile, int width, int height)
{
    std::cout << "Bitmap::save2():: outputFile:" << outputFile << std::endl;
    int fd;                                                  // 文件描述
    fd = open(outputFile, O_RDWR | O_CREAT | O_TRUNC, 0644); // 打开文件,不存在,创建文件,如果已经存在,置空
    if (fd == -1)
    {
        perror("open error");
        std::cout << "创建并打开文件失败:" << outputFile << std::endl;
        return false;
    }

    // 设置bmp图片,文件信息,一共14个字节
    BitmapFileHeader fileHeader; // 图片文件头
    fileHeader.bfType = 0x4d42;  // 文件类型BM
    fileHeader.bfReserved1 = 0;
    fileHeader.bfReserved2 = 0;
    fileHeader.bfSize = sizeof(BitmapFileHeader) + sizeof(BitmapInfoHeader) + width * height * 3;
    std::cout << sizeof(BitmapFileHeader) << "," << sizeof(BitmapInfoHeader) << "," << fileHeader.bfSize << std::endl;
    fileHeader.bfOffBits = 0x36; // 偏移数54位

    // 设置bmp图片,位图信息头,一共40个字节
    BitmapInfoHeader infoHeader;
    infoHeader.biSize = sizeof(BitmapFileHeader);
    infoHeader.biWidth = width;
    infoHeader.biHeight = -height;
    infoHeader.biPlanes = 1;
    infoHeader.biBitCount = 24;
    infoHeader.biSizeImage = 0;
    infoHeader.biCompression = 0;
    infoHeader.biXPelsPerMeter = 5000;
    infoHeader.biYPelsPerMeter = 5000;
    infoHeader.biClrUsed = 0;
    infoHeader.biClrImportant = 0;

    // 向文件中写入,图片文件信息头,位图信息头
    int number = write(fd, &fileHeader, sizeof(fileHeader));
    number = write(fd, &infoHeader, sizeof(infoHeader));
    std::cout << "number:" << number << std::endl;

    // 当前颜色
    uint32_t currentColor = rainbowColors[0]; // 默认是红
    for (int i = 0; i < width; i++)
    {
        if (i < 100)
        {
            // currentColor = rainbowColors[0];
            currentColor = *rainbowColors;
        }
        else if (i < 200)
        {
            // currentColor = rainbowColors[1];
            currentColor = *(rainbowColors + 1);
        }
        else if (i < 300)
        {
            // currentColor = rainbowColors[2];
            currentColor = *(rainbowColors + 2);
        }
        else if (i < 400)
        {
            // currentColor = rainbowColors[3];
            currentColor = *(rainbowColors + 3);
        }
        else if (i < 500)
        {
            // currentColor = rainbowColors[4];
            currentColor = *(rainbowColors + 4);
        }
        else if (i < 600)
        {
            // currentColor = rainbowColors[5];
            currentColor = *(rainbowColors + 5);
        }
        else if (i < 700)
        {
            // currentColor = rainbowColors[6];
            currentColor = *(rainbowColors + 6);
        }

        // 获取当前颜色的 R 分量
        // uint8_t r = (currentColor & 0xFF0000) >> 16;
        uint8_t r = (currentColor & RGB24_MASK_RED_1) >> 16;

        // 获取当前颜色的 G 分量
        // uint8_t g = (currentColor & 0x00FF00) >> 16;
        uint8_t g = (currentColor & RGB24_MASK_GREEN_1) >> 8;

        // 获取当前颜色的 B 分量
        // uint8_t b = (currentColor & 0x0000FF);
        uint8_t b = (currentColor & RGB24_MASK_BLUE_1);
        // std::cout << sizeof(r) << "," << sizeof(g) << "," << sizeof(b) << std::endl;
        //   按 BGR 顺序写入一个像素 RGB24 到文件中
        for (int j = 0; j < height; j++)
        {

            int number = write(fd, &b, sizeof(r)); // 写入一个字键数据
            // std::cout << number << std::endl;
            number = write(fd, &g, sizeof(r)); // 写入一个字键数据
            number = write(fd, &r, sizeof(r)); // 写入一个字键数据
        }
    }

    // 关闭文件
    close(fd);
    return true;
}

void Bitmap::bmpDestroy()
{
    std::cout << "Bitmap::bmpDestroy()" << std::endl;
}