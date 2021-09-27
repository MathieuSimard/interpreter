#pragma once
#include <iostream>
#include <memory>


namespace solidity {


struct AstNode
{
  using Ptr = std::shared_ptr<AstNode>;

  enum Type
  {
    NUM,
    ADD,
    SUB,
    MUL,
    DIV,
    ERR,
  };

  static AstNode::Ptr create(Type type, const Ptr &left, const Ptr &right);
  static AstNode::Ptr create(double val);

  AstNode(Type type, double val, const Ptr &left, const Ptr &right);

  Type m_type = Type::ERR;
  double m_val = 0;
  Ptr m_left = nullptr;
  Ptr m_right = nullptr;
};

std::ostream& operator<<(std::ostream& os, AstNode::Type ast_node_type);


} // solidity
