#include "interpreter.hpp"


namespace solidity {


long Interpreter::eval(const std::string& line)
{
  if (line.empty())
  {
    return 0;
  }

  AstNode::Ptr ast = m_parser.parse(line);
  long val = m_evaluator.eval(ast);
  return val;
}


} // solidity
