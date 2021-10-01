#include <solidity.hpp>

#include <gtest/gtest.h>


#define ASSERT_EQ_(X, Y) ASSERT_EQ(test.eval(X), (Y))
#define ASSERT_THROW_(X, Y) ASSERT_THROW(test.eval(X), Y)


using namespace solidity;


TEST(InterpreterEval, Evaluation)
{
  Interpreter test;

  // problem statement examples
  ASSERT_EQ_("(4 + 5 * (7 - 3)) - 2", 22);
  ASSERT_EQ_("4+5+7/2", 12);
  ASSERT_THROW_("10 + 1", Parser::DigitException);
  ASSERT_THROW_("-10", Parser::UnaryOpException);

  // trivial case
  ASSERT_EQ_("", 0);
  ASSERT_THROW_("()", Parser::TokenException);

  // unbalanced parenthesis forbidden
  ASSERT_EQ_("(5)", 5);
  ASSERT_EQ_("((5))", 5);
  ASSERT_THROW_("(", Parser::ParenthesisException);
  ASSERT_THROW_(")", Parser::ParenthesisException);
  ASSERT_THROW_("(5", Parser::ParenthesisException);
  ASSERT_THROW_(")5", Parser::ParenthesisException);
  ASSERT_THROW_("(5))", Parser::ParenthesisException);
  ASSERT_THROW_("5)", Parser::ParenthesisException);
  ASSERT_THROW_("5))", Parser::ParenthesisException);

  // unary operations forbidden
  ASSERT_THROW_("-(5 + 9)", Parser::UnaryOpException);
  ASSERT_THROW_("--5", Parser::UnaryOpException);
  ASSERT_THROW_("(- (5 * 6) - 5)", Parser::UnaryOpException);
  ASSERT_THROW_("2*-3--4-8", Parser::UnaryOpException);
  ASSERT_THROW_("-4 - 3", Parser::UnaryOpException);
  ASSERT_THROW_("+5", Parser::UnaryOpException);
  ASSERT_THROW_("+(5 + 6)", Parser::UnaryOpException);

  // multi-digits/fractional numbers forbidden
  ASSERT_THROW_("(4 + 66) * 4", Parser::DigitException);
  ASSERT_THROW_("5 + 6.75", Parser::DigitException);
  ASSERT_THROW_("2 * 3e10", Parser::DigitException);
  ASSERT_THROW_("4E10 - 5", Parser::DigitException);
  
  // left associative division
  ASSERT_EQ_("9/2/2", 2);
  ASSERT_EQ_("9/3/3/1/1", 1);
  ASSERT_THROW_("5/0", Evaluator::DivideByZeroException);

  // others
  ASSERT_EQ_("2+3", 5);
  ASSERT_EQ_("2+3/4", 2);
  ASSERT_EQ_("2*3-4", 2);
  ASSERT_EQ_("2*(3+4)+5/6", 14);
  ASSERT_EQ_("2 * (3 + (4 * 5 + (6 * 7) * 8) - 9) * (2 * 5)", 7000);
  ASSERT_EQ_("((((2))))+ 3 * 5", 17);
  ASSERT_EQ_("1 + 2 * (3 + (4 * 5 + 6 * 7 * 8) - 9) / (2 * 5)", 71);
  ASSERT_EQ_("1 + 2*(3 - 2*(3 - 2)*((2 - 4)*5 - (2 * (5 + 6))/(7 + 2*(3 - 1)) - 1)) + 1", 60);
}
