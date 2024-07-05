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
#ifndef SENECA_MENU_H__
#define SENECA_MENU_H__

#define MAX_MENU_ITEMS 20

#include <iostream>
namespace seneca {
class MenuItem {
  friend class Menu;
  char *m_content;

  MenuItem(const char *content);
  ~MenuItem();

  operator bool() const;
  operator const char *() const;

  // display the content of the MenuItem on ostream
  std::ostream &display(std::ostream &ostr) const;

  // A MenuItem object cannot be copied from or assigned to another MenuItem
  // object.
  MenuItem &operator=(const MenuItem &) = delete;
  MenuItem(const MenuItem &) = delete;
};

class Menu {
  MenuItem m_title;
  MenuItem *m_items[MAX_MENU_ITEMS];
  int m_itemsCount;

  std::ostream &displayTitle(std::ostream &ostr) const;
  std::ostream &displayItems(std::ostream &ostr) const;

  // A Menu Object can not be copied or assigned to another Menu Object.
  Menu *operator=(const Menu &) = delete;
  Menu(const Menu &) = delete;

public:
  Menu(const char *title = nullptr);
  ~Menu();

  unsigned int run();
  unsigned int operator~() { return run(); }

  Menu &operator<<(const char *menuitemConent);

  explicit operator bool();
  operator int() const;
  operator unsigned int() const;

  const char *operator[](unsigned) const;

  friend std::ostream &operator<<(std::ostream &ostr, const Menu &menu);
};

} // namespace seneca

#endif