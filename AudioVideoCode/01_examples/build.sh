#! /bin/bash

PROJ_ROOT=$PWD
BUILD_ROOT=$PROJ_ROOT
echo "build root: $BUILD_ROOT"

# 先删除旧的安装文件
if [ -e $BUILD_ROOT/dist ] ;then
    echo "rm ${BUILD_ROOT}/dist"
    rm -rf ${BUILD_ROOT}/dist
fi

# 1. 先编译easy库文件
# mkdir的-p选项允许一次创建多层次的目录，而不是一次只创建单独的目录
if [ -e ${BUILD_ROOT}/build ]; then
    echo "rm ${BUILD_ROOT}/build"
    rm -rf ${BUILD_ROOT}/build
fi
mkdir -p $BUILD_ROOT/build
cd $BUILD_ROOT/build

EASY_ROOT=$PROJ_ROOT/src

cmake -DCMAKE_CXX_FLAGS=-g -DCMAKE_BUILD_TYPE=Release \
-DCMAKE_INSTALL_PREFIX:PATH=$BUILD_ROOT/dist $EASY_ROOT
make -j4
make install
cd -

# 2. 再编译执行文件
if [ -e $BUILD_ROOT/test_sdk/build ]; then
    echo "rm $BUILD_ROOT/test_sdk/build"
    rm -rf $BUILD_ROOT/test_sdk/build
fi
mkdir -p $BUILD_ROOT/test_sdk/build
cd $BUILD_ROOT/test_sdk/build

cmake -DCMAKE_BUILD_TYPE=Release  \
-DCMAKE_INSTALL_PREFIX:PATH=$PROJ_ROOT/dist $PROJ_ROOT
make -j4
make install
cd -

# 3. 执行,先设置库文件路径
# export LD_LIBRARY_PATH={PROJ_ROOT}/install/lib/math:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH=${PROJ_ROOT}/dist/lib
echo "LD_LIBRARY_PATH:${LD_LIBRARY_PATH}"
./dist/bin/Sample
