#include "log.hpp"


namespace solidity {


Log::operator std::string() const
{
  return m_oss.str();
}


} // solidity
