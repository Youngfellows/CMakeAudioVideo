# cmake 最低版本要求,不加入此行会受到警告信息
cmake_minimum_required(VERSION 3.15.0)

# 项目名称为 Sample
project(Sample)
message(STATUS "PROJECT_NAME: ${PROJECT_NAME}")

message(STATUS "=============== Cmake命令之set介绍 ========================")

#[[
设置环境变量
  命令格式：set(ENV{<variable>} [<value>])
  命令含义：将环境变量设置为值<value>（注意没有...），接着使用$ENV{<variable>}会得到新的值。cmake中的环境变量可以参考：环境变量。
  
环境变量设置的几个注意事项：
    1）该命令设置的环境变量只在当前的cmake进程生效，既不会影响调用者的环境变量，也不会影响系统环境变量。
    2）如果<value>值为空或者ENV{<variable>}后没有参数，则该命令会清除掉当前环境变量的值。
    3）<value>后的参数会被忽略。
]]
message(STATUS ">>> value = $ENV{CMAKE_PREFIX_PATH}")
set(ENV{CMAKE_PREFIX_PATH} "/test/sub")
message(STATUS ">>> value = $ENV{CMAKE_PREFIX_PATH}")
set(ENV{CMAKE_PREFIX_PATH})
message(STATUS ">>> value = $ENV{CMAKE_PREFIX_PATH}")
set(ENV{CMAKE_PREFIX_PATH} "/test/top/") 
message(STATUS ">>> value = $ENV{CMAKE_PREFIX_PATH}")
set(ENV{CMAKE_PREFIX_PATH} "") 
message(STATUS ">>> value = $ENV{CMAKE_PREFIX_PATH}")