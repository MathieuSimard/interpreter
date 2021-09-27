#include "astnode.hpp"

#include <iostream>
#include <map>
#include <string>


namespace solidity {


static std::map<AstNode::Type, std::string> ast_node_type_map
{
  { AstNode::Type::NUM, "NUMERIC" },
  { AstNode::Type::ADD, "ADDITION" },
  { AstNode::Type::SUB, "SUBSTRACTION" },
  { AstNode::Type::MUL, "MULTIPLICATION" },
  { AstNode::Type::DIV, "DIVISION" },
  { AstNode::Type::ERR, "ERROR" },
};

std::ostream& operator<<(std::ostream& os, AstNode::Type ast_node_type)
{
  os << ast_node_type_map.at(ast_node_type);
  return os;
}


} // solidity
