# 设置cmake支持最小版本
cmake_minimum_required(VERSION 3.14)

# 设置项目名称
project(Sample-rgb-to-jpeg-library)

# 设置C语言支持
set(CMAKE_C_STANDARD 99)

# 添加libjpeg-turbo依赖库
# aux_source_directory(../3rd/libjpeg-turbo LIBJPEG_TURBO_SRC)
link_directories(../3rd/libjpeg-turbo/build)
include_directories(../3rd/libjpeg-turbo/build)

# 生成可执行文件
add_executable(16-rgb-to-jpeg-library rgb-to-jpeg-with-libjpeg-turbo.c util.c)

# 添加链接库
target_link_libraries(16-rgb-to-jpeg-library libturbojpeg.dylib)

# 安装可执行文件到指定目录
install(TARGETS 16-rgb-to-jpeg-library DESTINATION bin)