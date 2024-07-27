#ifndef SENECA_TEXT_H__
#define SENECA_TEXT_H__

#include <iostream>

namespace seneca {
class Text {
  char *m_filename;
  char *m_content;

  int getFileLength() const;

  void setFilename(const char *filename);

  void setContent(const char *content);

protected:
  const char &operator[](int index) const;

public:
  Text(const char *filename = nullptr);

  // copy constructor
  Text(const Text &);

  ~Text();

  // copy assignment
  Text &operator=(const Text &);

  void read();

  virtual void write(std::ostream &os) const;
};

std::ostream &operator<<(std::ostream &os, const Text &text);
} // namespace seneca
#endif // !SENECA_PERSON_H__
