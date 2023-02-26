# cmake 最低版本要求,不加入此行会受到警告信息
cmake_minimum_required(VERSION 3.15.0)

# 项目名称为 Sample
project(Sample)
message(STATUS "PROJECT_NAME: " ${PROJECT_NAME})
message(STATUS "============== Cmake命令之cmake_host_system_information =================")

#[[
一、命令格式
    cmake_host_system_information(RESULT <variable> QUERY <key> ...)
    
查询CMake运行环境的系统信息，<key>指定待查询的信息，可以有多个，查询结果存放在<variable>中。
<key>可以是主机名称、内存信息、CPU信息等等，<key>的所有取值可以参考本文的第三章节更多细节。

<key>的取值如下：
    NUMBER_OF_LOGICAL_CORES：逻辑核心数量。
    NUMBER_OF_PHYSICAL_CORES：物理核心数量。
    HOSTNAME：主机名称。
    FQDN：主机域名全称。
    TOTAL_VIRTUAL_MEMORY：总虚拟内存，单位是M。
    AVAILABLE_VIRTUAL_MEMORY：可用虚拟内存，单位是M。
    TOTAL_PHYSICAL_MEMORY：总物理内存，单位是M。
    AVAILABLE_PHYSICAL_MEMORY：可用物理内存，单位是M。
    IS_64BIT：如果处理器是64位，查询结果为1。
    HAS_FPU：如果处理器拥有浮点处理单元，查询结果为1。
    HAS_MMX：如果处理器支持MMX指令集，查询结果为1。
    HAS_MMX_PLUS：如果处理器支持Ext. MMX指令集，查询结果为1。
    HAS_SSE：如果处理器支持SSE指令集，查询结果为1。
    HAS_SSE2：如果处理器支持SSE2指令集，查询结果为1。
    HAS_SSE_FP：如果处理器支持SSE FP指令集，查询结果为1。
    HAS_SSE_MMX：如果处理器支持SSE MMX指令集，查询结果为1。
    HAS_AMD_3DNOW：如果处理器支持3DNow指令集，查询结果为1。
    HAS_AMD_3DNOW_PLUS：如果处理器支持3DNow+指令集，查询结果为1。
    HAS_IA64：如果IA64处理器可以模拟X86，查询结果为1。
    HAS_SERIAL_NUMBER：如果处理器有序列号，查询结果为1。
    PROCESSOR_SERIAL_NUMBER：处理器序列号。
    PROCESSOR_NAME：可读的处理器全称。
    OS_NAME：操作系统名称，也就是uname -s的输出，三大操作系统对应的名称是Linux、Windows和Darwin（masOS），也可以通过CMAKE_HOST_SYSTEM_NAME变量获取。
    OS_RELEASE：操作系统子类型，例如Windows Professional。
    OS_VERSION：操作系统构建ID。
    OS_PLATFORM：处理器架构，Windows下可以通过PROCESSOR_ARCHITECTURE变量获取，Unix/Linux/macOS等平台可以通过uname -m或uname -p获取。也可以通过CMAKE_HOST_SYSTEM_PROCESSOR变量获取。
]]

cmake_host_system_information(RESULT var QUERY HOSTNAME)
message(STATUS "hostname: ${var}")

cmake_host_system_information(RESULT var QUERY NUMBER_OF_LOGICAL_CORES NUMBER_OF_PHYSICAL_CORES)
message(STATUS "cores: ${var}")

cmake_host_system_information(RESULT var QUERY TOTAL_VIRTUAL_MEMORY TOTAL_PHYSICAL_MEMORY)
message(STATUS "memory(MB): ${var}")

cmake_host_system_information(RESULT var QUERY PROCESSOR_NAME)
message(STATUS "processor name: ${var}")

cmake_host_system_information(RESULT var QUERY OS_NAME OS_RELEASE OS_VERSION OS_PLATFORM)
message(STATUS "os information: ${var}")


