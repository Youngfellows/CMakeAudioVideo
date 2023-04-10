# 设置cmake支持最小版本
cmake_minimum_required(VERSION 3.14)

# 设置项目名称
project(Sample-rgb-to-jpeg-library)

# 设置C语言支持
set(CMAKE_C_STANDARD 99)

# 添加libjpeg-turbo依赖库
# aux_source_directory(../3rd/libjpeg-turbo LIBJPEG_TURBO_SRC)
# link_directories(../3rd/libjpeg-turbo/build)
# include_directories(../3rd/libjpeg-turbo/build)
link_directories(../3rd/libjpeg-turbo/install/lib)
include_directories(../3rd/libjpeg-turbo/install/include)

# 生成可执行文件
add_executable(16-rgb-to-jpeg-library rgb-to-jpeg-with-libjpeg-turbo.c util.c)

# 方式1,添加链接库
set(LIB_JPEG_TURBO_PATH ../3rd/libjpeg-turbo/install/lib)
set(JPEG_TURBO_LIB_NAME libturbojpeg.so)
find_library(LIB_TURBO_JPEG ${JPEG_TURBO_LIB_NAME} ${LIB_JPEG_TURBO_PATH})
message(STATUS "libturbojpeg.so path:${LIB_TURBO_JPEG}")

# target_link_libraries(16-rgb-to-jpeg-library ${LIB_TURBO_JPEG})

# 方式2,添加链接库,必须设置link_directories
# target_link_libraries(16-rgb-to-jpeg-library libturbojpeg.dylib)
target_link_libraries(16-rgb-to-jpeg-library libturbojpeg.so)

# 安装可执行文件到指定目录
install(TARGETS 16-rgb-to-jpeg-library DESTINATION bin)