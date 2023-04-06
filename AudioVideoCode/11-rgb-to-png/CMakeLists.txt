# cmake支持最小版本
cmake_minimum_required(VERSION 3.14)

# 设置项目名称
project(SampleRgbToPng)

# 设置C语言支持
set(CMAKE_C_STANDARD 99)

# 设置zlib库依赖
aux_source_directory(../3rd/zlib ZLIB_SRC)
include_directories(../3rd/zlib)

# 生成可执行文件
add_executable(11-rgb-to-indexed-color-png rgb-to-indexed-color-png.c util.c ${ZLIB_SRC})
add_executable(11-rgb-to-true-color-png rgb-to-true-color-png.c util.c ${ZLIB_SRC})

# 安装可执行文件到指定目录
install(TARGETS 11-rgb-to-indexed-color-png DESTINATION bin)
install(TARGETS 11-rgb-to-true-color-png DESTINATION bin)