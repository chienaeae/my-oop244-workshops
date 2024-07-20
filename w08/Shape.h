#ifndef SENECA_SHAPE_H__
#define SENECA_SHAPE_H__

#include <iostream>

namespace seneca {
class Shape {
public:
  virtual void draw(std::ostream &ostr) const = 0;

  virtual void getSpecs(std::istream &istr) = 0;

  virtual ~Shape() = 0;
};

std::ostream &operator<<(std::ostream &ostr, const Shape &shape);

std::istream &operator>>(std::istream &istr, Shape &shape);
}; // namespace seneca

#endif