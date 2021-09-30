#pragma once
#include <iostream>
#include <sstream>
#include <string>


namespace solidity {


class Log
{
public:
  operator std::string() const;

  template <typename T>
  Log &operator<<(const T &other);

private:
  std::ostringstream m_oss;
};


} // solidity


#include "log_impl.hpp"
