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

# # 2. 再编译执行文件
# if [ -e $BUILD_ROOT/test_sdk/build ]; then
#     echo "rm $BUILD_ROOT/test_sdk/build"
#     rm -rf $BUILD_ROOT/test_sdk/build
# fi
# mkdir -p $BUILD_ROOT/test_sdk/build
# cd $BUILD_ROOT/test_sdk/build

# cmake -DCMAKE_BUILD_TYPE=Release  \
# -DCMAKE_INSTALL_PREFIX:PATH=$PROJ_ROOT/dist $PROJ_ROOT
# make clean
# make -j4
# make install
# cd -

# # 3. 执行,先设置库文件路径
# # export LD_LIBRARY_PATH={PROJ_ROOT}/install/lib/math:$LD_LIBRARY_PATH
# export LD_LIBRARY_PATH=${PROJ_ROOT}/dist/lib
# echo "LD_LIBRARY_PATH:${LD_LIBRARY_PATH}"
# ./dist/bin/Sample
