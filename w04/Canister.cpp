#define _CRT_SECURE_NO_WARNINGS
#include <istream>
#include <iomanip>
#include <cstring>
#include "Canister.h"

using namespace std;

namespace seneca
{
    const double PI = 3.14159265;

    Canister::Canister()
    {
        setToDefault();
    }

    Canister::Canister(const char *contentName)
    {
        setToDefault();
        setName(contentName);
    }

    Canister::Canister(double height, double diameter,
                       const char *contentName)
    {
        setToDefault();
        setName(contentName);

        if (height >= 10.0f && height <= 40.0f && diameter >= 10.0f && diameter <= 30.0f)
        {
            m_diameter = diameter;
            m_height = height;
        }
        else
        {
            m_usable = false;
        }
    }

    Canister::~Canister()
    {

        if (m_contentName != nullptr)
        {
            delete[] m_contentName;
            m_contentName = nullptr;
        }
    }

    void Canister::setToDefault()
    {
        m_contentName = nullptr;
        m_height = 13.0f;
        m_diameter = 10.0f;
        m_contentVolume = 0.0f;
        m_usable = true;
    }

    bool Canister::isEmpty() const
    {
        return m_contentVolume < 0.00001f;
    }

    bool Canister::hasSameContent(const Canister &C) const
    {
        return strcmp(m_contentName, C.m_contentName);
    }

    void Canister::setName(const char *Cstr)
    {
        if (Cstr != nullptr && m_usable)
        {
            if (m_contentName != nullptr)
            {
                delete[] m_contentName;
            }
            m_contentName = new char[strlen(Cstr) + 1];
            strcpy(m_contentName, Cstr);
        }
    }

    void Canister::clear()
    {
        if (m_contentName != nullptr)
        {
            delete[] m_contentName;
            m_contentName = nullptr;
        }
        m_contentVolume = 0.0f;
        m_usable = true;
    }

    double Canister::capacity() const
    {
        // PI: 3.14159265
        // H: Height
        // D: Diameter
        // Capacity = PI x (H - 0.267) x (D/2) x (D/2)
        return PI * (m_height - 0.267) * (m_diameter / 2) * (m_diameter / 2);
    }

    double Canister::volume() const
    {
        return m_contentVolume;
    }

    Canister &Canister::setContent(const char *contentName)
    {
        if (contentName == nullptr)
        {
            m_usable = false;
        }
        else if (isEmpty())
        {
            setName(contentName);
        }
        else if (strcmp(m_contentName, contentName) != 0)
        {
            m_usable = false;
        }
        return *this;
    }

    Canister &Canister::pour(double quantity)
    {
        if (m_usable && quantity > 0 && quantity + volume() <= capacity())
        {
            m_contentVolume += quantity;
        }
        else
        {
            m_usable = false;
        }
        return *this;
    }

    Canister &Canister::pour(Canister &C)
    {
        setContent(C.m_contentName);
        if (C.volume() > (capacity() - volume()))
        {
            C.m_contentVolume -= (capacity() - volume());
            m_contentVolume = capacity();
        }
        else
        {
            pour(C.m_contentVolume);
            C.m_contentVolume = 0.0f;
        }
        return *this;
    }

    std::ostream &Canister::display() const
    {
        cout.width(7);
        cout.precision(1);
        cout << fixed << capacity();

        cout << "cc (" << m_height << "x" << m_diameter << ") Canister";
        if (!m_usable)
        {
            cout << " of Unusable content, discard!";
        }
        else if (m_contentName != nullptr)
        {
            cout << " of ";

            cout.width(7);
            cout << volume();

            cout << "cc   " << m_contentName;
        }
        return cout;
    }
}