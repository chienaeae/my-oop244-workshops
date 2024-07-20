// Final Project Milestone 3
// Streamable Module
// File	Streamable.cpp
// Version 1.0
// Author	Chia-Yu Chien
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
//
/////////////////////////////////////////////////////////////////
#include "Streamable.h"
#include <iostream>

namespace seneca {

std::ostream &operator<<(std::ostream &os, const Streamable &s) {
  if (s) {
    s.write(os);
  }

  return os;
}

std::istream &operator>>(std::istream &is, Streamable &s) {
  s.read(is);
  return is;
}
} // namespace seneca