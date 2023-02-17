# cmake 最低版本要求,不加入此行会受到警告信息
cmake_minimum_required(VERSION 3.15.0)

# 项目名称为 Sample
project(Sample)
message("PROJECT_NAME: " ${PROJECT_NAME})

# 1. condition 条件语法
#[[condition 条件语法支持 if(<condition>), elseif(<condition>) and while(<condition>)。

布尔常量
True 常量为，1, ON, YES, TRUE, Y, or 非零数字.
False 常量为，0, OFF, NO, FALSE, N, IGNORE, NOTFOUND, 空字符串, 后缀为 -NOTFOUND。

布尔常量命名不区分大小写。
]]

#[[1.1 if(<constant>)
如果参数不是这些特定常量，则被视为变量或字符串。
]]

# 案例: 如果常量为 True，则输出，如果常量为 False，则不输出。
if(ON)
    message(STATUS "ON")
endif()

if(OFF)
    message(STATUS "OFF") # 不输出
endif()

#[[1.2 if(<variable|string>)
给定的变量被定义为一个非 False 常量，则被视为 True。表示变量被使用。
]]

# 案例: 判断变量是否被定义为一个非 False 常量，两种形式都可以。
if(DEBUG)
    message(STATUS "DEBUG: ${DEBUG}")
endif()

if(${DEBUG})
    message(STATUS "DEBUG: ${DEBUG}")
endif()

if(RELEASE)
    message(STATUS "RELEASE: ${RELEASE}")
endif()

# 运行 cmake .. -DDEBUG=Y -L，会打印信息。

# PS: if() 命令由一个特殊的条件语法，允许以短形式 <variable>，而不是 ${<variable>}。

# 2. 变量
#[[if(DEFINED <name>|CACHE{<name>}|ENV{<name>})
如果给定的名称为被定义的变量、缓存变量或环境变量，则为真。变量值无关紧要。

与 if(<variable|string>) 相比，if(<variable|string>) 是用来判断变量的值，而 if(DEFINED ...) 用来判断变量是否被定义。
]]

# 案例: 判断变量是否被定义
if(DEFINED MY_ADDRESS)
    message(STATUS "MY_ADDRESS: ${MY_ADDRESS}")
endif()

# 运行 cmake .. -DDEBUG=N -L，也会打印信息。