#! /bin/bash

PROJ_ROOT=$PWD
BUILD_ROOT=$PROJ_ROOT
echo "build root: $BUILD_ROOT"


# 设置Release目录
RELEASE_DIR=${BUILD_ROOT}/Release_
if [ -e ${RELEASE_DIR} ]; then
    echo "rm -rf ${RELEASE_DIR}"
    rm -rf ${RELEASE_DIR}
fi
mkdir -p ${RELEASE_DIR}

# 1. 先编译easy库文件
# mkdir的-p选项允许一次创建多层次的目录，而不是一次只创建单独的目录
# 设置build编译目录
BUILD_DIR=${BUILD_ROOT}/build
if [ -e ${BUILD_DIR} ]; then
    echo "rm -rf ${BUILD_DIR}"
    rm -rf ${BUILD_DIR}
fi
mkdir -p ${BUILD_DIR}
cd ${BUILD_DIR}

# 要编译库的CMakeLists.txt目录
EASY_ROOT=$PROJ_ROOT/src
#cmake -DCMAKE_CXX_FLAGS=-g -DCMAKE_BUILD_TYPE=Release \
cmake -DCMAKE_BUILD_TYPE=Release \
-DCMAKE_INSTALL_PREFIX:PATH=${RELEASE_DIR} $EASY_ROOT
make clean
make -j4
make install
cd -

# 2. 再编译执行文件
TEST_BUILD_DIR=$BUILD_ROOT/test_sdk/build
if [ -e $TEST_BUILD_DIR ]; then
    echo "rm $TEST_BUILD_DIR"
    rm -rf $TEST_BUILD_DIR
fi
mkdir -p $TEST_BUILD_DIR
cd $TEST_BUILD_DIR

cmake -DCMAKE_BUILD_TYPE=Release  \
-DCMAKE_INSTALL_PREFIX:PATH=$RELEASE_DIR $PROJ_ROOT
make clean
make -j4
make install
cd -

# 3. 执行,先设置库文件路径
# export LD_LIBRARY_PATH={PROJ_ROOT}/install/lib/math:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH=${RELEASE_DIR}/lib
echo "LD_LIBRARY_PATH:${LD_LIBRARY_PATH}"
${RELEASE_DIR}/bin/Sample
