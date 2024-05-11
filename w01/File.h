/*
I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/

#ifndef SENECA_FILE_H // replace with relevant names
#define SENECA_FILE_H

#include "ShoppingRec.h"

// Your header file content goes here
namespace seneca
{
    const char *const SHOPPING_DATA_FILE = "shoppinglist.csv";

    bool openFileForRead();
    bool openFileForOverwrite();
    void closeFile();
    bool freadShoppingRec(ShoppingRec *rec);
    void fwriteShoppintRec(const ShoppingRec *rec);
}

#endif