/*
    ==================================================
    Final Project (Milestone 5):
    ==================================================
    Name   :           Lei Du
    Seneca email:      ldu13@myseneca.ca
    Seneca Student ID: 047587134
    Date:              December 7, 2021
    Section:           NCC
*/
// I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments. My professor helped me modify the intCheck() function in Menu.cpp.

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <cstring>
#include "Publication.h"

using namespace std;

namespace sdds
{
    Publication::Publication()
    {
        setDef();
    }

    void Publication::setDef()
    {
        delete[]m_title;
        m_title = nullptr;
        m_shelfId[0] = '\0';
        m_membership = 0;
        m_libRef = -1;
        m_date.setToToday();
    }

    void Publication::set(int member_id)
    {
        if (member_id == 0)
            m_membership = 0;
        else if (member_id >= 10000 && member_id <= 99999)
            m_membership = member_id;
    }

    void Publication::setRef(int value)
    {
        m_libRef = value;
    }

    void Publication::resetDate()
    {
        m_date.setToToday();
    }

    char Publication::type() const
    {
        return 'P';
    }

    bool Publication::onLoan() const
    {
        return m_membership != 0;
    }

    Date Publication::checkoutDate() const
    {
        return m_date;
    }

    bool Publication::operator==(const char* title) const
    {
        bool res;
        if (strstr(m_title, title) != nullptr)
        {
            res = true;
        }
        else
        {
            res = false;
        }
        return res;
    }

    Publication::operator const char* () const
    {
        return m_title;
    }
    int Publication::getRef() const
    {
        return m_libRef;
    }

    bool Publication::conIO(std::ios& io) const
    {
        return (&io == &cin || &io == &cout);
    }

    std::ostream& Publication::write(std::ostream& os) const
    {
        if (conIO(os))
        {
            os << "| ";
            os.width(SDDS_SHELF_ID_LEN);
            os << m_shelfId;
            os << " | ";

            if (strlen(m_title) < SDDS_TITLE_WIDTH)
            {
                os.width(SDDS_TITLE_WIDTH);
                os.fill('.');
                os.setf(ios::left);
                os << m_title;
                os.fill(' ');
                os.unsetf(ios::left);
            }
            else
            {
                for (int i = 0; i < SDDS_TITLE_WIDTH; i++)
                {
                    os << m_title[i];
                }
            }

            if (m_membership != 0)
            {
                os << " | ";
                os.width(5);
                os << m_membership;
                os << " | ";
            }
            else
            {
                os << " |  ";
                os.width(3);
                os << "N/A";
                os << "  | ";
            }

            os << m_date;
            os << " |";
        }
        else
        {
            os << type() << '\t' << m_libRef << '\t' << m_shelfId << '\t' << m_title << '\t' << m_membership << '\t' << m_date;
        }
        return os;
    }

    std::istream& Publication::read(std::istream& is)
    {
        char* title{};
        char shelfId[SDDS_SHELF_ID_LEN + 1];
        int membership = 0;
        int libRef = -1;
        Date date;

        setDef();

        if (conIO(is))
        {
            cout << "Shelf No: ";
            is.getline(shelfId, SDDS_SHELF_ID_LEN + 1, '\n');
            if (strlen(shelfId) != SDDS_SHELF_ID_LEN)
                is.setstate(ios::failbit);

            cout << "Title: ";
            title = Utils::readInput(is);

            cout << "Date: ";
            date.read(is);

            if (!date)
                is.setstate(ios::failbit);
        }
        else
        {
            is >> libRef;
            Utils::extractChar(is, '\t');

            //is.getline(shelfId, SDDS_SHELF_ID_LEN + 1, '\t');
            is >> shelfId;
            Utils::extractChar(is, '\t');

            title = Utils::readInput(is, '\t');
            //Utils::extractChar(is, '\t');

            is >> membership;
            Utils::extractChar(is, '\t');

            date.read(is);
            if (!date)
                is.setstate(ios::failbit);
        }

        if (is)
        {
            Utils::alloCopy(m_title, title);

            strcpy(m_shelfId, shelfId);
            set(membership);
            m_date = date;

            setRef(libRef);
        }
        delete[]title;
        return is;
    }

    Publication::operator bool() const
    {
        return (m_title != nullptr && m_title[0] != '\0' && m_shelfId[0] != '\0');
    }

    Publication::Publication(const Publication& CP)
    {
        if (CP)
        {
            Utils::alloCopy(m_title, CP.m_title);
            strcpy(m_shelfId, CP.m_shelfId);
            set(CP.m_membership);
            m_date = CP.m_date;
            setRef(CP.m_libRef);
        }
        else
            setDef();
    }

    Publication& Publication::operator=(const Publication& CP)
    {
        if (this != &CP && CP)
        {
            Utils::alloCopy(m_title, CP.m_title);
            strcpy(m_shelfId, CP.m_shelfId);
            set(CP.m_membership);
            m_date = CP.m_date;
            setRef(CP.m_libRef);
        }
        return *this;
    }

    Publication::~Publication()
    {
        delete[] m_title;
    }
}