#pragma once
#include <iostream>


namespace solidity {


struct Token
{
  enum Type
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

  Type m_type = Type::ERR;
  double m_val = 0;
  char m_sym = 0;
};

std::ostream& operator<<(std::ostream& os, Token::Type token_type);


} // solidity
