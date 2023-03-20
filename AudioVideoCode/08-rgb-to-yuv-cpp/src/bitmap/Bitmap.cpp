#include "../../include/pixel/Bitmap.h"

Bitmap::Bitmap()
{
    std::cout << "Bitmap::" << __FUNCTION__ << "():: " << __LINE__ << std::endl;
}

Bitmap::~Bitmap()
{
    std::cout << "Bitmap::" << __FUNCTION__ << "():: " << __LINE__ << std::endl;
    destory();
}

void Bitmap::destory()
{
    std::cout << "Bitmap::" << __FUNCTION__ << "():: " << __LINE__ << std::endl;
    if (bmpDataBytes != NULL)
    {
        free(bmpDataBytes);
    }
    bmpDataBytes = NULL;
}

/**
 * @brief 生成彩虹图片的bmp格式像素数据
 *
 * @param width 宽
 * @param height 高
 * @return uint8_t* 返回彩虹图片的bmp格式像素数据
 */
uint8_t *Bitmap::bmpCreate(uint32_t width, uint32_t height)
{
    std::cout << "Bitmap::" << __FUNCTION__ << "():: " << __LINE__ << ",width:" << width << ",height:" << height << std::endl;
    this->width = abs(width);
    this->height = abs(height);
    this->bmpHeadLength = 14 + 40;
    this->bmpSize = bmpHeadLength + height * (width * 3 + (4 - (width * 3 % 4)));
    bmpDataBytes = (uint8_t *)malloc(sizeof(uint8_t) * bmpSize); // 动态申请内存
    std::cout << "Bitmap::" << __FUNCTION__ << "():: " << __LINE__ << ",bmpDataBytes sizeof:" << sizeof(bmpDataBytes) << ",bmpDataBytes size:" << bmpSize << ",bmpDataBytes:" << bmpDataBytes << std::endl;
    if (bmpDataBytes == NULL)
    {
        std::cout << "Bitmap::" << __FUNCTION__ << "():: " << __LINE__ << ",bmpDataBytes is null" << std::endl;
    }
    else
    {
        std::cout << "Bitmap::" << __FUNCTION__ << "():: " << __LINE__ << ",bmpDataBytes address:" << &bmpDataBytes << std::endl;
        std::cout << "Bitmap::" << __FUNCTION__ << "():: " << __LINE__ << ",bmpDataBytes address:" << bmpDataBytes + 1 << std::endl;
        printf("Bitmap::%s()::%d,%p,%p,%p\n", __FUNCTION__, __LINE__, bmpDataBytes, bmpDataBytes + 1, bmpDataBytes + 2);
    }
    // bmpDataBytes[0] = 'a';
    // bmpDataBytes[1] = 'b';
    // std::cout << "Rainbow::" << __FUNCTION__ << "():: " << __LINE__ << ",bmpDataBytes:" << bmpDataBytes << std::endl;
    // std::cout << "Rainbow::" << __FUNCTION__ << "():: " << __LINE__ << ",bmpDataBytes:" << bmpDataBytes[1] << std::endl;
    // std::cout << "Rainbow::" << __FUNCTION__ << "():: " << __LINE__ << ",bmpDataBytes address:" << bmpDataBytes + 1 << std::endl;
    // const char *bmpData = "欢迎来到中国深圳,这里是美丽的南山区,SHENZHEN BAI SHI ZHOU";
    // std::cout << "Rainbow::" << __FUNCTION__ << "():: " << __LINE__ << ",bmpData size:" << strlen(bmpData) << std::endl;
    // memcpy(bmpDataBytes, bmpData, strlen(bmpData)); // 向内存中写入数据
    // std::cout << "Rainbow::" << __FUNCTION__ << "():: " << __LINE__ << ",bmpDataBytes:" << bmpDataBytes << std::endl;
    createBmpPixelData(bmpDataBytes); // 生成bmp彩虹图片的像素数据
    return bmpDataBytes;
}

/**
 * @brief 获取内存中的BMP位图数据
 *
 * @return uint8_t*
 */
uint8_t *Bitmap::bmpData()
{
    return this->bmpDataBytes;
}

/**
 * @brief 获取BMP图片大小
 *
 * @return uint32_t
 */
