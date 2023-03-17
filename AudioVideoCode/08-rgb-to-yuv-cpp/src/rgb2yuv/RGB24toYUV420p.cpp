#include "../../include/rgb2yuv/RGB24toYUV420p.h"

RGB24toYUV420p::RGB24toYUV420p()
{
    std::cout << "RGB24toYUV420p::" << __FUNCTION__ << "():: " << __LINE__ << std::endl;
}

RGB24toYUV420p::~RGB24toYUV420p()
{
    std::cout << "RGB24toYUV420p::" << __FUNCTION__ << "():: " << __LINE__ << std::endl;
}

/**
 * @brief 申请rgb24像素信息内存
 *
 * @return true
 * @return false
 */
bool RGB24toYUV420p::mallocPixels()
{
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
 * @brief 打印图片像素信息
 *
 */
void RGB24toYUV420p::displayPixels()
{
    for (int i = 0; i < abs(height); i++)
    {
        for (int j = 0; j < width; j++)
        {
            uint8_t red = (*(*(pixels + i) + j)).red;
            uint8_t green = (*(*(pixels + i) + j)).green;
            uint8_t bulue = (*(*(pixels + i) + j)).bulue;
            std::cout << "(" << red << "," << green << "," << bulue << ")"
                      << " ";
        }
        std::cout << std::endl;
    }
}

/**
 * @brief 初始化
 *
 * @param width 宽
 * @param height 高
 */
bool RGB24toYUV420p::create(uint32_t width, uint32_t height)
{
    std::cout << "RGB24toYUV420p::" << __FUNCTION__ << "():: " << __LINE__ << std::endl;
    this->width = abs(width);
    this->height = abs(height);
    bool isMalloc = mallocPixels(); // 申请rgb24像素信息内存;
    if (!isMalloc)
    {
        return false;
    }
    displayPixels();
    genRGB24Data(); // 生成rgb24数据
    displayPixels();
    return true;
}

/**
 * @brief 初始化
 *
 * @param width 宽
 * @param height 高
 * @param rgb24FilePath rgb24文件路径
 */
bool RGB24toYUV420p::create(uint32_t width, uint32_t height, const char *rgb24FilePath)
{
    std::cout << "RGB24toYUV420p::" << __FUNCTION__ << "():: " << __LINE__ << std::endl;
    this->width = abs(width);
    this->height = abs(height);
    bool isMalloc = mallocPixels(); // 申请rgb24像素信息内存;
    if (!isMalloc)
    {
        return false;
    }
    getRGB24Data(rgb24FilePath); // 获取rgb24文件的像素信息
    return true;
}

/**
 * @brief rgb24转化为yuv420p
 *
 * @param yuv420pFilePath yuv420p文件路径
 */
void RGB24toYUV420p::rgb24ToYuv420p(const char *yuv420pFilePath)
{
    std::cout << "RGB24toYUV420p::" << __FUNCTION__ << "():: " << __LINE__ << std::endl;
}

/**
 * @brief 释放资源
 *
 */
void RGB24toYUV420p::freeResource()
{
    std::cout << "RGB24toYUV420p::" << __FUNCTION__ << "():: " << __LINE__ << std::endl;
}

/**
 * @brief 生成rgb24数据
 *
 */
void RGB24toYUV420p::genRGB24Data()
{
    std::cout << "RGB24toYUV420p::" << __FUNCTION__ << "():: " << __LINE__ << std::endl;
    IRainbow *rainbow = new Rainbow(); // 彩虹图片数据生成器
    rainbow->rgb24Data(&pixels, width, height);
    delete rainbow;
}

/**
 * @brief 获取rgb24文件的像素信息
 *
 * @param rgb24FilePath  rgb24文件路径
 */
void RGB24toYUV420p::getRGB24Data(const char *rgb24FilePath)
{
    std::cout << "RGB24toYUV420p::" << __FUNCTION__ << "():: " << __LINE__ << std::endl;
}