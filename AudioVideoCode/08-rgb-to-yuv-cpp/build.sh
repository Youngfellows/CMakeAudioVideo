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
# ./install/bin/Sample
# ${BUILD_ROOT}/install/bin/Sample
# ${BUILD_ROOT}/install/bin/DemoSizeof
# ${BUILD_ROOT}/install/bin/Demozlib

# 遍历指定目录下所有文件，包括子目录下的所有文件,并运行
BIN_DIR=${PROJ_ROOT}/install/bin
WIDTH=711 #宽
HEIGHT=711 #高
# 1.成bmp文件
for name in $(find $BIN_DIR -type f -name "*SampleBmpRainbow"); do
    echo "${name}"
    SAMPLE_BMP_RAINBOW=${name}
done

#-n,检测字符串长度是否为0，不为0返回 true。
if [ -n ${SAMPLE_BMP_RAINBOW} ]
then
    echo -e "\nrun::${name}"
    # 执行SampleRGB24Rainbow生成RGB24文件
    ${SAMPLE_BMP_RAINBOW} ${WIDTH} ${HEIGHT} # 运行可执行文件,并传递参数
else
    echo "SampleBmpRainbow is null"
    # exit 0
fi

# 2.成rgb24文件
for name in $(find $BIN_DIR -type f -name "*SampleRGB24Rainbow"); do
    echo "${name}"
    SAMPLE_RGB24_RAINBOW=${name}
done

#-n,检测字符串长度是否为0，不为0返回 true。
if [ -n ${SAMPLE_RGB24_RAINBOW} ]
then
    echo -e "\nrun::${name}"
    # 执行SampleRGB24Rainbow生成RGB24文件
    ${SAMPLE_RGB24_RAINBOW} ${WIDTH} ${HEIGHT} # 运行可执行文件,并传递参数
else
    echo "SampleRGB24Rainbow is null"
    # exit 0
fi

# 3.拷贝rgb24到指定目录
for name in $(find $BIN_DIR -type f -name "*SampleRGB24"); do
    echo "${name}"
    SAMPLE_RGB24=${name}
done

if [ -n ${SAMPLE_RGB24} ]
then
    echo -e "\nrun::${name}"
    # 执行SampleRGB24Rainbow生成RGB24文件
    ${SAMPLE_RGB24} ${WIDTH} ${HEIGHT} # 运行可执行文件,并传递参数
else
    echo "SampleRGB24 is null"
    # exit 0
fi

# 3. 执行剩下的可执行文件
for name in $(find $BIN_DIR -type f -name "*"); do
    if [[ ${name} != ${SAMPLE_RGB24_RAINBOW} && ${name} != ${SAMPLE_RGB24} && ${name} != ${SAMPLE_BMP_RAINBOW} ]]
    then
        echo -e "\nrun::${name}"
        ${name} ${WIDTH} ${HEIGHT} # 运行可执行文件,并传递参数
    fi
done

