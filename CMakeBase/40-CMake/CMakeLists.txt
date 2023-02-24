# cmake 最低版本要求,不加入此行会受到警告信息
cmake_minimum_required(VERSION 3.15.0)

# 项目名称为 Sample
project(Sample)
message(STATUS "PROJECT_NAME: ${PROJECT_NAME}")

# 6. 通过特殊变量，查看函数执行情况
# 我们可以在函数定义中，使用特殊变量，用于查看函数执行的情况。CMAKE_CURRENT_FUNCTION 表示函数名，
# CMAKE_CURRENT_FUNCTION_LIST_DIR 表示函数所在 CMakeLists.txt 文件目录，CMAKE_CURRENT_FUNCTION_LIST_FILE 表示函数所在 CMakeLists.txt 文件路径CMAKE_CURRENT_FUNCTION_LIST_LINE 表示函数执行所在行数。
add_subdirectory(math)

function(foo)
    message("CMAKE_CURRENT_FUNCTION ${CMAKE_CURRENT_FUNCTION}")
    message("CMAKE_CURRENT_FUNCTION_LIST_DIR ${CMAKE_CURRENT_FUNCTION_LIST_DIR}")
    message("CMAKE_CURRENT_FUNCTION_LIST_FILE ${CMAKE_CURRENT_FUNCTION_LIST_FILE}")
    message("CMAKE_CURRENT_FUNCTION_LIST_LINE ${CMAKE_CURRENT_FUNCTION_LIST_LINE}")
endfunction()

foo()
bar()

#[[
输出结果为
    CMAKE_CURRENT_FUNCTION foo
    CMAKE_CURRENT_FUNCTION_LIST_DIR /mnt/d/TempCPPCode2023/NDK-CMake/CMakeAudioVideo/CMakeBase/40-CMake
    CMAKE_CURRENT_FUNCTION_LIST_FILE /mnt/d/TempCPPCode2023/NDK-CMake/CMakeAudioVideo/CMakeBase/40-CMake/CMakeLists.txt
    CMAKE_CURRENT_FUNCTION_LIST_LINE 13
    CMAKE_CURRENT_FUNCTION bar
    CMAKE_CURRENT_FUNCTION_LIST_DIR /mnt/d/TempCPPCode2023/NDK-CMake/CMakeAudioVideo/CMakeBase/40-CMake/math
    CMAKE_CURRENT_FUNCTION_LIST_FILE /mnt/d/TempCPPCode2023/NDK-CMake/CMakeAudioVideo/CMakeBase/40-CMake/math/CMakeLists.txt
    CMAKE_CURRENT_FUNCTION_LIST_LINE 7
]]