# cmake 最低版本要求,不加入此行会受到警告信息
cmake_minimum_required(VERSION 3.15.0)

# 项目名称为 Sample
project(Sample)
message("PROJECT_NAME: " ${PROJECT_NAME})

# 1. 常规变量
message("======> 常规变量")

# 字符串类型，解释为列表类型用 `;` 分隔
set(PATHs "/tmp" "/bin" "/lib")
message("${PATHs}")

foreach(PATH ${PATHs})
    if(PATH)
        message(${PATH})
    endif()
endforeach()

unset(PATHs)

# or
# set(PATHs "")

# 2. 环境变量
message("======> 环境变量")
set(ENV{PATH} "/tmp;$ENV{PATH}")
message("PATH: $ENV{PATH}")

# 3. 缓存变量
message("======> 缓存变量")
set(BUILD_DEBUG "ON" CACHE STRING "Value Created by Me")
message("BUILD_DEBUG: ${BUILD_DEBUG}")
message("BUILD_RELEASE: ${BUILD_RELEASE}")
