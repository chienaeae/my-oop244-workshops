#include "LibApp.h"
#include "Book.h"
#include "Publication.h"
#include "PublicationSelector.h"

#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>

using namespace std;

namespace seneca {
LibApp::LibApp(const char *filename)
    : m_changed(false), m_mainMenu("Seneca Library Application"),
      m_exitMenu(
          "Changes have been made to the data, what would you like to do?"),
      m_pubMenu("Choose the type of publication:"), m_filename(nullptr) {
  // setup main menu
  m_mainMenu << "Add New Publication"
             << "Remove Publication"
             << "Checkout publication from library"
             << "Return publication to library";
  // setup exit menu
  m_exitMenu << "Save changes and exit"
             << "Cancel and go back to the main menu";
  // setup publication menu
  m_pubMenu << "Book"
            << "Publication";

  m_filename = new char[strlen(filename) + 1];
  strcpy(m_filename, filename);
  m_nolp = 0;
  m_llrn = 0;

  for (int i = 0; i < SENECA_LIBRARY_CAPACITY; i++) {
    m_ppa[i] = nullptr;
  }

  load();
}

LibApp::~LibApp() {
  delete[] m_filename;
  for (int i = 0; i < m_nolp; i++) {
    delete m_ppa[i];
  }
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

void LibApp::load() {
  cout << "Loading Data\n";
  ifstream infile(m_filename);
  char type{};
  int i;
  for (i = 0; infile; i++) {
    infile >> type;
    infile.ignore();
    if (infile) {
      Publication *pub = nullptr;
      if (type == 'P') {
        pub = new Publication;
      } else if (type == 'B') {
        pub = new Book;
      }

      if (pub) {
        m_ppa[i] = pub;
        infile >> *m_ppa[i];
        m_nolp++;
        m_llrn = m_ppa[i]->getRef() + 1;
      }
    }
  }

  infile.close();
}
void LibApp::save() {
  cout << "Saving Data\n";
  ofstream outfile(m_filename);

  for (int i = 0; i < m_nolp; i++) {
    // != 0 or != -1 ?
    if (m_ppa[i]->getRef() != 0) {
      outfile << *m_ppa[i];
      outfile << "\n";
    }
  }
}

int LibApp::search(int mode) {
  PublicationSelector pSelector("Select one of the following found matches:");

  unsigned int selection = m_pubMenu.run();
  if (selection == 0) {
    cout << "Aborted!\n\n";
    return -1;
  }

  cout << "Publication Title: ";
  char title[256];
  cin.getline(title, 256);

  for (int i = 0; i < m_nolp; i++) {
    // Check if the publication is a book or a publication
    if ((selection == 1 && m_ppa[i]->type() == 'B') ||
        (selection == 2 && m_ppa[i]->type() == 'P')) {

      // Check if the title matches the title of the publication
      if (m_ppa[i]->getRef() != 0 && m_ppa[i]->operator==(title)) {

        // Check if the publication matches selection mode
        if (mode == SEARCH_ALL) {
          pSelector << m_ppa[i];
        } else if (mode == SEARCH_ON_LOAN && m_ppa[i]->onLoan()) {
          pSelector << m_ppa[i];
        } else if (mode == SEARCH_AVAILABLE && !m_ppa[i]->onLoan()) {
          pSelector << m_ppa[i];
        }
      }
    }
  }
  int libRef = -1;
  if (pSelector) {
    pSelector.sort();
    libRef = pSelector.run();
    if (libRef == 0) {
      cout << "Aborted!\n\n";
    }
  } else {
    cout << "No matches found!\n\n";
  }

  return libRef;
}

Publication *LibApp::getPub(int libRef) {
  for (int i = 0; i < m_nolp; i++) {
    if (m_ppa[i]->getRef() == libRef) {
      return m_ppa[i];
    }
  }
  return nullptr;
}

void LibApp::newPublication() {
  if (m_nolp == SENECA_LIBRARY_CAPACITY) {
    cout << "Library is at its maximum capacity!\n\n";
    return;
  }

  cout << "Adding new publication to the library\n";
  Publication *pub = nullptr;
  unsigned int selection = m_pubMenu.run();

  // 1. get the publication type from the user.
  // 2. in a publication pointer, instantiate a dynamic "Publication" or "Book"
  // based on the user's choice.
  if (selection == 0) {
    cout << "Aborted!\n\n";
    return;
  } else if (selection == 1) {
    pub = new Book;
  } else {
    pub = new Publication;
  }

  // 3. Read the instantiated object from the cin object.
  cin >> *pub;
  // If the cin fails, flush the keyboard, print "Aborted!" and exit.
  if (cin.fail()) {
    delete pub;
    cin.ignore();
    cin.clear();
    cout << "Aborted!\n\n";
    return;
  }

  // If the publication object is not valid print: "Failed to add
  // publication!" and delete the allocated memory.
  if (!*pub) {
    cout << "Failed to add publication!\n";
    delete pub;
    return;
  }

  // If the cin is ok, then confirm that the user wants to add the publication
  // to the library using this prompt: "Add this publication to the library?".
  // If the user did not confirm, print "Aborted!" and exit.
  bool confirmed = confirm("Add this publication to the library?");
  if (confirmed) {
    // Add one to the LLRN and set the library reference number to the value
    pub->setRef(m_llrn++);

    // Add the publication object's address to the end of the PPA and add
    // one to the NOLP.
    m_ppa[m_nolp++] = pub;

    // set the "changed" flag to true
    m_changed = true;
    cout << "Publication added\n\n";
  } else {
    delete pub;
    cout << "Aborted!\n\n";
  }
}

void LibApp::removePublication() {
  cout << "Removing publication from the library\n";
  int libRef = search(SEARCH_ALL);
  Publication *pub = getPub(libRef);
  if (pub == nullptr) {
    return;
  }
  cout << *pub << endl;
  bool confirmed = confirm("Remove this publication from the library?");
  if (confirmed) {
    // Set the library reference of the selected publication to 0
    pub->setRef(0);
    m_changed = true;
    cout << "Publication removed\n\n";
  }
}

void LibApp::checkOutPub() {
  cout << "Checkout publication from the library\n";
  int libRef = search(SEARCH_AVAILABLE);
  Publication *pub = getPub(libRef);
  if (pub == nullptr) {
    return;
  }
  cout << *pub << endl;
  bool confirmed = confirm("Check out publication?");
  if (confirmed) {
    // read a 5-digit number from the console, if invalid print: "Invalid
    // membership number, try again: " and read again
    int membership;
    bool invalidMembership = true;
    cout << "Enter Membership number: ";
    do {
      cin >> membership;
      if (cin.fail() || membership < 10000 || membership > 99999) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid membership number, try again: ";
      } else {
        invalidMembership = false;
      }
    } while (invalidMembership);
    m_changed = true;
    pub->set(membership);
    cout << "Publication checked out\n\n";
  }
}

void LibApp::returnPub() {
  cout << "Return publication to the library\n";
  int libRef = search(SEARCH_ON_LOAN);
  Publication *pub = getPub(libRef);
  if (pub == nullptr) {
    return;
  }

  cout << *pub << endl;
  // If the user selects a publication and confirms the return
  bool confirmed = confirm("Return Publication?");
  if (confirmed) {
    // If the publication is more than 15 days on loan, a 50 cents per day
    // penalty will be calculated for the number of days exceeding the 15 days.
    // Following message is printed: Please pay $9.99 penalty for being X days
    // late!, 9.99 is replaced with the penalty value and X is replaced with the
    // number of late days.
    const Date today;
    const Date checkoutDate = pub->checkoutDate();
    int daysLate = today - checkoutDate - SENECA_MAX_LOAN_DAYS;
    if (daysLate > 0) {
      double penalty = daysLate * 0.5;

      cout << "Please pay $" << setprecision(2) << fixed << penalty
           << " penalty for being " << daysLate << " days late!\n";

      pub->set(0);
    }

    m_changed = true;
    cout << "Publication returned\n\n";
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
