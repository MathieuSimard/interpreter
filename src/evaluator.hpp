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

  long eval(const AstNode::Ptr &ast) const;

private:
  long evalSubTree(const AstNode::Ptr &ast) const;
};


} // solidity
