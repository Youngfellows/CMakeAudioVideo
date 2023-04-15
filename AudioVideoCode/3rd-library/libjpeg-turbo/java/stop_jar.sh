#! /bin/bash

# 终止jar包进程
SERVER_NAME="turbojpeg"
JAR_NAME=${SERVER_NAME}.jar

#查找进程
PID=$(ps -ef | grep ${JAR_NAME}= | grep -v grep | awk '{print $2}')

if [ ! $PID ]; then
    echo "process ${SERVER_NAME} not exit"
    exit
else
    echo "process id: $PID"
fi

#杀死进程
kill -9 ${PID}

#判断上一次命令执行的成功或者失败的状态。如果成功就是0，失败为1.
if [ $? -eq 0 ]; then
    echo "kill ${SERVER_NAME} success"
else
    echo "kill ${SERVER_NAME} fail"
fi