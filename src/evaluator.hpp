#pragma once
#include "astnode.hpp"

#include <stdexcept>
#include <string>


namespace solidity {


class Evaluator
{
public:
  class Exception : public std::runtime_error
  {
  public:
    Exception(const std::string &msg);
  };

  double eval(const AstNode::Ptr &ast) const;

private:
  double evalSubTree(const AstNode::Ptr &ast) const;
};


} // solidity
