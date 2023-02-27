# cmake 最低版本要求,不加入此行会受到警告信息
cmake_minimum_required(VERSION 3.15.0)

# 项目名称为 Sample
project(Sample)
message(STATUS "PROJECT_NAME: ${PROJECT_NAME}")

message(STATUS "============ Cmake命令之include_directories介绍 ============")

#[[
命令格式
    include_directories ([AFTER|BEFORE] [SYSTEM] dir1 [dir2 ...])
将指定目录添加到编译器的头文件搜索路径之下，指定的目录被解释成当前源码路径的相对路径。

命令解析
  默认情况下，include_directories命令会将目录添加到列表最后，可以通过命令设置CMAKE_INCLUDE_DIRECTORIES_BEFORE变量为ON来改变它默认行为，将目录添加到列表前面。也可以在每次调用include_directories命令时使用AFTER或BEFORE选项来指定是添加到列表的前面或者后面。
如果使用SYSTEM选项，会把指定目录当成系统的搜索目录。该命令作用范围只在当前的CMakeLists.txt。
]]
message(STATUS "============= include_directories命令的基本行为 ==============")

# 一、include_directories命令的基本行为：
include_directories(sub)
include_directories(sub2) # 默认将sub2添加到列表最后
include_directories(BEFORE sub3) # 可以临时改变行为，添加到列表最前面

get_property(dirs DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
message(STATUS ">>> include_dirs=${dirs}") # 打印一下目录情况

set(CMAKE_INCLUDE_DIRECTORIES_BEFORE ON) # 改变默认行为，默认添加到列表前面
include_directories(sub4)
include_directories(AFTER sub5) # 可以临时改变行为，添加到列表的最后
get_property(dirs DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
message(STATUS ">>> SET DEFAULT TO BEFORE, include_dirs=${dirs}")

# 场景1：不使用include_directories包含子目录math,直接在main.cpp里面包含"math/MathFunctions.h"。
aux_source_directory(. SRC_LISTS)
aux_source_directory(math MATH_SRC_LISTS)
message(STATUS "SRC_LISTS:${SRC_LISTS}")
message(STATUS "MATH_SRC_LISTS:${MATH_SRC_LISTS}")

add_executable(${PROJECT_NAME} ${SRC_LISTS} ${MATH_SRC_LISTS})