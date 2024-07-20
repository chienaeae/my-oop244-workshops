// Final Project Milestone 3
// Streamable Module
// File	Streamable.h
// Version 1.0
// Author	Chia-Yu Chien
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
//
/////////////////////////////////////////////////////////////////

#ifndef SENECA_STREAMABLE_H__
#define SENECA_STREAMABLE_H__

#include <iostream>

namespace seneca {

class Streamable {

public:
  // write receives and returns a reference of an ostream object.
  virtual std::ostream &write(std::ostream &os = std::cout) const = 0;

  // read receives and returns a reference of an istream object.
  virtual std::istream &read(std::istream &is = std::cin) = 0;

  // conIo receives a reference of an ios object and returns a Boolean.
  virtual bool conIO(std::ios &io) const = 0;

  // Boolean conversion overloads of this method will return if the Streamable
  // object is in a valid state or not.
  virtual operator bool() const = 0;

  ~Streamable() {}
};

std::ostream &operator<<(std::ostream &os, const Streamable &s);

std::istream &operator>>(std::istream &is, Streamable &s);

} // namespace seneca

#endif