# cmake 最低版本要求,不加入此行会受到警告信息
cmake_minimum_required(VERSION 3.15.0)

# 项目名称为 Sample
project(Sample)
message(STATUS "PROJECT_NAME:${PROJECT_NAME}")

message(STATUS "============ Cmake命令之add_executable  ===============")

#[[
命令格式
    add_executable (<name> [WIN32] [MACOSX_BUNDLE]
          [EXCLUDE_FROM_ALL]
          [source1] [source2 ...])
    add_executable (<name> IMPORTED [GLOBAL])
    add_executable (<name> ALIAS <target>)
    使用指定的源文件来生成目标可执行文件。这里的目标可执行文件分为三类：普通可执行目标文件、导入可执行目标文件、别名可执行目标文件。
    分别对应上面的三种命令格式。
]]

#[[
1. 普通可执行目标文件
add_executable (<name> [WIN32] [MACOSX_BUNDLE]
      [EXCLUDE_FROM_ALL]
      [source1] [source2 ...])

通过指定的源文件列表构建出可执行目标文件。
name:可执行目标文件的名字，在一个cmake工程中，这个名字必须全局唯一。
WIN32:用于windows系统下创建一个以WinMain为入口的可执行目标文件（通常入口函数为main），它不是一个控制台应用程序，而是一个GUI应用程序。当WIN32选项使用的时候，可执行目标的 WIN32_EXECUTABLE会被置位ON。
MACOSX_BUNDLE:用于mac系统或者IOS系统下创建一个GUI可执行应用程序，当MACOSX_BUNDLE选项使用的时候，可执行目标的MACOSX_BUNDLE会被置位ON。
EXCLUDE_FROM_ALL:用于指定可执行目标是否会被构建，当该选项使用的时候，可执行目标不会被构建。
[source1] [source2 ...]:构建可执行目标文件所需要的源文件。也可以通过target_sources()继续为可执行目标文件添加源文件，要求是在调用target_sources之前，可执行目标文件必须已经通过add_executable或add_library定义了。
]]
include_directories(math)
aux_source_directory(. SRC_LISTSS)
aux_source_directory(math MATH_SRC_LISTS)
add_executable(${PROJECT_NAME} ${SRC_LISTSS} ${MATH_SRC_LISTS})
