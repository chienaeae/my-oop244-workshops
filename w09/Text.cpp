#include "Text.h"
#include <cstring>
#include <fstream>

using namespace std;

namespace seneca {

Text::Text(const char *filename) : m_filename(nullptr), m_content(nullptr) {
  if (filename != nullptr) {
    m_filename = new char[strlen(filename) + 1];
    strcpy(m_filename, filename);
    read();
  }
}

Text::Text(const Text &other) : m_filename(nullptr), m_content(nullptr) {
  setFilename(other.m_filename);
  setContent(other.m_content);
}

Text::~Text() {
  if (m_filename != nullptr) {
    delete[] m_filename;
    m_filename = nullptr;
  }

  if (m_content != nullptr) {
    delete[] m_content;
    m_content = nullptr;
  }
}

Text &Text::operator=(const Text &other) {
  if (this != &other) {
    setFilename(other.m_filename);
    setContent(other.m_content);
  }
  return *this;
}

int Text::getFileLength() const {
  int len = 0;
  ifstream fin(m_filename);
  while (fin) {
    fin.get();
    len += !!fin;
  }
  return len;
}

void Text::setFilename(const char *filename) {
  if (m_filename != nullptr) {
    delete[] m_filename;
    m_filename = nullptr;
  }

  if (filename) {
    m_filename = new char[strlen(filename) + 1];
    strcpy(m_filename, filename);
  }
}

void Text::setContent(const char *content) {
  if (m_content != nullptr) {
    delete[] m_content;
    m_content = nullptr;
  }

  if (content) {
    m_content = new char[strlen(content) + 1];
    strcpy(m_content, content);
  }
}

const char &Text::operator[](int index) const { return m_content[index]; }

void Text::read() {
  if (m_content != nullptr) {
    delete[] m_content;
    m_content = nullptr;
  }

  int length = getFileLength();
  m_content = new char[length + 1];

  ifstream fin(m_filename);
  if (fin.is_open()) {
    int index = 0;
    char ch;
    while (fin.get(ch)) {
      m_content[index] = ch;
      index++;
    }
    m_content[index] = '\0';
    fin.close();
  }
}

void Text::write(std::ostream &os) const {
  if (m_content != nullptr) {
    os << m_content;
  }
}

std::ostream &operator<<(std::ostream &os, const Text &text) {
  text.write(os);
  return os;
}
} // namespace seneca