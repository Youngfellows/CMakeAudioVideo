# cmake 最低版本要求,不加入此行会受到警告信息
cmake_minimum_required(VERSION 3.15.0)

# 项目名称为 Sample
project(Sample)
message(STATUS "PROJECT_NAME: " ${PROJECT_NAME})

message(STATUS "=============== 逻辑运算 =================")

#[[
1.逻辑运算
    # 否
    if(NOT <condition>)
    # 与
    if(<cond1> AND <cond2>)
    # 或
    if(<cond1> OR <cond2>)
    # 逻辑组合
    if((condition) AND (condition OR (condition)))
]]
message(STATUS "=============== 逻辑非 =================")

# 逻辑非
if(NOT RELEASE)
    message(STATUS "这不是RELEASE版本...")
else()
    message(STATUS "这是RELEASE版本...")
endif()

set(VERSION1 "20230217")
set(VERSION2 "20231024")
set(VERSION "20230808")

# 判断字符串是否相等
if(VERSION1 STREQUAL VERSION2)
    message(STATUS "VERSION1 EQUAL VERSION2")
else()
    message(STATUS "VERSION1 NOT EQUAL VERSION2")
endif()

message(STATUS "=============== 逻辑与 =================")

# 逻辑与
if(RELEASE AND(VERSION1 STREQUAL VERSION2))
    message(STATUS "指定RELEASE版本:${VERSION1}")
else()
    message(STATUS "不是指定RELEASE版本:${VERSION1}")
endif()

message(STATUS "=============== 逻辑或 =================")

# 逻辑或
if((VERSION1 STRGREATER VERSION) OR(VERSION2 STRGREATER VERSION))
    message(STATUS "VERSION1:${VERSION1} 或 VERSION2:${VERSION2} 比 VERSION:${VERSION} 大")
else()
    message(STATUS "VERSION1:${VERSION1} 和 VERSION2:${VERSION2} 都比 VERSION:${VERSION} 小")
endif()

message(STATUS "=============== 逻辑组合 =================")
# 逻辑组合
if(RELEASE AND((VERSION1 STRGREATER VERSION) OR(VERSION2 STRGREATER VERSION)))
    message(STATUS "是RELEASE版本,RELASE:${RELEASE},VERSION1:${VERSION1} 或 VERSION2:${VERSION2} 比 VERSION:${VERSION} 大")
else()
    message(STATUS "不是满足条件的 ...")
endif()