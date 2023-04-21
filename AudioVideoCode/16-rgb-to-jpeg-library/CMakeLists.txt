# 设置cmake支持最小版本
cmake_minimum_required(VERSION 3.14)

# 设置项目名称
project(Sample-rgb-to-jpeg-library)

# 启动对C11标准的支持
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 14)

# 显式要求指明支持C/C++标准
set(CMAKE_C_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# 全部可执行文件的名称列表
set(SAMPLES)

# 查找父目录3rd
message(STATUS "CMAKE_CURRENT_SOURCE_DIR::${CMAKE_CURRENT_SOURCE_DIR}")
get_filename_component(VAR_PARENT ${CMAKE_CURRENT_SOURCE_DIR}/.. ABSOLUTE)
message(STATUS "parent dir::${VAR_PARENT}")

# 设置3rd/libjpeg-turbo目录
set(3RD_LIBRARY_DIR ${VAR_PARENT}/3rd/libjpeg-turbo)
message(STATUS "3rd dir::${3RD_LIBRARY_DIR}")

# 添加libjpeg-turbo依赖库查找路径
# link_directories(../3rd/libjpeg-turbo/install/lib)
link_directories(${3RD_LIBRARY_DIR}/install/lib)

# 添加libjpeg-turb头文件查找路径
# include_directories(../3rd/libjpeg-turbo/install/include)
include_directories(${3RD_LIBRARY_DIR}/install/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/include)

# 生成可执行文件
add_executable(16-rgb-to-jpeg-library rgb-to-jpeg-with-libjpeg-turbo.c ./src/util.c)

# 方式1,添加链接库,OK
# set(LIB_JPEG_TURBO_PATH ../3rd/libjpeg-turbo/install/lib)
#[[
set(LIB_JPEG_TURBO_PATH ${3RD_LIBRARY_DIR}/install/lib)
set(JPEG_TURBO_LIB_NAME libturbojpeg.a)
set(JPEG_LIB_NAME libjpeg.a)
find_library(LIB_JPEG_TURBO ${JPEG_TURBO_LIB_NAME} ${LIB_JPEG_TURBO_PATH})
find_library(LIB_JPEG ${JPEG_LIB_NAME} ${LIB_JPEG_TURBO_PATH})
message(STATUS "libturbojpeg path:${LIB_JPEG_TURBO}")
message(STATUS "libjpeg path:${LIB_JPEG}")
target_link_libraries(16-rgb-to-jpeg-library ${LIB_JPEG} ${LIB_JPEG_TURBO})
]]

# 方式2,添加链接库,必须设置link_directories,OK
target_link_libraries(16-rgb-to-jpeg-library libjpeg.a libturbojpeg.a)

# 方式3,添加链接库,OK
#[[
set(libjpeg_lib_dir ${3RD_LIBRARY_DIR}/install/lib)
set(LIB_JPEG libjpeg)
set(LIB_TURBO_JPEG libturbojpeg)
add_library(${LIB_JPEG} STATIC IMPORTED)
add_library(${LIB_TURBO_JPEG} STATIC IMPORTED)
set_target_properties(${LIB_JPEG} PROPERTIES IMPORTED_LOCATION ${libjpeg_lib_dir}/libjpeg.a)
set_target_properties(${LIB_TURBO_JPEG} PROPERTIES IMPORTED_LOCATION ${libjpeg_lib_dir}/libturbojpeg.a)
target_link_libraries(16-rgb-to-jpeg-library ${LIB_JPEG} ${LIB_TURBO_JPEG})
]]

# 添加各个sample可执行文件
set(DECODE_JPEG_SRC "./src/jpeg/decode-jpeg.c" "./src/sample-decode-jpeg.c")
message(STATUS "DECODE_JPEG_SRC:${DECODE_JPEG_SRC}")
add_executable(sample-decode-jpeg ${DECODE_JPEG_SRC})
target_link_libraries(sample-decode-jpeg libjpeg.a libturbojpeg.a)

set(ENCODE_JPEG_SRC "./src/jpeg/encode-jpeg.c" "./src/sample-encode-jpeg.c" "./src/util.c")
message(STATUS "ENCODE_JPEG_SRC:${ENCODE_JPEG_SRC}")
add_executable(sample-encode-jpeg ${ENCODE_JPEG_SRC})
target_link_libraries(sample-encode-jpeg libjpeg.a libturbojpeg.a)

set(ENCODE_2_JPEG_SRC "./src/jpeg/encode-jpeg.c" "./src/sample-encode2-jpeg.c" "./src/util.c")
message(STATUS "ENCODE_2_JPEG_SRC:${ENCODE_2_JPEG_SRC}")
add_executable(sample-encode2-jpeg ${ENCODE_2_JPEG_SRC})
target_link_libraries(sample-encode2-jpeg libjpeg.a libturbojpeg.a)

set(ENCODE_3_JPEG_SRC "./src/jpeg/decode-jpeg.c;\
./src/jpeg/encode-jpeg.c;\
./src/sample-encode3-jpeg.c;\
./src/util.c")
message(STATUS "ENCODE_3_JPEG_SRC:${ENCODE_3_JPEG_SRC}")
add_executable(sample-encode3-jpeg ${ENCODE_3_JPEG_SRC})
target_link_libraries(sample-encode3-jpeg libjpeg.a libturbojpeg.a)

set(JPEG2YUV_SRC "./src/jpeg/jpeg2yuv.c;\
./src/sample-jpeg2yuv.c;\
./src/util.c")
message(STATUS "JPEG2YUV_SRC:${JPEG2YUV_SRC}")
add_executable(sample-jpeg2yuv ${JPEG2YUV_SRC})
target_link_libraries(sample-jpeg2yuv libjpeg.a libturbojpeg.a)

set(YUV2JPEG_SRC "./src/jpeg/yuv2jpeg.c;\
./src/sample-yuv2jpeg.c;\
./src/util.c")
message(STATUS "YUV2JPEG_SRC:${YUV2JPEG_SRC}")
add_executable(sample-yuv2jpeg ${YUV2JPEG_SRC})
target_link_libraries(sample-yuv2jpeg libjpeg.a libturbojpeg.a)

set(TEST_LIB_JPEG_TURBO_SRC "./src/Libjpeg-turbo-Test.cpp;\
./src/jpeg/funset.cpp")
message(STATUS "TEST_LIB_JPEG_TURBO_SRC:${TEST_LIB_JPEG_TURBO_SRC}")
add_executable(sample-jpeg-turbo ${TEST_LIB_JPEG_TURBO_SRC})
target_link_libraries(sample-jpeg-turbo libjpeg.a libturbojpeg.a)

# 添加可执行文件到列表
# list(APPEND SAMPLES 16-rgb-to-jpeg-library)
list(APPEND SAMPLES sample-decode-jpeg)
list(APPEND SAMPLES sample-encode-jpeg)
list(APPEND SAMPLES sample-encode2-jpeg)
list(APPEND SAMPLES sample-encode3-jpeg)
list(APPEND SAMPLES sample-jpeg2yuv)
list(APPEND SAMPLES sample-yuv2jpeg)
list(APPEND SAMPLES sample-jpeg-turbo)

# 安装可执行文件到指定目录
# install(TARGETS 16-rgb-to-jpeg-library DESTINATION bin)
foreach(SAMPLE ${SAMPLES})
    install(TARGETS ${SAMPLE} DESTINATION bin)
    message(STATUS "install ${SAMPLE} success ...")
endforeach()