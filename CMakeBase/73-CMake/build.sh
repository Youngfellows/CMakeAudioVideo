#! /bin/bash 

# set -e # Exit immediately if a command exits with a non-zero status

PROJ_ROOT=$PWD
BUILD_ROOT=$PROJ_ROOT
echo "build root: $BUILD_ROOT"

if [ "$1" == "--no-test" ]; then
	NO_TEST=1
else
	NO_TEST=0
fi

echo "no test: $NO_TEST"

# 先删除旧的安装文件
if [ -e $BUILD_ROOT/install ] ;then
	echo "rm ${BUILD_ROOT}/install"
	rm -rf ${BUILD_ROOT}/install
fi

if [ -e $BUILD_ROOT/test_sdk_install ] ;then
	echo "rm ${BUILD_ROOT}/test_sdk_install"
	rm -rf ${BUILD_ROOT}/test_sdk_install
fi


# 1. 先编译库文件
# mkdir的-p选项允许一次创建多层次的目录，而不是一次只创建单独的目录
if [ -e $BUILD_ROOT/build ]; then
    echo "rm $BUILD_ROOT/build"
	rm -rf $BUILD_ROOT/build
fi
mkdir -p $BUILD_ROOT/build
cd $BUILD_ROOT/build
cmake -DCMAKE_CXX_FLAGS=-g -DCMAKE_BUILD_TYPE=Release \
	-DCMAKE_INSTALL_PREFIX:PATH=$BUILD_ROOT/install $PROJ_ROOT
make -j4 # 并行处理,cpu个数
make install #> ${BUILD_ROOT}/build/math_oper1.txt

cd -

echo "============ 再编译执行文件 ==============="

# 2. 再编译执行文件
if [ -e $BUILD_ROOT/test_sdk/build ]; then
    echo "rm $BUILD_ROOT/test_sdk/build"
	rm -rf $BUILD_ROOT/test_sdk/build
fi
mkdir -p $BUILD_ROOT/test_sdk/build
cd $BUILD_ROOT/test_sdk/build
cmake -DCMAKE_BUILD_TYPE=Release -DNO_TESTBENCH=$NO_TEST \
	-DSDK_INSTALL_PATH=$BUILD_ROOT/install \
	-DCMAKE_INSTALL_PREFIX:PATH=$PROJ_ROOT/test_sdk_install $PROJ_ROOT/test_sdk
make -j4
make install #> ${BUILD_ROOT}/build/math_oper2.txt

cd -

# 3. 执行
export LD_LIBRARY_PATH=install/lib
./test_sdk_install/bin/Sample 5 2
