# cmake 最低版本要求,不加入此行会受到警告信息
cmake_minimum_required(VERSION 3.15.0)

# 项目名称为 Sample
project(Sample)
message("PROJECT_NAME: " ${PROJECT_NAME})

#[[1. foreach 循环
for 循环:: foreach, endforeach，支持语法如下，

    # foreach
    foreach(<loop_var> <items>)
    # endforeach
    endforeach([<loop_var>])

概要
    foreach(<loop_var> <items>)
    <commands>
    endforeach()
]]

#[[变体一:
    foreach(<loop_var> <items>)
    其中 <items> 是由分号或空格分隔的项目列表。每次迭代开始变量 <loop_var> 被设置为当前项的值。
]]

# 变体二:
# foreach(<loop_var> IN [LISTS [<lists>]] [ITEMS [<items>]])
# 在这个变体中，<lists> 是列表变量，其值由分号或空格分隔。
# 跟在 ITEMS 关键字后面的 <items> 像 foreach 命令的第一个变体中一样处理。LISTS A 和 ITEMS ${A} 是等价形式。

# 案例: 如何处理列表
# 列表定义
set(A 0;1)
set(B 2 3)
set(C "4 5") # 不是列表，是字符串
set(D 6;7 8)
set(E "")

message(STATUS ${A}) # 不分开
message(STATUS "${A}") # 使用;分开

message(STATUS "==============>>foreach变体一")

# 变体一
foreach(X ${A} ${B} ${C} ${D} ${E})
    message(STATUS "X=${X}")
endforeach()

message(STATUS "==============>>foreach变体二")

# 变体二，等价于 foreach(X IN LISTS A B C ITEMS ${D} ${E})
foreach(X IN LISTS A B C D E)
    message(STATUS "X=${X}")
endforeach()

#[[变体三:
    foreach(<loop_var> RANGE <stop>)
    这个变体中，遍历数字 0, 1, … 直到(并包括) 整数 <stop>。

变体四:
    foreach(<loop_var> RANGE <start> <stop> [<step>])
    这个变体，有起始值 <start> 和 步长 <step>
]]

# 案例: 如何处理 1-10
message(STATUS "==============>>foreach变体三")

# 变体三
foreach(X RANGE 10)
    message(STATUS "X=${X}")
endforeach()

message(STATUS "==============>>foreach变体四")

# 变体四
foreach(X RANGE 10 20 3)
    message(STATUS "X=${X}")
endforeach()

#[[变体五:
    foreach(<loop_var>... IN ZIP_LISTS <lists>)
    在这个变体中，<lists> 是列表变量，其值由分号或空格分隔。
    这个变量主要用于打包多个列表变量的值。

    foreach 同时迭代所有的列表，
    如果给定一个变量 <loop_var>，那么它给一系列的 <loop_var_N> 变量设置对应列表的当前项。
    如果给定多个变量，那么列表数目与变量数目匹配。
    如果列表的长度不一致，较短的列表对应的变量项为空。
]]
message(STATUS "==============>>foreach变体五")

# 案例: 打包两个长度不一致的列表的项
list(APPEND Animals dog cat tigger lion duck) # 定义列表 Animal
list(APPEND Citys shenzhen beijing nanjing shanghai wuhan guangzhou chengdu)

foreach(num IN ZIP_LISTS Animals Citys)
    message(STATUS "num_0=${num_0},num_1=${num_1}")
endforeach()

message(STATUS "=============================")

foreach(animal city IN ZIP_LISTS Animals Citys)
    message(STATUS "animal=${animal},city=${city}")
endforeach()

message(STATUS "=============================")
