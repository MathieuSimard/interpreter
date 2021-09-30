list(
  APPEND
  srcs
  astnode.cpp
  evaluator.cpp
  interpreter.cpp
  log.cpp
  parser.cpp
  token.cpp
)

add_executable(interpreter ${srcs} main.cpp)

add_library(interpreter_lib SHARED ${srcs})
