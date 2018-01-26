cmake_minimum_required(VERSION 3.7)
project(Packer)

option(BUILD_STATIC_LIBS "Build static libraries" OFF)

set(LIB_TYPE SHARED)

if(BUILD_STATIC_LIBS)
    set(LIB_TYPE STATIC)
    add_definitions(-DUSE_STATIC_LIB)
endif(BUILD_STATIC_LIBS)

add_subdirectory(src)

