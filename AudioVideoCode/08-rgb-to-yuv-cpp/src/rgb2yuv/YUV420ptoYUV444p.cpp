#include "../../include/rgb2yuv/YUV420ptoYUV444p.h"

YUV420ptoYUV444p::YUV420ptoYUV444p()
{
    std::cout << TAG << __FUNCTION__ << "():: Line " << __LINE__ << std::endl;
    this->rgb24ToYuv420p = new RGB24toYUV420p(); // 初始化rgb24转化为yuv420p转换器
}

YUV420ptoYUV444p::~YUV420ptoYUV444p()
{
    std::cout << TAG << __FUNCTION__ << "():: Line " << __LINE__ << std::endl;
    destory();
}

/**
 * @brief  初始化,默认使用彩虹图片
 *
 * @param width 宽
 * @param height 高
 * @return true
 * @return false
 */
bool YUV420ptoYUV444p::create(uint32_t width, uint32_t height)
{
    std::cout << TAG << __FUNCTION__ << "():: Line " << __LINE__ << std::endl;
    this->width = abs((int)width);
    this->height = abs((int)height);
    bool isCreate = rgb24ToYuv420p->create(width, height); // 初始rgb24转yuv420p转换器,默认彩虹图片
    std::cout << TAG << __FUNCTION__ << "():: Line " << __LINE__ << std::endl;
    if (!isCreate)
    {
        std::cout << TAG << __FUNCTION__ << "():: Line " << __LINE__ << std::endl;
        return false;
    }
    std::cout << TAG << __FUNCTION__ << "():: Line " << __LINE__ << std::endl;
    rgb24ToYuv420p->rgb24ToYuv420p();                       // rgb24转化为yuv420p
    this->yuv420pData = rgb24ToYuv420p->yuv420pDataBytes(); // 获取yuv420p内存数据
    if (yuv420pData == NULL)
    {
        return false;
    }
    std::cout << TAG << __FUNCTION__ << "():: Line " << __LINE__ << std::endl;
    bool isMallocYuv444 = mallocYuv444p();
    if (!isMallocYuv444)
    {
        return false;
    }
    std::cout << TAG << __FUNCTION__ << "():: Line " << __LINE__ << std::endl;
    return true;
}

/**
 * @brief 使用本地rgb24文件初始化,然后再转化为yuv420p
 *
 * @param rgb24FilePath rgb24文件路径
 * @param width 宽
 * @param height 高
 * @return true
 * @return false
 */
bool YUV420ptoYUV444p::createFromRgb24(const char *rgb24FilePath, uint32_t width, uint32_t height)
{
    std::cout << TAG << __FUNCTION__ << "():: Line " << __LINE__ << std::endl;
    this->width = abs((int)width);
    this->height = abs((int)height);
    bool isCreate = rgb24ToYuv420p->create(width, height, rgb24FilePath); // 初始rgb24转yuv420p转换器,使用指定图片
    if (!isCreate)
    {
        return false;
    }
    rgb24ToYuv420p->rgb24ToYuv420p();                       // rgb24转化为yuv420p
    this->yuv420pData = rgb24ToYuv420p->yuv420pDataBytes(); // 获取yuv420p内存数据
    if (yuv420pData == NULL)
    {
        return false;
    }
    std::cout << TAG << __FUNCTION__ << "():: Line " << __LINE__ << std::endl;
    std::cout << TAG << __FUNCTION__ << "():: Line " << __LINE__ << std::endl;
    bool isMallocYuv444 = mallocYuv444p();
    if (!isMallocYuv444)
    {
        return false;
    }
    std::cout << TAG << __FUNCTION__ << "():: Line " << __LINE__ << std::endl;
    return true;
}

/**
 * @brief 使用本地yuv420p文件初始化
 *
 * @param yuv420pFilePath yuv420p文件路径
 * @param width 宽
 * @param height 高
 * @return true
 * @return false
 */
bool YUV420ptoYUV444p::createFromYuv420p(const char *yuv420pFilePath, uint32_t width, uint32_t height)
{
    std::cout << TAG << __FUNCTION__ << "():: Line " << __LINE__ << std::endl;
    this->width = abs((int)width);
    this->height = abs((int)height);
    bool isMallocYuv420 = mallocYuv420p();
    if (!isMallocYuv420)
    {
        return false;
    }
    std::cout << TAG << __FUNCTION__ << "():: Line " << __LINE__ << std::endl;
    bool isReadSuccess = readYuv420p(yuv420pFilePath);
    if (!isReadSuccess)
    {
        return false;
    }
    std::cout << TAG << __FUNCTION__ << "():: Line " << __LINE__ << std::endl;
    bool isMallocYuv444 = mallocYuv444p();
    if (!isMallocYuv444)
    {
        return false;
    }
    std::cout << TAG << __FUNCTION__ << "():: Line " << __LINE__ << std::endl;
    return true;
}

/**
 * @brief 读取yuv420p文件数据到内存
 *
 * @param yuv420pFilePath
 */
