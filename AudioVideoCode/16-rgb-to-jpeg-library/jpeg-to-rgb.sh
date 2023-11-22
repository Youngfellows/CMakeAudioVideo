#! /bin/bash

# 获得shell脚本所在的绝对路径
PROJ_ROOT=$(cd $(dirname $0); pwd)
#PROJ_ROOT=$PWD
BUILD_ROOT=${PROJ_ROOT}
echo "build root: ${BUILD_ROOT}"

# 获得shell脚本所在目录的父级目录的绝对路径
PARENT_ROOT=$(cd $(dirname $0); cd ..; pwd)
echo "parent root:${PARENT_ROOT}"

# 设置jepg-resource目录
JPEG_RESOURCE_DIR=${BUILD_ROOT}/jepg-resource
if [ ! -e ${JPEG_RESOURCE_DIR} ]; then
    echo "not exist: ${JPEG_RESOURCE_DIR}"
    exist 0
fi

# 获取libjpeg-turbo-test-image.jpg图片路径
JPEG_FILE_NAME=libjpeg-turbo-test-image
JPEG_FILE_PATH=${PROJ_ROOT}/jepg-resource/${JPEG_FILE_NAME}.jpg
echo "JPEG file path:${JPEG_FILE_PATH}"

# 判断文件是否存在
if [[ ! -e ${JPEG_FILE_PATH} ]]; then
    echo "Error: file does not exist: ${JPEG_FILE_PATH}"
    exit 1
fi

# 使用ffmpeg命令,把JPEG转化为rgb24和yuv444
# ffmpeg -i Disney.png -video_size 700x700 -pix_fmt rgb24 Disney-rgb24.rgb
# ffmpeg -i meizi.jpg -video_size 1010x1324 -pix_fmt rgb24 meizi-rgb24.rgb
# ffmpeg -i Disney.png -video_size 700x700 -pix_fmt yuv444p Disney-yuv444p.yuv
# ffmpeg -i meizi.jpg -video_size 1010x1324 -pix_fmt yuv444p meizi-yuv444p.yuv
# ffmpeg -i meizi.jpg -video_size 1010x1324 -pix_fmt yuv420p meizi-yuv444p.yuv
#  ffmpeg -i .\libjpeg-turbo-test-image.jpg -video_size 1010x1324 -pix_fmt rgb24 meizi-rgb24.rgb
WIDTH=1010 # 图片宽
HEIGHT=1324 # 图片高
RGB24_FILE_PATH=${JPEG_RESOURCE_DIR}/ffmpeg-${JPEG_FILE_NAME}-rgb24.rgb
YUV444_FILE_PATH=${JPEG_RESOURCE_DIR}/ffmpeg-${JPEG_FILE_NAME}-yuv444p.yuv
YUV420_FILE_PATH=${JPEG_RESOURCE_DIR}/ffmpeg-${JPEG_FILE_NAME}-yuv420p.yuv
if [ -e ${RGB24_FILE_PATH} ]; then
    echo "rm:${RGB24_FILE_PATH}"
    rm ${RGB24_FILE_PATH}
fi
if [ -e ${YUV444_FILE_PATH} ]; then
    echo "rm:${YUV444_FILE_PATH}"
    rm ${YUV444_FILE_PATH}
fi
if [ -e ${YUV420_FILE_PATH} ]; then
    echo "rm:${YUV420_FILE_PATH}"
    rm ${YUV420_FILE_PATH}
fi
ffmpeg -i ${JPEG_FILE_PATH} -video_size ${WIDTH}x${HEIGHT} -pix_fmt rgb24 ${RGB24_FILE_PATH}
ffmpeg -i ${JPEG_FILE_PATH} -video_size ${WIDTH}x${HEIGHT} -pix_fmt yuv444p ${YUV444_FILE_PATH}
ffmpeg -i ${JPEG_FILE_PATH} -video_size ${WIDTH}x${HEIGHT} -pix_fmt yuv420p ${YUV420_FILE_PATH}

# 判断cpu架构
ARCH=`arch`
echo "arch is ${ARCH}"
if [[ $ARCH =~ "x86_64" ]];then
    echo "ARCH is x86_64"
    elif [[ $ARCH =~ "aarch64" ]];then
    echo "ARCH is arm64"
    elif [[ $ARCH =~ "mips64" ]];then
    echo "ARCH is mips64"
else
    echo "Unknown ARCH!!"
fi




