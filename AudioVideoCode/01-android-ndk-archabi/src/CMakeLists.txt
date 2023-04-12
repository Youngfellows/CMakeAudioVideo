# 设置cmake最小版本
cmake_minimum_required(VERSION 3.12.1)

# 设置项目名称
project(library-easyarray)

# 启动对C11标准的支持
set(CMAKE_C_STANDARD 11)

# 显式要求指明支持C标准
set(CMAKE_C_STANDARD_REQUIRED True)

# 查找父目录3rd
message(STATUS "CMAKE_CURRENT_SOURCE_DIR::${CMAKE_CURRENT_SOURCE_DIR}")
get_filename_component(VAR_PARENT ${CMAKE_CURRENT_SOURCE_DIR}/.. ABSOLUTE)
message(STATUS "VAR_PARENT::${VAR_PARENT}")

# 头文件查找目录
set(INCLUDE_PATH ${VAR_PARENT}/include/array)
message(STATUS "include path:${INCLUDE_PATH}")
include_directories(${INCLUDE_PATH})

# 查找源文件列表
aux_source_directory(./array ARRAY_SRC)

message(STATUS "编译动态库:${ARRAY_SRC}")

# 生成动态库
set(EASY_ARRAY_LIB easyarray)
add_library(${EASY_ARRAY_LIB} SHARED ${ARRAY_SRC})

# 安装动态库/头文件到指定目录
message(STATUS "安装动态库:${CMAKE_INSTALL_PREFIX}")
install(TARGETS ${EASY_ARRAY_LIB} DESTINATION lib)
install(DIRECTORY ${INCLUDE_PATH} DESTINATION include)

#[[
install(DIRECTORY ${INCLUDE_PATH}
    DESTINATION include
    FILES_MATCHING PATTERN "*.h"
)
]]