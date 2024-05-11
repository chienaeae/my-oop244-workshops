/*
I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/

#ifndef SENECA_SHOPPINGLIST_H // replace with relevant names
#define SENECA_SHOPPINGLIST_H

#include "ShoppingRec.h"

// Your header file content goes here
namespace seneca
{
    const int MAX_NO_OF_RECS = 15;

    bool loadList();
    void displayList();
    void removeBoughtItems();
    void removeItem(int index);
    bool saveList();
    void clearList();
    void toggleBought();
    void addItemToList();
    void removeItemfromList();
    bool listIsEmpty();
};

#endif