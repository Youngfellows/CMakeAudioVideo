#! /bin/bash

PROJ_ROOT=$PWD
BUILD_ROOT=${PROJ_ROOT}
echo "build root: ${BUILD_ROOT}"

# 设置build编译目录
BUILD_DIR=${BUILD_ROOT}/build
if [ -e ${BUILD_DIR} ]; then
    echo "rm -rf ${BUILD_DIR}"
    rm -rf ${BUILD_DIR}
fi
mkdir -p ${BUILD_DIR}
cd ${BUILD_DIR}

# 设置install目录
INSTALL_DIR=${BUILD_ROOT}/install
if [ -e ${INSTALL_DIR} ]; then
    echo "rm -rf ${INSTALL_DIR}"
    rm -rf ${INSTALL_DIR}
fi
mkdir -p ${INSTALL_DIR}

# 安装目录
LIBRARY_NAME=libjpeg-turbo
PREFIX=${PROJ_ROOT}/install/${LIBRARY_NAME}
# cmake -G"Unix Makefiles" -DCMAKE_INSTALL_PREFIX:PATH=./ -DCMAKE_INSTALL_BINDIR:PATH=./ -DCMAKE_INSTALL_DATAROOTDIR:PATH=./ -DCMAKE_INSTALL_DOCDIR:PATH=./ -DCMAKE_INSTALL_LIBDIR:PATH=./  -DCMAKE_INSTALL_INCLUDEDIR:PATH=./  -DCMAKE_INSTALL_MANDIR:PATH=./ ..

# 编译
cmake -G"Unix Makefiles" \
-DCMAKE_CXX_FLAGS=-g -DCMAKE_BUILD_TYPE=Release \
-DCMAKE_INSTALL_PREFIX:PATH=${PREFIX} $PROJ_ROOT
make -j4
make install
cd -