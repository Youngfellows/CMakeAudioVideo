# cmake 支持最小版本
cmake_minimum_required(VERSION 3.14)

# 设置支持语言
#set(CMAKE_C_STANDARD 99)

# 设置项目名称
project(yuv-conversion)

# 查找libyuv
aux_source_directory(../3rd/libyuv/source LIBYUV_SRC)
include_directories(../3rd/libyuv/include)

# 生成可执行文件
add_executable(10-yuv-rotation yuv-rotation.cpp ${LIBYUV_SRC})
add_executable(10-yuv-mirror yuv-mirror.cpp ${LIBYUV_SRC})
add_executable(10-yuv-scale yuv-scale.cpp ${LIBYUV_SRC})
add_executable(10-yuv-clip yuv-clip.cpp ${LIBYUV_SRC})
add_executable(10-yuv-blend yuv-blend.cpp ${LIBYUV_SRC})

# 安装可执行文件到指定路径
install(TARGETS 10-yuv-rotation DESTINATION bin)
install(TARGETS 10-yuv-mirror DESTINATION bin)
install(TARGETS 10-yuv-scale DESTINATION bin)
install(TARGETS 10-yuv-clip DESTINATION bin)
install(TARGETS 10-yuv-blend DESTINATION bin)