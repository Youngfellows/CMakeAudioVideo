# cmake 最低版本要求,不加入此行会受到警告信息
cmake_minimum_required(VERSION 3.15.0)

# 项目名称为 Sample
project(Sample)
message(STATUS "PROJECT_NAME: ${PROJECT_NAME}")
message(STATUS "========== 归档(Archiving) ============")

message(STATUS "=========== 创建归档 ==============")

# 归档(Archiving)
# 1. 创建归档
# file(ARCHIVE_CREATE OUTPUT <archive>
# PATHS <paths>...
# [FORMAT <format>]
# [COMPRESSION <compression> [COMPRESSION_LEVEL <compression-level>]]
# [MTIME <mtime>]
# [VERBOSE])

#[[
根据 <paths> 中的文件或目录 创建归档文件 <archive>。FORMAT 指定归档格式，支持的值为 7zip、gnutar、pax、paxr、raw 和 zip，默认格式为 paxr。

例，将 目录 include, 目录 src, 文件 main.cpp 归档为 out.zip。
file(ARCHIVE_CREATE OUTPUT out.zip
	PATHS ${CMAKE_CURRENT_SOURCE_DIR}/src ${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
	FORMAT zip
)
请注意，<paths> 需要是绝对路径。
某些存档格式允许指定压缩类型。7zip 和 zip 允许压缩类型，可以使用 COMPRESSION 选项指示这样做。<compression> 的有效值为
None、BZip2、GZip、XZ 和 Zstd。使用 COMPRESSION_LEVEL 选项指定压缩级别。<compression-level> 应该在 0-9 之间，默认值为 0。当给出 COMPRESSION_LEVEL 时必须存在 COMPRESSION 选项。
VERBOSE 选项为归档操作启用详细输出。
要指定记录在 tarball 条目中的修改时间，请使用 MTIME 选项。
]]
set(outArchiving "${CMAKE_CURRENT_SOURCE_DIR}/myArchiving.zip")
file(ARCHIVE_CREATE OUTPUT ${outArchiving}
    PATHS ${CMAKE_CURRENT_SOURCE_DIR}/src ${CMAKE_CURRENT_SOURCE_DIR}/file ${CMAKE_CURRENT_SOURCE_DIR}/math ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    FORMAT zip
)

#[[
2.提取归档
file(ARCHIVE_EXTRACT INPUT <archive>
  [DESTINATION <dir>]
  [PATTERNS <patterns>...]
  [LIST_ONLY]
  [VERBOSE])

提取归档文件 <archive>，并输出到 DESTINATION 目录中，如果目录不存在，它将被创建，默认情况下输出目录为 CMAKE_CURRENT_BINARY_DIR。

例，提取归档文件 out.zip
    file(ARCHIVE_EXTRACT INPUT out.zip)

请注意，<archive> 默认所在目录在 CMAKE_CURRENT_BINARY_DIR。
如果需要，您可以使用指定的 <patterns> 选择要列出或从存档中提取的文件和目录。支持通配符。 如果未给出 PATTERNS 选项，则将列出或提取整个存档。
LIST_ONLY 将列出存档中的文件而不是提取它们。
使用 VERBOSE，该命令将产生详细输出。
]]
set(fileName "${CMAKE_CURRENT_SOURCE_DIR}/myArchiving.zip")
file(ARCHIVE_EXTRACT INPUT ${fileName} DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/myArchiving PATTERNS *.cpp LIST_ONLY VERBOSE)