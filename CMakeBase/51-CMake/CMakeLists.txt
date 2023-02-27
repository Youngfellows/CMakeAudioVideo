# cmake 最低版本要求,不加入此行会受到警告信息
cmake_minimum_required(VERSION 3.15.0)

# 项目名称为 Sample
project(Sample)
message("PROJECT_NAME: " ${PROJECT_NAME})
message(STATUS "========= cmake的add_library函数,创建静态库和共享库 =========")

#[[
1、add_library
    add_library(libname [SHARED | STATIC | MODULE] [EXCLUDE_FROM_ALL] SRC_LIST)
    生成动态库或静态库
    SHARED 动态库
    STATIC 静态库
    MODULE 在使用dyld的系统有效,若不支持dyld,等同于SHARED
    EXCLUDE_FROM_ALL 表示该库不会被默认构建
    另外BUILD_SHARED_LIBS也可控制编译成哪种库。
]]
# 2、target_link_libraries用来链接库，用法如下：
# target_link_libraries(<target> [item1 [item2 [...]]] [[debug|optimized|general] <item>] ...)
add_subdirectory(math)
include_directories(math)
aux_source_directory(. SRC_LISTSS)
add_executable(${PROJECT_NAME} ${SRC_LISTSS})
target_link_libraries(${PROJECT_NAME} MathFunctions)
