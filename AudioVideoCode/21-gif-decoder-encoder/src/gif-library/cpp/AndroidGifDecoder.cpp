
#include "AndroidGifDecoder.h"
#include <cstring>

AndroidGifDecoder::AndroidGifDecoder()
{
    printf("%s():: Line %d\n", __FUNCTION__, __LINE__);
}

AndroidGifDecoder::~AndroidGifDecoder()
{
    printf("%s():: Line %d\n", __FUNCTION__, __LINE__);
}

/**
 * @brief  初始化Gif解码器
 *
 * @return true
 * @return false
 */
bool AndroidGifDecoder::initialize()
{
    printf("%s():: Line %d\n", __FUNCTION__, __LINE__);
    if (gifDecoder == NULL)
    {
        gifDecoder = new GifDecoder();
    }
    return true;
}

/**
 * @brief  加载Gif动画
 *
 * @param filePath
 * @return true
 * @return false
 */
bool AndroidGifDecoder::load(const char *filePath)
{
    printf("%s():: Line %d\n", __FUNCTION__, __LINE__);
    if (filePath == NULL)
    {
        printf("%s():: Line %d,file is null\n", __FUNCTION__, __LINE__);
        return false;
    }
    if (gifDecoder == NULL)
    {
        return false;
    }
    bool result = gifDecoder->load(filePath);
    printf("%s():: Line %d,result:%d\n", __FUNCTION__, __LINE__, result);
    return result;
}

/**
 * @brief  加载Gif动画
 *
 * @param filePath
 * @return true
 * @return false
 */
bool AndroidGifDecoder::loadUsingIterator(const char *filePath)
{
    printf("%s():: Line %d\n", __FUNCTION__, __LINE__);
    if (filePath == NULL)
    {
        printf("%s():: Line %d,file is null\n", __FUNCTION__, __LINE__);
        return false;
    }
    if (gifDecoder == NULL)
    {
        return false;
    }
    bitmapIterator = gifDecoder->loadUsingIterator(filePath);
    printf("%s():: Line %d,result:%p\n", __FUNCTION__, __LINE__, bitmapIterator);
    if (bitmapIterator == NULL)
    {
        return false;
    }
    return true;
}

/**
 * @brief  获取是否有下一帧
 *
 * @return true
 * @return false
 */
bool AndroidGifDecoder::bitmapIteratorHasNext()
{
    printf("%s():: Line %d\n", __FUNCTION__, __LINE__);
    if (bitmapIterator == NULL)
    {
        return false;
    }
    return bitmapIterator->hasNext();
}

/**
 * @brief 获取下一帧数据

 *
 * @return GifFrame
 */
GifFrame *AndroidGifDecoder::bitmapIteratornext()
{
    printf("%s():: Line %d\n", __FUNCTION__, __LINE__);
    if (bitmapIterator == NULL)
    {
        return NULL;
    }
    const uint32_t *frame = NULL;
    uint32_t delayMs = 0;
    bool result = bitmapIterator->next(&frame, &delayMs);
    if (!result)
    {
        return NULL;
    }
    if (frame == NULL)
    {
        printf("%s():: Line %d,frame data is null\n", __FUNCTION__, __LINE__);
        return NULL;
    }
    // 拷贝每一帧数据
    int32_t pixelNum = getWidth() * getHeight();
    printf("%s():: Line %d\n", __FUNCTION__, __LINE__);
    uint32_t *frameData = new uint32_t[pixelNum * 4];
    memset(frameData, 0, pixelNum * 4); // 先清空内存
    printf("%s():: Line %d\n", __FUNCTION__, __LINE__);
    memcpy(frameData, frame, pixelNum * 4);
    printf("%s():: Line %d\n", __FUNCTION__, __LINE__);
    GifFrame *gifFrame = new GifFrame(frameData, delayMs);
    printf("%s():: Line %d\n", __FUNCTION__, __LINE__);
    delete[] frameData; // 释放内存
    return gifFrame;
}
/**
 * @brief 获取Gif动画帧数
 *
 * @return uint32_t
 */
uint32_t AndroidGifDecoder::getFrameCount()
{
    printf("%s():: Line %d\n", __FUNCTION__, __LINE__);
    if (gifDecoder == NULL)
    {
        return 0;
    }
    return gifDecoder->getFrameCount();
}

/**
 * @brief  获取每一帧延时时长
 *
 * @param index
 * @return uint32_t
 */
uint32_t AndroidGifDecoder::getDelay(int32_t index)
{
    // printf("%s():: Line %d\n", __FUNCTION__, __LINE__);
    if (gifDecoder == NULL)
    {
        return 0;
    }
    if (index >= getFrameCount())
    {
        return 0;
    }

    return gifDecoder->getDelay(index);
}

/**
 * @brief 获取每一帧数据
 *
 * @param index
 * @return GifFrame
 */
GifFrame *AndroidGifDecoder::getFrame(int32_t index)
{
    // printf("%s():: Line %d\n", __FUNCTION__, __LINE__);
    if (gifDecoder == NULL)
    {
        return NULL;
    }
    if (index >= gifDecoder->getFrameCount())
    {
        printf("%s():: Line %d,index out of bounds\n", __FUNCTION__, __LINE__);
        return NULL;
    }

    // 获取Gif指定帧数据
    const uint32_t *data = gifDecoder->getFrame(index);
    uint32_t delayMs = gifDecoder->getDelay(index);

    // 拷贝每一帧数据
    int32_t pixelNum = getWidth() * getHeight();
    uint32_t *frameData = new uint32_t[pixelNum * 4];
    memset(frameData, 0, pixelNum * 4); // 先清空内存
    memcpy(frameData, data, pixelNum * 4);
    GifFrame *gifFrame = new GifFrame(frameData, delayMs);
    delete[] frameData; // 释放内存
    return gifFrame;
}

/**
 * @brief获取Gif图片宽
 *
 * @return uint32_t
 */
uint32_t AndroidGifDecoder::getWidth()
{
    // printf("%s():: Line %d\n", __FUNCTION__, __LINE__);
    if (gifDecoder == NULL)
    {
        return 0;
    }
    return gifDecoder->getWidth();
}

/**
 * @brief 获取Gif图片高
 *
 * @return uint32_t
 */
uint32_t AndroidGifDecoder::getHeight()
{
    // printf("%s():: Line %d\n", __FUNCTION__, __LINE__);
    if (gifDecoder == NULL)
    {
        return 0;
    }
    return gifDecoder->getHeight();
}

/**
 * @brief 销毁Gif解码器资源
 *
 */
void AndroidGifDecoder::destory()
{
    printf("%s():: Line %d\n", __FUNCTION__, __LINE__);
    if (gifDecoder != NULL)
    {
    }
}