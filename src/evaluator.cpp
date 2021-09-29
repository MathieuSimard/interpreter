#include "evaluator.hpp"

#include <stdexcept>
#include <string>


namespace solidity {


Evaluator::Exception::Exception(const std::string &msg)
:
  std::runtime_error(msg)
{
}

long Evaluator::eval(const AstNode::Ptr &ast) const
{
  if (!ast)
  {
    throw Exception("null abstract syntax tree");
  }
  evalSubTree(ast);
}

long Evaluator::evalSubTree(const AstNode::Ptr &ast) const
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
      std::cout << "vl = " << vl << std::endl;
      std::cout << "vr = " << vr << std::endl;
      return vl / vr;
    }
  }
  throw Exception("invalid abstract syntax tree");
}


} // solidity
