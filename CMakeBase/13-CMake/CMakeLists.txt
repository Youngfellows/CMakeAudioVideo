# cmake 最低版本要求,不加入此行会受到警告信息
cmake_minimum_required(VERSION 3.15.0)

# 项目名称为 Sample
project(Sample)
message("PROJECT_NAME: " ${PROJECT_NAME})

#[[ 1. while 循环
    while 循环: while, endwhile，支持语法如下，
    # while
    while(<condition>)
    # endwhile
    endwhile([<condition>])

    如果 while 命令，条件为真，则一直执行。

    概要
        while(<condition>)
        <commands>
        endwhile()
]]

#[[4. 跳出循环
    break 和 continue 支持 foreach 循环 和 while 循环。
    我们使用 break() 命令提前终止循环，而使用 continue() 命令可用于立即开始下一次迭代。
]]
message(STATUS "==============================")
set(i 2)
set(n 7)
math(EXPR cntr ${n}/2)

message(STATUS ${i}, ${n}, ${cntr})

# When I use `LESS` instead of `LESS_EQUAL` the loop works fine
while(i LESS_EQUAL cntr)
    message(STATUS "Checking ${i}")
    math(EXPR RESULT ${n}%${i})
    message(STATUS "RESULT: ${RESULT}")

    if(RESULT EQUAL 0)
        message(STATUS "${n} is not Prime, as ${n}%${i} is 0")
        break()
    endif()

    math(EXPR i ${i}+1)
endwhile()

if(i EQUAL cntr)
    message(STATUS "${n} is Prime")
endif()

message(STATUS "==============================")

set(var_max 5)

while(${var_max} GREATER 0)
    message(STATUS ${var_max})
    math(EXPR var_max "${var_max} - 1")
endwhile()

message(STATUS "==============================")
set(age 18)

while(${age} GREATER 0)
    if(age EQUAL 9)
        break()
    endif()

    message(STATUS "age: ${age}")
    math(EXPR age "${age} - 1")
endwhile()

message(STATUS "==============================")

#[[CMake中的while命令用于在条件为true时评估(evaluate)一组命令，其格式如下：
    while(<condition>)
    <commands>
    endwhile()
      在while和匹配的endwhile之间的所有命令都被记录下来而不被调用。一旦评估了endwhile，只要<condition>为true,就会调用记录的命令列表。
      while中的<condition>与if命令中的<condition>具有相同语法和相同的逻辑进行评估。
      命令break和continue提供了从正常控制流中退出的方法。
]]
set(var 1)

while(${var} LESS 4)
    message(STATUS "var: ${var}")
    math(EXPR var "${var}+1")
endwhile()

message(STATUS "=======================>>continue 使用")

#[[CMake中的continue命令用于continue到foreach或while循环的顶部(top)，其格式如下：
    continue()
        continue命令允许cmake脚本中止foreach或while循环的当前迭代的其余部分，并从下一次迭代的顶部开始。
]]
set(var 1)

while(${var} LESS 4)
    message("var: ${var}")
    math(EXPR var "${var}+1")

    if(${var} EQUAL 3)
        continue() # 跳过3,继续下次循环
    endif()

    message("after math, var: ${var}")
endwhile()

message(STATUS "=======================>>break 使用")

#[[ CMake中的break命令用于从foreach或while循环中中断(break)，其格式如下：从当前的foreach或while循环中退出
break()
]]
set(var 1)

while(${var} LESS 4)
    message(STATUS "var: ${var}")
    math(EXPR var "${var}+1")

    if(${var} EQUAL 3)
        break() # 结束循环
    endif()

    message(STATUS "after math, var: ${var}")
endwhile()

message(STATUS "var: ${var}")
