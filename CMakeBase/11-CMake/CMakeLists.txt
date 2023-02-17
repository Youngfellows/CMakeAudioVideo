# cmake 最低版本要求,不加入此行会受到警告信息
cmake_minimum_required(VERSION 3.15.0)

# 项目名称为 Sample
project(Sample)
message("PROJECT_NAME: " ${PROJECT_NAME})

# 1. if 条件
#[[if 条件: if, elseif, else, endif，支持语法如下，
    # if
    if(<condition>)
    # elseif
    elseif(<condition>)
    # else
    else([<condition>])
    # endif
    endif([<condition>])

PS: endif() 命令中 <condition> 仅用于向后兼容。如果使用它，必须于 if() 命令参数相同。
]]
if(DEBUG)
    message(STATUS "DEBUG: ${DEBUG}")

    if(RELEASE)
        message(STATUS "RELEASE: ${RELEASE}")
    endif()
endif(DEBUG)

if(DEFINED CITY)
    message(STATUS "CITY: ${CITY}")
endif()

if(DEFINED BRAND)
    message(STATUS "BRAND: ${BRAND}")
endif()

if(NOT DEFINED BRAND)
    message(STATUS "NOT DEFINE BRAND")
endif()
