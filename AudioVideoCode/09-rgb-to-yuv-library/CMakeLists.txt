cmake_minimum_required(VERSION 3.14)
project(rgb-to-bmp)

# set(CMAKE_C_STANDARD 99)
aux_source_directory(../3rd/libyuv/source LIBYUV_SRC)
include_directories(../3rd/libyuv/include)

# aux_source_directory(../3rd/descampsa/yuv2rgb YUV2RGB)
set(YUV2RGB ../3rd/descampsa/yuv2rgb/yuv_rgb.c)
include_directories(../3rd/descampsa/yuv2rgb)

add_executable(09-rgb-to-yuv-with-libyuv rgb-to-yuv-with-libyuv.cpp ${LIBYUV_SRC})
add_executable(09-yuv-to-rgb-with-libyuv yuv-to-rgb-with-libyuv.cpp ${LIBYUV_SRC})

add_executable(09-rgb-to-yuv-with-descampsa rgb-to-yuv-with-descampsa-yuv2rgb.c ${YUV2RGB})
add_executable(09-yuv-to-rgb-with-descampsa yuv-to-rgb-with-descampsa-yuv2rgb.c ${YUV2RGB})

# 安装可执行文件到指定目录
install(TARGETS 09-rgb-to-yuv-with-libyuv DESTINATION bin)
install(TARGETS 09-yuv-to-rgb-with-libyuv DESTINATION bin)
install(TARGETS 09-rgb-to-yuv-with-descampsa DESTINATION bin)
install(TARGETS 09-yuv-to-rgb-with-descampsa DESTINATION bin)