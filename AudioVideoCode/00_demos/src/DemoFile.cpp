#include <iostream>
#include <cstring>

using namespace std;

/**
 * @brief 函数声明:  读取PPM图片文件
 *
 * @param filename 文件名
 * @param width 宽
 * @param height 高
 * @param RGB 返回读取到数据
 * @return int
 */
int readPPM(const char *filename, uint32_t *width, uint32_t *height, uint8_t **RGB);

/**
 * @brief 格式化读取二进制文件
 *
 * @param filename
 * @return int
 */
int formatReadBinary(const char *filename);

int main(int arg, char **argv)
{
    const char *TAG = "DemoFile::";
    std::cout << TAG << __FUNCTION__ << "():: Line " << __LINE__ << std::endl;
    const char *rgb24FilePath = "./resource/test1.ppm";
    uint32_t width;
    uint32_t heigth;
    uint8_t *RGB;
    int errNum = readPPM(rgb24FilePath, &width, &heigth, &RGB); // 读取PPM图片文件
    std::cout << TAG << __FUNCTION__ << "():: Line " << __LINE__ << ",errNum:" << errNum << std::endl;
    if (!errNum)
    {
        std::cout << TAG << __FUNCTION__ << "():: Line " << __LINE__ << ",读取PPM文件成功,errNum:" << errNum << std::endl;
        std::cout << TAG << __FUNCTION__ << "():: Line " << __LINE__ << ",width:" << width << std::endl;
        std::cout << TAG << __FUNCTION__ << "():: Line " << __LINE__ << ",heigth:" << heigth << std::endl;
    }
    else
    {
        std::cout << TAG << __FUNCTION__ << "():: Line " << __LINE__ << ",读取PPM文件错误,errNum:" << errNum << std::endl;
    }

    const char *dataFilePath = "./resource/data.txt";
    errNum = formatReadBinary(dataFilePath); // 格式化读取二进制文件
    return 0;
}

/**
 * @brief 读取PPM图片文件
 *
 * @param filename 文件名
 * @param width 宽
 * @param height 高
 * @param RGB 返回读取到数据
 * @return int
 */
int readPPM(const char *filename, uint32_t *width, uint32_t *height, uint8_t **RGB)
{
    const char *TAG = "DemoFile::";

    FILE *fp = fopen(filename, "rb"); // 打开文件
    if (!fp)
    {
        perror("Error opening rgb image for read");
        return 1;
    }

    char magic[3];
    size_t result = fread(magic, 1, 2, fp); // 读取前2个字节，获取标准位是否为P6
    printf("%s%s():: Line %d,result:%ld\n", TAG, __FUNCTION__, __LINE__, result);
    magic[2] = '\0';
    printf("%s%s():: Line %d,magic:%s\n", TAG, __FUNCTION__, __LINE__, magic);
    if (result != 2 || strcmp(magic, "P6") != 0)
    {
        perror("Error reading rgb image header, or invalid format");
        fclose(fp);
        return 3;
    }
    // 格式化读取width/heigth/max等,每一个数是4个字节,一共读取12个字节
    uint32_t max;
    result = fscanf(fp, " %u %u %u ", width, height, &max);
    printf("%s%s():: Line %d,width:%d,heigth:%d,max:%d\n", TAG, __FUNCTION__, __LINE__, *width, *height, max);
    if (result != 3 || max > 255)
    {
        perror("Error reading rgb image header, or invalid values");
        fclose(fp);
        return 3;
    }

    size_t size = 3 * (*width) * (*height);
    printf("%s%s():: Line %d,size:%ld\n", TAG, __FUNCTION__, __LINE__, size);
    *RGB = (uint8_t *)malloc(size); // 申请内存空间
    if (!*RGB)
    {
        perror("Error allocating rgb image memory");
        fclose(fp);
        return 2;
    }

    result = fread(*RGB, 1, size, fp);
    printf("%s%s():: Line %d,result:%ld\n", TAG, __FUNCTION__, __LINE__, result); // 读取剩下的size个字节数据并存入RGB内存中
    if (result != size)
    {
        perror("Error reading rgb image");
        fclose(fp);
        return 3;
    }
    fclose(fp);
    return 0;
}

/**
 * @brief 格式化读取二进制文件
 *
 * @param filename
 * @return int
 */
int formatReadBinary(const char *filename)
{
    const char *TAG = "DemoFile::";
    printf("%s%s():: Line %d\n", TAG, __FUNCTION__, __LINE__);
    long dev;
    long offset;
    long length;
    char ch;
    double ts = 0.000000;
    FILE *fp = fopen(filename, "rb"); // 打开文件
    if (!fp)
    {
        printf("open the file is error!\n");
        return 1;
    }
    fseek(fp, 7, SEEK_SET); // 一定文件指针到第7个字节
    int result = fscanf(fp, "%ld,%ld,#%ld,%c,%lf\n", &dev, &offset, &length, &ch, &ts);
    if (result == 5)
    {
        // 在这里就是第二个參数指定分隔參数的格式，在这里使用的是，来分隔。
        // 这样就非常easy的获取了记录的各个字段的值并不须要自己编写函数来进行解析什么的。
        printf("%s%s():: Line %d,%ld,%ld,%ld,%c,%lf\n", TAG, __FUNCTION__, __LINE__, dev, offset, length, ch, ts);
    }
    else
    {
        printf("%s\n", "格式读取文件错误");
        return 2;
    }

    fseek(fp, 7, SEEK_CUR); // 一定文件指针到第7个字节
    result = fscanf(fp, "%ld,%ld,#%ld,%c,%lf\n", &dev, &offset, &length, &ch, &ts);
    if (result == 5)
    {
        // 在这里就是第二个參数指定分隔參数的格式，在这里使用的是，来分隔。
        // 这样就非常easy的获取了记录的各个字段的值并不须要自己编写函数来进行解析什么的。
        printf("%s%s():: Line %d,%ld,%ld,%ld,%c,%lf\n", TAG, __FUNCTION__, __LINE__, dev, offset, length, ch, ts);
    }
    else
    {
        printf("%s%s():: Line %d,%s\n", TAG, __FUNCTION__, __LINE__, "格式读取文件错误");
        return 3;
    }
    fclose(fp); // 关闭文件
    return 0;
}