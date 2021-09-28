#pragma once
#include <iostream>


namespace solidity {


struct Token
{
  enum Type
  {
    NONE,
    NUM,
    ADD,
    SUB,
    MUL,
    DIV,
    OPAR,
    CPAR,
    EOL,
  };

  Type m_type = Type::NONE;
  double m_val = 0;
};

std::ostream& operator<<(std::ostream& os, Token::Type token_type);


} // solidity
