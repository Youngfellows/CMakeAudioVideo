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

# 设置Release目录
RELEASE_DIR=${BUILD_ROOT}/Release
if [ -e ${RELEASE_DIR} ]; then
    echo "rm -rf ${RELEASE_DIR}"
    rm -rf ${RELEASE_DIR}
fi
mkdir -p ${RELEASE_DIR}

# 设置build编译目录
BUILD_DIR=${BUILD_ROOT}/build
if [ -e ${BUILD_DIR} ]; then
    echo "rm -rf ${BUILD_DIR}"
    rm -rf ${BUILD_DIR}
fi
mkdir -p ${BUILD_DIR}
cd ${BUILD_DIR}

# 编译
#cmake -DCMAKE_CXX_FLAGS=-g -DCMAKE_BUILD_TYPE=Release \
cmake -DCMAKE_BUILD_TYPE=Release \
-DCMAKE_INSTALL_PREFIX:PATH=${RELEASE_DIR} $PROJ_ROOT
make -j4
make install
cd -

# 运行
${RELEASE_DIR}/bin/06-drawing-time-rainbow
${RELEASE_DIR}/bin/06-drawing-time-checkerboard
${RELEASE_DIR}/bin/06-drawing-time-gradient
${RELEASE_DIR}/bin/06-drawing-time-mandelbrot-set
${RELEASE_DIR}/bin/06-drawing-time-julia-set
${RELEASE_DIR}/bin/06-drawing-time-magnifying-glass
${RELEASE_DIR}/bin/06-drawing-time-swirl-effect
${RELEASE_DIR}/bin/06-drawing-time-frosted-glass-effect