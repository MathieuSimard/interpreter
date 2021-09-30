#pragma once
#include "evaluator.hpp"
#include "parser.hpp"

#include <string>


namespace solidity {


class Interpreter
{
public:
  long eval(const std::string& line);

private:
  Parser m_parser;
  Evaluator m_evaluator;
};


} // solidity
