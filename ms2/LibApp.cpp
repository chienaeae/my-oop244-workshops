#include "LibApp.h"

#include <iostream>

using namespace std;

namespace seneca {
LibApp::LibApp()
    : m_changed(false), m_mainMenu("Seneca Library Application"),
      m_exitMenu(
          "Changes have been made to the data, what would you like to do?") {
  // setup main menu
  m_mainMenu << "Add New Publication"
             << "Remove Publication"
             << "Checkout publication from library"
             << "Return publication to library";
  // setup exit menu
  m_exitMenu << "Save changes and exit"
             << "Cancel and go back to the main menu";

  load();
}

bool LibApp::confirm(const char *message) {
  Menu confirmMenu(message);
  confirmMenu << "Yes";
  // run the menu and return true if the run method of Menu returns 1 otherwise
  // this function returns false
  unsigned int selection = confirmMenu.run();
  if (selection == 0) {
    cout << "\n";
  }
  return selection == 1;
}

void LibApp::load() { cout << "Loading Data\n"; }
void LibApp::save() { cout << "Saving Data\n"; }
void LibApp::search() { cout << "Searching for publication\n"; }
void LibApp::returnPub() {
  search();
  cout << "Returning publication\n";
  cout << "Publication returned\n\n";
  m_changed = true;
}

void LibApp::newPublication() {
  cout << "Adding new publication to library\n";
  bool confirmed = confirm("Add this publication to library?");
  if (confirmed) {
    m_changed = true;
    cout << "Publication added\n\n";
  }
}

void LibApp::removePublication() {
  cout << "Removing publication from library\n";
  search();
  bool confirmed = confirm("Remove this publication from the library?");
  if (confirmed) {
    m_changed = true;
    cout << "Publication removed\n\n";
  }
}
void LibApp::checkOutPub() {
  search();
  bool confirmed = confirm("Check out publication?");
  if (confirmed) {
    m_changed = true;
    cout << "Publication checked out\n\n";
  }
}

void LibApp::run() {
  /*
  loop until done
    display menu
    if first option  new publication otherwise
    if second option remove publication otherwise
    if third option checkout otherwise
    if fourth option return publication otherwise
        if changed
           Warning menu and choices
           if save selected save and its done otherwise
           if discard selected
              final confirmation for exit
              if exit selected
                 its done (no saving)
              end if
           end if
        otherwise (no change)
           it is done
        end if
    end if
  end loop
  goodbye message
  */
  bool done = false;
  while (!done) {
    unsigned int selection = m_mainMenu.run();
    switch (selection) {
    case 1:
      newPublication();
      break;
    case 2:
      removePublication();
      break;
    case 3:
      checkOutPub();
      break;
    case 4:
      returnPub();
      break;
    default:
      if (m_changed) {
        unsigned int exitSelection = m_exitMenu.run();
        if (exitSelection == 1) {
          // Save changes and exit
          save();
          done = true;
        } else if (exitSelection == 2) {
          // Cancel and go back to the main menu
          cout << "\n";
          break;
        } else {
          bool confirmed =
              confirm("This will discard all the changes are you sure?");
          if (confirmed) {
            done = true;
          }
        }
      } else {
        done = true;
      }
      break;
    }
  }
  cout << "\n";
  cout << "-------------------------------------------\n";
  cout << "Thanks for using Seneca Library Application\n";
}
} // namespace seneca
