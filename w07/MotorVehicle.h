/*/////////////////////////////////////////////////////////////////////////
                        Assignment 7 - Milestone 1
Full Name  : Chia-Yu Chien
Student ID#: 157049222
Email      : cchien8@myseneca.ca
Section    : NCC

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
/////////////////////////////////////////////////////////////////////////*/

#ifndef SENECA_MOTORVECHICLE_H__
#define SENECA_MOTORVECHICLE_H__

#define LICENSE_PLATE_CHAR_LENGTH 9
#define ADDRESS_CHAR_LENGTH 64

#include <iostream>

namespace seneca {

class MotorVehicle {
  // m_license is a license plate number as a statically allocated array of
  // characters of size 9.
  char m_license[LICENSE_PLATE_CHAR_LENGTH];
  // m_address is the address where the vehicle is at a given moment as a
  // statically allocated array of characters of size 64.
  char m_address[ADDRESS_CHAR_LENGTH];
  // m_builtYear is the year when the vehicle was built.
  int m_builtYear;

public:
  MotorVehicle(const char *license, int builtYear);

  void moveTo(const char *address);

  std::ostream &write(std::ostream &os) const;

  std::istream &read(std::istream &in);
};

std::ostream &operator<<(std::ostream &ostr, const MotorVehicle &vehicle);

std::istream &operator>>(std::istream &istr, MotorVehicle &vehicle);
} // namespace seneca

#endif // !SENECA_MOTORVECHICLE_H__