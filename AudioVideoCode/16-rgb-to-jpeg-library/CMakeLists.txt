# 设置cmake支持最小版本
cmake_minimum_required(VERSION 3.14)

# 设置项目名称
project(Sample-rgb-to-jpeg-library)

# 设置C语言支持
set(CMAKE_C_STANDARD 99)

# 查找父目录3rd
message(STATUS "CMAKE_CURRENT_SOURCE_DIR::${CMAKE_CURRENT_SOURCE_DIR}")
get_filename_component(VAR_PARENT ${CMAKE_CURRENT_SOURCE_DIR}/.. ABSOLUTE)
message(STATUS "parent dir::${VAR_PARENT}")

# 设置3rd/libjpeg-turbo目录
set(3RD_LIBRARY_DIR ${VAR_PARENT}/3rd/libjpeg-turbo)
message(STATUS "3rd dir::${3RD_LIBRARY_DIR}")

# 添加libjpeg-turbo依赖库
# aux_source_directory(../3rd/libjpeg-turbo LIBJPEG_TURBO_SRC)
# link_directories(../3rd/libjpeg-turbo/build)
# include_directories(../3rd/libjpeg-turbo/build)
# link_directories(../3rd/libjpeg-turbo/install/lib)
# include_directories(../3rd/libjpeg-turbo/install/include)
link_directories(${3RD_LIBRARY_DIR}/install/lib)
include_directories(${3RD_LIBRARY_DIR}/install/include)

# 生成可执行文件
add_executable(16-rgb-to-jpeg-library rgb-to-jpeg-with-libjpeg-turbo.c util.c)

# 方式1,添加链接库
# set(LIB_JPEG_TURBO_PATH ../3rd/libjpeg-turbo/install/lib)
set(LIB_JPEG_TURBO_PATH ${3RD_LIBRARY_DIR}/install/lib)
set(JPEG_TURBO_LIB_NAME libturbojpeg.so)
set(JPEG_LIB_NAME libjpeg.so)
find_library(LIB_JPEG_TURBO ${JPEG_TURBO_LIB_NAME} ${LIB_JPEG_TURBO_PATH})
find_library(LIB_JPEG ${JPEG_LIB_NAME} ${LIB_JPEG_TURBO_PATH})
message(STATUS "libturbojpeg path:${LIB_JPEG_TURBO}")
message(STATUS "libjpeg path:${LIB_JPEG}")

target_link_libraries(16-rgb-to-jpeg-library ${LIB_JPEG} ${LIB_JPEG_TURBO})

# 方式2,添加链接库,必须设置link_directories
# target_link_libraries(16-rgb-to-jpeg-library libturbojpeg.dylib)
# target_link_libraries(16-rgb-to-jpeg-library libturbojpeg.so)

# set(libjpeg_lib_dir ${3RD_LIBRARY_DIR}/install/lib)
# add_library(libjpeg SHARED IMPORTED)
# add_library(libturbojpeg SHARED IMPORTED)
# set_target_properties(libjpeg PROPERTIES IMPORTED_LOCATION ${libjpeg_lib_dir}/libjpeg.so)
# set_target_properties(libturbojpeg PROPERTIES IMPORTED_LOCATION ${libjpeg_lib_dir}/libturbojpeg.so)
# target_link_libraries(16-rgb-to-jpeg-library libjpeg libturbojpeg)

# 安装可执行文件到指定目录
install(TARGETS 16-rgb-to-jpeg-library DESTINATION bin)