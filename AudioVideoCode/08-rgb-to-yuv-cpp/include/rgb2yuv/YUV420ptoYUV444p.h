#ifndef _YUV420P_TO_YUV444P_H_
#define _YUV420P_TO_YUV444P_H_

#include <iostream>
#include <string>
#include "./interfaces/IYUV420ptoYUV444p.h"
#include "./RGB24toYUV420p.h"

using namespace std;

/**
 * @brief 具体实现类:yuv420p转化为yuv444p
 *
 */
class YUV420ptoYUV444p : public IYUV420ptoYUV444p
{
private:
    std::string TAG = "YUV420ptoYUV444p::";
    uint32_t width;                  // 宽
    uint32_t height;                 // 高
    IRGB24toYUV420p *rgb24ToYuv420p; // rgb24转为yuv420p转换器
    uint8_t *yuv420pData;            // yuv420p内存数据
    uint8_t *yuv444pData;            // yuv444p内存数据

public:
    YUV420ptoYUV444p();
    ~YUV420ptoYUV444p();
    virtual bool create(uint32_t width, uint32_t height) override;                                         // 初始化,默认使用彩虹图片
    virtual bool createFromRgb24(const char *rgb24FilePath, uint32_t width, uint32_t height) override;     // 使用本地rgb24文件初始化,然后再转化为yuv420p
    virtual bool createFromYuv420p(const char *yuv420pFilePath, uint32_t width, uint32_t height) override; // 使用本地yuv420p文件初始化
    virtual void yuv420pToYuv444p(const char *yuv444pFilePath) override;                                   // yuv420p转化为yuv444p
    virtual void destory() override;                                                                       // 释放资源

private:
    void yuv420pToYuv444p();                       // yuv420p转化为yuv444p
    void saveYuv444p(const char *yuv444pFilePath); // 保存yuv444p数据到文件
};
#endif