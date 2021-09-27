#pragma once
#include <iostream>
#include <memory>


namespace solidity {


struct AstNode
{
  enum Type
  {
    NUM,
    ADD,
    SUB,
    MUL,
    DIV,
    ERR,
  };

  Type m_type = Type::ERR;
  double m_val = 0;
  std::unique_ptr<AstNode> m_left = nullptr;
  std::unique_ptr<AstNode> m_right = nullptr;
};

std::ostream& operator<<(std::ostream& os, AstNode::Type ast_node_type);


} // solidity
