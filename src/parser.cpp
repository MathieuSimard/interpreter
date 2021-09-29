#include "parser.hpp"

#include "astnode.hpp"
#include "log.hpp"
#include "token.hpp"

#include <sstream>
#include <stdexcept>

#include <cctype>


namespace solidity {


Parser::DigitException::DigitException(std::size_t index)                                                                        
:                                                                                                                              
  std::runtime_error(Log() << "single digit required, index = " << index)
{                                                                                                                              
}                                                                                                                              

Parser::UnaryMinusException::UnaryMinusException(std::size_t index)                                                                        
:                                                                                                                              
  std::runtime_error(Log() << "unary minus forbidden, index = " << index)
{                                                                                                                              
}                                                                                                                              

Parser::TokenException::TokenException(char token, std::size_t index)                                                                        
:                                                                                                                              
  std::runtime_error(Log() << "invalid token " << token << ", index = " << index)
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
    return AstNode::create(0);
  }
}

AstNode::Ptr Parser::Term()
{
  AstNode::Ptr left = Factor();
  Token::Type type = m_token.m_type;
  AstNode::Ptr right = TermPr();
  if (type == Token::Type::MUL)
  {
    return AstNode::create(AstNode::Type::MUL, left, right);
  }
  else if (type == Token::Type::DIV)
  {
    return AstNode::create(AstNode::Type::DIV, left, right);
  }
  else
  {
    return left;
  }
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
    Token::Type type = m_token.m_type;
    if (type == Token::Type::DIV)
    {
      left = TermPr();
      return AstNode::create(AstNode::Type::DIV, left, right);
    }
    else
    {
      return right;
    }
  }
  else
  {
    return AstNode::create(1);
  }
}

AstNode::Ptr Parser::Factor()
{
  AstNode::Ptr node;
  if (m_token.m_type == Token::Type::OPAR)
  {
    toNextToken();
    node = Exp();
    if (m_line.at(m_index - 1) == ')')
    {
      toNextToken();
      return node;
    }
    else
    {
      throw TokenException(getToken(), m_index);
    }
  }
  else if (m_token.m_type == Token::Type::NUM)
  {
    long val = m_token.m_val; 
    toNextToken();
    return AstNode::create(val);
  }
  else if (m_token.m_type == Token::Type::SUB)
  {
    throw UnaryMinusException(m_index);
  }
  else
  {
    throw TokenException(getToken(), m_index);
  }
}

char Parser::getToken() const
{
  return m_line.at(m_index);
}

void Parser::toNextToken()
{
  m_token.m_type = Token::Type::NONE;
  m_token.m_val = 0;
  
  if (m_index == m_line.size())
  {
    m_token.m_type = Token::Type::EOL;
    return;
  }

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
    if (m_index + 1 < m_line.size() && std::isdigit(m_line.at(m_index + 1)))
    {
      throw DigitException(m_index);
    }
    m_token.m_type = Token::Type::NUM;
    m_token.m_val = getToken() - '0';
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
    throw TokenException(getToken(), m_index);
  }

  ++m_index;
}


} // solidity
