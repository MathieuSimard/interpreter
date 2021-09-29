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
  class DigitException : public std::runtime_error                                                                                  
  {                                                                                                                            
  public:                                                                                                                      
    DigitException(std::size_t index);                                                                                         
  };

  class UnaryMinusException : public std::runtime_error                                                                                  
  {                                                                                                                            
  public:                                                                                                                      
    UnaryMinusException(std::size_t index);                                                                                         
  };

  class TokenException : public std::runtime_error                                                                                  
  {                                                                                                                            
  public:                                                                                                                      
    TokenException(char token, std::size_t index);                                                                                         
  };

  AstNode::Ptr parse(const std::string &line);

private:
  AstNode::Ptr Exp();
  AstNode::Ptr ExpPr();
  AstNode::Ptr Term();
  AstNode::Ptr TermPr();
  AstNode::Ptr Factor();

  char getToken() const;
  void toNextToken();

  std::string m_line;
  std::size_t m_index;
  Token m_token;
};


} // solidity