uint32_t Bitmap::getBmpSize()
{
    std::cout << "Rainbow::" << __FUNCTION__ << "():: " << __LINE__ << std::endl;
    return this->bmpSize;
}

/**
 * @brief 生成mp彩虹图片的位图文件头数据
 *
 * @param bitmapData bmp图片数据内存
 * @param size bmp数据
 * @param width 宽
 * @param height 高
 */
void Bitmap::createBmpFileHeaderData(uint8_t *bitmapData)
{
    std::cout << "Rainbow::" << __FUNCTION__ << "():: " << __LINE__ << ",width:" << width << ",height:" << height << std::endl;
    this->bmpFHeader;            // 位图文件头
    bmpFHeader.bfType = 0x4D42;  // BM
    bmpFHeader.bfSize = bmpSize; //  整个BMP文件大小,BMP大小要4字节对齐
    bmpFHeader.bfReserved1 = 0x00;
    bmpFHeader.bfReserved2 = 0;
    bmpFHeader.bfOffBits = 54; // 0x36
    std::cout << "bfType:" << bmpFHeader.bfType << std::endl;
    std::cout << "bfSize:" << bmpFHeader.bfSize << std::endl;
    std::cout << "bfReserved1:" << bmpFHeader.bfReserved1 << std::endl;
    std::cout << "bfReserved2:" << bmpFHeader.bfReserved2 << std::endl;
    std::cout << "bfOffBits:" << bmpFHeader.bfOffBits << std::endl;

    // 把位图文件头写入内存中
    // uint32_t i = 0;
    uint8_t *bmpData = bitmapData;
    // *(bmpData + 0) = bmpFHeader.bfType >> 8;
    // *(bmpData + 1) = bmpFHeader.bfType >> 0;
    setShortToBytes(bmpFHeader.bfType, bmpData, 0); // 写入BM到内存中
    std::cout << "bfType:" << *(bmpData + 0) << std::endl;
    std::cout << "bfType:" << *(bmpData + 1) << std::endl;
    uint16_t bfType = shortFromBytes(bmpData, 0); // 获取内存中的type
    std::cout << "bfType:" << bfType << std::endl;
    std::cout << "bfType:" << std::bitset<15>(bfType) << std::endl;

    setIntToBytes(bmpFHeader.bfSize, bmpData, 2); // 写入size到内存中
    uint32_t bfSize = intFromBytes(bmpData, 2);   // 获取内存中的size
    std::cout << "bfSize:" << bfSize << std::endl;
    // std::cout << "bfSize:" << std::bitset<31>(bfSize) << std::endl;
    setShortToBytes(bmpFHeader.bfReserved1, bmpData, 6);
    setShortToBytes(bmpFHeader.bfReserved2, bmpData, 8);
    setIntToBytes(bmpFHeader.bfOffBits, bmpData, 10);
}

/**
 * @brief 设置指定位置连续2个字节表示的整数到内存中
 *
 * @param number
 * @param bytes
 * @param pos
 */
void Bitmap::setShortToBytes(uint16_t number, uint8_t *bytes, uint32_t pos)
{
    // *(bytes + pos + 0) = number >> 8;
    // *(bytes + pos + 1) = number >> 0;
    uint8_t byte1 = number >> 0;
    uint8_t byte2 = number >> 8;
    memcpy(bytes + pos, &byte1, sizeof(uint8_t));
    memcpy(bytes + pos + 1, &byte2, sizeof(uint8_t));
}

/**
 * @brief 设置指定位置连续4个字节表示的整数到内存中
 *
 * @param number
 * @param bytes
 * @param pos
 */
void Bitmap::setIntToBytes(uint32_t number, uint8_t *bytes, uint32_t pos)
{
    *(bytes + pos + 0) = number >> 0;
    *(bytes + pos + 1) = number >> 8;
    *(bytes + pos + 2) = number >> 16;
    *(bytes + pos + 3) = number >> 24;
}

/**
 * @brief 获取内存中指定位置连续2个字节表示的整数
 *
 * @param bytes
 * @param pos
 * @return uint16_t
 */
