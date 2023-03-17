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
set(YUV444P_TO_RGB24_SRC ./src/SampleYUV444pToRGB24.cpp ./src/rgb2yuv/YUV444ptoRGB24.cpp)

# 生成可执行文件
set(SAMPLES) # 可执行文件列表

set(SAMPLE_RGB24_TO_YUV444P SampleRGB24ToYUV444p)
add_executable(${SAMPLE_RGB24_TO_YUV444P} ${RGB24_TO_YUV444P_SRC})
list(APPEND SAMPLES ${SAMPLE_RGB24_TO_YUV444P})

set(SAMPLE_YUV444_TO_RGB24 SampleYUV444pToRGB24)
add_executable(${SAMPLE_YUV444_TO_RGB24} ${YUV444P_TO_RGB24_SRC})
list(APPEND SAMPLES ${SAMPLE_YUV444_TO_RGB24})

# 安装可执行文件到指定目录
message(STATUS "install samples start")

# install(TARGETS ${SAMPLE_RGB24_TO_YUV444P} DESTINATION bin)
foreach(SAMPLE ${SAMPLES})
    message(STATUS "SAMPLE:${SAMPLE}")
    install(TARGETS ${SAMPLE} DESTINATION bin)
endforeach()
