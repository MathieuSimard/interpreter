list(
  APPEND
  srcs
  astnode.cpp
  evaluator.cpp
  interpreter.cpp
  parser.cpp
  token.cpp
  main.cpp
)

add_executable(main ${srcs})
