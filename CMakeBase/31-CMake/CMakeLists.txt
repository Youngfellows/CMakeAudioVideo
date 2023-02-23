# cmake 最低版本要求,不加入此行会受到警告信息
cmake_minimum_required(VERSION 3.15.0)

# 项目名称为 Sample
project(Sample)
message(STATUS "PROJECT_NAME: ${PROJECT_NAME}")

message(STATUS "============== 路径转换(Path Conversion) =================")
message(STATUS "============== 转换为绝对路径 =================")

#[[
1. 转换为绝对路径
    file(REAL_PATH <path> <out-var> [BASE_DIRECTORY <dir>])
将相对路径 <path> 转换为 绝对路径，并存储在变量 <out-var> 中。
绝对路径是基于 <dir> 进行计算，默认情况下为 CMAKE_CURRENT_SOURCE_DIR。

若路径 <path> 为绝对路径，那么返回就是该绝对路径。
请注意，<path> 仅用来计算路径，与文件是否存在，是否为链接文件无关。

例，
    file(REAL_PATH main.cpp REAL_PATH_VAR)
    file(REAL_PATH C:\\CMake\\example\\main.cpp REAL_PATH_VAR)
]]
file(REAL_PATH main.java realPath)
message(STATUS "REAL_PATH:${realPath}")
file(REAL_PATH C:\\CMake\\example\\main.cpp realPath)
message(STATUS "REAL_PATH:${realPath}")

message(STATUS "============== 转换为相对路径 =================")

#[[
1.2 转换为相对路径
    file(RELATIVE_PATH <out-var> <directory> <file>)
计算从目录 <directory> 到 文件 <file> 的相对路径，并存储在变量 <out-var> 中。

例，
    file(RELATIVE_PATH RELATIVE_PATH_VAR C:\\CMake\\example C:\\CMake\\example\\main.cpp)
]]
file(RELATIVE_PATH relativePath "${CMAKE_SOURCE_DIR}/src/java/com/tiffany/cmake" "${CMAKE_SOURCE_DIR}/main.java")
message(STATUS "RELATIVE_PATH:${relativePath}")

message(STATUS "============= CMake 路径 与 本机 路径 风格之间的转换 =============")

#[[
1.3 CMake 路径 与 本机 路径 风格之间的转换
    file(TO_CMAKE_PATH <path> <out-var>)
    file(TO_NATIVE_PATH <path> <out-var>)

CMake 风格的路径与 Linux 风格路径是一样的用正斜杠 '/'，而 Windows 风格路径是用反斜杠 '\'。
我们有些见需要将各种平台的路径统一风格，那么使用 TO_CMAKE_PATH 模式，将路径 <path> 转换为 CMake 风格的路径。
也可以使用 TO_NATIVE_PATH 模式，将路径 <path> 根部不同的操作系统，转换为特定平台的本机路径。

例，演示 CMake 风格的路径 和 Windows 风格的路径
    set(FILE_PATH C:\\CMake\\example\\main.cpp)
    message(${FILE_PATH})
    file(TO_CMAKE_PATH ${FILE_PATH} CMAKE_FILE_PATH)
    message("CMake Style: ${CMAKE_FILE_PATH}")
    file(TO_NATIVE_PATH "${FILE_PATH}" NATIVE_FILE_PATH)
    message("Native Style: ${NATIVE_FILE_PATH}")
]]
set(filePath "C:\\CMake\\example\\main.cpp")
message(STATUS "filePath:${filePath}")
file(TO_CMAKE_PATH ${filePath} cmakeFilePath)
message(STATUS "CMake Style,cmakeFilePath:${cmakeFilePath}")
file(TO_NATIVE_PATH ${filePath} nativeFilePath)
message(STATUS "Native Style,nativeFilePath:${nativeFilePath}")

#[[
1.4 上传和下载(Transfer)
    file(DOWNLOAD <url> [<file>] [<options>...])
    file(UPLOAD   <file> <url> [<options>...])

DOWNLOAD 子命令将 <url> 下载到本地 <file>。如果未指定保存文件 <file>，则不保存文件，用于检查文件是否可下载，这很有用。将文件下载到 CMAKE_CURRENT_BINARY_DIR 目录。
UPLOAD 子命令将本地 <file> 文件上传到 <url>。

