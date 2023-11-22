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
-DCMAKE_INSTALL_PREFIX:PATH=${PROJ_ROOT}/install $PROJ_ROOT
make -j4
make install
cd -

# 运行
# ${BUILD_ROOT}/install/bin/11-rgb-to-indexed-color-png
# ${BUILD_ROOT}/install/bin/11-rgb-to-true-color-png
BIN_DIR=${PROJ_ROOT}/install/bin
for name in $(find $BIN_DIR -type f -name "*"); do
    echo -e "\nrun::${name}"
    ${name} # 运行可执行文件
done
