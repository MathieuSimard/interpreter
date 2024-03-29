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

  struct UnaryOpException : std::runtime_error                                                                                  
  {                                                                                                                            
    UnaryOpException(const Parser &p);                                                                                         
  };

  struct TokenException : std::runtime_error                                                                                  
  {                                                                                                                            
    TokenException(const Parser &p);                                                                                         
  };

  AstNode::Ptr parse(const std::string &line);

private:
  AstNode::Ptr Expr();
  AstNode::Ptr Term();
  AstNode::Ptr Factor();

  void checkParenthesis() const;
  void nextToken();

  std::string m_line;
  std::size_t m_index;
  Token m_token;
};


} // solidity
