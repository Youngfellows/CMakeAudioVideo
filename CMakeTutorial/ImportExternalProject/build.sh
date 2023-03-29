#! /bin/bash

PROJ_ROOT=$PWD
BUILD_ROOT=$PROJ_ROOT
echo "build root: $BUILD_ROOT"

# 先删除旧的安装文件
if [ -e $BUILD_ROOT/install ] ;then
    echo "rm ${BUILD_ROOT}/install"
    rm -rf ${BUILD_ROOT}/install
fi

# mkdir的-p选项允许一次创建多层次的目录，而不是一次只创建单独的目录
if [ -e ${BUILD_ROOT}/build ]; then
    echo "rm ${BUILD_ROOT}/build"
    rm -rf ${BUILD_ROOT}/build
fi
mkdir -p $BUILD_ROOT/build
cd $BUILD_ROOT/build

cmake -DCMAKE_CXX_FLAGS=-g -DCMAKE_BUILD_TYPE=Release \
-DCMAKE_INSTALL_PREFIX:PATH=$BUILD_ROOT/install $PROJ_ROOT
make -j4 # 并行处理,cpu个数
make install
cd -

# 执行,先设置库文件路径
# export LD_LIBRARY_PATH=${PROJ_ROOT}/install/lib/math
# echo "LD_LIBRARY_PATH:${LD_LIBRARY_PATH}"
./install/bin/test_spdlog
