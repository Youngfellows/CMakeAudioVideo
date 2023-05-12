#include "AndroidGifEncoder.h"

AndroidGifEncoder::AndroidGifEncoder(/* args */)
{
    printf("%s():: Line %d\n", __FUNCTION__, __LINE__);
}

AndroidGifEncoder::~AndroidGifEncoder()
{
    printf("%s():: Line %d\n", __FUNCTION__, __LINE__);
    destory();
}

/**
 * @brief 初始化Gif编码器
 *
 * @param width
 * @param height
 * @param filePath
 * @param encodingType
 * @param threadCount
 * @return true
 * @return false
 */
bool AndroidGifEncoder::initialize(uint32_t width, uint32_t height, const char *filePath,
                                   EncodingType encodingType, uint32_t threadCount)
{
    printf("%s():: Line %d\n", __FUNCTION__, __LINE__);
    gifEncoder = new GifEncoder(encodingType);
    gifEncoder->setThreadCount(threadCount);
    bool result = gifEncoder->init(width, height, filePath);
    return result;
}

/**
 * @brief 设置使用抖动
 *
 * @param useDither
 */
void AndroidGifEncoder::setDither(bool useDither)
{
    printf("%s():: Line %d\n", __FUNCTION__, __LINE__);
    if (gifEncoder != NULL)
    {
        gifEncoder->setDither(useDither);
    }
}

/**
 * @brief  编码帧数据
 *
 * @param frame
 * @param delayMs
 * @return true
 * @return false
 */
bool AndroidGifEncoder::encodeFrame(uint8_t *pixels, uint32_t delayMs)
{
    // printf("%s():: Line %d\n", __FUNCTION__, __LINE__);
    if (gifEncoder == NULL)
    {
        return false;
    }
    uint16_t imgWidth = gifEncoder->getWidth();
    uint16_t imgHeight = gifEncoder->getHeight();
    uint32_t *src = (uint32_t *)pixels;
    uint32_t *tempPixels = new unsigned int[imgWidth * imgHeight];
    int stride = imgWidth * 4;
    int pixelsCount = stride * imgHeight;
    memcpy(tempPixels, src, pixelsCount);
    gifEncoder->encodeFrame(tempPixels, delayMs);
    delete[] tempPixels;
    return true;
}

/**
 * @brief 设置线程数量
 *
 * @param threadCount
 */
void AndroidGifEncoder::setThreadCount(uint32_t threadCount)
{
    printf("%s():: Line %d\n", __FUNCTION__, __LINE__);
}

/**
 * @brief 释放资源
 *
 */
void AndroidGifEncoder::destory()
{
    printf("%s():: Line %d\n", __FUNCTION__, __LINE__);
    if (gifEncoder != NULL)
    {
        gifEncoder->release();
    }
    delete gifEncoder;
    gifEncoder = NULL;
}