#! /bin/bash

PROJ_ROOT=$PWD
BUILD_ROOT=${PROJ_ROOT}
echo "build root: ${BUILD_ROOT}"

# 设置resource目录
RESOURCE_DIR=${BUILD_ROOT}/resource
if [ -e ${RESOURCE_DIR} ]; then
    echo "rm -rf ${RESOURCE_DIR}"
    rm -rf ${RESOURCE_DIR}
fi
mkdir -p ${RESOURCE_DIR}

# 设置install目录
INSTALL_DIR=${BUILD_ROOT}/install
if [ -e ${INSTALL_DIR} ]; then
    echo "rm -rf ${INSTALL_DIR}"
    rm -rf ${INSTALL_DIR}
fi
mkdir -p ${INSTALL_DIR}

# 设置build编译目录
BUILD_DIR=${BUILD_ROOT}/build
if [ -e ${BUILD_DIR} ]; then
    echo "rm -rf ${BUILD_DIR}"
    rm -rf ${BUILD_DIR}
fi
mkdir -p ${BUILD_DIR}
cd ${BUILD_DIR}

# 编译
cmake -DCMAKE_CXX_FLAGS=-g -DCMAKE_BUILD_TYPE=Release \
-DUSE_FFMPEG=OFF \
-DUSE_IPP=OFF \
-DCMAKE_INSTALL_PREFIX:PATH=${PROJ_ROOT}/install $PROJ_ROOT
make -j4
make install
cd -

# 运行
:<<!
Usage : test yuv2rgb <yuv image file> <image width> <image height> <output template filename>
Or    : test yuv2rgb_nv12 <yuv image file> <image width> <image height> <output template filename>
Or    : test yuv2rgb_nv21 <yuv image file> <image width> <image height> <output template filename>
Or    : test rgb2yuv <rgb24 binary ppm image file> <output template filename>
Or    : test rgba2yuv <rgb24 binary ppm image file> <output template filename>
!
WIDTH=711
HEIGHT=711
${BUILD_ROOT}/install/bin/test_yuv_rgb rgb2yuv ${PROJ_ROOT}/data/test1.ppm ${RESOURCE_DIR}/test1_ppm_rgb24_to_yuv.yuv