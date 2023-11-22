#include <iostream>
#include <cstring>
#include "AndroidGifEncoder.h"
#include "GifDecoderEncoderSample.h"

using namespace std;

// 颜色表
uint32_t colors[] = {
    0XFFFF0000, // 赤
    0XFFFFA500, // 橙
    0XFFFFFF00, // 黄
    0XFF00FF00, // 绿
    0XFF007FFF, // 青
    0XFF0000FF, // 蓝
    0XFF8B00FF, // 紫
    0XFF000000  // 黑
};

/**
 * @brief Gif编码
 *
 * @param arc
 * @param argv
 * @return int
 */
int main(int arc, char *argv[])
{
    testSimpleGCTGifEncoder();
    testLCTGifEncoder();
    testGCTGifEncoder();
    testFastGifEncoder();
    testGifEncoder();
    return 0;
}

void testGifEncoder()
{
    const char *tag = "SampleGifEncoder::";
    printf("%s%s():: Line %d\n", tag, __FUNCTION__, __LINE__);

    char *rgbFiles[] = {
        "./resource/gif-decoder2-0.rgb",
        "./resource/gif-decoder2-1.rgb",
        "./resource/gif-decoder2-2.rgb",
        "./resource/gif-decoder2-3.rgb",
        "./resource/gif-decoder2-4.rgb"};

    AndroidGifEncoder *androidGifEncoder = new AndroidGifEncoder();
    uint32_t width = 220;
    uint32_t height = 220;
    uint32_t threadCount = 1;
    bool useDither = true;
    int delayMs = 50;
    EncodingType encodingType = ENCODING_TYPE_NORMAL_LOW_MEMORY;
    const char *filePath = "./resource/gen-test2.gif";
    androidGifEncoder->initialize(width, height, filePath, encodingType, threadCount);
    androidGifEncoder->setDither(useDither);
    uint32_t size = sizeof(rgbFiles) / sizeof(rgbFiles[0]);
    printf("%s%s():: Line %d,size:%d\n", tag, __FUNCTION__, __LINE__, size);
    for (int i = 0; i < size; i++)
    {
        FILE *fp = fopen(rgbFiles[i], "rb");
        if (fp != NULL)
        {
            fseek(fp, 0, SEEK_END);
            int32_t fileSize = ftell(fp);
            uint8_t *pixels = new uint8_t[fileSize]; // 申请图像帧数据内存
            rewind(fp);
            memset(pixels, 0, fileSize); // 先清空内存
            fread(pixels, fileSize, 1, fp);
            androidGifEncoder->encodeFrame(pixels, delayMs);
            delete[] pixels; // 释放内存
            fclose(fp);
        }
    }
    androidGifEncoder->destory();
}

void testSimpleGCTGifEncoder()
{
    const char *tag = "SampleGifEncoder::";
    printf("%s%s():: Line %d\n", tag, __FUNCTION__, __LINE__);
    AndroidGifEncoder *androidGifEncoder = new AndroidGifEncoder();
    uint32_t width = 300;
    uint32_t height = 300;
    uint32_t threadCount = 1;
    bool useDither = true;
    int delayMs = 50;
    EncodingType encodingType = ENCODING_TYPE_SIMPLE_FAST;
    const char *filePath = "./resource/simple-fast.gif";
    androidGifEncoder->initialize(width, height, filePath, encodingType, threadCount);
    androidGifEncoder->setDither(useDither);
    uint32_t size = sizeof(colors) / sizeof(colors[0]);
    printf("%s%s():: Line %d,size:%d\n", tag, __FUNCTION__, __LINE__, size);
    // 申请图像帧数据内存
    int32_t pixelNum = width * height;
    uint8_t *pixels = new uint8_t[pixelNum * 4];
    for (int i = 0; i < size; i++)
    {
        memset(pixels, 0, pixelNum * 4); // 先清空内存
        // 当前颜色 ARBB 分量
        uint32_t currentColor = colors[i];
        uint8_t A = (currentColor & 0xFF000000) >> 24;
        uint8_t R = (currentColor & 0x00FF0000) >> 16;
        uint8_t G = (currentColor & 0x0000FF00) >> 8;
        uint8_t B = currentColor & 0x000000FF;
        // printf("%s%s():: Line %d,a:%x,r:%x,g:%x,b:%x\n", tag, __FUNCTION__, __LINE__, A, R, G, B);

        for (int i = 0; i < height; ++i)
        {
            for (int j = 0; j < width; ++j)
            {
                uint32_t index = (i * width + j) * 4;
                // printf("%s%s():: Line %d,a:%x,r:%x,g:%x,b:%x,index:%d\n", tag, __FUNCTION__, __LINE__, A, R, G, B, index);
                memcpy(pixels + index, &A, sizeof(uint8_t));
                memcpy(pixels + index + 1, &R, sizeof(uint8_t));
                memcpy(pixels + index + 2, &G, sizeof(uint8_t));
                memcpy(pixels + index + 3, &B, sizeof(uint8_t));
            }
        }
        androidGifEncoder->encodeFrame(pixels, delayMs);
    }
    delete[] pixels; // 释放内存
    androidGifEncoder->destory();
}

