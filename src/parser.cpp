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
  m_token.m_type = Token::Type::NONE;
  m_token.m_sym = 0;
  m_token.m_val = 0;

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
    if (!(m_index < m_line.size() - 1 || !std::isdigit(m_line.at(m_index + 1))))
    {
      throw Exception("only sigle-digit decimal integer allowed");
    }
    m_token.m_type = Token::Type::NUM;
    m_token.m_sym = m_line.at(m_index);
    m_token.m_val = m_token.m_sym - '0';
    ++m_index;
    return;
  }

  char c = m_line.at(m_index);
  if (c == '+')
  {
    m_token.m_type = Token::Type::ADD;
  }
  else if (c == '-')
  {
    m_token.m_type = Token::Type::SUB;
  }
  else if (c == '*')
  {
    m_token.m_type = Token::Type::MUL;
  }
  else if (c == '/')
  {
    m_token.m_type = Token::Type::DIV;
  }
  else if (c == '(')
  {
    m_token.m_type = Token::Type::OPAR;
  }
  else if (c == ')')
  {
    m_token.m_type = Token::Type::CPAR;
  }
  else
  {
    std::ostringstream msg;
    msg << "invalid token '" << c << "' at position " << m_index; 
    throw Exception(msg.str());
  }

  m_token.m_sym = c;
  ++m_index;
}


} // solidity
