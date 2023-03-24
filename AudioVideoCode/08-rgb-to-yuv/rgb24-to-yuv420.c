//
// Created by hubin on 2019/9/17.
//

#include <stdio.h>
#include <stdint.h>

// 彩虹的七种颜色
uint32_t rainbowColors[] = {
    0XFF0000, // 红
    0XFFA500, // 橙
    0XFFFF00, // 黄
    0X00FF00, // 绿
    0X007FFF, // 青
    0X0000FF, // 蓝
    0X8B00FF  // 紫
};

void genRGB24Data(uint8_t *rgbData, int width, int height)
{

    for (int i = 0; i < width; ++i)
    {
        // 当前颜色
        uint32_t currentColor = rainbowColors[0];
        if (i < 100)
        {
            currentColor = rainbowColors[0];
        }
        else if (i < 200)
        {
            currentColor = rainbowColors[1];
        }
        else if (i < 300)
        {
            currentColor = rainbowColors[2];
        }
        else if (i < 400)
        {
            currentColor = rainbowColors[3];
        }
        else if (i < 500)
        {
            currentColor = rainbowColors[4];
        }
        else if (i < 600)
        {
            currentColor = rainbowColors[5];
        }
        else if (i < 700)
        {
            currentColor = rainbowColors[6];
        }
        // 当前颜色 R 分量
        uint8_t R = (currentColor & 0xFF0000) >> 16;
        // 当前颜色 G 分量
        uint8_t G = (currentColor & 0x00FF00) >> 8;
        // 当前颜色 B 分量
        uint8_t B = currentColor & 0x0000FF;

        for (int j = 0; j < height; ++j)
        {
            int currentIndex = 3 * (i * height + j);
            rgbData[currentIndex] = R;
            rgbData[currentIndex + 1] = G;
            rgbData[currentIndex + 2] = B;
        }
    }
}

void rgb24ToYuv420p(uint8_t *destination, uint8_t *rgb, int width, int height)
{
    size_t image_size = width * height;
    size_t upos = image_size;
    size_t vpos = upos + upos / 4;
    size_t i = 0;

    for (size_t line = 0; line < height; ++line)
    {
        if (!(line % 2))
        {
            for (size_t x = 0; x < width; x += 2)
            {
                uint8_t r = rgb[3 * i];
                uint8_t g = rgb[3 * i + 1];
                uint8_t b = rgb[3 * i + 2];

                destination[i++] = ((66 * r + 129 * g + 25 * b) >> 8) + 16;

                destination[upos++] = ((-38 * r + -74 * g + 112 * b) >> 8) + 128;
                destination[vpos++] = ((112 * r + -94 * g + -18 * b) >> 8) + 128;

                r = rgb[3 * i];
                g = rgb[3 * i + 1];
                b = rgb[3 * i + 2];

                destination[i++] = ((66 * r + 129 * g + 25 * b) >> 8) + 16;
            }
        }
        else
        {
            for (size_t x = 0; x < width; x += 1)
            {
                uint8_t r = rgb[3 * i];
                uint8_t g = rgb[3 * i + 1];
                uint8_t b = rgb[3 * i + 2];

                destination[i++] = ((66 * r + 129 * g + 25 * b) >> 8) + 16;
            }
        }
    }
}

// yuv420pData, rgb24Data, width, height
void rgb24ToYuv420p2(uint8_t *yuv420pData, uint8_t *rgb24Data, int width, int height)
{
    size_t y_size = width * height;
    size_t u_size = ((width + 1) / 2) * ((height + 1) / 2);
    size_t v_size = ((width + 1) / 2) * (height / 2);
    uint32_t size = y_size + u_size + v_size;

    size_t upos = y_size;
    size_t vpos = upos + u_size;
    size_t i = 0;

    printf("%s():: Line:%d,upos:%d,vpos:%d\n", __FUNCTION__, __LINE__, upos, vpos);

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

int main(int arg, char **argv)
{
    // const char *TAG = "rgb24-to-yuv420";
    printf("\n%s::%s():: Line:%d,arg:%d\n", __FILE__, __FUNCTION__, __LINE__, arg);
    // std::cout << TAG << __FUNCTION__ << ",Line " << __LINE__ << ",arg:" << arg << std::endl;
    // if (arg < 3)
    // {
    //     std::cout << TAG << __FUNCTION__ << ",Line " << __LINE__ << ",使用: " << argv[0] << " 宽 高" << std::endl;
    //     std::cout << TAG << __FUNCTION__ << ",Line " << __LINE__ << ",使用: " << argv[0] << " 711 711" << std::endl;
    //     return 1;
    // }
    // uint32_t width = 711;  // 宽
    // uint32_t height = 711; // 高
    uint32_t width = atoi(argv[1]);  // 宽
    uint32_t height = atoi(argv[2]); // 高
    printf("width:%d,height:%d\n", width, height);

    // int width = 700, height = 700;
    size_t y_size = width * height;
    size_t u_size = ((width + 1) / 2) * ((height + 1) / 2);
    size_t v_size = ((width + 1) / 2) * (height / 2);
    uint32_t size = y_size + u_size + v_size;

    uint8_t rgb24Data[width * height * 3];
    // uint8_t yuv420pData[width * height * 3 / 2];
    uint8_t yuv420pData[size];

    genRGB24Data(rgb24Data, width, height);
    printf("%s():: Line:%d\n", __FUNCTION__, __LINE__);
    rgb24ToYuv420p2(yuv420pData, rgb24Data, width, height);
    // rgb24ToYuv420p(yuv420pData, rgb24Data, width, height);
    printf("%s():: Line:%d\n", __FUNCTION__, __LINE__);

    FILE *yuvFile = fopen("./resource/rainbow-700x700-rgb24-toyuv420p.yuv", "wb");
    if (yuvFile == NULL)
    {
        printf("%s():: Line:%d,%s\n", __FUNCTION__, __LINE__, "打开文件失败");
    }
    printf("%s():: Line:%d\n", __FUNCTION__, __LINE__);
    fwrite(yuv420pData, sizeof(yuv420pData), 1, yuvFile);
    printf("%s():: Line:%d\n", __FUNCTION__, __LINE__);
    fclose(yuvFile);
    printf("%s():: Line:%d\n", __FUNCTION__, __LINE__);
    return 0;
}