/*
I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/

#ifndef SENECA_UTILS_H // replace with relevant names
#define SENECA_UTILS_H

// Your header file content goes here
namespace seneca
{
    void flushkeys();
    bool ValidYesResponse(char ch);
    bool yes();
    void readCstr(char cstr[], int len);
    int readInt(int min, int max);

}

#endif