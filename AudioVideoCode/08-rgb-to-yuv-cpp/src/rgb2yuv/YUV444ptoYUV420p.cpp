#include "../../include/rgb2yuv/YUV444ptoYUV420p.h"

YUV444ptoYUV420p::YUV444ptoYUV420p()
{
    std::cout << TAG << __FUNCTION__ << "():: Line " << __LINE__ << std::endl;
}

YUV444ptoYUV420p::~YUV444ptoYUV420p()
{
    std::cout << TAG << __FUNCTION__ << "():: Line " << __LINE__ << std::endl;
    destory();
}

/**
 * @brief 默认初始化
 * @brief 使用彩虹图片作为默认的rgb24数据
 *
 * @param width 宽
 * @param height 高
 * @return true
 * @return false
 */
bool YUV444ptoYUV420p::create(uint32_t width, uint32_t height)
{
    std::cout << TAG << __FUNCTION__ << "():: Line " << __LINE__ << std::endl;
    this->width = abs((long)width);
    this->height = abs((long)width);
    std::cout << TAG << __FUNCTION__ << "():: Line " << __LINE__ << ",width:" << width << ",heitht:" << height << std::endl;
    // this->width = width;
    // this->height = height;

    this->rainbow = new Rainbow();
    bool isCreate = rainbow->createRGB24(width, height); // 初始化彩虹图片
    if (!isCreate)
    {
        return false;
    }
    rainbow->createRGB24Pixels();                  // 初始化rgb24彩虹图片像素信息
    this->rgb24Data = rainbow->rainbowRGB24Data(); // 获取rgb24内存字节数据
    if (rgb24Data == NULL)
    {
        return false;
    }
    bool isMallocYuv444 = mallocYuv444(); // 申请yuv444p内存空间
    return isMallocYuv444;
}

/**
 * @brief rgb24文件初始化
 *
 * @param rgb24FilePath rgb24文件路径
 * @param width 宽
 * @param height 高
 * @return true
 * @return false
 */
bool YUV444ptoYUV420p::createFromRGB24(const char *rgb24FilePath, uint32_t width, uint32_t height)
{
    std::cout << TAG << __FUNCTION__ << "():: Line " << __LINE__ << std::endl;
    this->width = abs((long)width);
    this->height = abs((long)width);
    std::cout << TAG << __FUNCTION__ << "():: Line " << __LINE__ << ",width:" << width << ",heitht:" << height << std::endl;
    // this->height = abs(height);
    // this->width = width;
    // this->height = height;

    this->rgb24 = new RGB24();                                        // rgb24像素生成器
    bool isCreate = rgb24->rgb24Create(rgb24FilePath, width, height); // 初始化rgb24数据
    if (!isCreate)
    {
        return false;
    }
    this->rgb24Data = rgb24->rgb24Data(); // 获取rgb24内存数据
    if (rgb24Data == NULL)
    {
        return false;
    }
    bool isMallocYuv444 = mallocYuv444(); // 申请yuv444p内存空间
    return isMallocYuv444;
}

/**
 * @brief yuv444p文件初始化
 *
 * @param yuv444pFilePath yuv444p文件路径
 * @param width 宽
 * @param height 高
 * @return true
 * @return false
 */
bool YUV444ptoYUV420p::createFromYUV444p(const char *yuv444pFilePath, uint32_t width, uint32_t height)
{
    std::cout << TAG << __FUNCTION__ << "():: Line " << __LINE__ << std::endl;
    this->width = abs((long)width);
    this->height = abs((long)width);
    std::cout << TAG << __FUNCTION__ << "():: Line " << __LINE__ << ",width:" << width << ",heitht:" << height << std::endl;
    // this->width = width;
    // this->height = height;
    bool isMallocYuv444 = mallocYuv444(); // 申请yuv444p内存空间
    return isMallocYuv444;
}

/**
 * @brief 申请yuv444p内存空间
 *
 * @return true
 * @return false
 */
bool YUV444ptoYUV420p::mallocYuv444()
{
    this->yuv444pData = (uint8_t *)malloc(sizeof(uint8_t) * width * height * 3); // 申请内存空间
    if (yuv420pData == NULL)
    {
        return false;
    }
    return true;
}

/**
 * @brief yuv444p转化为yuv420p
 *
 * @param yuv420pFilePath
 */
void YUV444ptoYUV420p::yuv444pToYuv420p(const char *yuv420pFilePath)
{
    std::cout << TAG << __FUNCTION__ << "():: Line " << __LINE__ << std::endl;
    bool isSuccess = rgb24ToYuv444(); // rgb24转化为yuv444
    if (isSuccess)
    {
        saveYuv420p(yuv420pFilePath); // 保存yuv420p数据到文件
    }
}

