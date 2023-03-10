#include "../include/rainbow/Rainbow.h"

Rainbow::Rainbow()
{
    std::cout << "Rainbow::Rainbow()构造函数" << std::endl;
    this->initRainbowColors();
}

void Rainbow::initRainbowColors()
{
    std::cout << "Rainbow::initRainbowColors():: ..." << std::endl;
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

Rainbow::~Rainbow()
{
    std::cout << "Rainbow::~Rainbow()析构函数" << std::endl;
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
bool Rainbow::writeRainbow(const char *outputFile, int width, int height)
{
    std::cout << "Rainbow::writeRainbow():: outputFile:" << outputFile << std::endl;
    // 打开文件
    FILE *rgbFile = fopen(outputFile, "wb+");
    // 当前颜色
    uint32_t currentColor = rainbowColors[0]; // 默认是红
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
            currentColor = rainbowColors[4];
            // currentColor = *(rainbowColors + 4);
        }
        else if (i < 700)
        {
            currentColor = rainbowColors[6];
            // currentColor = *(rainbowColors + 6;
        }

        // 获取当前颜色的 R 分量
        // uint8_t r = (currentColor & 0xFF0000) >> 16;
        uint8_t r = (currentColor & RGB24_MASK_RED) >> 16;

        // 获取当前颜色的 G 分量
        // uint8_t g = (currentColor & 0x00FF00) >> 8;
        uint8_t g = (currentColor & RGB24_MASK_GREEN) >> 8;

        // 获取当前颜色的 B 分量
        // uint8_t b = (currentColor & 0x0000FF);
        uint8_t b = (currentColor & RGB24_MASK_BLUE);

        // 按 BGR 顺序写入一个像素 RGB24 到文件中
        for (int j = 0; j < height; j++)
        {
            fputc(r, rgbFile);
            fputc(g, rgbFile);
            fputc(b, rgbFile);
        }
    }

    // 关闭文件
    fclose(rgbFile);
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
bool Rainbow::writeRainbow2(const char *outputFile, int width, int height)
{
    std::cout << "Rainbow::writeRainbow():: outputFile:" << outputFile << std::endl;
    int fd;                                                  // 文件描述
    fd = open(outputFile, O_RDWR | O_CREAT | O_TRUNC, 0644); // 打开文件,不存在,创建文件,如果已经存在,置空
    if (fd == -1)
    {
        perror("open error");
        std::cout << "创建并打开文件失败:" << outputFile << std::endl;
        return false;
    }

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
            // currentColor = rainbowColors[1];
            currentColor = *(rainbowColors + 1);
        }
        else if (i < 400)
        {
            // currentColor = rainbowColors[1];
            currentColor = *(rainbowColors + 1);
        }
        else if (i < 500)
        {
            // currentColor = rainbowColors[1];
            currentColor = *(rainbowColors + 1);
        }
        else if (i < 600)
        {
            // currentColor = rainbowColors[1];
            currentColor = *(rainbowColors + 1);
        }
        else if (i < 700)
        {
            // currentColor = rainbowColors[1];
            currentColor = *(rainbowColors + 1);
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
        //  按 BGR 顺序写入一个像素 RGB24 到文件中
        for (int j = 0; j < height; j++)
        {
            int number = write(fd, &r, sizeof(r)); // 写入一个字键数据
            number = write(fd, &g, sizeof(r));     // 写入一个字键数据
            number = write(fd, &b, sizeof(r));     // 写入一个字键数据
        }
    }

    // 关闭文件
    close(fd);
    return true;
}