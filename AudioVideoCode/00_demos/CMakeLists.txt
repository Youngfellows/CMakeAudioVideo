# cmake 要求最低版本
cmake_minimum_required(VERSION 3.15.0)

# 设置项目名称
project(SampleDemos)

# 设置C/C++语言支持
set(CMAKE_CXX_STANDARD 17)

# 设置项目名称
set(SAMPLE_NAME_SIZEOF DemoSizeof)

# 查找源文件
aux_source_directory(./src DEMOS_SRC_LISTS)

# 生成可执行文件
# set(SIZEOF_SRC_LIST "./src/DemoSizeof.cpp")
# add_executable(${SAMPLE_NAME_SIZEOF} ${SIZEOF_SRC_LIST})

# 定义添加列表元素的函数
function(append executables ele)
    list(APPEND ${executables} ${ele})
    set(${executables} ${${executables}} PARENT_SCOPE)
endfunction()

# 全部可执行文件的名称列表
set(EXECUTABLES)

#[[ 
生成可执行文件
    1.遍历所有.c和.cpp文件
    2.获取文件名列表
    3.生成可执行文件
]]
foreach(PATH ${DEMOS_SRC_LISTS})
    message(STATUS "PATH:${PATH}")
    string(LENGTH ${PATH} SIZE)
    string(FIND ${PATH} "/" INDEX REVERSE) # 获取最后一个字符/的位置
    string(FIND ${PATH} "." DOT_INDEX REVERSE) # 获取最后一个字符.的位置
    message(STATUS "INDEX:${INDEX},DOT_INDEX:${DOT_INDEX},SIZE:${SIZE}")

    if(NOT(${INDEX} EQUAL -1) AND(NOT(${DOT_INDEX} EQUAL -1)))
        math(EXPR LEN "${DOT_INDEX}-${INDEX}-1" OUTPUT_FORMAT DECIMAL)
        math(EXPR START "${INDEX}+1" OUTPUT_FORMAT DECIMAL)
        message(STATUS "LEN:${LEN}")
        string(SUBSTRING ${PATH} ${START} ${LEN} EXEC_NAME) # 获取可执行文件名
        message(STATUS "EXEC_NAME:${EXEC_NAME}")
        add_executable(${EXEC_NAME} ${PATH}) # 生成可执行文件

        list(APPEND EXECUTABLES ${EXEC_NAME}) # 向列表添加元素

        # append(EXECUTABLES ${EXEC_NAME})
    endif()
endforeach()

# 安装可执行文件到指定目录
# install(TARGETS ${SAMPLE_NAME_SIZEOF} DESTINATION bin)
message(STATUS "install,EXECUTABLES:${EXECUTABLES}")

foreach(EXEC ${EXECUTABLES})
    install(TARGETS ${EXEC} DESTINATION bin)
    message(STATUS "install ${EXEC} success ...")
endforeach()
