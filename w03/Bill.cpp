#include <iostream>
#include <cstring>
#include "Bill.h"

using namespace std;

namespace seneca
{
    Bill::Bill() : m_title(), m_items(nullptr), m_noOfItems(0), m_itemsAdded(0) {}

    void Bill::setEmpty()
    {
        strcpy(m_title, "");
        m_items = nullptr;
    }

    bool Bill::isValid() const
    {
        if (strcmp(m_title, "") == 0 || m_items == nullptr)
        {
            return false;
        }

        for (int i = 0; i < m_noOfItems; i++)
        {
            if (!m_items[i].isValid())
            {
                return false;
            }
        }
        return true;
    }

    double Bill::totalTax() const
    {
        double totalTax = 0;
        for (int i = 0; i < m_noOfItems; i++)
        {
            totalTax += m_items[i].tax();
        }
        return totalTax;
    }

    double Bill::totalPrice() const
    {
        double totalPrice = 0;
        for (int i = 0; i < m_noOfItems; i++)
        {
            totalPrice += m_items[i].price();
        }
        return totalPrice;
    }

    void Bill::Title() const
    {
        cout << "+--------------------------------------+\n";
        if (isValid())
        {
            cout << "| ";
            cout.width(36);
            cout.setf(ios::left, ios::adjustfield);
            cout << m_title;
            cout << " |\n";
        }
        else
        {
            cout << "| Invalid Bill                         |\n";
        }
        cout << "+----------------------+---------+-----+\n"
             << "| Item Name            | Price   + Tax |\n"
             << "+----------------------+---------+-----+\n";
    }

    void Bill::footer() const
    {
        cout << "+----------------------+---------+-----+\n";
        if (isValid())
        {
            cout.fill(' ');
            cout.setf(ios::right, ios::adjustfield);

            cout << "|                Total Tax: ";
            cout.width(10);
            cout.precision(2);
            cout << fixed << totalTax();
            cout << " |\n";

            cout << "|              Total Price: ";
            cout.width(10);
            cout.precision(2);
            cout << fixed << totalPrice();
            cout << " |\n";

            cout << "|          Total After Tax: ";
            cout.width(10);
            cout.precision(2);
            cout << fixed << totalTax() + totalPrice();
            cout << " |\n";
        }
        else
        {
            cout << "| Invalid Bill                         |\n";
        }
        cout << "+--------------------------------------+\n";
    }

    void Bill::init(const char *title, int noOfItems)
    {
        if (title == nullptr || noOfItems <= 0)
        {
            setEmpty();
            return;
        }
        m_noOfItems = noOfItems;
        m_itemsAdded = 0;
        strncpy(m_title, title, 36);
        m_title[36] = '\0';

        m_items = new Item[m_noOfItems];
    }

    bool Bill::add(const char *item_name, double price, bool taxed)
    {
        if (m_itemsAdded < m_noOfItems)
        {
            m_items[m_itemsAdded]
                .set(item_name, price, taxed);
            m_itemsAdded++;
            return true;
        }
        else
        {
            return false;
        }
    }

    void Bill::display() const
    {
        Title();
        for (int i = 0; i < m_noOfItems; i++)
        {
            m_items[i].display();
        }
        footer();
    }

    void Bill::deallocate()
    {
        delete[] m_items;
        m_items = nullptr;
    }
}