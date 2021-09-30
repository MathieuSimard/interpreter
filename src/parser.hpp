#pragma once
#include "astnode.hpp"
#include "token.hpp"

#include <stdexcept>
#include <string>

#include <cstdlib>


namespace solidity {


class Parser
{
public:
  struct ParenthesisException : std::runtime_error                                                                                  
  {                                                                                                                            
    ParenthesisException(std::size_t i);                                                                                         
  };

  struct DigitException : std::runtime_error                                                                                  
  {                                                                                                                            
    DigitException(const Parser &p);                                                                                         
  };

  struct UnaryMinusException : std::runtime_error                                                                                  
  {                                                                                                                            
    UnaryMinusException(const Parser &p);                                                                                         
  };

  struct TokenException : std::runtime_error                                                                                  
  {                                                                                                                            
    TokenException(const Parser &p);                                                                                         
  };

  AstNode::Ptr parse(const std::string &line);

private:
  AstNode::Ptr Exp();
  AstNode::Ptr ExpPr();
  AstNode::Ptr Term();
  AstNode::Ptr TermPr();
  AstNode::Ptr Factor();

  void checkParenthesis() const;
  void toNextToken();

  std::string m_line;
  std::size_t m_index;
  Token m_token;
};


} // solidity
