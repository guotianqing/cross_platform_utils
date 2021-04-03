cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

project(unittest CXX)

# enable c++ 11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# take respectives flags for debug & release process 
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-g -fno-omit-frame-pointer")
set(CMAKE_CXX_FLAGS_RELEASE_INIT "-O2")

if (MSVC)
    # warning level 4 and all warnings as errors
    add_compile_options(/W4 /WX)
else()
    # lots of warnings and all warnings as errors
    add_compile_options(-Wall -Wextra -pedantic -Werror -fPIC)
endif()

# default build type : Debug
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

INCLUDE_DIRECTORIES(../ /usr/local/tars/cpp/include) # 依赖的h文件路径
LINK_DIRECTORIES(/usr/local/lib) # 依赖的库文件路径

aux_source_directory(./ SRCS)
aux_source_directory(../ SRCS)

ADD_EXECUTABLE(test ${SRCS})

TARGET_LINK_LIBRARIES(test gtest gtest_main pthread) # 链接时依赖的库

