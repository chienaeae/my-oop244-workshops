#ifndef SENECA_LBLSHAPE_H__
#define SENECA_LBLSHAPE_H__

#include "Shape.h"
#include <iostream>

namespace seneca {
class LblShape : public Shape {

  char *m_label = nullptr;

  // copy and copy assignment prevention goes here
  LblShape &operator=(const LblShape &) = delete;

  LblShape(const LblShape &) = delete;

protected:
  const char *label() const;

public:
  void getSpecs(std::istream &istr) override;

  LblShape();

  LblShape(const char *label);

  ~LblShape() override;
};
}; // namespace seneca

#endif