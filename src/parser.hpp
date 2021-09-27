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

  Parser(const std::string &line);
  AstNode::Ptr parse() const;

private:
  static AstNode::Ptr createNode(AstNode::Type type, const AstNode::Ptr &left, const AstNode::Ptr &right);

  void init(const std::string &line);

  AstNode::Ptr Exp() const;
  AstNode::Ptr ExpPr() const;
  AstNode::Ptr Term() const;
  AstNode::Ptr TermPr() const;
  AstNode::Ptr Factor() const;

  void toNextToken();

  std::string m_line;
  std::size_t m_index;
  Token m_token;
};


} // solidity
