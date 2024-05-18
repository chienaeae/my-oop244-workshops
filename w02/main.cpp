/***********************************************************************
// Intro. to Object Oriented Programming
// Workshop 2
// Version 1.0
// Description
// professor's tester program
//
// Revision History
// -----------------------------------------------------------
// Name            Date            Reason
//
/////////////////////////////////////////////////////////////////
***********************************************************************/
#include "Employee.h"
#include <iostream>
using namespace seneca;
using namespace std;
int main()
{
   if (load())
   {
      display();
   }
   deallocateMemory();

   return 0;
}