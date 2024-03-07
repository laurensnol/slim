cmake_minimum_required(VERSION 3.21)
project(glad)

add_library(glad "${CMAKE_CURRENT_SOURCE_DIR}/src/gl.c" "${CMAKE_CURRENT_SOURCE_DIR}/include/glad/gl.h")
target_include_directories(glad PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
