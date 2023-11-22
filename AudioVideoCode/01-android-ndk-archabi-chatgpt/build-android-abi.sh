#! /bin/bash

PROJ_ROOT=$PWD
BUILD_ROOT=$PROJ_ROOT
echo "build root: $BUILD_ROOT"

# 设置Release目录
RELEASE_DIR=${BUILD_ROOT}/Release
if [ -e ${RELEASE_DIR} ]; then
    echo "rm -rf ${RELEASE_DIR}"
    rm -rf ${RELEASE_DIR}
fi
mkdir -p ${RELEASE_DIR}

LIBRARY_NAME=easyarray
INSTALL_DIR=$RELEASE_DIR/${LIBRARY_NAME}

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

build-android()
{
    echo "-------------------star build $1-------------------------"
    
    #设置CPU架构
    ARCH=$1
    echo "arch:$ARCH"
    
    # 设置库安装目录
    PREFIX=$INSTALL_DIR/$ARCH
    echo "install path:$PREFIX"
    
    # 设置arch build目录
    ARCH_BUILD_DIR=$BUILD_DIR/$ARCH
    mkdir -p $ARCH_BUILD_DIR
    cd $ARCH_BUILD_DIR
    echo "build path:$ARCH_BUILD_DIR"
    
    cmake -DCMAKE_CXX_FLAGS=-g -DCMAKE_BUILD_TYPE=Release \
    -DANDROID_ABI=$ARCH \
    -DCMAKE_INSTALL_PREFIX:PATH=$PREFIX $EASY_ROOT
    make clean
    make -j4
    make install
    cd ../..
    echo "当前路径:$PWD"
    echo "-------------------$1 build end--------------------------"
}

# 编译android各个平台运行库
build-android armeabi-v7a
build-android arm64-v8a
build-android x86
build-android x86_64
