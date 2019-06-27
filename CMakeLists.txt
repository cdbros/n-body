cmake_minimum_required(VERSION 3.14)

project(n-body)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SRCS "src/*.cpp")

add_executable(n-body ${SRCS})
