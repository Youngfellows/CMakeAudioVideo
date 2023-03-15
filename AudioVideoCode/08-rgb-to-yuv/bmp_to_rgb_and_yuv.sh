#! /bin/bash

# 获得shell脚本所在的绝对路径
PROJ_ROOT=$(cd $(dirname $0); pwd)
#PROJ_ROOT=$PWD
BUILD_ROOT=${PROJ_ROOT}
echo "build root: ${BUILD_ROOT}"

# 获得shell脚本所在目录的父级目录的绝对路径
PARENT_ROOT=$(cd $(dirname $0); cd ..; pwd)
echo "parent root:${PARENT_ROOT}"

# 设置resource目录
RESOURCE_DIR=${BUILD_ROOT}/res
if [ -e ${RESOURCE_DIR} ]; then
    echo "rm -rf ${RESOURCE_DIR}"
    rm -rf ${RESOURCE_DIR}
fi
mkdir -p ${RESOURCE_DIR}

# 获取rainbow-700x700.bmp图片路径
BMP_FILE_NAME="rainbow-700x700.bmp"
SRC_BMP_FILE_PATH=${PARENT_ROOT}/03_rgb_to_bmp/resource/${BMP_FILE_NAME}
echo "bitmap file path:${SRC_BMP_FILE_PATH}"

# 判断文件是否存在
if [[ ! -e ${SRC_BMP_FILE_PATH} ]]; then
    echo "Error: file does not exist: ${SRC_BMP_FILE_PATH}"
    exit 1
fi

# 拷贝文件到res目录
BMP_FILE_PATH=${RESOURCE_DIR}/${BMP_FILE_NAME}
cp ${SRC_BMP_FILE_PATH} ${BMP_FILE_PATH}

# 使用ffmpeg命令,把bmp转化为rgb24和yuv444
# ffmpeg -i ./res/rainbow-700x700.bmp -video_size 711x711 -pix_fmt rgb24 ./res/rainbow-bmp-rgb24.rgb
# ffmpeg -i ./res/rainbow-700x700.bmp -video_size 711x711 -pix_fmt yuv444p ./res/rainbow-bmp-yuv444p.yuv
RGB24_FILE_PATH=${RESOURCE_DIR}/rainbow-bmp-rgb24.rgb
YUV444_FILE_PATH=${RESOURCE_DIR}/rainbow-bmp-yuv444p.yuv
YUV420_FILE_PATH=${RESOURCE_DIR}/rainbow-bmp-yuv420p.yuv
ffmpeg -i ${BMP_FILE_PATH} -video_size 711x711 -pix_fmt rgb24 ${RGB24_FILE_PATH}
ffmpeg -i ${BMP_FILE_PATH} -video_size 711x711 -pix_fmt yuv444p ${YUV444_FILE_PATH}
ffmpeg -i ${BMP_FILE_PATH} -video_size 711x711 -pix_fmt yuv420p ${YUV420_FILE_PATH}

# 判断cpu架构
ARCH=`arch`
if [[ $ARCH =~ "x86_64" ]];then
    echo "ARCH is x86_64"
elif [[ $ARCH =~ "aarch64" ]];then
    echo "ARCH is arm64"
elif [[ $ARCH =~ "mips64" ]];then
    echo "ARCH is mips64"
else
    echo "Unknown ARCH!!"
fi




