#include "../../include/pixel/RGB24.h"

RGB24::RGB24()
{
    std::cout << "RGB24::" << __FUNCTION__ << "():: Line " << __LINE__ << std::endl;
}

RGB24::~RGB24()
{
    std::cout << "RGB24::" << __FUNCTION__ << "():: Line " << __LINE__ << std::endl;
}

/**
 * @brief 初始化rgb24数据
 *
 * @param width 宽
 * @param height 高
 * @return true
 * @return false
 */
bool RGB24::rgb24Create(uint32_t width, uint32_t height)
{
    std::cout << "RGB24::" << __FUNCTION__ << "():: Line " << __LINE__ << std::endl;
    this->width = abs(width);
    this->height = abs(height);
    bool isMallocPixel = mallocPixels(); // 按像素，申请rgb24像素内存空间
    if (!isMallocPixel)
    {
        return false;
    }
    bool isMallocRgb24 = mallocRgb24DataBytes(); // 按字节，申请rgb24像素内存空间
    return isMallocRgb24;
}

/**
 * @brief 设置RGB24图片每个像素的RGB颜色信息
 *
 * @param color 当前颜色值
 * @param x x位置,行
 * @param y y位置,列
 */
void RGB24::setRGB24Pixel(uint32_t color, uint32_t x, uint32_t y)
{
    // std::cout << "RGB24::" << __FUNCTION__ << "():: Line " << __LINE__ << std::endl;

    // 获取当前颜色的 RGB 分量
    uint32_t red = (color & RGB24_MASK_RED) >> 16;
    uint32_t green = (color & RGB24_MASK_GREEN) >> 8;
    uint32_t bulue = (color & RGB24_MASK_BLUE);

    RGBPixel rgbPixel(red, green, bulue);

    // std::cout << "RGB24::" << __FUNCTION__ << "():: " << __LINE__ << "(" << x << "," << y << ") ele(" << red << "," << rgbPixel.green << "," << rgbPixel.bulue << "),red sizeof:" << sizeof(rgbPixel.red) << std::endl;
    //  pixels[i][j] = rgbPixel;
    //  pixels[i][j].red = 66;
    //  pixels[i][j].green = 255;
    //  pixels[i][j].bulue = 77;
    //(*(pixels + i) + j)->red = rgbPixel.red; // 为元素赋值
    *(*(pixels + x) + y) = rgbPixel; // 为每一个像素赋值rgb颜色值

    RGBPixel ele = *(*(pixels + x) + y);
    uint8_t r = (uint8_t)red & 0xff;
    uint8_t g = (uint8_t)green & 0xff;
    uint8_t b = (uint8_t)bulue & 0xff;
    // *(rgb24DataBytes + (i * width + j)) = r;
    // *(rgb24DataBytes + (i * width + j)) + 1 = g;
    // *(rgb24DataBytes + (i * width + j)) + 2 = b;

    uint32_t index = (x * width + y) * 3;
    uint32_t rgbColor = (r << 16) | (g << 8) | (b << 0);
    // std::cout << "index:" << std::dec << index << "(" << x << "," << y << "),rgbColor(" << std::hex << rgbColor << ")" << std::endl;
    uint8_t *rgb24Data = rgb24DataBytes + index;
    memccpy(rgb24Data, &r, 1, sizeof(uint8_t));
    memccpy(rgb24Data + 1, &g, 1, sizeof(uint8_t));
    memccpy(rgb24Data + 2, &b, 1, sizeof(uint8_t));
}

/**
 * @brief 初始化rgb24数据
 *
 * @param rgb24FilePath rgb24文件路径
 * @param width 宽
 * @param height 高
 * @return true
 * @return false
 */
bool RGB24::rgb24Create(const char *rgb24FilePath, uint32_t width, uint32_t height)
{
    std::cout << "RGB24::" << __FUNCTION__ << "():: Line " << __LINE__ << std::endl;
    this->width = abs(width);
    this->height = abs(height);
    bool isMallocPixel = mallocPixels(); // 按像素，申请rgb24像素内存空间
    if (!isMallocPixel)
    {
        return false;
    }
    bool isMallocRgb24 = mallocRgb24DataBytes(); // 按字节，申请rgb24像素内存空间
    if (isMallocRgb24)
    {
        bool isGenRGB24 = genRGB24Data(rgb24FilePath); // 生成rgb24文件的像素数据
        return isGenRGB24;
    }
    return false;
}

/**
 * @brief 获取rgb24字节数据
 *
 * @return uint8_t*
 */
uint8_t *RGB24::rgb24Data()
{
    std::cout << "RGB24::" << __FUNCTION__ << "():: Line " << __LINE__ << std::endl;
    return this->rgb24DataBytes;
}

