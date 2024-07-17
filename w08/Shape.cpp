#include "Shape.h"
#include <iostream>

using namespace std;
namespace seneca {
Shape::~Shape() {}

std::ostream &operator<<(ostream &ostr, const Shape &shape) {
  shape.draw(ostr);
  return ostr;
}

std::istream &operator>>(istream &istr, Shape &shape) {
  shape.getSpecs(istr);
  return istr;
}
} // namespace seneca