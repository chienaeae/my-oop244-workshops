/*

Full Name  : Chia-Yu Chien
Student ID#: 157049222
Email      : cchien8@myseneca.ca

I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include "File.h"

namespace seneca
{
   FILE *fptr;
   bool openFile(const char filename[])
   {
      fptr = fopen(filename, "r");
      return fptr != NULL;
   }
   int noOfRecords()
   {
      int noOfRecs = 0;
      char ch;
      while (fscanf(fptr, "%c", &ch) == 1)
      {
         noOfRecs += (ch == '\n');
      }
      rewind(fptr);
      return noOfRecs;
   }
   void closeFile()
   {
      if (fptr)
         fclose(fptr);
   }

   /* TODO: read functions go here */
   bool read(char eName[])
   {
      int read = fscanf(fptr, "%[^\n]\n", eName);
      return read == 1;
   }

   bool read(int &eNumber)
   {
      int read = fscanf(fptr, "%d,", &eNumber);
      return read == 1;
   }

   bool read(double &eSalary)
   {
      int read = fscanf(fptr, "%lf,", &eSalary);
      return read == 1;
   }
}