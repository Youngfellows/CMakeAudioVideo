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
    std::cout << TAG << __FUNCTION__ << "():: Line " << __LINE__ << std::endl;
    if (rgb24Data == NULL)
    {
        std::cout << TAG << __FUNCTION__ << "():: Line " << __LINE__ << std::endl;
        return false;
    }
    std::cout << TAG << __FUNCTION__ << "():: Line " << __LINE__ << std::endl;
    bool isMallocYuv444 = mallocYuv444(); // 申请yuv444p内存空间
    if (!isMallocYuv444)
    {
        return false;
    }
    bool isMallocYuv420 = mallocYuv420(); // 申请yuv420p内存空间
    return isMallocYuv420;
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

    this->rgb24 = new RGB24();                       // rgb24像素生成器
    bool isCreateRgb24 = rgb24Parser(rgb24FilePath); // 获取rgb24数据
    if (!isCreateRgb24)
    {
        return false;
    }
    std::cout << TAG << __FUNCTION__ << "():: Line " << __LINE__ << std::endl;
    bool isMallocYuv444 = mallocYuv444(); // 申请yuv444p内存空间
    if (!isMallocYuv444)
    {
        return false;
    }
    bool isMallocYuv420 = mallocYuv420(); // 申请yuv420p内存空间
    return isMallocYuv420;
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
    std::cout << TAG << __FUNCTION__ << "():: Line " << __LINE__ << std::endl;
    bool isMallocYuv444 = mallocYuv444(); // 申请yuv444p内存空间
    if (!isMallocYuv444)
    {
        return false;
    }
    bool isMallocRGB24 = mallocRGB24(); // 申请RGB24内存空间
    if (!isMallocRGB24)
    {
        return false;
    }
    bool isCreateRgb24 = yuv444ptoRgb24(yuv444pFilePath); // 转化yuv444p内存数据为rgb24
    if (!isCreateRgb24)
    {
        return false;
    }
    bool isMallocYuv420 = mallocYuv420(); // 申请yuv420p内存空间
    return isMallocYuv420;
}

/**
 * @brief 申请yuv444p内存空间
 *
 * @return true
 * @return false
 */
bool YUV444ptoYUV420p::mallocYuv444()
{
    std::cout << TAG << __FUNCTION__ << "():: Line " << __LINE__ << ",width:" << width << ",height:" << height << std::endl;
    this->yuv444pData = (uint8_t *)malloc(sizeof(uint8_t) * width * height * 3); // 申请内存空间
    std::cout << TAG << __FUNCTION__ << "():: Line " << __LINE__ << std::endl;
    if (yuv444pData == NULL)
    {
        std::cout << TAG << __FUNCTION__ << "():: Line " << __LINE__ << std::endl;
        return false;
    }
    std::cout << TAG << __FUNCTION__ << "():: Line " << __LINE__ << std::endl;
    return true;
}

/**
 * @brief 申请RGB24内存空间
 *
 * @return true
 * @return false
 */
bool YUV444ptoYUV420p::mallocRGB24()
{
    this->rgb24Data = (uint8_t *)malloc(sizeof(uint8_t) * width * height * 3); // 申请内存空间
    std::cout << TAG << __FUNCTION__ << "():: Line " << __LINE__ << std::endl;
    if (rgb24Data == NULL)
    {
        std::cout << TAG << __FUNCTION__ << "():: Line " << __LINE__ << std::endl;
        return false;
    }
    std::cout << TAG << __FUNCTION__ << "():: Line " << __LINE__ << std::endl;
    return true;
}

/**
 * @brief 申请yuv420p内存空间
 *
 * @return true
 * @return false
 */
bool YUV444ptoYUV420p::mallocYuv420()
{
    std::cout << TAG << __FUNCTION__ << "():: Line " << __LINE__ << ",width:" << width << ",height:" << height << std::endl;
    // 1.精确方式
    // size_t y_size = width * height;                         // Y分量大小
    // size_t u_size = ((width + 1) / 2) * ((height + 1) / 2); // U分量大小
    // size_t v_size = ((width + 1) / 2) * (height / 2);       // V分量大小
    // uint32_t size = y_size + u_size + v_size;               // yuv420p大小
    // this->ySize = y_size;
    // this->uSize = u_size;
    // this->vSize = v_size;
    // this->yuv420pSize = size; // yuv420p大小;

    // 2.不精确方式
    // uint32_t size = width * height * 3 / 2;
    this->ySize = width * height;
    this->uSize = width * height / 4;
    this->vSize = width * height / 4;
    this->yuv420pSize = width * height * 3 / 2;
    this->yuv420pData = (uint8_t *)malloc(sizeof(uint8_t) * yuv420pSize); // 申请yuv420p内存空间
    if (yuv420pData == NULL)
    {
        return false;
    }
    std::cout << TAG << __FUNCTION__ << "():: Line " << __LINE__ << ",width:" << width << ",height:" << height << std::endl;
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
        yuv444pToYuv420p();           // yuv444转化为yuv420
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
    std::cout << TAG << __FUNCTION__ << "():: Line " << __LINE__ << std::endl;

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
    std::cout << TAG << __FUNCTION__ << "():: Line " << __LINE__ << std::endl;
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
    uint8_t *srcY = NULL;
    uint8_t *srcU = NULL;
    uint8_t *srcV = NULL;
    uint8_t *desY = NULL;
    uint8_t *desU = NULL;
    uint8_t *desV = NULL;

    srcY = yuv444pData;           // Y分量,来自于yuv444p
    srcU = srcY + width * height; // U分量,来自于yuv444p
    srcV = srcU + width * height; // V分量,来自于yuv444p

    desY = yuv420pData;               // yuv420p的Y分量首地址
    desU = desY + width * height;     // yuv420p的U分量首地址
    desV = desU + width * height / 4; // yuv420p的V分量首地址

    int half_width = width / 2;
    int half_height = height / 2;
    memcpy(desY, srcY, width * height * sizeof(uint8_t)); // Y分量直接拷贝即可
    // 再拷贝UV
    for (int i = 0; i < half_height; i++)
    {
        for (int j = 0; j < half_width; j++)
        {
            *desU = *srcU;
            *desV = *srcV;
            desU++;
            desV++;
            srcU += 2; // 每行隔2个像素取U分量
            srcV += 2; // 每行隔2个像素取U分量
        }
        srcU = srcU + width; // 隔1行再取U分量
        srcV = srcV + width; // 隔1行再取V分量
    }
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
    return true;
}

