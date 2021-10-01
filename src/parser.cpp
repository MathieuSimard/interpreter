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

Parser::UnaryOpException::UnaryOpException(const Parser &p)
:  
  std::runtime_error(Log() << "unary operation forbidden at index = " << p.m_index - 1)
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
  nextToken();
  return Expr();
}

/*
  left-associative parser (iteration)
*/

AstNode::Ptr Parser::Expr()
{
  AstNode::Ptr left = Term();
  while (m_token.m_type == Token::ADD || m_token.m_type == Token::SUB)
  {
    AstNode::Type type;
    if (m_token.m_type == Token::ADD)
    {
      type = AstNode::ADD;
    }
    else
    {
      type = AstNode::SUB;
    }
    nextToken();
    AstNode::Ptr right = Term();
    left = AstNode::create(type, left, right);
  }
  return left;
}

AstNode::Ptr Parser::Term()
{
  AstNode::Ptr left = Factor();
  while (m_token.m_type == Token::MUL || m_token.m_type == Token::DIV)
  {
    AstNode::Type type;
    if (m_token.m_type == Token::MUL)
    {
      type = AstNode::MUL;
    }
    else
    {
      type = AstNode::DIV;
    }
    nextToken();
    AstNode::Ptr right = Factor();
    left = AstNode::create(type, left, right);
  }
  return left;
}

AstNode::Ptr Parser::Factor()
{
  if (m_token.m_type == Token::OPAR)
  {
    nextToken();
    AstNode::Ptr expr = Expr();
    nextToken();
    return expr;
  }
  else if (m_token.m_type == Token::NUM)
  {
    long val = m_token.m_val; 
    nextToken();
    return AstNode::create(val);
  }
  else if (m_token.m_type == Token::ADD || m_token.m_type == Token::SUB)
  {
    throw UnaryOpException(*this);
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

void Parser::nextToken()
{
  m_token.m_type = Token::NONE;
  m_token.m_val = 0;
  
  if (m_index == m_line.size())
  {
    m_token.m_type = Token::EOL;
    return;
  }

  while (std::isspace(m_line.at(m_index)))
  {
    ++m_index;
    if (m_index == m_line.size())
    {
      m_token.m_type = Token::EOL;
      return;
    }
  }

  if (std::isdigit(m_line.at(m_index)))
  {
    if (m_index + 1 < m_line.size())
    {
      char c = m_line.at(m_index + 1);
      if (std::isdigit(c) || c == 'e' || c == 'E' || c == '.')
      {
        throw DigitException(*this);
      }
    }
    m_token.m_type = Token::NUM;
    m_token.m_val = m_line.at(m_index) - '0';
    ++m_index;
    return;
  }

  char token = m_line.at(m_index);
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
  
  ++m_index;
}


} // solidity
