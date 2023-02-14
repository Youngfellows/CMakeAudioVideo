# cmake 最低版本要求,不加入此行会受到警告信息
cmake_minimum_required(VERSION 3.15.0)

# cmake打印
message(VERSION: ${VERSION})

# Install script for directory: /mnt/d/TempCode2023/NDK/NDK-CMake/CMakeAudioVideo/01-CMake

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
    set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()

# 使用正则表达式替换,比如: "/usr////local" ,替换成: "/usr/local"
message("CMAKE_INSTALL_PREFIX: " ${CMAKE_INSTALL_PREFIX})
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")
message("CMAKE_INSTALL_PREFIX: " ${CMAKE_INSTALL_PREFIX})

set(BUILD_TYPE "@4$2*Sample333.apk")
message("BUILD_TYPE: " ${BUILD_TYPE})

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
    if(BUILD_TYPE)
        message("1,build bype")
        string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
            CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
    else()
        set(CMAKE_INSTALL_CONFIG_NAME "")
    endif()

    message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
    if(COMPONENT)
        message(STATUS "Install component: \"${COMPONENT}\"")
        set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
    else()
        set(CMAKE_INSTALL_COMPONENT)
    endif()
endif()

message("CMAKE_INSTALL_COMPONENT: " ${CMAKE_INSTALL_COMPONENT})

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
    set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
    set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
    set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if(CMAKE_INSTALL_COMPONENT)
    set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
    set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

message("CMAKE_INSTALL_MANIFEST: " ${CMAKE_INSTALL_MANIFEST})

set(CMAKE_INSTALL_MANIFEST_CONTENT "这是版本信息,20230214")
message("CMAKE_INSTALL_MANIFEST_CONTENT: " ${CMAKE_INSTALL_MANIFEST_CONTENT})

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
    "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE ${CMAKE_INSTALL_MANIFEST} "333333333333333333334444444444")
