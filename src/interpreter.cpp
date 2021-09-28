#include "interpreter.hpp"


namespace solidity {


double Interpreter::eval(const std::string& line)
{
  AstNode::Ptr ast = m_parser.parse(line);
  double val = m_evaluator.eval(ast);
  return val;
}


} // solidity