uint16_t Bitmap::shortFromBytes(uint8_t *bytes, uint32_t pos)
{
    // uint16_t a = *(bytes + pos + 0);
    // uint16_t b = *(bytes + pos + 1);
    // std::cout << "a:" << a << ",b:" << b << std::endl;
    // std::cout << std::hex << "a:" << a << ",b:" << b << std::endl;
    // // std::cout << std::bitset<sizeof(uint16_t) * 8>(a) << std::endl;
    // std::cout << std::bitset<15>(a) << std::endl;
    // std::cout << std::bitset<15>(b) << std::endl;
    // uint16_t c = a << 8;
    // uint16_t d = b >> 0;
    // std::cout << std::hex << "c:" << c << std::endl;
    // std::cout << std::hex << "d:" << d << std::endl;
    // std::cout << std::bitset<15>(c) << std::endl;
    // std::cout << std::bitset<15>(d) << std::endl;
    // uint16_t e = c | d;
    // std::cout << std::bitset<15>(e) << std::endl;
    return (*(bytes + pos + 0) << 0) | ((*(bytes + pos + 1)) >> 8);
}

/**
 * @brief 获取内存中指定位置连续4个字节表示的整数
 *
 * @param bytes
 * @param pos
 * @return uint32_t
 */
uint32_t Bitmap::intFromBytes(uint8_t *bytes, uint32_t pos)
{
    return (*(bytes + pos + 0) << 0) |
           ((*(bytes + pos + 1)) >> 8) |
           (*(bytes + pos + 2)) >> 16 |
           (*(bytes + pos + 3)) >> 24;
}

/**
 * @brief 生成mp彩虹图片的位图信息头数据
 *
 * @param bitmapData bmp图片数据内存
 * @param size bmp数据
 * @param width 宽
 * @param height 高
 */
void Bitmap::createBmpInfoHeaderData(uint8_t *bitmapData)
{
    std::cout << "Rainbow::" << __FUNCTION__ << "():: " << __LINE__ << ",width:" << width << ",height:" << height << std::endl;
    uint8_t *bmpData = bitmapData;
    BitmapInfoHeader *bmpInfoHeader = new BitmapInfoHeader();
    bmpInfoHeader->biSize = 40;             // 0x48
    bmpInfoHeader->biWidth = width;         // 位图宽
    bmpInfoHeader->biHeight = -abs(height); // 位图高
    bmpInfoHeader->biPlanes = 1;
    bmpInfoHeader->biBitCount = 0x18; // 24
    bmpInfoHeader->biCompression = 0;
    bmpInfoHeader->biSizeImage = 0;
    bmpInfoHeader->biXPelsPerMeter = 0;
    bmpInfoHeader->biYPelsPerMeter = 0;
    bmpInfoHeader->biClrUsed = 0;
    bmpInfoHeader->biClrImportant = 0;

    // 把位图信息头写入内存中
    setIntToBytes(bmpInfoHeader->biSize, bmpData, 14);
    setIntToBytes(bmpInfoHeader->biWidth, bmpData, 18);
    setIntToBytes(bmpInfoHeader->biHeight, bmpData, 22);
    setShortToBytes(bmpInfoHeader->biPlanes, bmpData, 26);
    setShortToBytes(bmpInfoHeader->biBitCount, bmpData, 28);
    setIntToBytes(bmpInfoHeader->biCompression, bmpData, 30);
    setIntToBytes(bmpInfoHeader->biSizeImage, bmpData, 34);
    setIntToBytes(bmpInfoHeader->biXPelsPerMeter, bmpData, 38);
    setIntToBytes(bmpInfoHeader->biYPelsPerMeter, bmpData, 42);
    setIntToBytes(bmpInfoHeader->biClrUsed, bmpData, 46);
    setIntToBytes(bmpInfoHeader->biClrImportant, bmpData, 50);
}

/**
 * @brief 设置指定位置的rgb像素值
 *
 * @param bmpData bmp内存
 * @param color RGB颜色值
 * @param x
 * @param y
 */
