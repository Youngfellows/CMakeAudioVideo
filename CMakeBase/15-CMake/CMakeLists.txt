# cmake 最低版本要求,不加入此行会受到警告信息
cmake_minimum_required(VERSION 3.15.0)

# 项目名称为 Sample
project(Sample)
message("PROJECT_NAME: " ${PROJECT_NAME})

message(STATUS "============ CMake 数学操作 ==============")

# CMake 数学操作
#[[ 
我们一般用 math 评估数学表达式。
math 语法：
    math(EXPR <variable> "<expression>" [OUTPUT_FORMAT <format>])

计算数学表达式 <expression>，并将结果保存在 <variable> 变量中，表达式的结果为 64 位有符号整数。
数学表达式以字符串形式给出。支持的运算符有 +, -, *, /, %, |, &, ^, ~, <<, >>, and (...)，它们与 C 语言中的含义相同。
数学表达式中的十六进制数字，带有前缀 0x，类似 C 语言 中。
结果会根据 <format> 进行格式化，其中选项之一：
HEXADECIMAL: 类似 C 语言中 的十六进制表示法，以 0x 开头。
DECIMAL: 默认值，十进制表示法。
]]

# 案例，数学表达式运算
math(EXPR value "100 * 0xA" OUTPUT_FORMAT DECIMAL)
message(STATUS "value: ${value}")
math(EXPR value "100 * 0xA" OUTPUT_FORMAT HEXADECIMAL)
message(STATUS "value: ${value}")
math(EXPR value "(2+4)*(1+3)" OUTPUT_FORMAT DECIMAL)
message(STATUS "value: ${value}")
math(EXPR value "(2+4)*(1+3)" OUTPUT_FORMAT HEXADECIMAL)
message(STATUS "value: ${value}")

message(STATUS "=============================")

set(m 8)
set(n 5)
math(EXPR result "${m}%${n}")
message(STATUS "${m}%${n}=${result}")

message(STATUS "=============================")

set(number 0)

while(${number} LESS 10)
    message(STATUS "number:${number}")
    math(EXPR number "${number} + 1")
endwhile()

message(STATUS "=============================")

set(speed 15)

while(YES)
    message(STATUS "speed: ${speed}")

    if(speed EQUAL 20)
        break()
    endif()

    math(EXPR speed "${speed} + 1")
endwhile()

message(STATUS "=============================")