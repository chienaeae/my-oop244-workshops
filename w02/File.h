/*

Full Name  : Chia-Yu Chien
Student ID#: 157049222
Email      : cchien8@myseneca.ca

I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/

#ifndef SENECA_FILE_H_
#define SENECA_FILE_H_
namespace seneca
{
   bool openFile(const char filename[]);
   void closeFile();
   int noOfRecords();
   // TODO: Declare read prototypes
   bool read(char eName[]);

   bool read(int &eNumber);

   bool read(double &eSalary);

}
#endif // !SENECA_FILE_H_
