# cmake 最低版本要求,不加入此行会受到警告信息
cmake_minimum_required(VERSION 3.15.0)

message(STATUS "==== add_library使用 $＜TARGET_OBJECTS:name＞ ====")

# Cmake分别生成静态链接库，OBJ链接库，并使用$<TARGET_OBJECTS:name>引用obj文件

# project name and language
project(Sample LANGUAGES CXX)

# generate an object library from sources
add_library(message-objs
    OBJECT
    Message.hpp
    Message.cpp
)

# message(STATUS "message-objs:${message-objs}")

# 开启(PIC) 编译动态库
set_target_properties(message-objs
    PROPERTIES
    POSITION_INDEPENDENT_CODE True
)

# message(STATUS $<TARGET_OBJECTS:message-objs>)

add_library(message-shared
    SHARED
    $<TARGET_OBJECTS:message-objs>
)

set_target_properties(message-shared
    PROPERTIES
    OUTPUT_NAME "message"
)

add_library(message-static
    STATIC
    $<TARGET_OBJECTS:message-objs>
)

set_target_properties(message-static
    PROPERTIES
    OUTPUT_NAME "message"
)

# message(STATUS $<TARGET_OBJECTS:message-objs>)

add_executable(${PROJECT_NAME} hello-world.cpp)

target_link_libraries(${PROJECT_NAME} message-static)