#include "parser.hpp"

#include "astnode.hpp"
#include "token.hpp"

#include <sstream>
#include <stdexcept>

#include <cctype>


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

AstNode::Ptr Parser::Exp()
{
  AstNode::Ptr left = Term();
  AstNode::Ptr right = ExpPr();
  return AstNode::create(AstNode::Type::ADD, left, right);
}

AstNode::Ptr Parser::ExpPr()
{
  AstNode::Ptr left;
  AstNode::Ptr right;
  if (m_token.m_type == Token::Type::ADD)
  {
    toNextToken();
    right = Term();
    left = ExpPr();
    return AstNode::create(AstNode::Type::ADD, left, right);  
  }
  else if (m_token.m_type == Token::Type::SUB)
  {
    toNextToken();
    right = Term();
    left = ExpPr();
    return AstNode::create(AstNode::Type::SUB, left, right);
  }
  else
  {
    AstNode::create(0);
  }
}

AstNode::Ptr Parser::Term()
{
  AstNode::Ptr left = Factor();
  AstNode::Ptr right = TermPr();
  return AstNode::create(AstNode::Type::MUL, left, right);
}

AstNode::Ptr Parser::TermPr()
{
  AstNode::Ptr left;
  AstNode::Ptr right;
  if (m_token.m_type == Token::Type::MUL)
  {
    toNextToken();
    right = Factor();
    left = TermPr();
    return AstNode::create(AstNode::Type::MUL, left, right);  
  }
  else if (m_token.m_type == Token::Type::DIV)
  {
    toNextToken();
    right = Factor();
    left = TermPr();
    return AstNode::create(AstNode::Type::DIV, left, right);
  }
  else
  {
    AstNode::create(1);
  }
}

AstNode::Ptr Parser::Factor()
{
  AstNode::Ptr node;
  if (m_token.m_type == Token::Type::OPAR)
  {
    toNextToken();
    node = Exp();
    if (getToken() == ')')
    {
      toNextToken();
      return node;
    }
    else
    {
      std::ostringstream msg;
      msg << "invalid token '" << getToken() << "' at position " << m_index << ", expected ')'";
      throw Exception(msg.str());
    }
  }
  else if (m_token.m_type == Token::Type::NUM)
  {
    toNextToken();
    return AstNode::create(m_token.m_val);
  }
  else
  {
    std::ostringstream msg;
    msg << "invalid token '" << getToken() << "' at position " << m_index;
    throw Exception(msg.str());
  }
}

char Parser::getToken() const
{
  return m_line.at(m_index);
}

void Parser::toNextToken()
{
  m_token.m_type = Token::Type::NONE;
  m_token.m_sym = 0;
  m_token.m_val = 0;

  while (std::isspace(getToken()))
  {
    ++m_index;
    if (m_index == m_line.size())
    {
      m_token.m_type = Token::Type::EOL;
      return;
    }
  }

  if (std::isdigit(getToken()))
  {
    if (!(m_index < m_line.size() - 1 || !std::isdigit(m_line.at(m_index + 1))))
    {
      throw Exception("only sigle-digit decimal integer allowed");
    }
    m_token.m_type = Token::Type::NUM;
    m_token.m_sym = getToken();
    m_token.m_val = m_token.m_sym - '0';
    ++m_index;
    return;
  }

  if (getToken() == '+')
  {
    m_token.m_type = Token::Type::ADD;
  }
  else if (getToken() == '-')
  {
    m_token.m_type = Token::Type::SUB;
  }
  else if (getToken() == '*')
  {
    m_token.m_type = Token::Type::MUL;
  }
  else if (getToken() == '/')
  {
    m_token.m_type = Token::Type::DIV;
  }
  else if (getToken() == '(')
  {
    m_token.m_type = Token::Type::OPAR;
  }
  else if (getToken() == ')')
  {
    m_token.m_type = Token::Type::CPAR;
  }
  else
  {
    std::ostringstream msg;
    msg << "invalid token '" << getToken() << "' at position " << m_index; 
    throw Exception(msg.str());
  }

  m_token.m_sym = getToken();
  ++m_index;
}


} // solidity
