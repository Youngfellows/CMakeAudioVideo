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

message(STATUS "================  数字的比较 ==================")

#[[
4.数字的比较
    比较数字的大小
    # 小于
    if(<variable|string> LESS <variable|string>)
    # 大于
    if(<variable|string> GREATER <variable|string>)
    # 等于
    if(<variable|string> EQUAL <variable|string>)
    # 小于或等于
    if(<variable|string> LESS_EQUAL <variable|string>)
    # 大于或等于
    if(<variable|string> GREATER_EQUAL <variable|string>)

]]
set(NUMBER 28)
set(MAX_NUMBER 30)
set(MIN_NUMBER 15)

if(NUMBER LESS MAX_NUMBER)
    message(STATUS "${NUMBER} 小于 ${MAX_NUMBER}")
else()
    message(STATUS "${NUMBER} 不小于 ${MAX_NUMBER}")
endif()

if(NUMBER GREATER MIN_NUMBER)
    message(STATUS "${NUMBER} 大于 ${MIN_NUMBER}")
else()
    message(STATUS "${NUMBER} 不大于 ${MIN_NUMBER}")
endif()

if(NUMBER EQUAL 28)
    message(STATUS "${NUMBER} 等于 28")
else()
    message(STATUS "${NUMBER} 不等于 28")
endif()

if(NUMBER LESS_EQUAL MAX_NUMBER)
    message(STATUS "${NUMBER} 小于等于 ${MAX_NUMBER}")
else()
    message(STATUS "${NUMBER} 不小于等于 ${MAX_NUMBER}")
endif()

if(NUMBER GREATER_EQUAL MIN_NUMBER)
    message(STATUS "${NUMBER} 大于等于 ${MIN_NUMBER}")
else()
    message(STATUS "${NUMBER} 不大于等于 ${MIN_NUMBER}")
endif()

set(PRICE_AVG "88.96")
set(PRICE_APPLE "16.50")
set(PRICE_BANANA "3.18")
set(PRICE_DURIAN "100.05")

if(${PRICE_APPLE} LESS PRICE_AVG)
    message(STATUS "苹果的价格${PRICE_APPLE}小于平均价格${PRICE_AVG}")
else()
    message(STATUS "苹果的价格${PRICE_APPLE}不小于平均价格${PRICE_AVG}")
endif()

if(PRICE_BANANA GREATER PRICE_AVG)
    message(STATUS "香蕉的价格${PRICE_BANANA}大于平均价格${PRICE_AVG}")
else()
    message(STATUS "香蕉的价格${PRICE_BANANA}不大于平均价格${PRICE_AVG}")
endif()

if(PRICE_DURIAN GREATER_EQUAL PRICE_AVG)
    message(STATUS "榴莲的价格${PRICE_DURIAN}大于等于平均价格${PRICE_AVG}")
else()
    message(STATUS "榴莲的价格${PRICE_DURIAN}不大于等于平均价格${PRICE_AVG}")
endif()