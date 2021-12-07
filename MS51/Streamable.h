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

#ifndef SDDS_STREAMABLE_H__
#define SDDS_STREAMABLE_H__
#include <iostream>
#include "Lib.h"
#include "Date.h"
#include "Utils.h"

namespace sdds
{
    class Streamable
    {
    public:
        virtual std::ostream& write(std::ostream& os) const = 0;
        virtual std::istream& read(std::istream& is) = 0;
        virtual bool conIO(std::ios& io) const = 0;
        virtual operator bool() const = 0;
        virtual ~Streamable()
        {
        };
    };

    std::ostream& operator<<(std::ostream& os, const Streamable& s);
    std::istream& operator>>(std::istream& is, Streamable& s);
}

#endif
