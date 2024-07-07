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

#include "MotorVehicle.h"

#include <cstring>
#include <iomanip>
#include <iostream>

using namespace std;
namespace seneca {

MotorVehicle::MotorVehicle(const char *license, int builtYear) {
  strcpy(m_license, license);
  strcpy(m_address, "Factory");
  m_builtYear = builtYear;
}

void MotorVehicle::moveTo(const char *address) {
  if (strcmp(m_address, address) != 0) {
    // Output Format: |[LICENSE_PLATE]| |[CURRENT_ADDRESS] --->
    // [NEW_ADDRESS]|<ENDL>
    cout << "|" << setw(8) << right << m_license << "| "
         << "|" << setw(20) << right << m_address << " ---> " << setw(20)
         << left << address << "|\n";
    strcpy(m_address, address);
  }
}

std::ostream &MotorVehicle::write(std::ostream &os) const {
  // Output Format: | [YEAR] | [PLATE] | [ADDRESS]
  os << "| " << m_builtYear << " | " << m_license << " | " << m_address;
  return os;
}

std::istream &MotorVehicle::read(std::istream &in) {
  cout << "Built year: ";
  in >> m_builtYear;
  cout << "License plate: ";
  in >> m_license;
  cout << "Current location: ";
  in >> m_address;
  return in;
}

std::ostream &operator<<(std::ostream &ostr, const MotorVehicle &vehicle) {
  return vehicle.write(ostr);
}

std::istream &operator>>(std::istream &istr, MotorVehicle &vehicle) {
  return vehicle.read(istr);
}
} // namespace seneca