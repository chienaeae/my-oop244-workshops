#include <iostream>
#include <cstring>
#include "Item.h"

using namespace std;

const double TAX_RATE = 0.13f;

namespace seneca
{
    Item::Item() : m_itemName(), m_price(0.0f), m_taxed(false) {}
    void Item::setName(const char *name)
    {
        if (name != nullptr)
        {
            strncpy(m_itemName, name, 20);
            m_itemName[20] = '\0';
        }
        else
        {
            strcpy(m_itemName, "");
        }
    }

    void Item::setEmpty()
    {
        strcpy(m_itemName, "");
        m_price = 0.0f;
        m_taxed = false;
    }

    void Item::set(const char *name, double price, bool taxed)
    {
        setName(name);
        m_price = price;
        m_taxed = taxed;
    }

    double Item::price() const
    {
        return m_price;
    }

    double Item::tax() const
    {
        return m_taxed ? m_price * TAX_RATE : 0.0f;
    }

    bool Item::isValid() const
    {

        return m_price > 0.0f && strcmp(m_itemName, "") != 0;
    }

    void Item::display() const
    {
        if (isValid())
        {
            cout << "| ";
            cout.width(20);
            cout.fill('.');
            cout.setf(ios::left, ios::adjustfield);
            cout << m_itemName;

            cout << " | ";
            cout.width(7);
            cout.fill(' ');
            cout.precision(2);
            cout.setf(ios::right, ios::adjustfield);
            cout << fixed << m_price;

            cout << " | ";
            if (m_taxed)
            {
                cout << "Yes";
            }
            else
            {
                cout << "No ";
            }

            cout << " |\n";
        }
        else
        {
            cout << "| xxxxxxxxxxxxxxxxxxxx | xxxxxxx | xxx |\n";
        }
    }
}