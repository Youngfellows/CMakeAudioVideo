#ifndef _YUV444P_TO_YUV420P_
#define _YUV444P_TO_YUV420P_

#include <iostream>
#include <string>
// #include <cmath>
#include "./interfaces/IYUV444ptoYUV420p.h"
#include "../rainbow/Rainbow.h"
#include "../pixel/RGB24.h"

using namespace std;

/**
 * @brief 具体实现类: YUV444p转化为YUV420p
 *
 */
class YUV444ptoYUV420p : public IYUV444ptoYUV420p
{
private:
    const std::string TAG = "YUV444ptoYUV420p::";
    uint32_t width;       // 宽
    uint32_t height;      // 高
    IRainbow *rainbow;    // 彩虹图片生成器
    IRGB24Pixel *rgb24;   // rgb24生成器
    uint8_t *yuv444pData; // yuv444p内存数据
    uint8_t *yuv420pData; // yuv420p内存数据
    uint8_t *rgb24Data;   // rgb24内存数据
    uint32_t ySize;       // Y分量大小
    uint32_t uSize;       // U分量大小
    uint32_t vSize;       // V分量大小
    uint32_t yuv420pSize; // yuv420p大小

public:
    YUV444ptoYUV420p();
    ~YUV444ptoYUV420p();
    virtual bool create(uint32_t width, uint32_t height) override;                                         // 覆写函数,初始化
    virtual bool createFromRGB24(const char *rgb24FilePath, uint32_t width, uint32_t height) override;     // 覆写函数,初始化
    virtual bool createFromYUV444p(const char *yuv444pFilePath, uint32_t width, uint32_t height) override; // 覆写函数,初始化
    virtual void yuv444pToYuv420p(const char *yuv420pFilePath) override;                                   // 覆写函数,yuv444p转化为yuv420p
    virtual void destory() override;                                                                       // 覆写函数,释放资源

private:
    bool rgb24ToYuv444();                                                            // rgb24转化为yuv444
    void yuv444pToYuv420p();                                                         // yuv444转化为yuv420
    bool rgb24Parser(const char *rgb24FilePath);                                     // 解析rgb24内存数据
    bool yuv444pParser(const char *yuv444pFilePath);                                 // 解析yuv444p内存数据
    void saveYuv420p(const char *yuv420pFilePath);                                   // 保存yuv420p数据到文件
    bool mallocYuv444();                                                             // 申请yuv444p内存空间
    void rgbToYuv(uint8_t R, uint8_t G, uint8_t B, int8_t *Y, int8_t *U, int8_t *V); // RGB转化为YUV
};

#endif