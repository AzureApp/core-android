cmake_minimum_required(VERSION 3.0.0)
project(azure C CXX)

file(GLOB_RECURSE daemon_android_HEADER_FILES "*.h")
file(GLOB_RECURSE daemon_android_SRC_FILES "*.cc")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

add_subdirectory(${CMAKE_SOURCE_DIR}/third_party/gflags ${CMAKE_CURRENT_BINARY_DIR}/gflags)

set(linenoise_SRC_FILES "${CMAKE_SOURCE_DIR}/third_party/linenoise/linenoise.c"
                        "${CMAKE_SOURCE_DIR}/third_party/linenoise/linenoise.h")
include_directories("${CMAKE_SOURCE_DIR}/third_party/linenoise/")
add_executable(azured ${daemon_android_HEADER_FILES} ${daemon_android_SRC_FILES} ${linenoise_SRC_FILES})
target_link_libraries(azured azure_core_android gflags)