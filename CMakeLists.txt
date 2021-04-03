# 指定最低版本
cmake_minimum_required(VERSION 2.8)

# 指定项目名称
project(CrossPlatformUtils)

# 设置C++编译参数(CMAKE_CXX_FLAGS是全局变量)
# set(CMAKE_CXX_FLAGS "-Wall -Wextra -fPIC -g")

# 指定为C++11 版本
set(CMAKE_CXX_STANDARD 11)
# set(CMAKE_CXX_STANDARD 14)

if (MSVC)
    # warning level 4 and all warnings as errors
    add_compile_options(/W4 /WX)
else()
    # lots of warnings and all warnings as errors
    add_compile_options(-Wall -Wextra -pedantic -Werror -fPIC)
endif()

# 把src目录下所有源文件写入变量DIR_SRCS
aux_source_directory(./ DIR_SRCS)

# 以DIR_SRCS为源文件生成目标文件
#add_executable(cross_platform_utils ${DIR_SRCS})

# 创建库文件
#add_library(cross_platform_utils SHARED ${DIR_SRCS})

# 生成动态库目标
add_library(cross_platform_utils SHARED ${DIR_SRCS})
# 生成静态库目标
add_library(cross_platform_utils_static STATIC ${DIR_SRCS})
 
# 指定静态库的输出名称
set_target_properties(cross_platform_utils_static PROPERTIES OUTPUT_NAME "cross_platform_utils")
# 使动态库和静态库同时存在
set_target_properties(cross_platform_utils PROPERTIES CLEAN_DIRECT_OUTPUT 1)
set_target_properties(cross_platform_utils_static PROPERTIES CLEAN_DIRECT_OUTPUT 1)
 
# 指定动态库版本
# VERSION 动态库版本
# SOVERSION API版本
set_target_properties(cross_platform_utils PROPERTIES VERSION 1.0 SOVERSION 1)