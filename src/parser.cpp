#include "parser.hpp"

#include <stdexcept>


namespace solidity {


Parser::Exception::Exception(const std::string &msg)                                                                        
:                                                                                                                              
  std::runtime_error(msg)                                                                                                      
{                                                                                                                              
}                                                                                                                              

Parser::Parser(const std::string &line)
{
  init(line);
}

AstNode::Ptr Parser::parse() const
{
  return Exp();
}

AstNode::Ptr createNode(AstNode::Type type, const AstNode::Ptr &left, const AstNode::Ptr &right)
{
}

void Parser::init(const std::string &line)
{
  m_line = line;
  m_index = 0;
  toNextToken();
}

AstNode::Ptr Parser::Exp() const
{
  return {};
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
