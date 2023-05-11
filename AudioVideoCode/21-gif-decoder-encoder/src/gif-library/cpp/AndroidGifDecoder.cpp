
#include "AndroidGifDecoder.h"

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
    bool result = gifDecoder->loadUsingIterator(filePath);
    printf("%s():: Line %d,result:%d\n", __FUNCTION__, __LINE__, result);
    return result;
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
    return true;
}

/**
 * @brief 获取下一帧数据

 *
 * @return GifFrame
 */
GifFrame *AndroidGifDecoder::bitmapIteratornext()
{
    printf("%s():: Line %d\n", __FUNCTION__, __LINE__);
    return NULL;
}
/**
 * @brief 获取Gif动画帧数
 *
 * @return uint32_t
 */
uint32_t AndroidGifDecoder::getFrameCount()
{
    printf("%s():: Line %d\n", __FUNCTION__, __LINE__);
    return 0;
}

/**
 * @brief  获取每一帧延时时长
 *
 * @param index
 * @return uint32_t
 */
uint32_t AndroidGifDecoder::getDelay(uint32_t index)
{
    printf("%s():: Line %d\n", __FUNCTION__, __LINE__);
    return 0;
}

/**
 * @brief 获取每一帧数据
 *
 * @param index
 * @return GifFrame
 */
GifFrame *AndroidGifDecoder::getFrame(uint32_t index)
{
    printf("%s():: Line %d\n", __FUNCTION__, __LINE__);
    return NULL;
}

/**
 * @brief获取Gif图片宽
 *
 * @return uint32_t
 */
uint32_t AndroidGifDecoder::getWidth()
{
    printf("%s():: Line %d\n", __FUNCTION__, __LINE__);
    return 0;
}

/**
 * @brief 获取Gif图片高
 *
 * @return uint32_t
 */
uint32_t AndroidGifDecoder::getHeight()
{
    printf("%s():: Line %d\n", __FUNCTION__, __LINE__);
    return 0;
}

/**
 * @brief 销毁Gif解码器资源
 *
 */
void AndroidGifDecoder::destory()
{
    printf("%s():: Line %d\n", __FUNCTION__, __LINE__);
}