/**
 * @brief 转化yuv444p内存数据为rgb24
 *
 * @param yuv444pFilePath
 * @return true
 * @return false
 */
bool YUV444ptoYUV420p::yuv444ptoRgb24(const char *yuv444pFilePath)
{
    std::cout << TAG << __FUNCTION__ << "():: Line " << __LINE__ << ",yuv444pFilePath:" << yuv444pFilePath << std::endl;
    FILE *yuv444pFile = fopen(yuv444pFilePath, "rb"); // 打开文件
    if (yuv444pFile == NULL)
    {
        std::cout << TAG << __FUNCTION__ << "():: Line " << __LINE__ << std::endl;
        return false;
    }
    std::cout << TAG << __FUNCTION__ << "():: Line " << __LINE__ << std::endl;
    uint32_t size = width * height * 3;
    // uint8_t yuv444p[size];
    // memset(yuv444pData, 0, size);                              // 先清空内存
    size_t readNum = fread(yuv444pData, size, 1, yuv444pFile); // 读取yuv444p文件内容到内存
    std::cout << TAG << __FUNCTION__ << "():: Line " << __LINE__ << ",size:" << size << ",readNum:" << readNum << std::endl;
    fclose(yuv444pFile); // 关闭文件
    std::cout << TAG << __FUNCTION__ << "():: Line " << __LINE__ << std::endl;

    // if (readNum < size)
    // {
    //     std::cout << TAG << __FUNCTION__ << "():: Line " << __LINE__ << ",size:" << size << ",readNum:" << readNum << ",read error" << std::endl;
    //     return false;
    // }

    uint8_t *srcY = yuv444pData; // Y分量在yuv444p中的首地址
    std::cout << TAG << __FUNCTION__ << "():: Line " << __LINE__ << std::endl;
    uint8_t *srcU = srcY + width * height; // U分量在yuv444p中的首地址
    std::cout << TAG << __FUNCTION__ << "():: Line " << __LINE__ << std::endl;
    uint8_t *srcV = srcU + width * height; // V分量在yuv444p中的首地址
    std::cout << TAG << __FUNCTION__ << "():: Line " << __LINE__ << std::endl;

    for (int i = 0; i < height; i++)
    {
        // std::cout << TAG << __FUNCTION__ << "():: Line " << __LINE__ << " sssssssss,i:" << i << std::endl;
        for (int j = 0; j < width; j++)
        {
            int currentYUVIndex = i * height + j; // 在当前像素位置(i,j)
            uint8_t Y = srcY[currentYUVIndex];
            uint8_t U = srcU[currentYUVIndex];
            uint8_t V = srcV[currentYUVIndex];
            // std::cout << TAG << __FUNCTION__ << "():: Line " << __LINE__ << "(" << i << "," << j << ")" << std::endl;

            int r_val = (int)round(1.164 * (Y - 16) + 1.596 * (V - 128));
            int g_val = (int)round(1.164 * (Y - 16) - 0.813 * (V - 128) - 0.391 * (U - 128));
            int b_val = (int)round(1.164 * (Y - 16) + 2.018 * (U - 128));
            // std::cout << TAG << __FUNCTION__ << "():: Line " << __LINE__ << "(" << i << "," << j << ")" << std::endl;

            int currentRGBIndex = 3 * (i * width + j); // rgb24像素数据在内存中的索引
            rgb24Data[currentRGBIndex] = bound(0, r_val, 255);
            rgb24Data[currentRGBIndex + 1] = bound(0, g_val, 255);
            rgb24Data[currentRGBIndex + 2] = bound(0, b_val, 255);
        }
    }
    std::cout << TAG << __FUNCTION__ << "():: Line " << __LINE__ << std::endl;
    return true;
}

/**
 * @brief 边界截取
 *
 * @param start
 * @param value
 * @param end
 * @return uint8_t
 */
uint8_t YUV444ptoYUV420p::bound(uint8_t start, int value, uint8_t end)
{
    if (value <= start)
    {
        return start;
    }
    if (value >= end)
    {
        return end;
    }
    return value;
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
    fwrite(yuv420pData, yuv420pSize, 1, yuv420pFile); // 向文件中写入数据
    fclose(yuv420pFile);                              // 关闭文件
}

/**
 * @brief 释放资源
 *
 */
void YUV444ptoYUV420p::destory()
{
    std::cout << TAG << __FUNCTION__ << "():: Line " << __LINE__ << std::endl;
    if (yuv444pData != NULL)
    {
        free(yuv444pData);
    }
    yuv444pData = NULL;
    if (yuv420pData != NULL)
    {
        free(yuv420pData);
    }
    // if (rgb24Data != NULL)
    // {
    //     free(rgb24Data);
    // }

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