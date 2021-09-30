#pragma once
#include "astnode.hpp"

#include <stdexcept>


namespace solidity {


class Evaluator
{
public:
  struct NullException : std::runtime_error
  {
    NullException();
  };

  struct TreeException : std::runtime_error
  {
    TreeException();
  };

  struct DivideByZeroException : std::runtime_error
  {
    DivideByZeroException();
  };

  long eval(const AstNode::Ptr &ast) const;

private:
  long evalSubTree(const AstNode::Ptr &ast) const;
};


} // solidity
