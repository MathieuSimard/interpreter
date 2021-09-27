#pragma once
#include <iostream>


enum class TokenType
{
  NUM,
  ADD,
  SUB,
  MUL,
  DIV,
  OPAR,
  CPAR,
  EOL,
  ERR,
};

std::ostream& operator<<(std::ostream& os, TokenType token_type);

struct Token
{
  TokenType type = TokenType::ERR;
  char sym = 0;
  double val = 0;
};
