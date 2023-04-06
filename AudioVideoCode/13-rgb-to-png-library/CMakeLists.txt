# 设置cmake支持最小版本
cmake_minimum_required(VERSION 3.20)

# 设置项目名称
project(SampleRgbToPngLibrary)

# 设置C语言支持
set(CMAKE_C_STANDARD 99)

# 1.设置第三方库svpng相关依赖
include_directories(../3rd/svpng)

# 生成可执行文件
add_executable(13-rgb-to-png-with-svpng rgb-to-png-with-svpng.c)

# 2.设置第三方库libattopng相关依赖
set(LIBATTOPNG_SRC ../3rd/libattopng/libattopng.c)
include_directories(../3rd/libattopng)

# 生成可执行文件
add_executable(13-rgb-to-png-with-libattopng rgb-to-png-with-libattopng.c ${LIBATTOPNG_SRC})

# 查找父目录3rd
message(STATUS "CMAKE_CURRENT_SOURCE_DIR::${CMAKE_CURRENT_SOURCE_DIR}")
get_filename_component(VAR_PARENT ${CMAKE_CURRENT_SOURCE_DIR}/.. ABSOLUTE)
message(STATUS "VAR_PARENT::${VAR_PARENT}")

# 设置3rd目录
set(3RD_LIBRARY_DIR ${VAR_PARENT}/3rd)
message(STATUS "3RD_LIBRARY_DIR::${3RD_LIBRARY_DIR}")

# 3.设置第三方库lodepng相关依赖
aux_source_directory(../3rd/lodepng LODEPNG_SRC)
list(REMOVE_ITEM LODEPNG_SRC "../3rd/lodepng/lodepng_benchmark.cpp")

# lodepng Demo (lodepng.cpp rename to lodepng.c)
#[[
file(COPY ${CMAKE_SOURCE_DIR}/3rd/lodepng/lodepng.cpp
        DESTINATION ${CMAKE_SOURCE_DIR}/3rd/lodepng/)
]]
# configure_file(${CMAKE_SOURCE_DIR}/3rd/lodepng/lodepng.cpp ${CMAKE_SOURCE_DIR}/3rd/lodepng/lodepng.c COPYONLY)
# configure_file(../3rd/lodepng/lodepng.cpp ../../3rd/lodepng/lodepng.c COPYONLY)
configure_file(${VAR_PARENT}/3rd/lodepng/lodepng.cpp ${VAR_PARENT}/3rd/lodepng/lodepng.c COPYONLY)

set(LODEPNG_SRC ../3rd/lodepng/lodepng.c)
include_directories(../3rd/lodepng)

# 生成可执行文件
add_executable(13-rgb-to-png-with-lodepng rgb-to-png-with-lodepng.c ${LODEPNG_SRC})

# 4.设置第三方库libpng，zlib相关依赖
aux_source_directory(../3rd/zlib ZLIB_SRC)

#[[ configure_file(
         ${CMAKE_SOURCE_DIR}/3rd/libpng/scripts/pnglibconf.h.prebuilt
         ${CMAKE_SOURCE_DIR}/3rd/libpng/pnglibconf.h
         COPYONLY)
]]
# configure_file(../3rd/libpng/scripts/pnglibconf.h.prebuilt ../3rd/libpng/pnglibconf.h COPYONLY)
configure_file(${VAR_PARENT}/3rd/libpng/scripts/pnglibconf.h.prebuilt ${VAR_PARENT}/3rd/libpng/pnglibconf.h COPYONLY)
aux_source_directory(../3rd/libpng LIBPNG_SRC)
list(REMOVE_ITEM LIBPNG_SRC "../3rd/libpng/pngtest.c")
include_directories(../3rd/libpng)
include_directories(../3rd/zlib)

# 生成可执行文件
# add_executable(13-rgb-to-png-with-libpng rgb-to-png-with-libpng.c ${ZLIB_SRC} ${LIBPNG_SRC})

# 安装可执行文件到指定目录
install(TARGETS 13-rgb-to-png-with-svpng DESTINATION bin)
install(TARGETS 13-rgb-to-png-with-libattopng DESTINATION bin)
install(TARGETS 13-rgb-to-png-with-lodepng DESTINATION bin)
# install(TARGETS 13-rgb-to-png-with-libpng DESTINATION bin)