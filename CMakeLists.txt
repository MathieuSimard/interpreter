cmake_minimum_required(VERSION 3.10)

project(
  "arithmetic interpreter"
  VERSION 1.0.0
  DESCRIPTION "arithmetic interpreter, single-digit decimal integer/binary operations"
  LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_SKIP_BUILD_RPATH FALSE)

set(ENV{PKG_CONFIG_PATH} ${CMAKE_SOURCE_DIR}/cmake)
find_package(PkgConfig MODULE REQUIRED)
pkg_search_module(PKG_GTEST REQUIRED IMPORTED_TARGET gtest_main)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -ggdb3 -O0")

add_subdirectory(src)
add_subdirectory(test)

