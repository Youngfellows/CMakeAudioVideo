# cmake 最低版本要求,不加入此行会受到警告信息
cmake_minimum_required(VERSION 3.15.0)

# 项目名称为 Sample
project(Sample)
message(STATUS "PROJECT_NAME: ${PROJECT_NAME}")

message(STATUS "=============== Cmake命令之set介绍 ========================")

#[[
设置缓存条目
  命令格式：set(<variable> <value>... CACHE <type> <docstring> [FORCE])
  命令含义：将缓存条目variable设置为值<value>...，除非用户进行设置或使用了选项FORCE，默认情况下缓存条目的值不会被覆盖。
缓存条目可以通过CMAKE的GUI界面的add entry按钮来增加。缓存条目的实质为可以跨层级进行传递的变量，类似于全局变量。
  
缓存条目的<type>主要有以下几类：
    BOOL：布尔值ON/OFF,CMAKE的GUI界面对此类缓存条目会提供一个复选框。
    FILEPATH：文件路径，CMAKE的GUI界面对此类缓存条目会提供一个文件选择框。
    PATH：目录路径，CMAKE的GUI界面对此类缓存条目会提供一个目录选择框。
    STRING / STRINGS：文本行，CMAKE的GUI界面对此类缓存条目会提供一个文本框（对应STRING）或下拉选择框（对应STRINGS）。
    INTERNAL：文本行，但是只用于内部，不对外呈现。主要用于运行过程中存储变量，因此使用该type意味着使用FORCE。

缓存条目的几个注意事项：
    1）如果变量先前未定义或者使用了FORCE选项，则缓存条目会直接被赋值。
    2）可以在使用cmake构建的使用通过-D选项来给缓存条目赋值，这样CMakeLists.txt内的set命令只会为缓存条目添加类型。
    3）如果变量类型是目录或者文件路径，通过-D选项传入的若只是相对路径，那么set会给这个相对路径前添加当前的工作目录以变成绝对路径（如果已经是绝对路径则不会处理）。
]]
set(cache_entry_val ON OFF CACHE BOOL "choose ON to enable")
message(STATUS ">>> value = ${cache_entry_val}")

set(cache_entry_val2 ON CACHE BOOL "choose ON to enable" FORCE)
message(STATUS ">>> value2 = ${cache_entry_val2}")

set(cache_entry_val3 ON)
set(cache_entry_val3 OFF CACHE BOOL "choose ON to enable")
message(STATUS ">>> value3 = ${cache_entry_val3}")

set(cache_entry_input OFF CACHE BOOL "choose ON to enable")
message(">>> value4 = ${cache_entry_input}")

set(mypath "test" CACHE FILEPATH "choose a file path")
message(STATUS ">>> value5 = ${mypath}")
