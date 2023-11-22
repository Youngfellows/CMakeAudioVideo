# 设置cmake最小版本
cmake_minimum_required(VERSION 3.14)

# 设置项目名称
project(image-to-gif)

# 设置C语言支持
set(CMAKE_C_STANDARD 99)

# 查找父目录3rd
message(STATUS "CMAKE_CURRENT_SOURCE_DIR::${CMAKE_CURRENT_SOURCE_DIR}")
get_filename_component(VAR_PARENT ${CMAKE_CURRENT_SOURCE_DIR}/.. ABSOLUTE)
message(STATUS "parent dir::${VAR_PARENT}")

# 设置依赖
# set(QDBMP_SRC
# ${CMAKE_SOURCE_DIR}/05-rgb-to-bmp-library/qdbmp/qdbmp.c
# )
# include_directories(${CMAKE_SOURCE_DIR}/05-rgb-to-bmp-library/qdbmp)
set(LIBBMP_SRC
        ${VAR_PARENT}/05-rgb-to-bmp-library/libbmp/libbmp.c
)
include_directories(${VAR_PARENT}/05-rgb-to-bmp-library/libbmp)

aux_source_directory(${VAR_PARENT}/3rd/zlib ZLIB_SRC)
include_directories(${VAR_PARENT}/3rd/zlib)
configure_file(
        ${VAR_PARENT}/3rd/libpng/scripts/pnglibconf.h.prebuilt
        ${VAR_PARENT}/3rd/libpng/pnglibconf.h
        COPYONLY)

aux_source_directory(${VAR_PARENT}/3rd/libpng LIBPNG_SRC)
list(REMOVE_ITEM LIBPNG_SRC "${VAR_PARENT}/3rd/libpng/pngtest.c")
include_directories(${VAR_PARENT}/3rd/libpng)

# link_directories(${VAR_PARENT}/3rd/libjpeg-turbo/build)
# include_directories(${VAR_PARENT}/3rd/libjpeg-turbo/build)

# 设置3rd/libjpeg-turbo目录
set(LIB_JPEG_TURBO_DIR ${VAR_PARENT}/3rd/libjpeg-turbo)
message(STATUS "libjpeg-turbo dir::${LIB_JPEG_TURBO_DIR}")

# 添加libjpeg-turbo依赖库查找路径
# link_directories(../3rd/libjpeg-turbo/install/lib)
link_directories(${LIB_JPEG_TURBO_DIR}/install/lib)

# 添加libjpeg-turb头文件查找路径
# include_directories(../3rd/libjpeg-turbo/install/include)
include_directories(${LIB_JPEG_TURBO_DIR}/install/include)

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
add_executable(20-image-to-gif image-to-gif.c ${LIBBMP_SRC} ${ZLIB_SRC} ${LIBPNG_SRC} ${GIFLIB_SRC})

# 添加math依赖库
find_library(LIB_MATH m) # 使用默认搜索路

# 添加链接库
# target_link_libraries(20-image-to-gif libturbojpeg.dylib)
target_link_libraries(20-image-to-gif libjpeg.a libturbojpeg.a ${LIB_MATH})

# 安装到指定目录
install(TARGETS 20-image-to-gif DESTINATION bin)