/**
 * @brief rgb24转化为yuv444
 *
 */
bool YUV444ptoYUV420p::rgb24ToYuv444()
{
    std::cout << TAG << __FUNCTION__ << "():: Line " << __LINE__ << std::endl;
    if (rgb24Data == NULL)
    {
        return false;
    }
    int8_t yuv_y[width * height];
    int8_t yuv_u[width * height];
    int8_t yuv_v[width * height];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // 获取内存中的rgb24像素数据
            uint32_t index = 3 * (i * width + j);
            uint8_t red = *(rgb24Data + index);       // R分量
            uint8_t green = *(rgb24Data + index + 1); // G分量
            uint8_t bulue = *(rgb24Data + index + 2); // B分量
            uint32_t color = red << 16 | green << 8 | bulue;
            // std::cout << TAG << __FUNCTION__ << "():: Line " << std::dec << __LINE__ << ",color:" << std::hex << color << std::endl;

            int8_t Y, U, V;
            rgbToYuv(red, green, bulue, &Y, &U, &V); // rgb转化为YUV
            int currentIndex = i * height + j;
            yuv_y[currentIndex] = Y;
            yuv_u[currentIndex] = U;
            yuv_v[currentIndex] = V;
        }
    }
    // 拷贝yuv444 Y/U/V数据到内存
    memcpy(yuv444pData, yuv_y, sizeof(yuv_y));
    memcpy(yuv444pData + width * height, yuv_u, sizeof(yuv_u));
    memcpy(yuv444pData + width * height * 2, yuv_v, sizeof(yuv_v));
    return true;
}

/**
 * @brief RGB转化为YUV
 *
 * @param R
 * @param G
 * @param B
 * @param Y
 * @param U
 * @param V
 */
void YUV444ptoYUV420p::rgbToYuv(uint8_t R, uint8_t G, uint8_t B, int8_t *Y, int8_t *U, int8_t *V)
{
    *Y = 0.257 * R + 0.504 * G + 0.098 * B + 16;
    *U = -0.148 * R - 0.291 * G + 0.439 * B + 128;
    *V = 0.439 * R - 0.368 * G - 0.071 * B + 128;
}

/**
 * @brief yuv444转化为yuv420
 *
 */
void YUV444ptoYUV420p::yuv444pToYuv420p()
{
    std::cout << TAG << __FUNCTION__ << "():: Line " << __LINE__ << std::endl;
}

/**
 * @brief 解析rgb24内存数据
 *
 * @param rgb24FilePath
 * @return true
 * @return false
 */
bool YUV444ptoYUV420p::rgb24Parser(const char *rgb24FilePath)
{
    std::cout << TAG << __FUNCTION__ << "():: Line " << __LINE__ << std::endl;
    return true;
}

/**
 * @brief 解析yuv444p内存数据
 *
 * @param yuv444pFilePath
 * @return true
 * @return false
 */
bool YUV444ptoYUV420p::yuv444pParser(const char *yuv444pFilePath)
{
    std::cout << TAG << __FUNCTION__ << "():: Line " << __LINE__ << std::endl;
    return true;
}

/**
 * @brief 保存yuv420p数据到文件
 *
 * @param yuv420pFilePath
 */
void YUV444ptoYUV420p::saveYuv420p(const char *yuv420pFilePath)
{
    std::cout << TAG << __FUNCTION__ << "():: Line " << __LINE__ << std::endl;
    FILE *yuv420pFile = fopen(yuv420pFilePath, "wb"); // 获取文件指针
    if (yuv420pFile == NULL)
    {
        std::cout << TAG << __FUNCTION__ << "():: Line " << __LINE__ << "打开文件错误:" << yuv420pFilePath << std::endl;
        return;
    }
    uint32_t size = width * height * 3;
    fwrite(yuv444pData, size, 1, yuv420pFile); // 向文件中写入数据
    fclose(yuv420pFile);                       // 关闭文件
}

/**
 * @brief 释放资源
 *
 */
void YUV444ptoYUV420p::destory()
{
    std::cout << TAG << __FUNCTION__ << "():: Line " << __LINE__ << std::endl;
    if (rainbow != NULL)
    {
        rainbow->destory();
    }
    delete rainbow;
    rainbow = NULL;
    if (rgb24 != NULL)
    {
        rgb24->destory();
    }
    delete rgb24;
    rgb24 = NULL;
}