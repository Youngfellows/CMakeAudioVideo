#include <iostream>
#include "AndroidGifDecoder.h"
#include "GifDecoderEncoderSample.h"

using namespace std;

/**
 * @brief Gif解码
 *
 * @param arc
 * @param argv
 * @return int
 */
int main(int arc, char *argv[])
{
    gifDecoderTest1();
    gifDecoderTest2();
    return 0;
}

/**
 * @brief  Gif解码方式1,按帧加载
 *
 */
void gifDecoderTest1()
{
    const char *tag = "SampleGifDecoder::";
    printf("%s%s,Line %d\n", tag, __FUNCTION__, __LINE__);
    const char *gifFilePath1 = "./resources/test1.gif";
    const char *outFileNamePattern1 = "./resource/gif-decoder1-%d.rgb";

    AndroidGifDecoder *androidGifDecoder = new AndroidGifDecoder();
    bool init = androidGifDecoder->initialize();
    printf("%s%s,Line %d,init:%d\n", tag, __FUNCTION__, __LINE__, init);
    // Gif解码方式1,按帧加载
    bool result = androidGifDecoder->load(gifFilePath1);
    printf("%s%s,Line %d,init:%d\n", tag, __FUNCTION__, __LINE__, result);
    if (result)
    {
        uint32_t width = androidGifDecoder->getWidth();
        uint32_t height = androidGifDecoder->getHeight();
        uint32_t frameCount = androidGifDecoder->getFrameCount();
        printf("%s%s,Line %d,width:%d,height:%d,frameCount:%d\n", tag, __FUNCTION__, __LINE__, width, height, frameCount);

        if (frameCount > 0)
        {
            uint32_t screenIndex = 0;
            // 获取每一帧的rgb数据并写入文件
            for (int i = 0; i < frameCount; i++)
            {
                GifFrame *gifFrame = androidGifDecoder->getFrame(i);
                if (gifFrame != NULL)
                {
                    int32_t delayMs = gifFrame->delayMs;
                    printf("%s%s,Line %d,delayMs:%d\n", tag, __FUNCTION__, __LINE__, delayMs);
                    char *outFilePath = (char *)malloc(255 * sizeof(char));
                    sprintf(outFilePath, outFileNamePattern1, screenIndex); // 字符串拼接,输出文件路径
                    printf("%s%s,Line %d,Final 1 File Name: %s\n", tag, __FUNCTION__, __LINE__, outFilePath);

                    // 把rgb数据写入文件
                    FILE *fp = fopen(outFilePath, "wb");
                    free(outFilePath);
                    if (!fp)
                    {
                        printf("%s%s,Line %d,open file error\n", tag, __FUNCTION__, __LINE__);
                    }
                    else
                    {
                        uint32_t size = width * height * 4;
                        fwrite(gifFrame->data, size, 1, fp);
                        fclose(fp);
                        printf("%s%s,Line %d,write %d success\n", tag, __FUNCTION__, __LINE__, screenIndex);
                        screenIndex++;
                    }
                }
            }
        }
    }
    delete androidGifDecoder;
}

/**
 * @brief Gif解码方式2,使用迭代器加载
 *
 */
void gifDecoderTest2()
{
    const char *tag = "SampleGifDecoder::";
    printf("\n%s%s,Line %d\n", tag, __FUNCTION__, __LINE__);
    const char *gifFilePath2 = "./resources/test2.gif";
    const char *outFileNamePattern2 = "./resource/gif-decoder2-%d.rgb";

    AndroidGifDecoder *androidGifDecoder2 = new AndroidGifDecoder();
    bool init = androidGifDecoder2->initialize();
    // Gif解码方式2,使用迭代器加载
    bool result1 = androidGifDecoder2->loadUsingIterator(gifFilePath2);
    printf("\n%s%s,Line %d,init:%d\n", tag, __FUNCTION__, __LINE__, result1);
    if (result1)
    {
        uint32_t width = androidGifDecoder2->getWidth();
        uint32_t height = androidGifDecoder2->getHeight();
        printf("%s%s,Line %d,width:%d,height:%d\n", tag, __FUNCTION__, __LINE__, width, height);
        uint32_t screenIndex = 0;
        bool hasNext = androidGifDecoder2->bitmapIteratorHasNext(); // 获取是否有下一帧
        while (hasNext)
        {
            GifFrame *gifFrame = androidGifDecoder2->bitmapIteratornext();
            if (gifFrame != NULL)
            {
                // 字符串拼接,输出文件路径
                char *outFilePath = (char *)malloc(255 * sizeof(char));
                sprintf(outFilePath, outFileNamePattern2, screenIndex);
                printf("%s%s,Line %d,Final 2 File Name: %s\n", tag, __FUNCTION__, __LINE__, outFilePath);
                // 把rgb数据写入文件
                FILE *fp = fopen(outFilePath, "wb");
                free(outFilePath);
                if (!fp)
                {
                    printf("%s%s,Line %d,open file error\n", tag, __FUNCTION__, __LINE__);
                }
                else
                {
                    uint32_t size = width * height * 4;
                    fwrite(gifFrame->data, size, 1, fp);
                    fclose(fp);
                    printf("%s%s,Line %d,write %d success\n", tag, __FUNCTION__, __LINE__, screenIndex);
                    screenIndex++;
                }
            }
            hasNext = androidGifDecoder2->bitmapIteratorHasNext(); // 继续迭代下一帧
        }
    }
    delete androidGifDecoder2;
}