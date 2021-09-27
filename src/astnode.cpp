#include "astnode.hpp"

#include <iostream>
#include <map>
#include <memory>
#include <string>


namespace solidity {


AstNode::Ptr AstNode::create(Type type, const Ptr &left, const Ptr &right)
{
  return std::make_shared<AstNode>(type, 0, left, right);
}

AstNode::Ptr AstNode::create(double val)
{
  return std::make_shared<AstNode>(AstNode::Type::NUM, val, nullptr, nullptr);
}

AstNode::AstNode(Type type, double val, const Ptr &left, const Ptr& right)
:
  m_type(type),
  m_val(val),
  m_left(left),
  m_right(right)
{
}

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
