#ifndef SENECA_LINE_H__
#define SENECA_LINE_H__

#include "LblShape.h"
#include <iostream>

namespace seneca {
class Line : public LblShape {
  int m_length;

public:
  Line();

  Line(const char *label, int length);

  void draw(std::ostream &ostr) const override;

  void getSpecs(std::istream &istr) override;
};
}; // namespace seneca

#endif