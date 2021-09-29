#include "evaluator.hpp"

#include <stdexcept>
#include <string>


namespace solidity {


Evaluator::NullException::NullException()
:
  std::runtime_error("null node")
{
}

Evaluator::TreeException::TreeException()
:
  std::runtime_error("invalid tree")
{
}

Evaluator::DivideByZeroException::DivideByZeroException()
:
  std::runtime_error("division by zero")
{
}

long Evaluator::eval(const AstNode::Ptr &ast) const
{
  if (!ast)
  {
    throw NullException();
  }
  evalSubTree(ast);
}

long Evaluator::evalSubTree(const AstNode::Ptr &ast) const
{
  if (!ast)
  {
    throw NullException();
  }

  if (ast->m_type == AstNode::Type::NUM)
  {
    return ast->m_val;
  }
  else
  {
    long vl = evalSubTree(ast->m_left);
    long vr = evalSubTree(ast->m_right);
    if (ast->m_type == AstNode::Type::ADD)
    {
      return vl + vr;
    }
    else if (ast->m_type == AstNode::Type::SUB)
    {
      return vl - vr;
    }
    else if (ast->m_type == AstNode::Type::MUL)
    {
      return vl * vr;
    }
    else if (ast->m_type == AstNode::Type::DIV)
    {
      if (vr == 0)
      {
        throw DivideByZeroException();
      }
      return vl / vr;
    }
  }
  throw TreeException();
}


} // solidity
