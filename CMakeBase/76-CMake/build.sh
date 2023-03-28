#! /bin/bash

PROJ_ROOT=$PWD
BUILD_ROOT=$PROJ_ROOT
echo "build root: $BUILD_ROOT"

# 先删除旧的安装文件
if [ -e $BUILD_ROOT/install ] ;then
    echo "rm ${BUILD_ROOT}/install"
    rm -rf ${BUILD_ROOT}/install
fi

# if [ -e $BUILD_ROOT/sdk_install ] ;then
#     echo "rm ${BUILD_ROOT}/sdk_install"
#     rm -rf ${BUILD_ROOT}/sdk_install
# fi

# 1. 先编译Math库文件
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
make install #> ${BUILD_ROOT}/build/math_oper1.txt
cd -

# 2. 再编译执行文件
if [ -e $BUILD_ROOT/test_sdk/build ]; then
    echo "rm $BUILD_ROOT/test_sdk/build"
    rm -rf $BUILD_ROOT/test_sdk/build
fi
mkdir -p $BUILD_ROOT/test_sdk/build
cd $BUILD_ROOT/test_sdk/build
cmake -DCMAKE_BUILD_TYPE=Release  \
-DSDK_INSTALL_PATH=$BUILD_ROOT/install \
-DUSE_FFMPEG=ON \
-DCMAKE_INSTALL_PREFIX:PATH=$PROJ_ROOT/install $PROJ_ROOT/src
make -j4
make install
cd -

# 3. 执行,先设置库文件路径
# export LD_LIBRARY_PATH={PROJ_ROOT}/install/lib/math:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH=${PROJ_ROOT}/install/lib/math
echo "LD_LIBRARY_PATH:${LD_LIBRARY_PATH}"
./install/bin/MathSdkSample 2 3
