#! /bin/bash

PROJ_ROOT=$PWD
BUILD_ROOT=${PROJ_ROOT}
echo "build root: ${BUILD_ROOT}"

# 设置Release目录
RELEASE_DIR=${BUILD_ROOT}/Release
if [ -e ${RELEASE_DIR} ]; then
    echo "rm -rf ${RELEASE_DIR}"
    rm -rf ${RELEASE_DIR}
fi
mkdir -p ${INSTALLRELEASE_DIR_DIR}

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
-DCMAKE_INSTALL_PREFIX:PATH=${RELEASE_DIR} $PROJ_ROOT
make -j4
make install
cd -

# 运行
# ./install/bin/Sample
# ${BUILD_ROOT}/install/bin/Sample
# ${BUILD_ROOT}/install/bin/DemoSizeof
# ${BUILD_ROOT}/install/bin/Demozlib

# 遍历指定目录下所有文件，包括子目录下的所有文件,并运行
BIN_DIR=${RELEASE_DIR}/bin
for name in $(find $BIN_DIR -type f -name "*"); do
    echo -e "\nrun::${name}"
    ${name}
done
