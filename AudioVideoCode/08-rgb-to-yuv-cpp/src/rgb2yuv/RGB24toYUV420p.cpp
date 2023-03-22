#include "../../include/rgb2yuv/RGB24toYUV420p.h"

RGB24toYUV420p::RGB24toYUV420p()
{
    std::cout << "RGB24toYUV420p::" << __FUNCTION__ << "():: " << __LINE__ << std::endl;
}

RGB24toYUV420p::~RGB24toYUV420p()
{
    std::cout << "RGB24toYUV420p::" << __FUNCTION__ << "():: " << __LINE__ << std::endl;
    destory();
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
    this->rainbow = new Rainbow();                       // 创建彩虹图片生成器
    bool isCreate = rainbow->createRGB24(width, height); // 初始化彩虹图片rgb24像素信息
    if (isCreate)
    {
        isCreate = createRainbowRGB24Pixels(); // 创建彩虹图片的RGB24图片信息
        if (isCreate)
        {
            return mallocYuv420pPixels(); // 申请yuv420p内存空间
        }
    }
    return false;
}

/**
 * @brief 申请yuv420p内存空间
 *
 * @return true
 * @return false
 */
bool RGB24toYUV420p::mallocYuv420pPixels()
{
    uint32_t size = width * height * 3 / 2;
    std::cout << "RGB24toYUV420p::" << __FUNCTION__ << "():: " << __LINE__ << ",size:" << size << std::endl;
    this->yuv420pData = (uint8_t *)malloc(sizeof(uint8_t) * size); // 申请yuv420p内存空间
    if (yuv420pData == NULL)
    {
        return false;
    }
    memset(yuv420pData, 0, size); // 清空yuv420p内存空间
    return true;
}

/**
 * @brief 创建彩虹图片的RGB24图片信息
 *
 */
bool RGB24toYUV420p::createRainbowRGB24Pixels()
{
    std::cout << "RGB24toYUV420p::" << __FUNCTION__ << "():: " << __LINE__ << std::endl;
    if (rainbow == NULL)
    {
        return false;
    }
    rainbow->createRGB24Pixels();            // 设置彩虹图片rgb24位图像素信息
    rgb24Data = rainbow->rainbowRGB24Data(); // 获取内存中的rgb24彩虹图片字节数据
    if (rgb24Data == NULL)
    {
        return false;
    }
    else
    {
        return mallocYuv420pPixels(); // 申请yuv420p内存空间
    }
    return false;
}

/**
 * @brief 创建指定路径图片的RGB24图片信息
 *
 * @param rgb24FilePath
 */
bool RGB24toYUV420p::createRGB24Pixels(const char *rgb24FilePath)
{
    std::cout << "RGB24toYUV420p::" << __FUNCTION__ << "():: " << __LINE__ << std::endl;
    if (rgb24 == NULL)
    {
        return false;
    }
    rgb24Data = rgb24->rgb24Data(); // 获取文件中的rgb24数据
    if (rgb24Data == NULL)
    {
        return false;
    }
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
    // 还有1种方式,直接读取rgb24文件内存数据
    this->rgb24 = new RGB24();                                        // 创建RGB24图片生成器
    bool isCreate = rgb24->rgb24Create(rgb24FilePath, width, height); // 初始化RGB24图片像素信息
    if (isCreate)
    {
        return createRGB24Pixels(rgb24FilePath); // 获取指定路径图片的RGB24图片信息
    }
    return false;
}

/**
 * @brief rgb24转化为yuv420p
 *
 * @param yuv420pFilePath yuv420p文件路径
 */
void RGB24toYUV420p::rgb24ToYuv420p(const char *yuv420pFilePath)
{
    std::cout << "RGB24toYUV420p::" << __FUNCTION__ << "():: " << __LINE__ << std::endl;
    rgb24ToYuv420p();
    saveYuv420p(yuv420pFilePath);
}

/**
 * @brief rgb24转化为yuv420p
 *
 */
void RGB24toYUV420p::rgb24ToYuv420p()
{
    std::cout << "RGB24toYUV420p::" << __FUNCTION__ << "():: " << __LINE__ << std::endl;
}

/**
 * @brief 保存yuv420p到文件
 *
 * @param yuv420pFilePath
 */
void RGB24toYUV420p::saveYuv420p(const char *yuv420pFilePath)
{
    std::cout << "RGB24toYUV420p::" << __FUNCTION__ << "():: " << __LINE__ << std::endl;
    FILE *yuv420pFile = fopen(yuv420pFilePath, "wb"); // 获取文件指针
    if (yuv420pFile == NULL)
    {
        return;
    }
    uint32_t size = width * height * 3;
    std::cout << "RGB24toYUV420p::" << __FUNCTION__ << "():: " << __LINE__ << ",size::" << size << std::endl;
    if (rgb24Data != NULL)
    {
        // size = strlen((char *)rgb24Data);
        // std::cout << "RGB24toYUV420p::" << __FUNCTION__ << "():: " << __LINE__ << ",size::" << size << std::endl;
        fwrite(rgb24Data, size, 1, yuv420pFile); // 把内存中的数据写入文件
    }
    fclose(yuv420pFile); // 关闭文件
}

/**
 * @brief 释放资源
 *
 */
void RGB24toYUV420p::destory()
{
    std::cout << "RGB24toYUV420p::" << __FUNCTION__ << "():: " << __LINE__ << std::endl;
    if (rgb24 != NULL)
    {
        rgb24->destory();
    }
    rgb24 = NULL;
    if (rainbow != NULL)
    {
        rainbow->destory();
    }
    rainbow = NULL;
    if (yuv420pData != NULL)
    {
        free(yuv420pData);
    }
    yuv420pData = NULL;
}