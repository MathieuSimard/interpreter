#pragma once
#include <iostream>
#include <memory>


namespace solidity {


struct AstNode
{
  using Ptr = std::unique_ptr<AstNode>;

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
  Ptr m_left = nullptr;
  Ptr m_right = nullptr;
};

std::ostream& operator<<(std::ostream& os, AstNode::Type ast_node_type);


} // solidity
