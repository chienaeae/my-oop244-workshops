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

#include "Truck.h"

#include <cstring>
#include <iostream>

#include "MotorVehicle.h"

using namespace std;

namespace seneca {

Truck::Truck(const char *license, int builtYear, double capacity,
             const char *address)
    : MotorVehicle(license, builtYear), m_capacity(capacity) {
  moveTo(address);
  m_cargoLoad = 0;
}

bool Truck::addCargo(double cargo) {
  if (m_cargoLoad >= m_capacity) {
    return false;
  }

  if (m_cargoLoad + cargo > m_capacity) {
    m_cargoLoad = m_capacity;
  } else {
    m_cargoLoad += cargo;
  }

  return true;
}

bool Truck::unloadCargo() {
  if (m_cargoLoad == 0) {
    return false;
  }

  m_cargoLoad = 0;
  return true;
}

std::ostream &Truck::write(std::ostream &os) const {
  // Output format: | [YEAR] | [PLATE] | [ADDRESS] | [CURRENT_CARGO]/[CAPACITY]
  os << static_cast<const MotorVehicle &>(*this) << " | " << m_cargoLoad << "/"
     << m_capacity;
  return os;
}

std::istream &Truck::read(std::istream &in) {
  in >> static_cast<MotorVehicle &>(*this);
  cout << "Capacity: ";
  in >> m_capacity;
  cout << "Cargo: ";
  in >> m_cargoLoad;
  return in;
}

std::ostream &operator<<(std::ostream &ostr, const Truck &truck) {
  return truck.write(ostr);
}

std::istream &operator>>(std::istream &istr, Truck &truck) {
  return truck.read(istr);
}
} // namespace seneca
