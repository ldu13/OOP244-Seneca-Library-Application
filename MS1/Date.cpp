/*
    ==================================================
    Final Project (Milestone 1):
    ==================================================
    Name   :           Lei Du
    Seneca email:      ldu13@myseneca.ca
    Seneca Student ID: 047587134
    Date:              November 09, 2021
*/
// I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

// Final Project Milestone 1 
// Date Module
// File	Date.cpp
// Version 1.0
// Author	Fardad Soleimanloo
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
// Fardad             2021/10/29		       Preliminary release
/////////////////////////////////////////////////////////////////
#define _CRT_SECURE_NO_WARNINGS
#include <iomanip>
#include <iostream>
#include <ctime>
#include "Date.h"

using namespace std;
namespace sdds
{
    int Date::daysSince0001_1_1()const
    {
        int ty = m_year;
        int tm = m_mon;
        if (tm < 3)
        {
            ty--;
            tm += 12;
        }
        return 365 * ty + ty / 4 - ty / 100 + ty / 400 + (153 * tm - 457) / 5 + m_day - 306;
    }

    bool Date::validate()
    {
        errCode(NO_ERROR);
        if (m_year < MIN_YEAR || m_year > m_CUR_YEAR + 1)
        {
            errCode(YEAR_ERROR);
        }
        else if (m_mon < 1 || m_mon > 12)
        {
            errCode(MON_ERROR);
        }
        else if (m_day < 1 || m_day > mdays())
        {
            errCode(DAY_ERROR);
        }
        return !bad();
    }

    void Date::errCode(int readErrorCode)
    {
        m_ErrorCode = readErrorCode;
    }

    int Date::systemYear()const
    {
        time_t t = time(NULL);
        tm lt = *localtime(&t);
        return lt.tm_year + 1900;
    }

    bool Date::bad()const
    {
        return m_ErrorCode != 0;
    }

    int Date::mdays()const
    {
        int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
        int mon = m_mon >= 1 && m_mon <= 12 ? m_mon : 13;
        mon--;
        return days[mon] + int((mon == 1) * ((m_year % 4 == 0) && (m_year % 100 != 0)) || (m_year % 400 == 0));
    }

    void Date::setToToday()
    {
        time_t t = time(NULL);
        tm lt = *localtime(&t);
        m_day = lt.tm_mday;
        m_mon = lt.tm_mon + 1;
        m_year = lt.tm_year + 1900;
        errCode(NO_ERROR);
    }

    Date::Date() :m_CUR_YEAR(systemYear())
    {
        setToToday();
    }

    Date::Date(int year, int mon, int day) : m_CUR_YEAR(systemYear())
    {
        m_year = year;
        m_mon = mon;
        m_day = day;
        validate();
    }

    int Date::errCode()const
    {
        return m_ErrorCode;
    }

    const char* Date::dateStatus()const
    {
        return DATE_ERROR[errCode()];
    }

    int Date::currentYear()const
    {
        return m_CUR_YEAR;
    }

    std::istream& Date::read(std::istream& is)
    {
        m_ErrorCode = NO_ERROR;
        is >> m_year;
        is.ignore();
        is >> m_mon;
        is.ignore();
        is >> m_day;
        if (!is)
        {
            m_ErrorCode = CIN_FAILED;
            is.clear();
        }
        else
        {
            validate();
        }
        is.ignore(1000, '\n');
        return is;
    }

    std::ostream& Date::write(std::ostream& os) const
    {
        if (bad())
        {
            os << dateStatus();
        }
        else
        {
            os << m_year;
            os << '/';
            os.width(2);
            os.setf(ios::right);
            os.fill('0');
            os << m_mon;

            os << '/';
            os.width(2);
            os.setf(ios::right);
            os.fill('0');
            os << m_day;
            os.unsetf(ios::right);
            os.fill(' ');
        }
        return os;
    }

    bool Date::operator==(const Date& RO) const
    {
        bool res;
        if (bool(*this) && bool(RO) && this->daysSince0001_1_1() == RO.daysSince0001_1_1())
        {
            res = true;
        }
        else
        {
            res = false;
        }
        return res;
    }

    bool Date::operator!=(const Date& RO) const
    {
        bool res;
        if (bool(*this) && bool(RO) && this->daysSince0001_1_1() != RO.daysSince0001_1_1())
        {
            res = true;
        }
        else
        {
            res = false;
        }
        return res;
    }

    bool Date::operator>=(const Date& RO) const
    {
        bool res;
        if (bool(*this) && bool(RO) && this->daysSince0001_1_1() >= RO.daysSince0001_1_1())
        {
            res = true;
        }
        else
        {
            res = false;
        }
        return res;
    }

    bool Date::operator<=(const Date& RO) const
    {
        bool res;
        if (bool(*this) && bool(RO) && this->daysSince0001_1_1() <= RO.daysSince0001_1_1())
        {
            res = true;
        }
        else
        {
            res = false;
        }
        return res;
    }

    bool Date::operator<(const Date& RO) const
    {
        bool res;
        if (bool(*this) && bool(RO) && this->daysSince0001_1_1() < RO.daysSince0001_1_1())
        {
            res = true;
        }
        else
        {
            res = false;
        }
        return res;
    }

    bool Date::operator>(const Date& RO) const
    {
        bool res;
        if (bool(*this) && bool(RO) && this->daysSince0001_1_1() > RO.daysSince0001_1_1())
        {
            res = true;
        }
        else
        {
            res = false;
        }
        return res;
    }

    Date::operator bool() const
    {
        bool res;
        if (!bad())
        {
            res = true;
        }
        else
        {
            res = false;
        }
        return res;
    }

    int operator-(const Date& d1, const Date& d2)
    {
        int diff = d1.daysSince0001_1_1() - d2.daysSince0001_1_1();
        return diff;
    }

    ostream& operator<<(ostream& os, const Date& RO)
    {
        return RO.write(os);
    }
    istream& operator>>(istream& is, Date& RO)
    {
        return RO.read(is);
    }
}