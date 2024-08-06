#ifndef SENECA_LIBAPP_H
#define SENECA_LIBAPP_H

#include "Lib.h"
#include "Menu.h"
#include "Publication.h"

namespace seneca {
class LibApp {
  bool m_changed;
  Menu m_mainMenu;
  Menu m_exitMenu;
  Menu m_pubMenu;
  // File name
  char *m_filename;
  // Publication Pointer Array
  Publication *m_ppa[SENECA_LIBRARY_CAPACITY];
  // Number of Loaded Publications
  int m_nolp;
  // Last Library Reference Number
  int m_llrn;

  bool confirm(const char *message);
  void load();
  void save();
  int search(int mode);
  Publication *getPub(int libRef);
  void newPublication();
  void removePublication();
  void returnPub();
  void checkOutPub();

public:
  LibApp(const char *filename);
  ~LibApp();
  void run();
};
} // namespace seneca
#endif // !SENECA_LIBAPP_H
