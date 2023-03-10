#ifndef IRAINBOW_H
#define IRAINBOW_H

/**
 * @brief 彩虹抽象类
 *
 */
class IRainbow
{
private:
public:
    virtual ~IRainbow() = default;
    /**
     * @brief 写入彩虹数据:纯虚函数,子类必须实现
     *
     * @param outputFile 文件名
     * @param width 宽
     * @param height 高
     * @return true 写入数据成功
     * @return false 写入数据成功
     */
    virtual bool writeRainbow(const char *outputFile, int width, int height) = 0;

    /**
     * @brief 写入彩虹数据:纯虚函数,子类必须实现
     *
     * @param outputFile 文件名
     * @param width 宽
     * @param height 高
     * @return true 写入数据成功
     * @return false 写入数据成功
     */
    virtual bool writeRainbow2(const char *outputFile, int width, int height) = 0;
};

#endif