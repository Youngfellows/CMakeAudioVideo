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

# 依赖动态库的全路径
CURRENT_DIR=$(cd $(dirname $0); pwd)
echo "current dir: ${CURRENT_DIR}"
PARENT_DIR=$(cd $(dirname $CURRENT_DIR); pwd)
echo "parent dir: ${PARENT_DIR}"
LD_LIBRARY_PATH=${PARENT_DIR}/install/lib
echo "ld library path:${LD_LIBRARY_PATH}"

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
-DCMAKE_INSTALL_FULL_LIBDIR=${LD_LIBRARY_PATH} \
-DCMAKE_INSTALL_PREFIX:PATH=${PROJ_ROOT}/install $PROJ_ROOT
make -j4
make install
cd -

# 运行
# ${BUILD_ROOT}/install/jar/turbojpeg.jar