void Bitmap::setBmpPixel(uint8_t *bmpData, uint32_t color, uint32_t x, uint32_t y)
{
    // std::cout << "Bitmap::" << __FUNCTION__ << "():: Line " << __LINE__ << ",RGB:" << std::hex << color << std::endl;
    // std::cout << std::dec << std::endl;
    //  获取当前颜色的 R 分量
    uint32_t red = (color & RGB24_MASK_RED) >> 16;

    // 获取当前颜色的 G 分量
    uint32_t green = (color & RGB24_MASK_GREEN) >> 8;

    // 获取当前颜色的 B 分量
    uint32_t bulue = (color & RGB24_MASK_BLUE);
    // uint32_t pad = (width * -3UL) & 3;   // 4字节对齐
    uint16_t pad = 4 - (width * 3 % 4); // 4字节对齐

    RGBPixel rgbPixel(red, green, bulue);                              // RGB像素信息
    uint32_t curIndex = bmpHeadLength + y * (3 * width + pad) + x * 3; // 4字节对齐
    // std::cout << "Bitmap::" << __FUNCTION__ << "():: Line " << __LINE__ << std::dec << "curIndex:" << curIndex << std::endl;

    uint8_t *pData = bmpData + curIndex;
    uint8_t r = rgbPixel.red & 0xff; // 取低8位，1个字节数据
    uint8_t g = (uint8_t)(rgbPixel.green & 0xff);
    uint8_t b = (uint8_t)(rgbPixel.bulue & 0xff);
    // std::cout << "r char is:" << std::hex << red << ",binary,r:" << std::bitset<8>(r) << ",binary,red:" << std::bitset<15>(red) << std::endl;
    // std::cout << "r char is:" << r << ",binary,r:" << std::bitset<8>(r) << ",binary,red:" << std::bitset<15>(red) << std::endl;
    // std::cout << "g char is:" << g << ",binary,green:" << std::bitset<15>(green) << std::endl;
    // std::cout << "b char is:" << b << ",binary,bulue:" << std::bitset<15>(bulue) << std::endl;

    uint32_t rgb = (r << 16) | (g << 8) | b; // 获取颜色
    // std::cout << std::hex << "rgb:" << rgb << std::endl;
    // std::cout << std::oct<<"curIndex:" << curIndex << std::endl;
    // std::cout << std::dec << "curIndex:" << curIndex << std::endl;

    memcpy(pData, &b, sizeof(uint8_t));
    memcpy(pData + 1, &g, sizeof(uint8_t));
    memcpy(pData + 2, &r, sizeof(uint8_t));
    // std::cout << "Bitmap::" << __FUNCTION__ << "():: Line " << __LINE__
    //           << "(" << i << "," << j << "),rgb(" << pData + 2 << "," << pData + 1 << "," << pData << ")" << std::endl;
}

/**
 * @brief 生成彩虹图片的bmp数据
 *
 * @param bitmapData bmp图片数据内存
 * @param size bmp数据
 * @param width 宽
 * @param height 高
 */
void Bitmap::createBmpPixelData(uint8_t *bitmapData)
{
    std::cout << "Bitmap::" << __FUNCTION__ << "():: " << __LINE__ << ",width:" << width << ",height:" << height << std::endl;
    createBmpFileHeaderData(bitmapData); // 生成mp彩虹图片的位图文件头数据
    createBmpInfoHeaderData(bitmapData); // 生成mp彩虹图片的位图信息头数据
}

/**
 * @brief 生成彩虹图片的rgb24格式数据
 *
 * @param pixels 图片像素信息内存空间
 * @param width 宽
 * @param height 高
 */
