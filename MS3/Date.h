/*
    ==================================================
    Final Project (Milestone 3):
    ==================================================
    Name   :           Lei Du
    Seneca email:      ldu13@myseneca.ca
    Seneca Student ID: 047587134
    Date:              November 22, 2021
    Section:           NCC
*/
// I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#ifndef SDDS_DATE_H__
#define SDDS_DATE_H__
#include <iostream>
#include "Lib.h"
#include "Utils.h"

namespace sdds
{
    const int NO_ERROR = 0;
    const int CIN_FAILED = 1;
    const int YEAR_ERROR = 2;
    const int MON_ERROR = 3;
    const int  DAY_ERROR = 4;
    const char DATE_ERROR[5][16] = {
       "No Error",
       "cin Failed",
       "Bad Year Value",
       "Bad Month Value",
       "Bad Day Value"
    };
    const int  MIN_YEAR = 1500;
    
    class Date
    {
    private:
        int m_year;
        int m_mon;
        int m_day;
        int m_ErrorCode;
        int m_CUR_YEAR;
        bool validate();
        void errCode(int);
        int systemYear()const;
        bool bad()const;
        int mdays()const;
        
    public:
        int daysSince0001_1_1()const;
        void setToToday();
        Date();
        Date(int year, int mon, int day);
        int errCode()const;
        const char* dateStatus()const;
        int currentYear()const;
        std::istream& read(std::istream& is = std::cin);
        std::ostream& write(std::ostream& os = std::cout)const;
        bool operator==(const Date& RO) const;
        bool operator!=(const Date& RO) const;
        bool operator>=(const Date& RO) const;
        bool operator<=(const Date& RO) const;
        bool operator<(const Date& RO) const;
        bool operator>(const Date& RO) const;
        operator bool() const;
    };

    int operator-(const Date& d1, const Date& d2);
    std::ostream& operator<<(std::ostream& os, const Date& RO);
    std::istream& operator>>(std::istream& is, Date& RO);

    extern bool sdds_test;
    extern int sdds_year;
    extern int sdds_mon;
    extern int sdds_day;
}

#endif