void testFastGifEncoder()
{
    const char *tag = "SampleGifEncoder::";
    printf("%s%s():: Line %d\n", tag, __FUNCTION__, __LINE__);
    AndroidGifEncoder *androidGifEncoder = new AndroidGifEncoder();
    uint32_t width = 300;
    uint32_t height = 300;
    uint32_t threadCount = 1;
    bool useDither = true;
    int delayMs = 50;
    EncodingType encodingType = ENCODING_TYPE_FAST;
    const char *filePath = "./resource/fast.gif";
    androidGifEncoder->initialize(width, height, filePath, encodingType, threadCount);
    androidGifEncoder->setDither(useDither);
    uint32_t size = sizeof(colors) / sizeof(colors[0]);
    printf("%s%s():: Line %d,size:%d\n", tag, __FUNCTION__, __LINE__, size);
    // 申请图像帧数据内存
    int32_t pixelNum = width * height;
    uint8_t *pixels = new uint8_t[pixelNum * 4];
    for (int i = 0; i < size; i++)
    {
        memset(pixels, 0, pixelNum * 4); // 先清空内存
        // 当前颜色 ARBB 分量
        uint32_t currentColor = colors[i];
        uint8_t A = (currentColor & 0xFF000000) >> 24;
        uint8_t R = (currentColor & 0x00FF0000) >> 16;
        uint8_t G = (currentColor & 0x0000FF00) >> 8;
        uint8_t B = currentColor & 0x000000FF;
        // printf("%s%s():: Line %d,a:%x,r:%x,g:%x,b:%x\n", tag, __FUNCTION__, __LINE__, A, R, G, B);

        for (int i = 0; i < height; ++i)
        {
            for (int j = 0; j < width; ++j)
            {
                uint32_t index = (i * width + j) * 4;
                // printf("%s%s():: Line %d,a:%x,r:%x,g:%x,b:%x,index:%d\n", tag, __FUNCTION__, __LINE__, A, R, G, B, index);
                memcpy(pixels + index, &A, sizeof(uint8_t));
                memcpy(pixels + index + 1, &R, sizeof(uint8_t));
                memcpy(pixels + index + 2, &G, sizeof(uint8_t));
                memcpy(pixels + index + 3, &B, sizeof(uint8_t));
            }
        }
        androidGifEncoder->encodeFrame(pixels, delayMs);
    }
    delete[] pixels; // 释放内存
    androidGifEncoder->destory();
}

