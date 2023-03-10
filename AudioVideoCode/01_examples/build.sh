#! /bin/bash

PROJ_ROOT=$PWD
BUILD_ROOT=${PROJ_ROOT}
echo "build root: ${BUILD_ROOT}"

# 设置build编译目录
BUILD_DIRECTORY=${BUILD_ROOT}/build
if [ -e ${BUILD_DIRECTORY} ]; then
    echo "rm -rf %{BUILD_DIRECTORY}"
    rm -rf ${BUILD_DIRECTORY}
fi
mkdir -p ${BUILD_DIRECTORY}
cd ${BUILD_DIRECTORY}

# 编译
cmake -DCMAKE_CXX_FLAGS=-g -DCMAKE_BUILD_TYPE=Release \
-DCMAKE_INSTALL_PREFIX:PATH=${PROJ_ROOT}/install $PROJ_ROOT
make -j4
make install
cd -

# 运行
# ${PROJ_ROOT}/install/bin/Sample
./install/bin/Sample


