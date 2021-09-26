list(
  APPEND
  srcs
  parser.t.cpp
  utest.cpp
)

add_executable(utest ${srcs})

target_link_Libraries(
  utest
  PRIVATE
  ${GTEST_LDFLAGS}
  PkgConfig::PKG_GTEST
)

target_compile_options(
  utest
  PRIVATE
  ${GTEST_CFLAGS}
)
