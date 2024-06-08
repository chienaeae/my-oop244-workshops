/*

Full Name  : Chia-Yu Chien
Student ID#: 157049222
Email      : cchien8@myseneca.ca

I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Account.h"

using namespace std;
namespace seneca
{
   void Account::setEmpty()
   {
      m_number = -1;
      m_balance = 0.0;
   }

   void Account::setInvalidEmpty()
   {
      m_number = -1;
      m_balance = 0;
   }

   // New account
   Account::Account()
   {
      m_number = 0;
      m_balance = 0.0;
   }
   Account::Account(int number, double balance)
   {
      setEmpty();
      if (number >= 10000 && number <= 99999 && balance > 0)
      {
         m_number = number;
         m_balance = balance;
      }
   }
   std::ostream &Account::display() const
   {
      if (*this)
      {
         cout << " ";
         cout << m_number;
         cout << " | ";
         cout.width(12);
         cout.precision(2);
         cout.setf(ios::right);
         cout.setf(ios::fixed);
         cout << m_balance;
         cout.unsetf(ios::right);
         cout << " ";
      }
      else if (~*this)
      {
         cout << "  NEW  |         0.00 ";
      }
      else
      {
         cout << "  BAD  |    ACCOUNT   ";
      }
      return cout;
   }

   bool Account::isInvalidEmpty() const
   {
      // invalid empty if number is set to -1 and the balance is set to 0
      return m_number == -1 && m_balance == 0;
   }

   bool Account::isNew() const
   {
      return m_number == 0;
   }

   bool Account::isValid() const
   {
      return isValidAccNumber(m_number) && m_balance >= 0;
   }

   bool Account::isValidAccNumber(int accNumber) const
   {
      return accNumber > 9999 && accNumber < 100000;
   }

   Account::operator bool() const
   {
      return isValid();
   }

   Account::operator int() const
   {
      return m_number;
   }

   Account::operator double() const
   {
      return m_balance;
   }

   bool Account::operator~() const
   {
      return isNew();
   }

   Account &Account::operator=(int accNumber)
   {
      if (!isValidAccNumber(accNumber))
      {
         // If the integer value is an invalid account number, the object should be set to an invalid empty state instead.
         setInvalidEmpty();
      }
      else if (!~*this)
      {
         // If the account is not new, then this operator should not perform any action.
      }
      else
      {
         m_number = accNumber;
      }
      return *this;
   }

   Account &Account::operator=(Account &acc)
   {
      if (!~*this || !acc.isValid())
      {
         // If the left Account operand is not new or the right account operand is not valid, no action should be taken.
      }
      else
      {
         m_number = acc.m_number;
         m_balance = acc.m_balance;
         acc.m_balance = 0;
         acc.m_number = 0;
      }

      return *this;
   }

   Account &Account::operator+=(double money)
   {
      if (!isValid() || money < 0)
      {
         // if the account is in an invalid state or the double value is negative, no action should be taken.
      }
      else
      {
         m_balance += money;
      }
      return *this;
   }
   Account &Account::operator-=(double money)
   {
      if (!isValid() || money < 0 || m_balance < money)
      {
         // if the account is in an invalid state, the double value is negative or there is not enough money in the account no action should be taken.
      }
      else
      {
         m_balance -= money;
      }
      return *this;
   }
   Account &Account::operator<<(Account &acc)
   {
      if (this == &acc)
      {
         // Funds of an account should not be able to be moved to itself and this operation does not affect the account.
      }
      else if (!isValid() || !acc.isValid())
      {
      }
      else
      {
         m_balance += acc.m_balance;
         acc.m_balance = 0;
      }
      return *this;
   }
   Account &Account::operator>>(Account &acc)
   {
      if (this == &acc)
      {
         // Funds of an account should not be able to be moved to itself and this operation does not affect the account.
      }
      else if (!isValid() || !acc.isValid())
      {
      }
      else
      {
         acc.m_balance += m_balance;
         m_balance = 0;
      }
      return *this;
   }

   double operator+(const Account &acc1, const Account &acc2)
   {
      if (!acc1.isValid() || !acc2.isValid())
      {
         // If any of the two accounts is invalid, then zero is returned.
         return 0;
      }
      return acc1.m_balance + acc2.m_balance;
   }

   double operator+=(double &money, const Account &acc)
   {
      if (!acc.isValid())
      {
         return 0;
      }
      money += acc.m_balance;
      return money;
   }

}