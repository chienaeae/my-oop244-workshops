#ifndef SENECA_RECTABGLE_H__
#define SENECA_RECTABGLE_H__

#include "LblShape.h"
#include <iostream>

namespace seneca {
class Rectangle : public LblShape {
  int m_width;
  int m_height;

public:
  Rectangle();
  Rectangle(const char *label, int width, int height);
  void draw(std::ostream &ostr) const override;
  void getSpecs(std::istream &istr) override;
};
}; // namespace seneca

#endif