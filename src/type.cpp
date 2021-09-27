#include "type.hpp"

#include <iostream>
#include <map>
#include <string>


std::map<TokenType, std::string> token_type_map
{
  { TokenType::NUM, "NUMERIC" },
  { TokenType::ADD, "ADDITION" },
  { TokenType::SUB, "SUBSTRACTION" },
  { TokenType::MUL, "MULTIPLICATION" },
  { TokenType::DIV, "DIVISION" },
  { TokenType::OPAR, "OPEN PARENTHESIS" },
  { TokenType::CPAR, "CLOSED PARENTHESIS" },
  { TokenType::EOL, "END OF LINE" },
  { TokenType::ERR, "ERROR" },
};

std::ostream& operator<<(std::ostream& os, TokenType token_type)
{
  os << token_type_map.at(token_type);
  return os;
}