/**
 * @brief 生成rgb24文件的像素数据
 *
 * @param rgb24FilePath
 */
bool RGB24::genRGB24Data(const char *rgb24FilePath)
{
    std::cout << "RGB24::" << __FUNCTION__ << "():: Line " << __LINE__ << std::endl;
    uint8_t *rgb24Data = readRgb24Data(rgb24FilePath); // 读取rgb24文件数据
    if (rgb24Data == NULL)
    {
        return false;
    }

    if (pixels == NULL)
    {
        return false;
    }

    // 为二维数组元素赋值
    for (int i = 0; i < height; i++)
    {
        // std::cout << "RGB24::" << __FUNCTION__ << "():: Line " << __LINE__ << ",i:" << i << std::endl;
        for (int j = 0; j < width; j++)
        {
            uint32_t currentIndex = 3 * (i * width + j);          // 当前位置索引
            pixels[i][j].red = *(rgb24Data + currentIndex);       // 获取内存中的red数据，为二维数组元素赋值
            pixels[i][j].green = *(rgb24Data + currentIndex + 1); // 获取内存中的green数据，为二维数组元素赋值
            pixels[i][j].bulue = *(rgb24Data + currentIndex + 2); // 获取内存中的bulue数据，为二维数组元素赋值

            uint32_t red = (*(*(pixels + i) + j)).red;
            uint32_t green = (*(*(pixels + i) + j)).green;
            uint32_t bulue = (*(*(pixels + i) + j)).bulue;
            uint32_t color = ((red & 0xFF) << 16) | ((green & 0xFF) << 8) | (bulue & 0xFF);
            // std::cout << "rgb(" << color << ") ";
        }
    }
    return true;
}

/**
 * @brief 读取rgb24文件字节数据
 *
 * @param rgb24FilePath
 * @return uint8_t*
 */
uint8_t *RGB24::readRgb24Data(const char *rgb24FilePath)
{
    std::cout << "RGB24::" << __FUNCTION__ << "():: Line " << __LINE__ << ",rgb24FilePath:" << rgb24FilePath << std::endl;
    FILE *rgb24File = fopen(rgb24FilePath, "rb"); // 获取rgb24文件指针

    if (rgb24File == NULL)
    {
        std::cout << "RGB24::" << __FUNCTION__ << "():: Line " << __LINE__ << ",rgb24File is NULL" << std::endl;
        return NULL;
    }
    size_t fileSize = getFileSize(rgb24FilePath); // 获取文件大小
    uint32_t rgb24size = rgb24DataSize();         // 获取rgb24文件字节数据大小
    std::cout << "RGB24::" << __FUNCTION__ << "():: Line " << __LINE__ << ",fileSize:" << fileSize << ",rgb24size:" << rgb24size << std::endl;
    if (fileSize == 0)
    {
        return NULL;
    }

    if (fileSize < rgb24size)
    {
        this->height = fileSize / 2;
        this->width = fileSize / 2;
        std::cout << "RGB24::" << __FUNCTION__ << "():: Line " << __LINE__ << ",文件太小了,从新设置大小,width:" << width << ",height:" << height << std::endl;
        reMalloc(); // 重新申请内存空间
    }

    if (rgb24DataBytes == NULL)
    {
        return NULL;
    }

    rgb24size = rgb24DataSize();                                 // 从新获取rgb24文件字节数据大小
    size_t len = fread(rgb24DataBytes, rgb24size, 1, rgb24File); // 读取rgb24文件字节数据
    std::cout << "RGB24::" << __FUNCTION__ << "():: Line " << __LINE__ << ",read len:" << len << std::endl;
    fclose(rgb24File); // 关闭文件
    return rgb24DataBytes;
}

/**
 * @brief 重新申请内存空间
 *
 * @return true
 * @return false
 */
bool RGB24::reMalloc()
{
    std::cout << "RGB24::" << __FUNCTION__ << "():: Line " << __LINE__ << std::endl;
    destory();                           // 先释放内存
    bool isMallocPixel = mallocPixels(); // 按像素，申请rgb24像素内存空间
    if (!isMallocPixel)
    {
        return false;
    }
    bool isMallocRgb24 = mallocRgb24DataBytes(); // 按字节，申请rgb24像素内存空间
    return isMallocRgb24;
}

/**
 * @brief 获取文件大小
 *
 * @param filePath
 * @return size_t
 */
