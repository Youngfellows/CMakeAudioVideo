#include "../../include/ZArchiver.h"

// 告诉编译器，这部分代码按C语言的格式进行编译，而不是C++的
#ifdef __cplusplus
extern "C"
{
#endif

    /**
     * @brief 解压缩
     *
     * @param dest
     * @param destLen
     * @param source
     * @param sourceLen
     */
    void unCompress(Bytef *dest, uLongf *destLen, const Bytef *source, uLong sourceLen)
    {
        uncompress(dest, destLen, source, sourceLen);
    }

#ifdef __cplusplus
}
#endif