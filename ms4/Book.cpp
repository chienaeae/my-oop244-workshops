// Final Project Milestone 4
// Book Module
// File	Book.cpp
// Author	Chia-Yu Chien
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
/////////////////////////////////////////////////////////////////

#include "Book.h"
#include "Date.h"
#include "Lib.h"
#include <cstring>
#include <iomanip>
#include <iostream>

using namespace std;

namespace seneca {
Book::Book() : m_authorName(nullptr) {}

Book::Book(const Book &other) : m_authorName(nullptr) {
  setAuthorName(other.m_authorName);
}

Book &Book::operator=(const Book &other) {
  if (this != &other) {
    Publication::operator=(other);
    setAuthorName(other.m_authorName);
  }
  return *this;
}

Book::~Book() {
  if (m_authorName != nullptr) {
    delete[] m_authorName;
  }
}

void Book::setAuthorName(const char *authorName) {
  if (m_authorName != nullptr) {
    delete[] m_authorName;
  }

  if (authorName) {
    m_authorName = new char[strlen(authorName) + 1];
    strcpy(m_authorName, authorName);
  } else {
    m_authorName = nullptr;
  }
}

char Book::type() const { return 'B'; }

std::ostream &Book::write(std::ostream &os) const {
  Publication::write(os);
  if (Publication::conIO(os)) {
    os << " ";
    if (m_authorName != nullptr) {
      if (strlen(m_authorName) > SENECA_AUTHOR_WIDTH) {
        char temp[SENECA_AUTHOR_WIDTH + 1];
        strncpy(temp, m_authorName, SENECA_AUTHOR_WIDTH);
        temp[SENECA_AUTHOR_WIDTH] = '\0';
        os << left << setw(SENECA_AUTHOR_WIDTH) << setfill(' ') << temp;
      } else {
        os << left << setw(SENECA_AUTHOR_WIDTH) << setfill(' ') << m_authorName;
      }
    } else {
      os << left << setw(SENECA_AUTHOR_WIDTH) << setfill(' ') << "";
    }

  } else {
    os << "\t";
    os << m_authorName;
  }

  os << " |";
  return os;
}

std::istream &Book::read(std::istream &is) {
  Publication::read(is);
  if (m_authorName != nullptr) {
    delete[] m_authorName;
    m_authorName = nullptr;
  }

  char buffer[257];
  if (Publication::conIO(is)) {
    is.ignore();
    cout << "Author: ";
    is.getline(buffer, 257);
  } else {
    is.ignore(1, '\t');
    is.get(buffer, 257);
  }

  if (!is.fail()) {
    m_authorName = new char[strlen(buffer) + 1];
    strcpy(m_authorName, buffer);
  }

  return is;
}

void Book::set(int member_id) {
  Publication::set(member_id);
  Publication::resetDate();
}

Book::operator bool() const {
  return m_authorName != nullptr && strcmp(m_authorName, "") != 0 &&
         Publication::operator bool();
}
}; // namespace seneca