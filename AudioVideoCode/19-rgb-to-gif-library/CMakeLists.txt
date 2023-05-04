# 设置cmake依赖最小版本
cmake_minimum_required(VERSION 3.14)

# 设置项目名称
project(gif-to-rgb)

# 设置C语言支持
set(CMAKE_C_STANDARD 99)

# 设置依赖源码
#[[
set(GIFLIB_SRC
        ${CMAKE_SOURCE_DIR}/3rd/giflib/dgif_lib.c
        ${CMAKE_SOURCE_DIR}/3rd/giflib/egif_lib.c
        ${CMAKE_SOURCE_DIR}/3rd/giflib/getarg.c
        ${CMAKE_SOURCE_DIR}/3rd/giflib/gif_err.c
        ${CMAKE_SOURCE_DIR}/3rd/giflib/gif_font.c
        ${CMAKE_SOURCE_DIR}/3rd/giflib/gif_hash.c
        ${CMAKE_SOURCE_DIR}/3rd/giflib/gif_lib.h
        ${CMAKE_SOURCE_DIR}/3rd/giflib/gifalloc.c
        ${CMAKE_SOURCE_DIR}/3rd/giflib/openbsd-reallocarray.c
        ${CMAKE_SOURCE_DIR}/3rd/giflib/qprintf.c
        ${CMAKE_SOURCE_DIR}/3rd/giflib/quantize.c
)
include_directories(${CMAKE_SOURCE_DIR}/3rd/giflib)
]]

# 查找父目录3rd
message(STATUS "CMAKE_CURRENT_SOURCE_DIR::${CMAKE_CURRENT_SOURCE_DIR}")
get_filename_component(VAR_PARENT ${CMAKE_CURRENT_SOURCE_DIR}/.. ABSOLUTE)
message(STATUS "parent dir::${VAR_PARENT}")

# 设置3rd/libjpeg-turbo目录
set(3RD_LIBRARY_DIR ${VAR_PARENT}/3rd/giflib)
message(STATUS "3rd dir::${3RD_LIBRARY_DIR}")

# 设置依赖源码
set(GIFLIB_SRC
        ${VAR_PARENT}/3rd/giflib/dgif_lib.c
        ${VAR_PARENT}/3rd/giflib/egif_lib.c
        ${VAR_PARENT}/3rd/giflib/getarg.c
        ${VAR_PARENT}/3rd/giflib/gif_err.c
        ${VAR_PARENT}/3rd/giflib/gif_font.c
        ${VAR_PARENT}/3rd/giflib/gif_hash.c
        ${VAR_PARENT}/3rd/giflib/gif_lib.h
        ${VAR_PARENT}/3rd/giflib/gifalloc.c
        ${VAR_PARENT}/3rd/giflib/openbsd-reallocarray.c
        ${VAR_PARENT}/3rd/giflib/qprintf.c
        ${VAR_PARENT}/3rd/giflib/quantize.c
)
include_directories(${VAR_PARENT}/3rd/giflib)

# 生成可执行文件
add_executable(19-gif-to-rgb-library gif-to-rgb-library.c ${GIFLIB_SRC})
add_executable(19-rgb-to-gif-library rgb-to-gif-library.c ${GIFLIB_SRC})

# 安装到指定目录
install(TARGETS 19-gif-to-rgb-library DESTINATION bin)
install(TARGETS 19-rgb-to-gif-library DESTINATION bin)