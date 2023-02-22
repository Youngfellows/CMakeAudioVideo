# cmake 最低版本要求,不加入此行会受到警告信息
cmake_minimum_required(VERSION 3.15.0)

# 项目名称为 Sample
project(Sample)
message(STATUS "PROJECT_NAME: ${PROJECT_NAME}")

message(STATUS "=========== CMake 路径操作 =============")
message(STATUS "============ 获取完整文件名路径的特定部分 =============")

#[[
1.get_filename_component 形式一
  获取完整文件名路径的特定部分。
    get_filename_component(<var> <FileName> <mode> [CACHE])
    
    文件名 <FileName> 根据处理模式 <mode>，结果保存到 <var> 中。
    <mode> 表示处理模式，是以下值之一:
        PATH      = Legacy alias for DIRECTORY (use for CMake <= 2.8.11)
        DIRECTORY = Directory without file name
        NAME      = File name without directory
        EXT       = File name longest extension (.b.c from d/a.b.c)
        NAME_WE   = File name with neither the directory nor the longest extension
        LAST_EXT  = File name last extension (.c from d/a.b.c)
        NAME_WLE  = File name with neither the directory nor the last extension

    PATH 和 DIRECTORY 表示文件路径名，PATH 是历史遗留。
    NAME 表示文件名。
    EXT 表示最长扩展名，NAME_WE 表示最短文件名
    LAST_EXT 表示最短扩展名，NAME_WLE 表示最长文件名
    CACHE 参数，则结果变量添加到缓存中。
]]

# 案例，获取完整文件名路径的特定部分。
function(getFileInfo fileName)
    message(STATUS "FileName:${fileName}")
    get_filename_component(path ${fileName} PATH)
    message(STATUS "PATH:${path}")
    get_filename_component(directory ${fileName} DIRECTORY)
    message(STATUS "DIRECTORY:${directory}")
    get_filename_component(name ${fileName} NAME)
    message(STATUS "NAME:${name}")
    get_filename_component(ext ${fileName} EXT)
    message(STATUS "EXT:${ext}")
    get_filename_component(nameWe ${fileName} NAME_WE)
    message(STATUS "NAME_WE:${nameWe}")
    get_filename_component(lastExt ${fileName} LAST_EXT)
    message(STATUS "LAST_EXT:${lastExt}")
    get_filename_component(nameWle ${fileName} NAME_WLE)
    message(STATUS "NAME_WLE:${nameWle}")
endfunction()

message(STATUS "================ 获取完整文件名路径的特定部分 ====================")

set(fileName "C:\\Windows\\System32\\drivers\\etc\\lmhosts.sam")
getFileInfo(${fileName})

message(STATUS "----------------------------------")
set(fileName "C:\\Windows\\System32\\drivers\\etc\\hosts")
getFileInfo(${fileName})

message(STATUS "----------------------------------")
set(fileName "C:\\Windows\\System32\\Windows.UI.dll")
getFileInfo(${fileName})

message(STATUS "========== 获取相对路径的绝对路径 =========")

#[[
2.get_filename_component 形式二
  获取相对路径的绝对路径。
    get_filename_component(<var> <FileName> <mode> [BASE_DIR <dir>] [CACHE])

    获取文件 <FileName> 的绝对路径，结果保存到 <var> 中。
    <mode> 是以下值之一:
        ABSOLUTE  = Full path to file
        REALPATH  = Full path to existing file with symlinks resolved

    ABSOLUTE 表示绝对路径，REALPATH 表示已存在的符号链接。
    如果提供文件路径 <FileName> 是相对路径，则它相对于给定的基本目录 <dir> 进行评估，基本目录默认值为 CMAKE_CURRENT_SOURCE_DIR。
    CACHE 参数，则结果变量添加到缓存中。
]]
# 案例，将相对路径转换为绝对路径
get_filename_component(absolute "Windows.UI.dll" ABSOLUTE)
message(STATUS "ABSOLUTE:${absolute}")

get_filename_component(absolute "Windows.UI.dll" ABSOLUTE BASE_DIR "C:\\Windows\\System32")
message(STATUS "ABSOLUTE_BASE_DIR:${absolute}")

message(STATUS "=========== 获取程序的路径 =============")

#[[
3.get_filename_component 形式三
  获取程序的路径
    get_filename_component(<var> <FileName> PROGRAM [PROGRAM_ARGS <arg_var>] [CACHE])

  如果给定 <FileName> 仅为程序名，在系统中搜索并获取完整的程序路径，结果保存到 <var> 中。
  如果给定 <FileName> 包括程序名和参数，<var> 保存程序路径，<arg_var> 保存程序参数。
  CACHE 参数，则结果变量添加到缓存中。
]]
# 案例，获取程序的路径
get_filename_component(programPath "shutdown" PROGRAM)
message(STATUS "PROGRAM:${programPath}")
get_filename_component(programPath "shutdown -s -t" PROGRAM PROGRAM_ARGS programArgs)
message(STATUS "PROGRAM:${programPath},PROGRAM_ARGS:${programArgs}")

#[[
REALPATH 和 PROGRAM 子命令已分别被 file(REAL_PATH) 和 separate_arguments(PROGRAM) 命令取代
https://cmake.org/cmake/help/v3.19/command/file.html#real-path
https://cmake.org/cmake/help/v3.19/command/separate_arguments.html
]]
message(STATUS "============ 判断文件是否存在 =============")

# 案例: 判断文件是否存在
# set(fileName "CMakeLists.txt")
set(fileName CMakeLists.txt)
get_filename_component(fileName ${fileName} ABSOLUTE)
message(STATUS "PATH:${fileName}")

if(EXISTS ${fileName})
    message(STATUS "文件存在:${fileName}")
else()
    message(STATUS "文件不存在:${fileName}")
endif()

set(fileName test2222.txt)
get_filename_component(fileName ${fileName} ABSOLUTE)
message(STATUS "PATH:${fileName}")

if(EXISTS ${fileName})
    message(STATUS "文件存在:${fileName}")
else()
    message(STATUS "文件不存在:${fileName}")
endif()