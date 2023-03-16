# 设置cmake最新版本
cmake_minimum_required(VERSION 3.15.0)

# 设置项目名称
project(SampleRGB2YUV)

# 设置包含头文件目录
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/rgb2yuv)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/rgb2yuv/interfaces)

# 获取源码
set(RGB24_TO_YUV444P_SRC ./src/SampleRGB24ToYUV444p.cpp ./src/rgb2yuv/RGB24ToYUV444p.cpp)

# 生成可执行文件
set(SAMPLE_RGB24_TO_YUV444P SampleRGB24ToYUV444p)
add_executable(${SAMPLE_RGB24_TO_YUV444P} ${RGB24_TO_YUV444P_SRC})

# 安装可执行文件到指定目录
install(TARGETS ${SAMPLE_RGB24_TO_YUV444P} DESTINATION bin)
