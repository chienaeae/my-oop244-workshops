#include "Line.h"
#include "LblShape.h"
#include <cstring>
#include <iostream>
#include <limits>

using namespace std;

namespace seneca {
Line::Line() : LblShape() { m_length = 0; }

Line::Line(const char *label, int length) : LblShape(label) {
  m_length = length;
}

void Line::draw(std::ostream &ostr) const {
  auto label = LblShape::label();
  if (m_length > 0 && label != nullptr) {
    ostr << label << "\n";
    for (int i = 0; i < m_length; i++) {
      ostr << "=";
    }
  }
}

void Line::getSpecs(std::istream &istr) {
  LblShape::getSpecs(istr);
  istr >> m_length;
  istr.ignore(numeric_limits<streamsize>::max(), '\n');
}

} // namespace seneca