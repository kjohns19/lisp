cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

include_directories(src)

set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -Wall")

project(Lisp)

file(GLOB_RECURSE SRC_FILES src/*.cpp)

add_executable(lisp ${SRC_FILES})
