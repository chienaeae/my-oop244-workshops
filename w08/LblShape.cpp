#include "LblShape.h"
#include "Shape.h"
#include <cstring>
#include <iostream>

using namespace std;
namespace seneca {
const char *LblShape::label() const { return m_label; }

LblShape::LblShape() { m_label = nullptr; }

LblShape::LblShape(const char *label) {
  m_label = new char[strlen(label) + 1];
  strcpy(m_label, label);
}

LblShape::~LblShape() {
  if (m_label != nullptr) {
    delete[] m_label;
    m_label = nullptr;
  }
}

void LblShape::getSpecs(std::istream &istr) {
  char temp[100];
  istr.getline(temp, 100, ',');

  if (m_label != nullptr) {
    delete[] m_label;
    m_label = nullptr;
  }
  m_label = new char[strlen(temp) + 1];
  strcpy(m_label, temp);
}
} // namespace seneca
