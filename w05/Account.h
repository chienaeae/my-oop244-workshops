/*

Full Name  : Chia-Yu Chien
Student ID#: 157049222
Email      : cchien8@myseneca.ca

I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/
#ifndef SENECA_ACCOUNT_H_
#define SENECA_ACCOUNT_H_
#include <iostream>

namespace seneca
{
   class Account
   {
      int m_number;
      double m_balance;
      void setEmpty();
      void setInvalidEmpty();

      bool isInvalidEmpty() const;
      bool isNew() const;
      bool isValid() const;
      bool isValidAccNumber(int accNumber) const;

   public:
      Account();
      Account(int number, double balance);
      std::ostream &display() const;

      operator bool() const;
      operator int() const;
      operator double() const;

      bool operator~() const;

      Account &operator=(int accNumber);
      Account &operator=(Account &acc);
      Account &operator+=(double money);
      Account &operator-=(double money);
      Account &operator<<(Account &acc);
      Account &operator>>(Account &acc);

      friend double operator+(const Account &acc1, const Account &acc2);
      friend double operator+=(double &money, const Account &acc);
   };

}
#endif // SENECA_ACCOUNT_H_