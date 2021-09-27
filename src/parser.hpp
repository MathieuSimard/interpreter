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
  class Exception : public std::runtime_error                                                                                  
  {                                                                                                                            
  public:                                                                                                                      
    Exception(const std::string &msg);                                                                                         
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
