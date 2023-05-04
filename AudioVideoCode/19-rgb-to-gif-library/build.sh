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
INSTALL_DIR=${BUILD_ROOT}/dist
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

# 设置so动态库查找路径
CURRENT_DIR=$(cd $(dirname $0); pwd)
echo "current dir: ${CURRENT_DIR}"
PARENT_DIR=$(cd $(dirname $CURRENT_DIR); pwd)
echo "parent dir: ${PARENT_DIR}"

# export LD_LIBRARY_PATH=${PARENT_DIR}/3rd/libjpeg-turbo/install/lib/
# echo "library path:${LD_LIBRARY_PATH}"

# 编译
cmake -DCMAKE_CXX_FLAGS=-g -DCMAKE_BUILD_TYPE=Release \
-DCMAKE_INSTALL_PREFIX:PATH=${INSTALL_DIR} $PROJ_ROOT
make -j4
make install
cd -

# 遍历指定目录下所有文件，包括子目录下的所有文件,并运行
# ${INSTALL_DIR}/bin/19-gif-to-rgb-library
# ${INSTALL_DIR}/bin/19-rgb-to-gif-library
BIN_DIR=${INSTALL_DIR}/bin/
for name in $(find $BIN_DIR -type f -name "*gif-to-rgb-library"); do
    echo "${name}"
    SAMPLE_GIF_TO_RGB=${name}
done

if [ -n ${SAMPLE_GIF_TO_RGB} ]
then
    echo -e "\nrun::${name}"
    # 执行19-gif-to-rgb-library
    ${SAMPLE_GIF_TO_RGB}
else
    echo "19-gif-to-rgb-library is null"
    exit 0
fi

for name in $(find $BIN_DIR -type f -name "*"); do
    if [[ ${name} != ${SAMPLE_GIF_TO_RGB} ]]
    then
        echo -e "\nrun::${name}"
        ${name} # 运行可执行文件,19-rgb-to-gif-library
    fi
done