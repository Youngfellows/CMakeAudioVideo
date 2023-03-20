#include "../../include/pixel/RGB24.h"

RGB24::RGB24()
{
    std::cout << "RGB24::" << __FUNCTION__ << "():: Line " << __LINE__ << std::endl;
}

RGB24::~RGB24()
{
    std::cout << "RGB24::" << __FUNCTION__ << "():: Line " << __LINE__ << std::endl;
}

bool RGB24::rgb24Create(uint32_t width, uint32_t height)
{
    std::cout << "RGB24::" << __FUNCTION__ << "():: Line " << __LINE__ << std::endl;
    this->width = abs(width);
    this->height = abs(height);
    bool isMalloc = mallocPixels();
    if (!isMalloc)
    {
        return false;
    }
    bool isMallocRgb24 = mallocRgb24DataBytes();
    if (isMallocRgb24)
    {
        genRGB24Data();
    }
    return isMallocRgb24;
}

bool RGB24::rgb24Create(const char *rgb24FilePath, uint32_t width, uint32_t height)
{
    std::cout << "RGB24::" << __FUNCTION__ << "():: Line " << __LINE__ << std::endl;
    this->width = abs(width);
    this->height = abs(height);
    bool isMalloc = mallocPixels();
    return true;
}

uint8_t *RGB24::rgb24Data()
{
    std::cout << "RGB24::" << __FUNCTION__ << "():: Line " << __LINE__ << std::endl;
    return this->rgb24DataBytes;
}

void RGB24::genRGB24Data(const char *rgb24FilePath)
{
    std::cout << "RGB24::" << __FUNCTION__ << "():: Line " << __LINE__ << std::endl;
}

void RGB24::saveRgb24(const char *rgb24FilePath)
{
    std::cout << "RGB24::" << __FUNCTION__ << "():: xxx Line " << __LINE__ << std::endl;
}

void RGB24::destory()
{
    std::cout << "RGB24::" << __FUNCTION__ << "():: Line " << __LINE__ << std::endl;
}

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

bool RGB24::mallocRgb24DataBytes()
{
    std::cout << "RGB24::" << __FUNCTION__ << "():: Line " << __LINE__ << std::endl;
    this->rgb24DataBytes = (uint8_t *)malloc(sizeof(uint8_t) * width * height); // 申请连续内存空间
    if (rgb24DataBytes == NULL)
    {
        return false;
    }
    return true;
}

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

/**
 * @brief 生成彩虹图片的rgb24格式数据
 */
void RGB24::genRGB24Data()
{
    std::cout << "RGB24::" << __FUNCTION__ << "():: " << __LINE__ << pixels << std::endl;
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
        std::cout << "RGB24::" << __FUNCTION__ << "():: ssssssss,i:" << i << ",(" << red << "," << green << "," << bulue << "),red sizeof:" << sizeof(red) << "," << (pixels + i) << std::endl;

        for (int j = 0; j < width; j++)
        {
            RGBPixel rgbPixel(red, green, bulue);
            // rgbPixel.red = red;     // 右移16位之后,有效数据其实只要1个字节8位,可以赋值
            // rgbPixel.green = green; // 右移8位之后,有效数据其实只要1个字节8位,可以赋值
            // rgbPixel.bulue = bulue; // 右移0位之后,有效数据其实只要1个字节8位,可以赋值

            std::cout << "RGB24::" << __FUNCTION__ << "():: " << __LINE__ << "(" << i << "," << j << ") ele(" << red << "," << rgbPixel.green << "," << rgbPixel.bulue << "),red sizeof:" << sizeof(rgbPixel.red) << std::endl;
            // pixels[i][j] = rgbPixel;
            // pixels[i][j].red = 66;
            // pixels[i][j].green = 255;
            // pixels[i][j].bulue = 77;
            //(*(pixels + i) + j)->red = rgbPixel.red; // 为元素赋值
            *(*(pixels + i) + j) = rgbPixel; // 为每一个像素赋值rgb颜色值

            RGBPixel ele = *(*(pixels + i) + j);
            std::cout << "RGB24::" << __FUNCTION__ << "():: " << __LINE__ << "(" << i << "," << j << ") ele(" << ele.red << "," << ele.green << "," << ele.bulue << "),red sizeof:" << sizeof(ele.red) << std::endl;

            uint8_t r = (uint8_t)red & 0xff;
            uint8_t g = (uint8_t)green & 0xff;
            uint8_t b = (uint8_t)bulue & 0xff;
            // *(rgb24DataBytes + (i * width + j)) = r;
            // *(rgb24DataBytes + (i * width + j)) + 1 = g;
            // *(rgb24DataBytes + (i * width + j)) + 2 = b;

            uint8_t *rgb24Data = rgb24DataBytes + i * width + j;
            memccpy(rgb24Data, &r, 1, sizeof(uint8_t));
            memccpy(rgb24Data + 1, &g, 1, sizeof(uint8_t));
            memccpy(rgb24Data + 2, &b, 1, sizeof(uint8_t));
        }
    }
}