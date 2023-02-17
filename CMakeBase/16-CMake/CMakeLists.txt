# cmake 最低版本要求,不加入此行会受到警告信息
cmake_minimum_required(VERSION 3.15.0)

# 项目名称为 Sample
set(PROJECT_NAME SAMPLE)
project(${PROJECT_NAME})
message(STATUS "PROJECT_NAME: " ${PROJECT_NAME})

message(STATUS "=================>>布尔常量 True")

#[[ 
1. 布尔常量
    True 常量为，1, ON, YES, TRUE, Y, or 非零数字.
    False 常量为，0, OFF, NO, FALSE, N, IGNORE, NOTFOUND, 空字符串, 后缀为 -NOTFOUND。

    布尔常量命名不区分大小写。

    if(<constant>)
    如果参数不是这些特定常量，则被视为变量或字符串。
]]

# 案例: 如果常量为 True，则输出，如果常量为 False，则不输出。
if(ON)
    message(STATUS "ON")
endif()

if(TRUE)
    message(STATUS "TRUE")
endif()

if(1024)
    message(STATUS "1024")
endif()

if(YES)
    message(STATUS "YES")
endif()

if(yes)
    message(STATUS "yes")
endif()

if(Y)
    message(STATUS "Y")
endif()

message(STATUS "=================>>布尔常量 False")

# False 常量为，0, OFF, NO, FALSE, N, IGNORE, NOTFOUND, 空字符串, 后缀为 -NOTFOUND。
if(NOT 0)
    message(STATUS "NOT 0")
endif()

if(OFF)
    message(STATUS "OFF")
else()
    message(STATUS "NOT OFF")
endif()

if(OFF)
    message(STATUS "NO")
else()
    message(STATUS "NOT NO")
endif()

if(FALSE)
    message(STATUS "FALSE")
else()
    message(STATUS "NOT FALSE")
endif()

if(N)
    message(STATUS "N")
else()
    message(STATUS "NOT N")
endif()

if(IGNORE)
    message(STATUS "IGNORE")
else()
    message(STATUS "NOT IGNORE")
endif()

if(NOTFOUND)
    message(STATUS "NOTFOUND")
else()
    message(STATUS "NOT NOTFOUND")
endif()

set(CITY "")

if(CITY)
    message(STATUS "CITY:${CITY} ...")
else()
    message(STATUS "CITY IS NULL:${CITY}")
endif()

set(ADDRESS-NOTFOUND "ShenZhen")

if(ADDRESS-NOTFOUND) # false
    message(STATUS "ADDRESS-NOTFOUND:${ADDRESS-NOTFOUND} ...")
else()
    message(STATUS "ADDRESS-NOTFOUND:${ADDRESS-NOTFOUND}")
endif()

if(false)
    message(STATUS "false")
else()
    message(STATUS "NOT false")
endif()

message(STATUS "========================>>判断变量是否被定义为一个非 False 常量")

#[[
if(<variable|string>)
给定的变量被定义为一个非 False 常量，则被视为 True。表示变量被使用。
]]
# 案例: 判断变量是否被定义为一个非 False 常量，两种形式都可以。
if(DEBUG)
    message(STATUS "TRUE DEBUG: ${DEBUG}")
else()
    message(STATUS "FALSE DEBUG: ${DEBUG}")
endif()

if(${DEBUG})
    message(STATUS "TRUE DEBUG: ${DEBUG}")
else()
    message(STATUS "FALSE DEBUG: ${DEBUG}")
endif()

# 运行 cmake .. -DDEBUG=Y -L，会打印信息。
# PS: if() 命令由一个特殊的条件语法，允许以短形式 <variable>，而不是 ${<variable>}。