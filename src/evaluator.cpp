#include "evaluator.hpp"

#include <stdexcept>
#include <string>


namespace solidity {


Evaluator::Exception::Exception(const std::string &msg)
:
  std::runtime_error(msg)
{
}

double Evaluator::eval(const std::unique_ptr<AstNode> &ast) const
{
  if (!ast)
  {
    throw Exception("null abstract syntax tree");
  }
  evalSubTree(ast);
}

double Evaluator::evalSubTree(const std::unique_ptr<AstNode> &ast) const
{
  if (!ast)
  {
    throw Exception("null abstract syntax tree");
  }

  if (ast->m_type == AstNode::Type::NUM)
  {
    return ast->m_val;
  }
  else
  {
    double vl = evalSubTree(ast->m_left);
    double vr = evalSubTree(ast->m_right);
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
      return vl / vr;
    }
  }
  throw Exception("invalid abstract syntax tree");
}


} // solidity
