# 设置cmake最小版本
cmake_minimum_required(VERSION 3.12.1)

# 设置项目名称
project(library-easyarray)

# 启动对C11标准的支持
set(CMAKE_C_STANDARD 11)

# 显式要求指明支持C标准
set(CMAKE_C_STANDARD_REQUIRED True)

# 设置NDK路径
set(NDK_PATH "/mnt/d/LinuxEnvironment/android-ndk-r16b-linux-x86_64/android-ndk-r16b")

# 设置支持的CPU架构
set(ARCHS arm64-v8a armeabi-v7a x86 x86_64)

# 设置编译选项
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

# 查找父目录3rd
message(STATUS "CMAKE_CURRENT_SOURCE_DIR::${CMAKE_CURRENT_SOURCE_DIR}")
get_filename_component(VAR_PARENT ${CMAKE_CURRENT_SOURCE_DIR}/../.. ABSOLUTE)
message(STATUS "VAR_PARENT::${VAR_PARENT}")

# 头文件查找目录
set(INCLUDE_PATH ${VAR_PARENT}/include/array)
message(STATUS "include path:${INCLUDE_PATH}")
include_directories(${INCLUDE_PATH})

# 查找源文件列表
aux_source_directory(. ARRAY_SRC)
message(STATUS "编译动态库:${ARRAY_SRC}")

# 设置动态库名称
set(EASY_ARRAY_LIB easyarray)

# 生成各个CPU平台动态库
add_library(${EASY_ARRAY_LIB} SHARED ${ARRAY_SRC})

# 遍历所有CPU架构进行编译
foreach(ARCH ${ARCHS})
    message(STATUS "编译CPU架构:${ARCH}")

    # 设置平台目录
    set(PLATFORM_DIR ${NDK_PATH}/platforms/android-27/arch-${ARCH})

    # 设置编译工具链路径
    set(TOOLCHAIN_DIR ${NDK_PATH}/toolchains/llvm/prebuilt/linux-x86_64)

    # 设置编译选项
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --sysroot=${PLATFORM_DIR}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -target ${ARCH}-none-linux-android")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -gcc-toolchain ${TOOLCHAIN_DIR}")

    # 设置输出路径
    # set(OUTPUT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs/${ARCH})
    # set(OUTPUT_DIR ${CMAKE_INSTALL_PREFIX}/${PROJECT_NAME}/libs/${ARCH})

    # 设置输出文件名
    # set_target_properties(${EASY_ARRAY_LIB} PROPERTIES
    # LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIR}
    # LIBRARY_OUTPUT_DIRECTORY_DEBUG ${OUTPUT_DIR}
    # LIBRARY_OUTPUT_DIRECTORY_RELEASE ${OUTPUT_DIR}
    # PREFIX "")

    # 安装动态库/头文件到指定目录
    message(STATUS "安装动态库:${CMAKE_INSTALL_PREFIX}")
    install(TARGETS ${EASY_ARRAY_LIB} DESTINATION ${ARCH}/lib)
    install(DIRECTORY ${INCLUDE_PATH} DESTINATION ${ARCH}/include)
endforeach()

# 安装动态库/头文件到指定目录
# message(STATUS "安装动态库:${CMAKE_INSTALL_PREFIX}")
# install(TARGETS ${EASY_ARRAY_LIB} DESTINATION lib)
# install(DIRECTORY ${INCLUDE_PATH} DESTINATION include)

#[[
install(DIRECTORY ${INCLUDE_PATH}
    DESTINATION include
    FILES_MATCHING PATTERN "*.h"
)
]]