void testGCTGifEncoder()
{
    const char *tag = "SampleGifEncoder::";
    printf("%s%s():: Line %d\n", tag, __FUNCTION__, __LINE__);
    AndroidGifEncoder *androidGifEncoder = new AndroidGifEncoder();
    uint32_t width = 300;
    uint32_t height = 300;
    uint32_t threadCount = 1;
    bool useDither = true;
    int delayMs = 50;
    EncodingType encodingType = ENCODING_TYPE_STABLE_HIGH_MEMORY;
    const char *filePath = "./resource/stable-high-memory.gif";
    androidGifEncoder->initialize(width, height, filePath, encodingType, threadCount);
    androidGifEncoder->setDither(useDither);
    uint32_t size = sizeof(colors) / sizeof(colors[0]);
    printf("%s%s():: Line %d,size:%d\n", tag, __FUNCTION__, __LINE__, size);
    // 申请图像帧数据内存
    int32_t pixelNum = width * height;
    uint8_t *pixels = new uint8_t[pixelNum * 4];
    for (int i = 0; i < size; i++)
    {
        memset(pixels, 0, pixelNum * 4); // 先清空内存
        // 当前颜色 ARBB 分量
        uint32_t currentColor = colors[i];
        uint8_t A = (currentColor & 0xFF000000) >> 24;
        uint8_t R = (currentColor & 0x00FF0000) >> 16;
        uint8_t G = (currentColor & 0x0000FF00) >> 8;
        uint8_t B = currentColor & 0x000000FF;
        // printf("%s%s():: Line %d,a:%x,r:%x,g:%x,b:%x\n", tag, __FUNCTION__, __LINE__, A, R, G, B);

        for (int i = 0; i < height; ++i)
        {
            for (int j = 0; j < width; ++j)
            {
                uint32_t index = (i * width + j) * 4;
                // printf("%s%s():: Line %d,a:%x,r:%x,g:%x,b:%x,index:%d\n", tag, __FUNCTION__, __LINE__, A, R, G, B, index);
                memcpy(pixels + index, &A, sizeof(uint8_t));
                memcpy(pixels + index + 1, &R, sizeof(uint8_t));
                memcpy(pixels + index + 2, &G, sizeof(uint8_t));
                memcpy(pixels + index + 3, &B, sizeof(uint8_t));
            }
        }
        androidGifEncoder->encodeFrame(pixels, delayMs);
    }
    delete[] pixels; // 释放内存
    androidGifEncoder->destory();
}

void testLCTGifEncoder()
{
    const char *tag = "SampleGifEncoder::";
    printf("%s%s():: Line %d\n", tag, __FUNCTION__, __LINE__);
    AndroidGifEncoder *androidGifEncoder = new AndroidGifEncoder();
    uint32_t width = 300;
    uint32_t height = 300;
    uint32_t threadCount = 1;
    bool useDither = true;
    int delayMs = 50;
    EncodingType encodingType = ENCODING_TYPE_NORMAL_LOW_MEMORY;
    const char *filePath = "./resource/normal-low-memory.gif";
    androidGifEncoder->initialize(width, height, filePath, encodingType, threadCount);
    androidGifEncoder->setDither(useDither);
    uint32_t size = sizeof(colors) / sizeof(colors[0]);
    printf("%s%s():: Line %d,size:%d\n", tag, __FUNCTION__, __LINE__, size);
    // 申请图像帧数据内存
    int32_t pixelNum = width * height;
    uint8_t *pixels = new uint8_t[pixelNum * 4];
    for (int i = 0; i < size; i++)
    {
        memset(pixels, 0, pixelNum * 4); // 先清空内存
        // 当前颜色 ARBB 分量
        uint32_t currentColor = colors[i];
        uint8_t A = (currentColor & 0xFF000000) >> 24;
        uint8_t R = (currentColor & 0x00FF0000) >> 16;
        uint8_t G = (currentColor & 0x0000FF00) >> 8;
        uint8_t B = currentColor & 0x000000FF;
        // printf("%s%s():: Line %d,a:%x,r:%x,g:%x,b:%x\n", tag, __FUNCTION__, __LINE__, A, R, G, B);

        for (int i = 0; i < height; ++i)
        {
            for (int j = 0; j < width; ++j)
            {
                uint32_t index = (i * width + j) * 4;
                // printf("%s%s():: Line %d,a:%x,r:%x,g:%x,b:%x,index:%d\n", tag, __FUNCTION__, __LINE__, A, R, G, B, index);
                memcpy(pixels + index, &A, sizeof(uint8_t));
                memcpy(pixels + index + 1, &R, sizeof(uint8_t));
                memcpy(pixels + index + 2, &G, sizeof(uint8_t));
                memcpy(pixels + index + 3, &B, sizeof(uint8_t));
            }
        }
        androidGifEncoder->encodeFrame(pixels, delayMs);
    }
    delete[] pixels; // 释放内存
    androidGifEncoder->destory();
}
