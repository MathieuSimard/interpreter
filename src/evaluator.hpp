#pragma once
#include "astnode.hpp"

#include <memory>
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

  double eval(const std::unique_ptr<AstNode> &ast) const;

private:
  double evalSubTree(const std::unique_ptr<AstNode> &ast) const;
};


} // solidity
