#ifndef SENECA_LIBAPP_H
#define SENECA_LIBAPP_H

#include "Menu.h"

namespace seneca {
class LibApp {
  bool m_changed;
  Menu m_mainMenu;
  Menu m_exitMenu;

  bool confirm(const char *message);
  void load();
  void save();
  void search();
  void returnPub();
  void newPublication();
  void removePublication();
  void checkOutPub();

public:
  LibApp();
  void run();
};
} // namespace seneca
#endif // !SENECA_LIBAPP_H