void Bitmap::rgb24Data(RGBPixel **pixels, uint32_t width, uint32_t height)
{
    std::cout << "Bitmap::" << __FUNCTION__ << "():: " << __LINE__ << std::endl;
    std::cout << "Bitmap::" << __FUNCTION__ << "():: " << __LINE__ << pixels << std::endl;
    this->width = abs(width);
    this->height = abs(height);
    for (int i = 0; i < height; i++)
    {
        uint32_t currentColor = RAINBOW_COLORS[0]; // 获取改行的rgb彩虹颜色
        if (i < 100)
        {
            currentColor = RAINBOW_COLORS[0]; // 赤色
        }
        else if (i < 200)
        {
            currentColor = RAINBOW_COLORS[1]; // 橙色
        }
        else if (i < 300)
        {
            currentColor = RAINBOW_COLORS[2]; // 红色
        }
        else if (i < 400)
        {
            currentColor = RAINBOW_COLORS[3]; // 绿色
        }
        else if (i < 500)
        {
            currentColor = RAINBOW_COLORS[4]; // 青色
        }
        else if (i < 600)
        {
            currentColor = RAINBOW_COLORS[5]; // 蓝色
        }
        else if (i < 700)
        {
            currentColor = RAINBOW_COLORS[6]; // 紫色
        }

        // uint8_t red = (currentColor & 0xFF0000) >> 16;
        //  unsigned int red = (currentColor & 0xFF0000) >> 16;
        uint32_t red = (currentColor & 0xFF0000) >> 16;

        // 获取当前颜色的 G 分量
        // uint8_t green = (currentColor & 0x00FF00) >> 8;
        // unsigned int green = (currentColor & RGB24_MASK_GREEN) >> 8;
        uint32_t green = (currentColor & RGB24_MASK_GREEN) >> 8;

        // 获取当前颜色的 B 分量
        // uint8_t bulue = (currentColor & 0x0000FF);
        // unsigned int bulue = (currentColor & RGB24_MASK_BLUE);
        uint32_t bulue = (currentColor & RGB24_MASK_BLUE);
        std::cout << "Bitmap::" << __FUNCTION__ << "():: ssssssss,i:" << i << ",(" << red << "," << green << "," << bulue << "),red sizeof:" << sizeof(red) << "," << (pixels + i) << std::endl;

        for (int j = 0; j < width; j++)
        {
            RGBPixel rgbPixel(red, green, bulue);
            // rgbPixel.red = red;     // 右移16位之后,有效数据其实只要1个字节8位,可以赋值
            // rgbPixel.green = green; // 右移8位之后,有效数据其实只要1个字节8位,可以赋值
            // rgbPixel.bulue = bulue; // 右移0位之后,有效数据其实只要1个字节8位,可以赋值

            std::cout << "Bitmap::" << __FUNCTION__ << "():: " << __LINE__ << "(" << i << "," << j << ") ele(" << red << "," << rgbPixel.green << "," << rgbPixel.bulue << "),red sizeof:" << sizeof(rgbPixel.red) << std::endl;
            // pixels[i][j] = rgbPixel;
            // pixels[i][j].red = 66;
            // pixels[i][j].green = 255;
            // pixels[i][j].bulue = 77;
            //(*(pixels + i) + j)->red = rgbPixel.red; // 为元素赋值
            *(*(pixels + i) + j) = rgbPixel; // 为每一个像素赋值rgb颜色值

            RGBPixel ele = *(*(pixels + i) + j);
            std::cout << "Bitmap::" << __FUNCTION__ << "():: " << __LINE__ << "(" << i << "," << j << ") ele(" << ele.red << "," << ele.green << "," << ele.bulue << "),red sizeof:" << sizeof(ele.red) << std::endl;
        }
    }
}

/**
 * @brief 保存rgb24像素数据到文件
 *
 * @param path
 * @param data
 * @param size
 */
bool Bitmap::saveRgb24(const char *path, uint8_t *data, uint32_t size)
{
    std::cout << "Bitmap::" << __FUNCTION__ << "():: " << __LINE__ << std::endl;
    return true;
}

/**
 * @brief 保存bmp像素数据到文件
 *
 * @param path
 * @param data
 * @param size
 */
bool Bitmap::saveBitmap(const char *path, uint8_t *data, uint32_t size)
{
    std::cout << "Bitmap::" << __FUNCTION__ << "():: " << __LINE__ << ",size:" << size << ",path:" << path << std::endl;
    FILE *bitmapFile = fopen(path, "wb+"); // 获取文件指针
    std::cout << "Bitmap::" << __FUNCTION__ << "():: " << __LINE__ << ",bitmapFile:" << bitmapFile << std::endl;
    if (bitmapFile == NULL)
    {
        return false;
    }
    uint32_t len = fwrite(data, size, 1, bitmapFile); // 向文件中写入数据
    std::cout << "Bitmap::" << __FUNCTION__ << "():: " << __LINE__ << ",size:" << size << ",len:" << len << std::endl;
    fclose(bitmapFile); // 关闭文件
    return true;
}