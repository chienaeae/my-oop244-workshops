// Final Project Milestone 1
// Menu Module
// File	Menu.cpp
// Version 1.0
// Author	Chia-Yu Chien
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
//
/////////////////////////////////////////////////////////////////

#include "Menu.h"
#include <cstring>
#include <iostream>

using namespace std;

namespace seneca {

// -- MenuItem
MenuItem::MenuItem(const char *content) {
  if (content == nullptr) {
    m_content = nullptr;
    return;
  }
  m_content = new char[strlen(content) + 1];
  strcpy(m_content, content);
}
MenuItem::~MenuItem() { delete[] m_content; }

MenuItem::operator bool() const { return m_content != nullptr; }

MenuItem::operator const char *() const { return m_content; }

std::ostream &MenuItem::display(std::ostream &ostr) const {
  ostr << m_content;

  return ostr;
}

// -- Menu

Menu::Menu(const char *title) : m_title(title), m_items(), m_itemsCount(0) {}

Menu::~Menu() {
  for (auto item : m_items) {
    delete item;
  }
}
std::ostream &Menu::displayTitle(std::ostream &ostr) const {
  if (m_title) {
    m_title.display(ostr);
  }
  return ostr;
}

std::ostream &Menu::displayItems(std::ostream &ostr) const {
  for (int i = 0; i < m_itemsCount; i++) {
    ostr << " " << i + 1 << "- ";
    m_items[i]->display(ostr);
    ostr << "\n";
  }

  ostr << " 0- Exit\n";
  ostr << "> ";

  return ostr;
}

unsigned int Menu::run() {
  if (m_title) {
    m_title.display(cout);
    cout << ":\n";
  }
  displayItems(cout);

  int selection;
  cin >> selection;

  while (cin.fail() || selection < 0 || selection > m_itemsCount) {
    while ((getchar()) != '\n')
      ;
    cin.clear();
    cout << "Invalid Selection, try again: ";
    cin >> selection;
  }

  while ((getchar()) != '\n')
    ;
  return (unsigned int)selection;
}

Menu &Menu::operator<<(const char *menuitemConent) {

  if (m_itemsCount == MAX_MENU_ITEMS) {
    return *this;
  }

  auto newItem = new MenuItem(menuitemConent);
  m_items[m_itemsCount] = newItem;

  m_itemsCount++;

  return *this;
}

Menu::operator bool() {
  // return true if the Menu has one or more
  return m_itemsCount != 0;
}

Menu::operator int() const {
  // return the number of MenuItems
  return m_itemsCount;
}

Menu::operator unsigned int() const {
  // return the number of MenuItems
  return m_itemsCount;
}

const char *Menu::operator[](unsigned index) const {
  return m_items[index % m_itemsCount]->m_content;
}

std::ostream &operator<<(std::ostream &ostr, const Menu &menu) {
  menu.displayTitle(ostr);
  return ostr;
}

} // namespace seneca
