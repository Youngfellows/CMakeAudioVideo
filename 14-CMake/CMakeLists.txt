# cmake 最低版本要求,不加入此行会受到警告信息
cmake_minimum_required(VERSION 3.18)

# 设置工程名称
set(PROJECT_NAME Sample)

# 设置工程版本号
set(PROJECT_VERSION "1.0.0.10" CACHE STRING "默认版本号")

# 工程定义
project(${PROJECT_NAME}
    LANGUAGES CXX C
    VERSION ${PROJECT_VERSION}
)

# 打印开始日志
message(STATUS "\n########## BEGIN_TEST_PROCESS_CONTROL")
message(STATUS "PROJECT_NAME: " ${PROJECT_NAME})

message(STATUS "========== if 举例 ===========>>")

# 1. if 举例
set(var_3 "camke")

if(DEFINED var_1)
    message("defined var_1:${var_1}")
elseif(DEFINED var_2)
    message("defined var_2:${var_2}")
elseif(DEFINED var_3)
    message("defined var_3:${var_2}")
else()
    message("defined nothing")
endif()

message(STATUS "========== foreach 举例: foreach 方式一===========>>")

# # 2. foreach 举例

# # foreach 方式一：
set(var_list "C++" "JAVA" Python "CMake" 1024)

foreach(item ${var_list})
    message("当前变量是：${item}")
endforeach()

message(STATUS "========== foreach 举例: foreach 方式二===========>>")

# # foreach 方式二：
set(result 0)
set(end 0)

foreach(element RANGE 0 100)
    math(EXPR result "${result} + ${element}")

    if(result LESS 100)
        continue() # # continue
    endif()

    if(result GREATER 1000)
        set(end ${element})
        break() # # break
    endif()
endforeach()

message(STATUS "from 0 plus to ${end} is : ${result}\n")

message(STATUS "========== foreach 举例: foreach 方式三===========>>")

# # foreach 方式三：
foreach(every RANGE 0 10 2)
    message(STATUS "every = ${every}")
endforeach()

message(STATUS "========== foreach 举例: foreach 方式四===========>>")

# # foreach 方式四：
set(X a b c)

foreach(var IN LISTS X)
    message(STATUS "var = ${var}")
endforeach()

message(STATUS "========== foreach 举例: foreach 方式五===========>>")

# # foreach 方式五：
set(A a b c)
set(B 3 4 5)
set(C "11 22")
set(D 8;9 10)
set(E "")

foreach(m IN LISTS A B C D E)
    message(STATUS "m = ${m}")
endforeach()

message(STATUS "========== foreach 举例: foreach 方式六===========>>")

# # foreach 方式六：
foreach(pair IN ZIP_LISTS A B)
    message(STATUS "pair_0 = ${pair_0}, pair_1 = ${pair_1}")
endforeach()

message(STATUS "========== foreach 举例: foreach 方式七===========>>")

# # foreach 方式七：
foreach(first second IN ZIP_LISTS A B)
    message(STATUS "first = ${first}, second = ${second}")
endforeach()

# # endforeach
message(STATUS "========== while 举例 ===========>>")

# ## 3. while 举例
set(var_max 5)

while(${var_max} GREATER 0)
    message(${var_max})
    math(EXPR var_max "${var_max} - 1")
endwhile()

# ## endwhile

# 打印结束日志
message(STATUS "########## END_TEST_PROCESS_CONTROL\n")
