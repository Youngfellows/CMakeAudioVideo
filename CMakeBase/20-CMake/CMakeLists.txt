# cmake 最低版本要求,不加入此行会受到警告信息
cmake_minimum_required(VERSION 3.15.0)

# 项目名称为 Sample
project(Sample)
message(STATUS "PROJECT_NAME:  ${PROJECT_NAME}")

#[[
1.文件操作
    文件的操作，CMake官方文档中都要求使用全路径，if判断的结果才是有明确定义的，相对路径可能无法识别（例如~不会解析成home目录）。
]]

# if(EXISTS path-to-file-or-directory)：判断文件或目录是否存在。

#[[
    # 先来创建一些文件和软连接
    touch /tmp/testfile
    mkdir /tmp/testdir
    ln -s /tmp/target /tmp/link1
    touch /tmp/target # link1链接到target
    ln -s /tmp/target2 /tmp/link2 # link2链接的文件实际不存在
]]
set(myfile "/tmp/testfile")
set(mydir "/tmp/testdir")
set(mylink1 "/tmp/link1")
set(mylink2 "/tmp/link2")

if(EXISTS ${myfile})
    message(STATUS "file exist:${myfile}")
else()
    message(STATUS "file not exist:${myfile}")
endif()

if(EXISTS ${mydir})
    message(STATUS "directory exist:${mydir}")
else()
    message(STATUS "directory not exist:${mydir}")
endif()

if(EXISTS ${mylink1})
    message(STATUS "连接文件存在:${mylink1}")
else()
    message(STATUS "连接文件不存在:${mylink1}")
endif()

if(EXISTS ${mylink2})
    message(STATUS "连接文件存在:${mylink2}")
else()
    message(STATUS "连接文件不存在:${mylink2}")
endif()

# if(file1 IS_NEWER_THAN file2)：判断文件1是否比文件2要新。注意：当有文件不存在的时候，该判断返回true
set(oldfile "/tmp/oldfile")
set(newfile "/tmp/newfile")

if(${newfile} IS_NEWER_THAN ${oldfile})
    message(STATUS "${newfile} 文件比 ${oldfile} 文件新")
else()
    message(STATUS "${newfile} 文件不比 ${oldfile} 文件新")
endif()

#[[
创建文件
    touch /tmp/oldfile
    touch /tmp/newfile
]]

# if(IS_SYMLINK file-name)：判断是否为链接文件
if(IS_SYMLINK ${myfile})
    message(STATUS "是连接文件: ${myfile}")
else()
    message(STATUS "不是连接文件: ${myfile}")
endif()

if(IS_SYMLINK ${mylink1})
    message(STATUS "是连接文件: ${mylink1}")
else()
    message(STATUS "不是连接文件: ${mylink1}")
endif()

#[[
if(IS_ABSOLUTE path)：判断是否为绝对路径；注意有几个特殊的处理
    1）空路径判定为false；
    2）Windows下，以盘符和冒号开头（例如C:），或以正斜线/反斜线开头的都将判定为true，因此C:no\base\dir为true，管盘符后的no\base\dir是一个相对路径
    3）非Windows，例如Linux或macOS下，~开头的也会判定为true，即使路径并不存在
]]
if(IS_ABSOLUTE ${myfile})
    message(STATUS "是绝对路径:${myfile}")
else()
    message(STATUS "不是绝对路径:${myfile}")
endif()

set(nofile "~/no-file")

if(IS_ABSOLUTE ${nofile})
    message(STATUS "是绝对路径:${nofile}")
else()
    message(STATUS "不是绝对路径:${nofile}")
endif()

set(cmakelists "./CMakeLists.txt")

if(IS_ABSOLUTE ${cmakelists})
    message(STATUS "是绝对路径:${cmakelists}")
else()
    message(STATUS "不是绝对路径:${cmakelists}")
endif()