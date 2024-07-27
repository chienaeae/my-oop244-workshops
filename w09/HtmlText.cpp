#include "HtmlText.h"
#include "Text.h"
#include <cstring>
#include <iostream>

using namespace std;

namespace seneca {

HtmlText::HtmlText(const char *filename, const char *title)
    : Text(filename), m_title(nullptr) {
  if (title != nullptr) {
    m_title = new char[strlen(title) + 1];
    strcpy(m_title, title);
  }
}

HtmlText::HtmlText(const HtmlText &other) : Text(other), m_title(nullptr) {
  setTitle(other.m_title);
}

HtmlText::~HtmlText() {
  if (m_title != nullptr) {
    delete[] m_title;
    m_title = nullptr;
  }
}

HtmlText &HtmlText::operator=(const HtmlText &other) {
  if (this != &other) {
    Text::operator=(other);
    setTitle(other.m_title);
  }

  return *this;
}

void HtmlText::setTitle(const char *title) {
  if (title) {
    m_title = new char[strlen(title) + 1];
    strcpy(m_title, title);
  } else {
    m_title = nullptr;
  }
}

void HtmlText::write(std::ostream &os) const {
  const char *title = m_title != nullptr ? m_title : "No Title";
  os << "<html><head><title>" << title << "</title></head>\n<body>\n";

  if (m_title != nullptr) {
    os << "<h1>" << m_title << "</h1>\n";
  }

  bool ms = false;
  int index = 0;

  char ch = (*this)[index];
  while (ch != '\0') {
    switch (ch) {
    case ' ':
      if (ms) {
        os << "&nbsp;";
      } else {
        ms = true;
        os << ' ';
      }
      break;
    case '<':
      os << "&lt;";
      ms = false;
      break;
    case '>':
      os << "&gt;";
      ms = false;
      break;
    case '\n':
      os << "<br />\n";
      ms = false;
      break;
    default:
      ms = false;
      os << ch;
      break;
    }
    index++;
    ch = (*this)[index];
  };

  os << "</body>\n</html>";
}

} // namespace seneca