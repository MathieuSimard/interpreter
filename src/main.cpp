#include "solidity.hpp"

#include <iostream>


using namespace solidity;


int main(int argc, char *argv[])
{
  Interpreter test;
  std::cout << test.eval(argv[1]) << std::endl;
}
