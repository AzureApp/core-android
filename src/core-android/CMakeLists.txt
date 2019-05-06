cmake_minimum_required(VERSION 3.0.0)
project(azure C CXX)

if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "No build type selected, default to Debug")
    set(CMAKE_BUILD_TYPE "Debug")
endif ()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

file(GLOB_RECURSE core_android_HEADER_FILES "*.h")
file(GLOB_RECURSE core_android_SRC_FILES "*.cc")

# find headers
set(core_android_INCLUDE_FILES "")
foreach (_headerFile ${core_android_HEADER_FILES})
    get_filename_component(_dir ${_headerFile} PATH)
    list(APPEND core_android_INCLUDE_FILES ${_dir})
endforeach ()
list(REMOVE_DUPLICATES core_android_INCLUDE_FILES)


include_directories(.)
# third party includes
include_directories(${CMAKE_SOURCE_DIR}/third_party/libazure)

add_subdirectory(${CMAKE_SOURCE_DIR}/third_party/libazure ${CMAKE_CURRENT_BINARY_DIR}/libazure)

add_library(azure_core_android STATIC ${core_android_SRC_FILES} ${core_android_INCLUDE_FILES})
target_include_directories(azure_core_android PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
target_link_libraries(azure_core_android log android libazure)