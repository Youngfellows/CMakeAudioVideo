#! /bin/bash

PROJ_ROOT=$PWD
BUILD_ROOT=$PROJ_ROOT
echo "build root: $BUILD_ROOT"

# 设置安装目录
LIBRARY_NAME=easyarray
INSTALL_DIR=$BUILD_ROOT/dist/${LIBRARY_NAME}
if [ -e $INSTALL_DIR ] ;then
    echo "rm $INSTALL_DIR"
    rm -rf $INSTALL_DIR
fi

# 1. 先编译easy库文件
# mkdir的-p选项允许一次创建多层次的目录，而不是一次只创建单独的目录
BUILD_DIR=${BUILD_ROOT}/build
if [ -e ${BUILD_DIR} ]; then
    echo "rm ${BUILD_DIR}"
    rm -rf ${BUILD_DIR}
fi
mkdir -p $BUILD_DIR
# cd $BUILD_DIR

# 要编译库的CMakeLists.txt目录
EASY_ROOT=$PROJ_ROOT/src

#  CMake 环境变量
export PATH=/mnt/d/LinuxEnvironment/cmake-3.12.1-Linux-x86_64/bin:$PATH

# NDK编译环境
export NDK_PATH=/mnt/d/LinuxEnvironment/android-ndk-r25c-linux/android-ndk-r25c
export PATH=$NDK_PATH:$PATH
TOOLCHAIN_GCC=gcc
TOOLCHAIN_GXX=gxx
TOOLCHAIN_CLANG=clang

TOOLCHAIN=$TOOLCHAIN_GCC
ANDROID_VERSION=21

# 编译cpu架构
ARCH=arm
ARCH_ABI=armeabi-v7a
echo "arch:$ARCH"

# 动态库安装目录
PREFIX=$INSTALL_DIR/$ARCH_ABI
echo "arch install dir:$PREFIX"

# 编译目录
ARCH_BUILD_DIR=$BUILD_DIR/$ARCH_ABI
echo "arch build dir:$ARCH_BUILD_DIR"

# 进入到编译目录
mkdir -p $ARCH_BUILD_DIR
cd $ARCH_BUILD_DIR
echo "进入到编译目录:$PWD"

# 开始编译
cmake -G"Unix Makefiles" \
-DANDROID_ABI=$ARCH_ABI \
-DANDROID_ARM_MODE=$ARCH \
-DANDROID_PLATFORM=android-${ANDROID_VERSION} \
-DANDROID_TOOLCHAIN=${TOOLCHAIN} \
-DCMAKE_ASM_FLAGS="--target=arm-linux-androideabi${ANDROID_VERSION}" \
-DCMAKE_TOOLCHAIN_FILE=${NDK_PATH}/build/cmake/android.toolchain.cmake \
-DCMAKE_INSTALL_PREFIX=${PREFIX} \
[additional CMake flags] $EASY_ROOT

make clean
make -j4
make install
cd -
echo "当前目录:$PWD"