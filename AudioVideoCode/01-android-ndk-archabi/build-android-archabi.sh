#! /bin/bash

PROJ_ROOT=$PWD
BUILD_ROOT=${PROJ_ROOT}
echo "build root: ${BUILD_ROOT}"

# 根据BUILDING.md编译Android平台可运行的libjpeg-turbo库

# lib-name
MY_LIBS_NAME=libeasyarray

# 源码文件目录
# MY_SOURCE_DIR=/home/sharry/Desktop/libjpeg-turbo-master
MY_SOURCE_DIR=${PROJ_ROOT}/src

# 编译的过程中产生的中间件的存放目录，为了区分编译目录，源码目录，install目录
MY_BUILD_DIR=build

# 设置build编译目录
BUILD_DIR=${BUILD_ROOT}/${MY_BUILD_DIR}
if [ -e ${BUILD_DIR} ]; then
    echo "rm -rf ${BUILD_DIR}"
    rm -rf ${BUILD_DIR}
fi
mkdir -p ${BUILD_DIR}

# 设置dist最终生成安装目录
DIST_DIR=${BUILD_ROOT}/dist
if [ -e ${DIST_DIR} ]; then
    echo "rm -rf ${DIST_DIR}"
    rm -rf ${DIST_DIR}
fi
mkdir -p ${DIST_DIR}

#  CMake 环境变量
export PATH=/mnt/d/LinuxEnvironment/cmake-3.12.1-Linux-x86_64/bin:$PATH

# NDK环境变量
NDK_PATH=/mnt/d/LinuxEnvironment/android-ndk-r16b-linux-x86_64/android-ndk-r16b
BUILD_PLATFORM=linux-x86_64
TOOLCHAIN_VERSION=4.9
# ANDROID_VERSION=19
ANDROID_VERSION=21

ANDROID_ARMV5_CFLAGS="-march=armv5te"
ANDROID_ARMV7_CFLAGS="-march=armv7-a -mfloat-abi=softfp -mfpu=neon"  # -mfpu=vfpv3-d16  -fexceptions -frtti
ANDROID_ARMV8_CFLAGS="-march=armv8-a"   # -mfloat-abi=softfp -mfpu=neon -fexceptions -frtti
ANDROID_X86_CFLAGS="-march=i386 -mtune=intel -mssse3 -mfpmath=sse -m32"
ANDROID_X86_64_CFLAGS="-march=x86-64 -msse4.2 -mpopcnt -m64 -mtune=intel"

# 定义编译函数
# params($1:arch,$2:arch_abi,$3:host,$4:compiler,$5:cflags,$6:processor)
build_bin() {

    echo "-------------------star build $2-------------------------"

    ARCH=$1                # arm arm64 x86 x86_64
    ANDROID_ARCH_ABI=$2    # armeabi armeabi-v7a x86 mips
    # 最终编译的安装目录
    PREFIX=$(pwd)/dist/${MY_LIBS_NAME}/${ANDROID_ARCH_ABI}/
    HOST=$3
    COMPILER=$4
    PROCESSOR=$6
    SYSROOT=${NDK_PATH}/platforms/android-${ANDROID_VERSION}/arch-${ARCH}
    CFALGS="$5"
    TOOLCHAIN=${NDK_PATH}/toolchains/${HOST}-${TOOLCHAIN_VERSION}/prebuilt/${BUILD_PLATFORM}

    # build 中间件
    BUILD_DIR=./${MY_BUILD_DIR}/${ANDROID_ARCH_ABI}

    export CFLAGS="$5 -Os -D__ANDROID_API__=${ANDROID_VERSION} --sysroot=${SYSROOT} \
                   -isystem ${NDK_PATH}/sysroot/usr/include \
                   -isystem ${NDK_PATH}/sysroot/usr/include/${HOST} "
    export LDFLAGS=-pie

    echo "path==>$PATH"
    echo "build_dir==>$BUILD_DIR"
    echo "ARCH==>$ARCH"
    echo "ANDROID_ARCH_ABI==>$ANDROID_ARCH_ABI"
    echo "HOST==>$HOST"
    echo "CFALGS==>$CFALGS"
    echo "COMPILER==>$COMPILER-gcc"
    echo "CXX_COMPILER==>$COMPILER-g++"
    echo "PROCESSOR==>$PROCESSOR"

    mkdir -p ${BUILD_DIR}   #创建当前arch_abi的编译目录,比如:binary/armeabi-v7a
    cd ${BUILD_DIR}         #此处 进了当前arch_abi的2级编译目录

# 运行时创建临时编译链文件toolchain.cmake
cat >toolchain.cmake << EOF
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR $6)
set(CMAKE_C_COMPILER ${TOOLCHAIN}/bin/${COMPILER}-gcc)
set(CMAKE_CXX_COMPILER ${TOOLCHAIN}/bin/${COMPILER}-g++)
set(CMAKE_FIND_ROOT_PATH ${TOOLCHAIN}/${COMPILER})
EOF

    cmake -G"Unix Makefiles" \
          -DCMAKE_TOOLCHAIN_FILE=toolchain.cmake \
          -DCMAKE_POSITION_INDEPENDENT_CODE=1 \
          -DCMAKE_INSTALL_PREFIX=${PREFIX} \
          -DWITH_JPEG8=1 \
          ${MY_SOURCE_DIR}

    make clean
    make -j4
    make install

    #从当前arch_abi编译目录跳出，对应上面的cd ${BUILD_DIR},以便function多次执行
    cd ../../

    echo "-------------------$2 build end-------------------------"
}

# 调用编译函数并传递参数,参数2和参数6是一样的
# params($1:arch,$2:arch_abi,$3:host,$4:compiler,$5:cflags,$6:processor)
# ARCH=$1                # arm arm64 x86 x86_64
# ANDROID_ARCH_ABI=$2    # armeabi armeabi-v7a x86 mips mips64

# build android abi
build_bin arm arm arm-linux-androideabi arm-linux-androideabi "$ANDROID_ARMV7_CFLAGS" arm
# build_bin arm armeabi arm-linux-androideabi arm-linux-androideabi "$ANDROID_ARMV7_CFLAGS" armeabi
# build_bin arm armeabi-v7a arm-linux-androideabi arm-linux-androideabi "$ANDROID_ARMV7_CFLAGS" armeabi-v7a
# build_bin arm64 arm64-v8a aarch64-linux-android aarch64-linux-android "$ANDROID_ARMV8_CFLAGS" arm64-v8a
# build_bin x86 x86 x86 i686-linux-android "$ANDROID_X86_CFLAGS" x86
# build_bin x86_64 x86_64 x86_64 x86_64-linux-android "$ANDROID_X86_64_CFLAGS" x86_64