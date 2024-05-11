/*
I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/

#ifndef SENECA_SHOPPINGREC_H // replace with relevant names
#define SENECA_SHOPPINGREC_H

// Your header file content goes here
namespace seneca
{
    const int MAX_TITLE_LENGTH = 50;
    const int MAX_QUANTITY_VALUE = 50;
    struct ShoppingRec
    {
        char m_title[MAX_TITLE_LENGTH + 1];
        int m_quantity;
        bool m_bought;
    };

    ShoppingRec getShoppingRec();
    void displayShoppingRec(const ShoppingRec *shp);
    void toggleBoughtFlag(ShoppingRec *rec);
    bool isShoppingRecEmpty(const ShoppingRec *shp);
};

#endif