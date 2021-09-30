list(
  APPEND
  srcs
  interpreter.t.cpp
  utest.cpp
)

add_executable(utest ${srcs})

target_include_directories(
  utest
  PRIVATE
  ${CMAKE_SOURCE_DIR}/src
)

target_compile_options(
  utest
  PRIVATE
  ${GTEST_CFLAGS}
)

target_link_Libraries(
  utest
  PRIVATE
  ${GTEST_LDFLAGS}
  PkgConfig::PKG_GTEST
  interpreter_lib 
)
