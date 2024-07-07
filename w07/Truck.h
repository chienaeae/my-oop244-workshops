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

#ifndef SENECA_TRUCK_H__
#define SENECA_TRUCK_H__
#include <iostream>

#include "MotorVehicle.h"

namespace seneca {

class Truck : public MotorVehicle {
  double m_capacity;
  double m_cargoLoad;

public:
  Truck(const char *license, int builtYear, double capacity,
        const char *address);

  bool addCargo(double cargo);

  bool unloadCargo();

  std::ostream &write(std::ostream &os) const;

  std::istream &read(std::istream &in);
};

std::ostream &operator<<(std::ostream &ostr, const Truck &truck);

std::istream &operator>>(std::istream &istr, Truck &truck);
} // namespace seneca

#endif // SENECA_TRUCK_H__