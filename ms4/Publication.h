// Final Project Milestone 4
// Publication Module
// File	Publication.h
// Version 1.0
// Author	Chia-Yu Chien
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
//
/////////////////////////////////////////////////////////////////

#ifndef SENECA_PUBLICATION_H__
#define SENECA_PUBLICATION_H__

#include "Date.h"
#include "Lib.h"
#include "Utils.h"

namespace seneca {

class Publication : public Streamable {

  // m_title is a c-string to hold a dynamic title for the publication.
  //
  // This attribute is null by default.
  char *m_title;

  // m_shelfId holds the location of the publication in the library. m_shelfId
  // is a c-string that is exactly 4 characters long.
  //
  // This attribute is an empty string by default.
  char *m_shelfId;

  // m_membership is an integer to hold a 5-digit membership number of members
  // of the library.  if the membership number is '0', it means the publication
  // is available and is not checked out by any members. If the membership
  // number is a five-digit number, it means the publication is checked out by
  // the member holding that membership number.
  //
  // This attribute is zero by default.
  int m_membership;

  // m_libRef is the serial number is used internally to uniquely identify each
  // publication in the system.
  //
  // This attribute is -1 by default.
  int m_libRef;

  // In periodical publications, this date is used for the publish date of
  // the item.
  //
  // In Books, this date is used to keep the date on which the book was borrowed
  // by the member.
  //
  // The Date, by default, is set to the current date.
  Date m_date;

  void reset();

  bool isValidShelfID(const char *m_shelfId);

public:
  // Sets all the attributes to their default values.
  Publication();

  ~Publication();

  // Sets the membership attribute to either zero or a five-digit integer.
  virtual void set(int member_id);

  // Sets the **libRef** attribute value
  void setRef(int value);

  void setTitle(const char *title);

  void setShelfId(const char *sheldIf);

  // Sets the date to the current date of the system.
  void resetDate();

  // Returns the character 'P' to identify this object as a "Publication object"
  virtual char type() const;

  // Returns true is the publication is checkout (membership is non-zero)
  bool onLoan() const;

  // Returns the date attribute
  Date checkoutDate() const;

  // Returns true if the argument title appears anywhere in the title of the
  // publication. Otherwise, it returns false; (use strstr() function in
  // <cstring>)
  bool operator==(const char *title) const;

  // Returns the title attribute
  operator const char *() const;

  // Returns the libRef attirbute.
  int getRef() const;

  std::ostream &write(std::ostream &os = std::cout) const override;

  std::istream &read(std::istream &is = std::cin) override;

  bool conIO(std::ios &io) const override;

  operator bool() const override;

  Publication &operator=(const Publication &);

  Publication(const Publication &);
};

}; // namespace seneca

#endif