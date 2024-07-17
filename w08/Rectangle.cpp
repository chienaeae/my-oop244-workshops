#include "Rectangle.h"
#include "LblShape.h"
#include <cstring>
#include <iomanip>
#include <iostream>
#include <limits>

using namespace std;
namespace seneca {

Rectangle::Rectangle(const char *label, int width, int height)
    : LblShape(label) {
  m_width = width;
  m_height = height;
  int labelLength = strlen(LblShape::label());
  if (m_width < 3 || m_width < labelLength + 2) {
    m_width = 0;
    m_height = 0;
  }
}

Rectangle::Rectangle() : LblShape() {
  m_width = 0;
  m_height = 0;
}

void Rectangle::draw(std::ostream &ostr) const {
  if (m_width != 0 && m_height != 0) {

    // first line
    ostr << "+";
    for (int i = 0; i < m_width - 2; i++) {
      ostr << "-";
    }
    ostr << "+\n";

    // second line
    auto label = LblShape::label();
    ostr << "|";
    ostr << label << right << setw(m_width - strlen(label));
    ostr << "|\n";

    // next lines
    for (int i = 0; i < m_height - 3; i++) {
      ostr << "|";
      ostr << right << setw(m_width);
      ostr << "|\n";
    }
    // last line
    ostr << "+";
    for (int i = 0; i < m_width - 2; i++) {
      ostr << "-";
    }
    ostr << "+";
  }
}

void Rectangle::getSpecs(std::istream &istr) {
  LblShape::getSpecs(istr);
  char comma; // `,`
  istr >> m_width >> comma >> m_height;
  istr.ignore(numeric_limits<streamsize>::max(), '\n');
}
} // namespace seneca