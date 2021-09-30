#include "parser.hpp"

#include "astnode.hpp"
#include "log.hpp"
#include "token.hpp"

#include <sstream>
#include <stdexcept>

#include <cctype>


namespace solidity {

Parser::ParenthesisException::ParenthesisException(std::size_t i)
:                                                                                                                              
  std::runtime_error(Log() << "unbalanced parenthesis at index = " << i)
{                                                                                                                              
}                                                                                                                              

Parser::DigitException::DigitException(const Parser &p)
:                                                                                                                              
  std::runtime_error(Log() << "single digit required at index = " << p.m_index)
{                                                                                                                              
}                                                                                                                              

Parser::UnaryMinusException::UnaryMinusException(const Parser &p)
:                                                                                                                              
  std::runtime_error(Log() << "unary minus forbidden at index = " << p.m_index - 1)
{                                                                                                                              
}                                                                                                                              

Parser::TokenException::TokenException(const Parser &p)
:                                                                                                                              
  std::runtime_error(Log() << "invalid token '"
    << p.m_line.at(p.m_index - 1) << "' at index = " << p.m_index - 1)
{                                                                                                                              
}                                                                                                                              

AstNode::Ptr Parser::parse(const std::string &line)
{
  m_line = line;
  m_index = 0;

  checkParenthesis();
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
  if (m_token.m_type == Token::MUL)
  {
    toNextToken();
    right = Factor();
    left = TermPr();
    return AstNode::create(AstNode::MUL, left, right);  
  }
  else if (m_token.m_type == Token::DIV)
  {
    toNextToken();
    right = Factor();
    Token::Type type = m_token.m_type;
    if (type == Token::DIV)
    {
      left = TermPr();
      return AstNode::create(AstNode::DIV, left, right);
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
  if (m_token.m_type == Token::OPAR)
  {
    toNextToken();
    AstNode::Ptr exp = Exp();
    toNextToken();
    return exp;
  }
  else if (m_token.m_type == Token::NUM)
  {
    long val = m_token.m_val; 
    toNextToken();
    return AstNode::create(val);
  }
  else if (m_token.m_type == Token::SUB)
  {
    throw UnaryMinusException(*this);
  }
  else
  {
    throw TokenException(*this);
  }
}

void Parser::checkParenthesis() const
{
  int idx = 0;
  int cnt = 0;
  for (char token : m_line)
  {
    if (token == ')')
    {
      if (cnt == 0)
      {
        throw ParenthesisException(idx);
      }
      --cnt;
    }
    else if (token == '(')
    {
      ++cnt;
    }
    ++idx;
  }
  if (cnt != 0)
  {
    throw ParenthesisException(idx);
  }
}

void Parser::toNextToken()
{
  m_token.m_type = Token::NONE;
  m_token.m_val = 0;
  
  if (m_index == m_line.size())
  {
    m_token.m_type = Token::Type::EOL;
    return;
  }

  while (std::isspace(m_line.at(m_index)))
  {
    ++m_index;
    if (m_index == m_line.size())
    {
      m_token.m_type = Token::Type::EOL;
      return;
    }
  }

  if (std::isdigit(m_line.at(m_index)))
  {
    if (m_index + 1 < m_line.size() && std::isdigit(m_line.at(m_index + 1)))
    {
      throw DigitException(*this);
    }
    m_token.m_type = Token::Type::NUM;
    m_token.m_val = m_line.at(m_index) - '0';
    ++m_index;
    return;
  }

  char token = m_line.at(m_index);
  ++m_index;
  if (token == '+')
  {
    m_token.m_type = Token::ADD;
  }
  else if (token == '-')
  {
    m_token.m_type = Token::SUB;
  }
  else if (token == '*')
  {
    m_token.m_type = Token::MUL;
  }
  else if (token == '/')
  {
    m_token.m_type = Token::DIV;
  }
  else if (token == '(')
  {
    m_token.m_type = Token::OPAR;
  }
  else if (token == ')')
  {
    m_token.m_type = Token::CPAR;
  }
  else
  {
    throw TokenException(*this);
  }
}


} // solidity
