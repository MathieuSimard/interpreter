#pragma once


namespace solidity {


template <typename T>
Log &Log::operator<<(const T &other)
{
  m_oss << other;
  return *this;
}


} // solidity
