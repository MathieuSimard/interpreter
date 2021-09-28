#include "solidity.hpp"

#include <iostream>


using namespace solidity;


int main(int argc, char *argv[])
{
  std::cout << argv[1] << std::endl;
  Interpreter test;
  std::cout << test.eval(argv[1]) << std::endl;
}
