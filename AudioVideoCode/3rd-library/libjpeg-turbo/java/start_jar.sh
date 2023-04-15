#! /bin/bash

# 开启jar包进程

# 获取当前目录
PROJ_ROOT=$PWD

# jar包名称
JAR_NAME="turbojpeg"

# -Xms: 设置初始化堆内存大小；
# -Xmx: 设置最大可分配堆内存大小
# MetaspaceSize:元空间默认大小
# MaxMetaspaceSize:元空间最大大小
# JVM参数配置
JVM_OPTS="-Xms128m -XX:MetaspaceSize=128M -Xmx128m -XX:MaxMetaspaceSize=512M -Dfile.encoding=utf-8"
LOG_HOME=${PROJ_ROOT}/install/logs

# 当前日期
TODAY=$(date -d "now" +"%Y-%m-%d")
# 日志文件路径
LOG_DIR=${LOG_HOME}/${JAR_NAME}/${TODAY}
if [ -e ${LOG_DIR} ]; then
    echo "exist log dir:${LOG_DIR}"
else
    echo "mkdir: ${LOG_DIR}"
    mkdir -p ${LOG_DIR}
fi
LOG_PATH="${LOG_DIR}/com.turbojpeg-debug.log"
echo "log path:${LOG_PATH}"

# 配置文件环境
ACTIVE="test"
# 脚本绝对路径
SCRIPT_DIR="$( cd -P "$( dirname "$SOURCE" )" && pwd )"
echo "src dir:${SCRIPT_DIR}"

# jar包绝对路径
JAR_PATH=${SCRIPT_DIR}/install/jar/${JAR_NAME}.jar
if [ -e ${JAR_PATH} ]; then
    echo "${JAR_NAME}.jar exist:${JAR_PATH}"
else
    echo "${JAR_NAME}.jar not exist:${JAR_PATH}"
    exit 0
fi
echo start ${JAR_NAME} ..


CURRENT_DIR=$(cd $(dirname $0); pwd)
echo "current dir: ${CURRENT_DIR}"
PARENT_DIR=$(cd $(dirname $CURRENT_DIR); pwd)
echo "parent dir: ${PARENT_DIR}"

# 启动jar包 + 指定配置文件环境 +读取启动日志+后台启动
# nohup java ${JVM_OPTS} -jar ${JAR_PATH} --spring.profiles.active=${ACTIVE}>${LOG_PATH} 2>&1 & tail -200f ${LOG_PATH}
# echo 'start successful'

# 设置so动态库查找路径
# export LD_LIBRARY_PATH=${PARENT_DIR}/install/lib/libturbojpeg.so
export LD_LIBRARY_PATH=${PARENT_DIR}/install/lib/
echo "library path:${LD_LIBRARY_PATH}"

# 启动jar包 + 指定配置文件环境 +读取启动日志+后台启动
nohup java ${JVM_OPTS} -Djava.ext.dirs=${LD_LIBRARY_PATH} -jar ${JAR_PATH} --spring.profiles.active=${ACTIVE}>${LOG_PATH} 2>&1 & tail -200f ${LOG_PATH}
echo 'start successful'