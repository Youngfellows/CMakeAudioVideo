# cmake 最低版本要求,不加入此行会受到警告信息
cmake_minimum_required(VERSION 3.15.0)

# 项目名称为 Sample
project(Sample)
message(STATUS "PROJECT_NAME: " ${PROJECT_NAME})

#[[ 
1. 字符串匹配
    按照正则表达式去匹配，左边是待匹配的值，右边是正则表达式，能匹配为时为真。
    
    格式为：
    if(<variable|string> MATCHES regex)
]]
message(STATUS "================== 字符串的正则表达式匹配 ==============")
set(ADDRESS "GuangZhou")

# set(ADDRESS "ShenZhen")
if(ADDRESS MATCHES .*)
    message(STATUS "${ADDRESS} ,匹配任何字符 ...")
else()
    message(STATUS "${ADDRESS} ,不匹配任何字符 ...")
endif()

if(ADDRESS MATCHES "ShenZhen")
    message(STATUS "${ADDRESS} ,匹配 ShenZhen")
else()
    message(STATUS "${ADDRESS} ,不匹配 ShenZhen")
endif()

message(STATUS "=================  字符串的比较  ====================")

#[[
2.字符串的比较
    按字典的顺序，比较字符串的大小。
    if(<variable|string> STRLESS <variable|string>)
    if(<variable|string> STRGREATER <variable|string>)
    if(<variable|string> STREQUAL <variable|string>)
    if(<variable|string> STRLESS_EQUAL <variable|string>)
    if(<variable|string> STRGREATER_EQUAL <variable|string>)
]]
set(APPLE "apple")
set(ORANGE "orange")
set(BANANA "banana")
set(ARBUTUS "arbutus")
set(BERRY "berry")

if(APPLE STRLESS ORANGE)
    message(STATUS "${APPLE} 小于 ${ORANGE}")
else()
    message(STATUS "${APPLE} 不小于 ${ORANGE}")
endif()

if(ORANGE STRGREATER BANANA)
    message(STATUS "${ORANGE} 大于 ${BANANA}")
else()
    message(STATUS "${ORANGE} 不大于 ${BANANA}")
endif()

if(BANANA STREQUAL BERRY)
    message(STATUS "${BANANA} 等于 ${BERRY}")
else()
    message(STATUS "${BANANA} 不等于 ${BERRY}")
endif()

if(ORANGE STRLESS_EQUAL BANANA)
    message(STATUS "${ORANGE} 小于等于 ${BANANA}")
else()
    message(STATUS "${ORANGE} 不小于等于 ${BANANA}")
endif()

if(ORANGE STRGREATER_EQUAL BANANA)
    message(STATUS "${ORANGE} 大于等于 ${BANANA}")
else()
    message(STATUS "${ORANGE} 不大于等于 ${BANANA}")
endif()

message(STATUS "=============== 元素是否在列表中 ======================")

#[[
3.元素是否在列表中
    if(<variable|string> IN_LIST <variable>)
    如果给定元素在列表中，则为真。
]]
# 定义水果列表
list(APPEND FRUITS apple;banana;orange;berry;lemon)
message(STATUS "${FRUITS}")

if(apple IN_LIST FRUITS)
    message(STATUS "apple 在列表中:${FRUITS}")
else()
    message(STATUS "apple 不在列表中:${FRUITS}")
endif()

set(PEAR "pear")

if(PEAR IN_LIST FRUITS)
    message(STATUS "${PEAR} 在列表中:${FRUITS}")
else()
    message(STATUS "${PEAR} 不在列表中:${FRUITS}")
endif()