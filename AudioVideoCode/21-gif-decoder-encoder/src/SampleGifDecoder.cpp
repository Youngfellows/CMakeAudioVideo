#include <iostream>
#include "AndroidGifDecoder.h"

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
    const char *tag = "SampleGifDecoder::";
    printf("%s%s,Line %d\n", tag, __FUNCTION__, __LINE__);
    const char *filePath = "./resource/test4.gif";
    AndroidGifDecoder *androidGifDecoder = new AndroidGifDecoder();
    bool init = androidGifDecoder->initialize();
    printf("%s%s,Line %d,init:%d\n", tag, __FUNCTION__, __LINE__, init);
    if (init)
    {
        bool result = androidGifDecoder->load(filePath);
        printf("%s%s,Line %d,init:%d\n", tag, __FUNCTION__, __LINE__, result);
        uint32_t width = androidGifDecoder->getWidth();
        uint32_t height = androidGifDecoder->getHeight();
        uint32_t frameCount = androidGifDecoder->getFrameCount();
        GifFrame *gifFrame = androidGifDecoder->getFrame(1);

        bool result1 = androidGifDecoder->loadUsingIterator(filePath);
        bool hasNext = androidGifDecoder->bitmapIteratorHasNext();
        GifFrame *gifFrame1 = androidGifDecoder->bitmapIteratornext();
    }

    delete androidGifDecoder;
    return 0;
}