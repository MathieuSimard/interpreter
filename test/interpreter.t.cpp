#include <solidity.hpp>

#include <gtest/gtest.h>


using namespace solidity;


TEST(InterpreterEval, Evaluation)
{
  Interpreter test;
  
  EXPECT_EQ(test.eval("(4 + 5 * (7 - 3)) - 2"), 22);
  EXPECT_EQ(test.eval("4+5+7/2"), 12);
  EXPECT_THROW(test.eval("10 + 1"), Parser::DigitException);
  EXPECT_THROW(test.eval("-10"), Parser::UnaryMinusException);

  ASSERT_EQ(test.eval(""), 0);
  EXPECT_THROW(test.eval("()"), Parser::TokenException);

  EXPECT_EQ(test.eval("(5)"), 5);
  EXPECT_EQ(test.eval("((5))"), 5);
  EXPECT_THROW(test.eval("("), Parser::ParenthesisException);
  EXPECT_THROW(test.eval(")"), Parser::ParenthesisException);
  EXPECT_THROW(test.eval("(5"), Parser::ParenthesisException);
  EXPECT_THROW(test.eval(")5"), Parser::ParenthesisException);
  EXPECT_THROW(test.eval("(5))"), Parser::ParenthesisException);
  EXPECT_THROW(test.eval("5)"), Parser::ParenthesisException);
  EXPECT_THROW(test.eval("5))"), Parser::ParenthesisException);

  EXPECT_EQ(test.eval("9/2/2"), 2);
  EXPECT_THROW(test.eval("5/0"), Evaluator::DivideByZeroException);
}