bool YUV420ptoYUV444p::readYuv420p(const char *yuv420pFilePath)
{
    std::cout << TAG << __FUNCTION__ << "():: Line " << __LINE__ << std::endl;
    FILE *yuv420pFile = fopen(yuv420pFilePath, "rb"); // 打开文件,获取文件指针
    if (yuv420pFile == NULL)
    {
        return false;
    }
    uint32_t size = width * height * 3 / 2;
    memset(yuv420pData, 0, size);                             // 清空内存
    size_t result = fread(yuv420pData, size, 1, yuv420pFile); // 读取文件内容
    std::cout << TAG << __FUNCTION__ << "():: Line " << __LINE__ << ",result:" << result << std::endl;
    fclose(yuv420pFile); // 关闭文件
    if (result != 1)
    {
        return false;
    }
    return true;
}

/**
 * @brief  申请yuv420p数据内存空间
 *
 * @return true
 * @return false
 */
bool YUV420ptoYUV444p::mallocYuv420p()
{
    this->yuv420pData = (uint8_t *)malloc(sizeof(uint8_t) * width * height * 3 / 2);
    if (yuv420pData == NULL)
    {
        return false;
    }
    return true;
}

/**
 * @brief 申请yuv444p数据内存空间
 *
 * @return true
 * @return false
 */
bool YUV420ptoYUV444p::mallocYuv444p()
{
    this->yuv444pData = (uint8_t *)malloc(sizeof(uint8_t) * width * height * 3);
    if (yuv444pData == NULL)
    {
        return false;
    }
    return true;
}

/**
 * @brief yuv420p转化为yuv444p
 *
 * @param yuv444pFilePath
 */
void YUV420ptoYUV444p::yuv420pToYuv444p(const char *yuv444pFilePath)
{
    std::cout << TAG << __FUNCTION__ << "():: Line " << __LINE__ << std::endl;
    yuv420pToYuv444p();
    saveYuv444p(yuv444pFilePath);
}

/**
 * @brief 释放资源
 *
 */
void YUV420ptoYUV444p::destory()
{
    std::cout << TAG << __FUNCTION__ << "():: Line " << __LINE__ << std::endl;
    if (rgb24ToYuv420p != NULL)
    {
        rgb24ToYuv420p->destory();
    }
    else
    {
        if (yuv420pData != NULL)
        {
            free(yuv420pData);
        }
    }
    rgb24ToYuv420p = NULL;
    yuv420pData = NULL;
    if (yuv444pData != NULL)
    {
        free(yuv444pData);
    }
    yuv444pData = NULL;
}

/**
 * @brief yuv420p转化为yuv444p
 *
 */
void YUV420ptoYUV444p::yuv420pToYuv444p()
{
    std::cout << TAG << __FUNCTION__ << "():: Line " << __LINE__ << std::endl;
    uint8_t *srcY = NULL;
    uint8_t *srcU = NULL;
    uint8_t *srcV = NULL;

    uint8_t *desY = NULL;
    uint8_t *desU = NULL;
    uint8_t *desV = NULL;

    srcY = yuv420pData;               // Y分量,来源于yuv420p
    srcU = srcY + width * height;     // U分量,来源于yuv420p
    srcV = srcU + width * height / 4; // V分量,来源于yuv420p

    desY = yuv444pData;           // Y分量,写入yuv444p
    desU = desY + width * height; // Y分量,写入yuv444p
    desV = desU + width * height; // Y分量,写入yuv444p

    memcpy(desY, srcY, width * height * sizeof(uint8_t)); // Y分量直接拷贝即可
    // UV分量转换
    int i, j;
    for (i = 0; i < height; i += 2)
    { // 行
        for (j = 0; j < width; j += 2)
        { // 列
            // U
            desU[i * width + j] = srcU[i / 2 * width / 2 + j / 2];
            desU[i * width + j + 1] = srcU[i / 2 * width / 2 + j / 2];
            desU[(i + 1) * width + j] = srcU[i / 2 * width / 2 + j / 2];
            desU[(i + 1) * width + j + 1] = srcU[i / 2 * width / 2 + j / 2];
            // V
            desV[i * width + j] = srcV[i / 2 * width / 2 + j / 2];
            desV[i * width + j + 1] = srcV[i / 2 * width / 2 + j / 2];
            desV[(i + 1) * width + j] = srcV[i / 2 * width / 2 + j / 2];
            desV[(i + 1) * width + j + 1] = srcV[i / 2 * width / 2 + j / 2];
        }
    }
}

/**
 * @brief 保存yuv444p数据到文件
 *
 * @param yuv444pFilePath
 */
void YUV420ptoYUV444p::saveYuv444p(const char *yuv444pFilePath)
{
    std::cout << TAG << __FUNCTION__ << "():: Line " << __LINE__ << ",yuv444pFilePath:" << yuv444pFilePath << std::endl;
    if (yuv444pData == NULL)
    {
        return;
    }
    FILE *fp = fopen(yuv444pFilePath, "wb"); // 打开文件
    if (fp == NULL)
    {
        std::cout << TAG << __FUNCTION__ << "():: Line " << __LINE__ << ",打开文件失败:" << yuv444pFilePath << std::endl;
        return;
    }
    uint32_t size = width * height * 3;
    fwrite(yuv444pData, size, 1, fp); // 向文件写入内存数据
    fclose(fp);                       // 关闭文件
    std::cout << TAG << __FUNCTION__ << "():: Line " << __LINE__ << std::endl;
}