DOWNLOAD 和 UPLOAD 的选项 <options> 为:
    INACTIVITY_TIMEOUT <seconds>: 在一段时间不活动后终止操作。
    LOG <variable>: 将操作存储在日志中。
    SHOW_PROGRESS: 打印进度信息。
    STATUS <variable>: 将操作的结果状态存储在变量中。
    TIMEOUT <seconds>: 超时后终止操作。
    USERPWD <username>:<password>: 设置用户和密码。
    HTTPHEADER <HTTP-header>: 用于操作的 HTTP 头。子选项可以重复多次。
    NETRC <level>: 指定是否使用 .netrc 文件进行操作。如果未指定此选项，则将使用 CMAKE_NETRC 变量的值。有效级别为：
        IGNORED: .netrc 文件被忽略。 这是默认设置。
        OPTIONAL: .netrc 文件是可选的，URL 中的信息是首选。 将扫描文件以查找 URL 中未指定的信息。
        REQUIRED: .netrc 文件是必需的，URL 中的信息将被忽略。
    NETRC_FILE <file>: 如果 NETRC 级别为 OPTIONAL 或 REQUIRED，则指定替代 .netrc 文件到您的主目录中的文件。 如果未指定此选项，则将使用 CMAKE_NETRC_FILE 变量的值。如果没有给出 NETRC 选项，CMake 将分别检查变量 CMAKE_NETRC 和 CMAKE_NETRC_FILE。
    TLS_VERIFY <ON|OFF>: 指定是否验证 https://URLs 的服务器证书。 默认是不验证。
    TLS_CAINFO <file>: 为 https://URLs 指定自定义证书颁发机构文件。
    对于 https://URLs，CMake 必须使用 OpenSSL 支持构建。 默认情况下不检查 TLS/SSL 证书。将 TLS_VERIFY 设置为 ON 以检查证书。如果没有给出 TLS 选项，CMake 将分别检查变量 CMAKE_TLS_VERIFY 和 CMAKE_TLS_CAINFO。

DOWNLOAD 其他选项:
    EXPECTED_HASH ALGO=<value>: 验证下载的内容哈希是否与预期值匹配，其中 ALGO 是 file(<HASH>) 支持的算法之一。如果不匹配，操作将失败并显示错误。如果没有给 DOWNLOAD 一个 <file>，那么指定这个是错误的。
    EXPECTED_MD5 <value>: 是 EXPECTED_HASH MD5=<value> 的简写。 如果没有给 DOWNLOAD 一个 <file>，那么指定这个是错误的。
]]

#[[
1.5 文件锁(Locking)
file(LOCK <path> [DIRECTORY] [RELEASE]
     [GUARD <FUNCTION|FILE|PROCESS>]
     [RESULT_VARIABLE <variable>]
     [TIMEOUT <seconds>])

可以锁定文件或目录。锁定由 <path> 指定的文件，若指定 DIRECTORY 选项，锁定 <path>/cmake.lock 文件。
文件锁定范围由 GUARD 选项定义，默认值为 PROCESS。
RELEASE 选项可用于显式解锁文件。
若想设置等锁定的超时时间，指定 TIMEOUT 选项。如果 TIMEOUT 设置为 0 锁定将尝试一次并立即报告结果。如果 TIMEOUT 不是 0，CMake 将尝试在 <seconds> 值指定的时间段内锁定文件。若未指定 TIMEOUT 选项，CMake 将等待锁定成功或发生致命错误。
若想保存返回结果，指定 RESULT_VARIABLE 选项，将结果将存储在 <variable> 变量中，成功时为 0，失败时为错误消息。若未指定 RESULT_VARIABLE 选项，任何错误都将被解释为致命错误。

请注意，锁是建议性的。不能保证其他进程会尊重这个锁，即锁同步两个或多个共享一些可修改资源的 CMake 实例。应用于 DIRECTORY 选项的类似逻辑，锁定父目录不会阻止其他 LOCK 命令锁定任何子目录或文件。

不允许尝试锁定文件两次。如果它们不存在，任何中间目录和文件本身将被创建。在 RELEASE 操作中忽略 GUARD 和 TIMEOUT 选项。
]]
