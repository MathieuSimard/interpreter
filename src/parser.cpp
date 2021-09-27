#include "parser.hpp"

#include "astnode.hpp"

#include <stdexcept>


namespace solidity {


Parser::Exception::Exception(const std::string &msg)                                                                        
:                                                                                                                              
  std::runtime_error(msg)                                                                                                      
{                                                                                                                              
}                                                                                                                              

AstNode::Ptr Parser::parse(const std::string &line)
{
  m_line = line;
  m_index = 0;
  toNextToken();
  return Exp();
}

AstNode::Ptr Parser::Exp() const
{
  AstNode::Ptr left = Term();
  AstNode::Ptr right = ExpPr();
  return AstNode::create(AstNode::Type::ADD, left, right);
}

AstNode::Ptr Parser::ExpPr() const
{
  return {};
}

AstNode::Ptr Parser::Term() const
{
  return {};
}

AstNode::Ptr Parser::TermPr() const
{
  return {};
}

AstNode::Ptr Parser::Factor() const
{
  return {};
}

void Parser::toNextToken()
{
}


} // solidity
