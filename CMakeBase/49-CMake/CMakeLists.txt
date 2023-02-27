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
别名可执行目标文件
    add_executable (<name> ALIAS <target>)
为可执行目标文件创建一个别名。创建该别名后，可以使用别名进行可执行目标的读、测试操作，但是不能利用别名对可执行目标的修改属性操作。
]]
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY output)
include_directories(math)
aux_source_directory(. SRC_LISTSS)
aux_source_directory(math MATH_SRC_LISTS)
add_executable(${PROJECT_NAME} ${SRC_LISTSS} ${MATH_SRC_LISTS})

add_executable(test_name ALIAS ${PROJECT_NAME})
get_target_property(alias_name test_name ALIASED_TARGET)

if(alias_name)
    message(STATUS ">>> The name test_name is an ALIAS for ${alias_name}")
endif()