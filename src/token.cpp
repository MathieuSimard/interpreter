#include "token.hpp"

#include <iostream>
#include <map>
#include <string>


namespace solidity {


static std::map<Token::Type, std::string> token_type_map
{
  { Token::Type::NUM, "NUMERIC" },
  { Token::Type::ADD, "ADDITION" },
  { Token::Type::SUB, "SUBSTRACTION" },
  { Token::Type::MUL, "MULTIPLICATION" },
  { Token::Type::DIV, "DIVISION" },
  { Token::Type::OPAR, "OPEN PARENTHESIS" },
  { Token::Type::CPAR, "CLOSED PARENTHESIS" },
  { Token::Type::EOL, "END OF LINE" },
  { Token::Type::ERR, "ERROR" },
};

std::ostream& operator<<(std::ostream& os, Token::Type token_type)
{
  os << token_type_map.at(token_type);
  return os;
}


} // solidity
