// Final Project Milestone 4
// Publication Module
// File	Publication.cpp
// Version 1.0
// Author	Chia-Yu Chien
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
//
/////////////////////////////////////////////////////////////////

#include "Publication.h"
#include "Date.h"
#include "Utils.h"
#include <cstring>
#include <iomanip>
#include <string>

using namespace std;

namespace seneca {

Publication::Publication()
    : m_title(nullptr), m_shelfId(nullptr), m_membership(0), m_libRef(-1),
      m_date() {
  m_shelfId = new char[1];
  m_shelfId[0] = '\0';
}

Publication::~Publication() {
  if (m_title != nullptr) {
    delete[] m_title;
  }

  if (m_shelfId != nullptr) {
    delete[] m_shelfId;
  }
}

void Publication::set(int member_id) { m_membership = member_id; }

void Publication::setRef(int value) { m_libRef = value; }

void Publication::setTitle(const char *title) {
  if (m_title != nullptr) {
    delete[] m_title;
  }
  if (title) {
    m_title = new char[strlen(title) + 1];
    strcpy(m_title, title);
  } else {
    m_title = nullptr;
  }
}

void Publication::setShelfId(const char *shelfId) {
  if (m_shelfId != nullptr) {
    delete[] m_shelfId;
  }
  if (shelfId) {
    m_shelfId = new char[strlen(shelfId) + 1];
    strcpy(m_shelfId, shelfId);
  } else {
    m_shelfId = new char[1];
    m_shelfId[0] = '\0';
  }
}
void Publication::resetDate() { m_date = Date(); }

char Publication::type() const { return 'P'; }

bool Publication::onLoan() const { return m_membership != 0; }

Date Publication::checkoutDate() const { return m_date; }

bool Publication::operator==(const char *title) const {
  return strstr(m_title, title) != nullptr;
}

Publication::operator const char *() const { return m_title; }

int Publication::getRef() const { return m_libRef; }

void Publication::reset() {
  if (m_title != nullptr) {
    delete[] m_title;
    m_title = nullptr;
  }

  if (m_shelfId != nullptr) {
    delete[] m_shelfId;
    m_shelfId = new char[1];
    m_shelfId[0] = '\0';
  }
  m_membership = 0;
  m_libRef = -1;
  resetDate();
}

bool Publication::isValidShelfID(const char *m_shelfId) {
  return m_shelfId != nullptr &&
         (m_shelfId[0] == '\0' || strlen(m_shelfId) == 4);
}

std::ostream &Publication::write(std::ostream &os) const {
  string printMembership =
      m_membership != 0 ? to_string(m_membership) : " N/A ";

  char truncatedTitle[SENECA_TITLE_WIDTH + 1];
  if (strlen(m_title) > SENECA_TITLE_WIDTH) {
    strncpy(truncatedTitle, m_title, SENECA_TITLE_WIDTH);
    truncatedTitle[SENECA_TITLE_WIDTH] = '\0';
  } else {
    strncpy(truncatedTitle, m_title, strlen(m_title) + 1);
  }

  if (conIO(os)) {
    os << "| " << m_shelfId << " | " << left << setw(SENECA_TITLE_WIDTH)
       << setfill('.') << truncatedTitle << " | " << printMembership << " | "
       << m_date << " |";
  } else {
    os << type() << "\t" << getRef() << "\t" << m_shelfId << "\t" << left
       << setw(SENECA_TITLE_WIDTH) << setfill('.') << truncatedTitle << "\t"
       << printMembership << "\t" << m_date;
  }
  return os;
}

std::istream &Publication::read(std::istream &istr) {
  reset();

  char newShelfID[100];
  char newTitle[100];
  Date newDate;
  int newLibRef;
  int newMembership = 0;

  if (conIO(istr)) {
    // read shelf number
    std::cout << "Shelf No: ";
    istr.get(newShelfID, 100);
    if (!isValidShelfID(newShelfID)) {
      istr.setstate(std::ios::failbit);
    }

    // read title
    std::cout << "Title: ";
    if (!istr.fail()) {
      istr.ignore(1000, '\n');
      istr.get(newTitle, 100);
    }

    // read date
    std::cout << "Date: ";
    if (!istr.fail()) {
      istr >> newDate;
    }

    newLibRef = -1;
  } else {
    // read the libRef number
    istr >> newLibRef;
    istr.ignore();

    // read the shelf number
    istr.get(newShelfID, 100, '\t');
    istr.ignore();

    // read the title
    istr.get(newTitle, 100, '\t');

    // read the membership
    istr >> newMembership;
    istr.ignore();

    // read the date
    istr >> newDate;
  }

  if (!newDate) {
    istr.setstate(std::ios::failbit);
  }

  if (!istr.fail()) {
    setTitle(newTitle);
    setShelfId(newShelfID);
    set(newMembership);
    m_date = newDate;
    setRef(newLibRef);
  }
  return istr;
}

bool Publication::conIO(std::ios &io) const {
  return &io == &cin || &io == &cout;
}

Publication::operator bool() const {
  return m_shelfId != nullptr && m_shelfId[0] != '\0';
}

Publication &Publication::operator=(const Publication &other) {
  if (this != &other) {
    setTitle(other.m_title);
    setShelfId(other.m_shelfId);
    m_membership = other.m_membership;
    m_libRef = other.m_libRef;
    m_date = other.m_date;
  }
  return *this;
}

Publication::Publication(const Publication &other)
    : m_title(nullptr), m_shelfId(nullptr), m_membership(0), m_libRef(-1),
      m_date() {
  setTitle(other.m_title);
  setShelfId(other.m_shelfId);
  m_membership = other.m_membership;
  m_libRef = other.m_libRef;
  m_date = other.m_date;
}
}; // namespace seneca