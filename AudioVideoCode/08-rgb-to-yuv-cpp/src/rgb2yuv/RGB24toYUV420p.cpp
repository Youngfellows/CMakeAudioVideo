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
    // uint32_t size = width * height * 3 / 2;
    // uint32_t size = width * height * 3;
    size_t y_size = width * height;
    size_t u_size = ((width + 1) / 2) * ((height + 1) / 2);
    size_t v_size = ((width + 1) / 2) * (height / 2);
    uint32_t size = y_size + u_size + v_size;
    this->ySize = y_size;
    this->uSize = u_size;
    this->vSize = v_size;
    this->yuv420pSize = size;
    std::cout << "RGB24toYUV420p::" << __FUNCTION__ << "():: " << __LINE__ << ",yuv420pSize:" << yuv420pSize << ",ySize:" << ySize << ",uSize:" << uSize << ",vSize:" << vSize << std::endl;

    this->yuv420pData = (uint8_t *)malloc(sizeof(uint8_t) * yuv420pSize); // 申请yuv420p内存空间
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
    return true;
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
    std::cout << "RGB24toYUV420p::" << __FUNCTION__ << "():: " << __LINE__ << std::endl;
    if (isCreate)
    {
        std::cout << "RGB24toYUV420p::" << __FUNCTION__ << "():: " << __LINE__ << std::endl;
        isCreate = createRGB24Pixels(rgb24FilePath); // 获取指定路径图片的RGB24图片信息
        std::cout << "RGB24toYUV420p::" << __FUNCTION__ << "():: " << __LINE__ << std::endl;
        if (isCreate)
        {
            std::cout << "RGB24toYUV420p::" << __FUNCTION__ << "():: " << __LINE__ << std::endl;
            return mallocYuv420pPixels(); // 申请yuv420p内存空间
        }
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
 * @brief yuv420p内存像素数据
 *
 * @return uint8_t*
 */
uint8_t *RGB24toYUV420p::yuv420pDataBytes()
{
    return this->yuv420pData;
}

/**
 * @brief rgb24转化为yuv420p,YU12类型
 *  Y = 0.257*R + 0.504*G + 0.098*B + 16;
 *  U = -0.148*R - 0.291*G + 0.439*B + 128;
 *  V = 0.439*R - 0.368*G - 0.071*B + 128;
 *
 *  int y_val = (int)round(0.257 * R + 0.504 * G + 0.098 * B + 16);
 *  int u_val = (int)round(-0.148 * R - 0.291 * G + 0.439 * B + 128);
 *  int v_val = (int)round(0.439 * R - 0.368 * G - 0.071 * B + 128);
 */
void RGB24toYUV420p::rgb24ToYuv420p()
{
    // size_t image_size = width * height;
    // size_t upos = image_size;
    // size_t vpos = upos + upos / 4;
    // size_t i = 0;

    size_t upos = ySize;
    size_t vpos = upos + uSize;
    size_t i = 0;

    std::cout << "RGB24toYUV420p::" << __FUNCTION__ << "():: Line:" << __LINE__ << ",yuv420pSize:" << yuv420pSize << ",upos:" << upos << ",vpos:" << vpos << std::endl;

    for (size_t y = 0; y < height; y++)
    {
        // std::cout << "RGB24toYUV420p::" << __FUNCTION__ << "():: Line:" << __LINE__ << ",line y:" << y << std::endl;
        if (!(y % 2)) // 偶数行,能被2整除，保存Y、U
        {
            // std::cout << "RGB24toYUV420p::" << __FUNCTION__ << "():: Line:" << __LINE__ << ",1111,y:" << y << std::endl;
            for (size_t x = 0; x < width; x++)
            {
                uint32_t index = (y * width + x) * 3;
                uint8_t r = rgb24Data[index];
                uint8_t g = rgb24Data[index + 1];
                uint8_t b = rgb24Data[index + 2];

                int y_val = (int)round(0.257 * r + 0.504 * g + 0.098 * b + 16);
                int y_val_1 = ((66 * r + 129 * g + 25 * b) >> 8) + 16;

                uint32_t color = r << 16 | g << 8 | b;
                // std::cout << std::hex << "color:" << color << std::endl;
                // std::cout << std::dec << "index:" << index << ",i:" << i << ",upos:" << upos << ",vpos:" << vpos << ",(" << y << "," << x << "),y_val:" << std::hex << y_val << ",y_val_1:" << y_val_1 << std::endl;
                //  yuv420pData[i++] = ((66 * r + 129 * g + 25 * b) >> 8) + 16;
                //  yuv420pData[i++] = y_val_1;
                yuv420pData[i++] = y_val;

                // 偶数列保存U分量
                if (!(x % 2))
                {
                    int u_val = (int)round(-0.148 * r - 0.291 * g + 0.439 * b + 128);
                    // int u_val_1 = ((-38 * r + -74 * g + 112 * b) >> 8) + 128;
                    // yuv420pData[upos++] = u_val;
                    // std::cout << "upos:" << std::dec << upos << std::hex << ",U:" << u_val << std::endl;
                    yuv420pData[upos++] = u_val;
                }
            }
        }
        else
        {
            // 基数行,不能被2整除,，保存Y、V
            // std::cout << "RGB24toYUV420p::" << __FUNCTION__ << "():: Line:" << __LINE__ << ",2222,line:" << y << std::endl;
            for (size_t x = 0; x < width; x++)
            {
                uint32_t index = (y * width + x) * 3;
                uint8_t r = rgb24Data[index];
                uint8_t g = rgb24Data[index + 1];
                uint8_t b = rgb24Data[index + 2];

                int y_val = (int)round(0.257 * r + 0.504 * g + 0.098 * b + 16);
                int y_val_2 = ((66 * r + 129 * g + 25 * b) >> 8) + 16;

                uint32_t color = r << 16 | g << 8 | b;
                // std::cout << std::hex << "color:" << color << std::endl;
                // std::cout << std::dec << "index:" << index << ",i:" << i << ",upos:" << upos << ",vpos:" << vpos << ",(" << y << "," << x << "),y_val:" << std::hex << y_val << ",y_val_2:" << y_val_2 << std::endl;
                //  yuv420pData[i++] = ((66 * r + 129 * g + 25 * b) >> 8) + 16;
                //  yuv420pData[i++] = y_val_1;
                yuv420pData[i++] = y_val;

                // 基数列保存V分量
                if (!(x % 2))
                {
                    int v_val = (int)round(0.439 * r - 0.368 * g - 0.071 * b + 128);
                    int v_val_1 = ((112 * r + -94 * g + -18 * b) >> 8) + 128;
                    // std::cout << "vpos:" << std::dec << vpos << std::hex << ",V:" << v_val << std::endl;
                    //  yuv420pData[vpos++] = v_val_1;
                    yuv420pData[vpos++] = v_val;
                }
            }
        }
    }
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
    // uint32_t size = width * height * 3 / 2;
    uint32_t size = yuv420pSize;
    std::cout << "RGB24toYUV420p::" << __FUNCTION__ << "():: " << __LINE__ << ",size::" << size << std::endl;
    if (yuv420pData != NULL)
    {
        // size = strlen((char *)rgb24Data);
        // std::cout << "RGB24toYUV420p::" << __FUNCTION__ << "():: " << __LINE__ << ",size::" << size << std::endl;
        fwrite(yuv420pData, size, 1, yuv420pFile); // 把内存中的数据写入文件
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