size_t RGB24::getFileSize(const char *filePath)
{
    std::cout << "RGB24::" << __FUNCTION__ << "():: Line " << __LINE__ << std::endl;
    if (filePath == NULL)
    {
        return 0;
    }
    // 这是一个存储文件(夹)信息的结构体，其中有文件大小和创建时间、访问时间、修改时间等
    struct stat statbuf;

    // 提供文件名字符串，获得文件属性结构体
    stat(filePath, &statbuf);

    // 获取文件大小
    size_t filesize = statbuf.st_size;
    return filesize;
}

/**
 * @brief 保存rgb24像素数据到内存
 *
 * @param rgb24FilePath 文件路径
 */
void RGB24::saveRgb24(const char *rgb24FilePath)
{
    std::cout << "RGB24::" << __FUNCTION__ << "():: xxx Line " << __LINE__ << std::endl;
    FILE *rgb24File = fopen(rgb24FilePath, "wb+"); // 获取rgb24文件指针
    std::cout << "RGB24::" << __FUNCTION__ << "():: " << __LINE__ << ",rgb24File:" << rgb24File << std::endl;
    if (rgb24File == NULL)
    {
        return;
    }
    uint32_t size = rgb24DataSize();                           // 获取rgb24像素数据字节大小
    uint32_t len = fwrite(rgb24DataBytes, size, 1, rgb24File); // 向文件中写入数据
    fclose(rgb24File);                                         // 关闭文件
}

/**
 * @brief 获取rgb24文件字节数据大小
 *
 * @return uint32_t
 */
uint32_t RGB24::rgb24DataSize()
{
    std::cout << "RGB24::" << __FUNCTION__ << "():: Line " << __LINE__ << std::endl;
    return width * height * 3;
}

/**
 * @brief 释放二维数组资源
 *
 */
void RGB24::destory()
{
    std::cout << "RGB24::" << __FUNCTION__ << "():: Line " << __LINE__ << std::endl;
    if (pixels != NULL)
    {
        for (int i = 0; i < height; i++)
        {
            // std::cout << "RGB24::" << __FUNCTION__ << "():: Line " << __LINE__ << std::endl;
            free(*(pixels + i)); // 释放内存
            // free(pixels[i]); // 释放内存
        }
    }
    free(pixels);
    pixels = NULL;
    // std::cout << "RGB24::" << __FUNCTION__ << "():: Line " << __LINE__ << std::endl;
    if (rgb24DataBytes != NULL)
    {
        free(rgb24DataBytes);
    }
    rgb24DataBytes = NULL;
}

/**
 * @brief 按像素，申请rgb24像素内存空间
 *
 * @return true
 * @return false
 */
bool RGB24::mallocPixels()
{
    std::cout << "RGB24::" << __FUNCTION__ << "():: Line " << __LINE__ << std::endl;
    this->pixels = (RGBPixel **)malloc(sizeof(RGBPixel *) * height); // 申请height行二级指针,可以保存RGBPixel *地址
    if (pixels == NULL)
    {
        return false;
    }
    bool isMallocError = false;

    for (int i = 0; i < height; i++)
    {
        // pixels[i] = (RGBPixel *)malloc(sizeof(RGBPixel) * (width));  //为每一行申请width个的连续内存空间
        *(pixels + i) = (RGBPixel *)malloc(sizeof(RGBPixel) * (width)); // 为每一行申请width个的连续内存空间
        if (*(pixels + i) == nullptr)
        {
            isMallocError = true;
            break;
        }

        for (int j = 0; j < width; j++)
        {
            pixels[i][j].red = 66;
            pixels[i][j].green = 255;
            pixels[i][j].bulue = 77;
            // pixels[i][j].red = 255;
            // pixels[i][j].green = 255;
            // pixels[i][j].bulue = 255;
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
 * @brief 按字节，申请rgb24像素内存空间
 *
 * @return true
 * @return false
 */
bool RGB24::mallocRgb24DataBytes()
{
    std::cout << "RGB24::" << __FUNCTION__ << "():: Line " << __LINE__ << std::endl;
    this->rgb24DataBytes = (uint8_t *)malloc(sizeof(uint8_t) * width * height * 3); // 申请连续内存空间
    if (rgb24DataBytes == NULL)
    {
        return false;
    }
    return true;
}

/**
 * @brief 显示内存rgb24像素信息
 *
 */
void RGB24::displayPixels()
{
    std::cout << "RGB24::" << __FUNCTION__ << "():: Line " << __LINE__ << std::endl;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            uint32_t red = (*(*(pixels + i) + j)).red;
            uint32_t green = (*(*(pixels + i) + j)).green;
            uint32_t bulue = (*(*(pixels + i) + j)).bulue;
            std::cout << "RGB24::" << __FUNCTION__ << "():: Line " << __LINE__ << "(" << red << "," << green << "," << bulue << ")"
                      << " ";
        }
        std::cout << std::endl;
    }
}