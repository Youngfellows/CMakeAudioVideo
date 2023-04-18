#! /bin/bash

PROJ_ROOT=$PWD
BUILD_ROOT=$PROJ_ROOT
echo "build root: $BUILD_ROOT"

# 设置安装目录
LIBRARY_NAME=libjpeg-turbo
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
MY_SOURCE_DIR=$PROJ_ROOT

#  CMake 环境变量
export PATH=/mnt/d/LinuxEnvironment/cmake-3.12.1-Linux-x86_64/bin:$PATH

# NDK编译环境
# export NDK_PATH=/mnt/d/LinuxEnvironment/android-ndk-r25c-linux/android-ndk-r25c
export NDK_PATH=/mnt/d/LinuxEnvironment/android-ndk-r16b-linux-x86_64/android-ndk-r16b
export PATH=$NDK_PATH:$PATH
TOOLCHAIN_GCC=gcc
# TOOLCHAIN_GXX=gxx
# TOOLCHAIN_CLANG=clang

TOOLCHAIN=$TOOLCHAIN_GCC
ANDROID_VERSION=21

build-android()
{
    echo "-------------------star build $2-------------------------"
    # 编译cpu架构
    ARCH=$1
    # ARCH_ABI=armeabi-v7a
    ARCH_ABI=$2
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
    # cmake -G"Unix Makefiles" \
    # -DANDROID_ABI=$ARCH_ABI \
    # -DANDROID_ARM_MODE=$ARCH \
    # -DANDROID_PLATFORM=android-${ANDROID_VERSION} \
    # -DANDROID_TOOLCHAIN=${TOOLCHAIN} \
    # -DCMAKE_ASM_FLAGS="--target=arm-linux-androideabi${ANDROID_VERSION}" \
    # -DCMAKE_TOOLCHAIN_FILE=${NDK_PATH}/build/cmake/android.toolchain.cmake \
    # -DCMAKE_INSTALL_PREFIX=${PREFIX} \
    # [additional CMake flags] $MY_SOURCE_DIR
    
    # 开始编译
    cmake \
    -DCMAKE_TOOLCHAIN_FILE=$NDK_PATH/build/cmake/android.toolchain.cmake \
    -DANDROID_ABI=$ARCH_ABI  \
    -DANDROID_NDK=$NDK_PATH \
    -DANDROID_NATIVE_API_LEVEL=$ANDROID_VERSION \
    -DASSIMP_BUILD_TESTS=OFF \
    -DASSIMP_NO_EXPORT=TRUE \
    -DANDROID_TOOLCHAIN=${TOOLCHAIN} \
    -DCMAKE_INSTALL_PREFIX=${PREFIX} \
    -DBUILD_SHARED_LIBS=1 $MY_SOURCE_DIR
    
    # 注意：
    #  $NDK_ROOT为配置的环境变量指向ndk的具体版本，编译前可自行配置
    # -DANDROID_ABI  执行交叉编译的库支持的cpu架构版本，常用的为 armeabi-v7a 和 arm64-v8a
    # -DANDROID_NATIVE_API_LEVEL  执行交叉编译的库支持的最低android版本
    # -DBUILD_SHARED_LIBS 1和0分别表示生成动态库和静态库
    
    make clean
    make -j4
    make install
    cd -
    echo "当前目录:$PWD"
    echo "-------------------$2 build end -------------------------"
}

# 编译android各个平台运行库
build-android arm armeabi
build-android arm armeabi-v7a
build-android arm arm64-v8a
build-android x86 x86
build-android x86_64 x86_64

