# cmake要求最低版本
cmake_minimum_required(VERSION 3.15.0)

# 项目名称
project(Sample)
message(STATUS "start build,project name:${PROJECT_NAME}")

# 依赖头文件
include_directories(${CMAKE_SOURCE_DIR}/include/array)

# 库文件链接路径
message(STATUS "link_directories:${CMAKE_INSTALL_PREFIX}")

# link_directories(${CMAKE_INSTALL_PREFIX}/lib)
# link_directories(${CMAKE_CURRENT_SOURCE_DIR}/dist/lib)

# 查找源文件
aux_source_directory(. EXAMPLE_SRC_LIST)

# aux_source_directory(./src/array ARRAY_SRC_LIST)

# 生成可执行文件
# add_executable(${PROJECT_NAME} ${EXAMPLE_SRC_LIST} ${ARRAY_SRC_LIST})
add_executable(${PROJECT_NAME} ${EXAMPLE_SRC_LIST})

# 查找链接库easyarray并连接
set(EASY_LIB_PATH ${CMAKE_CURRENT_SOURCE_DIR}/dist/lib)
find_library(lib-easyarray NAMES easyarray PATHS ${EASY_LIB_PATH})
message(STATUS "easyarray,path:${lib-easyarray}")

target_link_libraries(${PROJECT_NAME} ${lib-easyarray})

# 指定可执行文件安装路径
install(TARGETS ${PROJECT_NAME} DESTINATION bin)

# 设置Java和JNI环境

# 查找Java库,查找JNI库
find_package(Java)
find_package(JNI)

message(STATUS "Java_FOUND:${Java_FOUND}")
message(STATUS "JNI_FOUND:${JNI_FOUND}")

if (Java_FOUND)
    message(STATUS "Java_INCLUDE_DIRS=${Java_INCLUDE_DIRS}")
    message(STATUS "Java_LIBRARIES=${Java_LIBRARIES}")
else()
    message(STATUS "Java_NOT_FOUND")
endif ()

if (JNI_FOUND)
    message(STATUS "JNI_INCLUDE_DIRS=${JNI_INCLUDE_DIRS}")
    message(STATUS "JNI_LIBRARIES=${JNI_LIBRARIES}")
else()
    message(STATUS "JNI_NOT_FOUND")
endif ()

if(Java_FOUND)
    # Allow the Java compiler flags to be set using an environment variable
    if(NOT DEFINED CMAKE_JAVA_COMPILE_FLAGS AND DEFINED ENV{JAVAFLAGS})
        set(CMAKE_JAVA_COMPILE_FLAGS $ENV{JAVAFLAGS})
    endif()

    include(UseJava)

    set(CMAKE_JAVA_COMPILE_FLAGS "${CMAKE_JAVA_COMPILE_FLAGS} -J-Dfile.encoding=UTF8")
    message(STATUS "CMAKE_JAVA_COMPILE_FLAGS = ${CMAKE_JAVA_COMPILE_FLAGS}")
    string(REGEX REPLACE " " ";" CMAKE_JAVA_COMPILE_FLAGS "${CMAKE_JAVA_COMPILE_FLAGS}")

    set(JAVAARGS "" CACHE STRING "Additional arguments to pass to java when running unit tests (example: -d32)")
    message(STATUS "JAVAARGS = ${JAVAARGS}")
endif()

