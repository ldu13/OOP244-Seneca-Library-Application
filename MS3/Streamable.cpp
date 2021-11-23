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

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <cstring>
#include "Streamable.h"
using namespace std;

namespace sdds
{
    std::ostream& operator<<(std::ostream& os, const Streamable& s)
    {
        if (s) s.write(os);
        return os;

    }
    std::istream& operator>>(std::istream& is, Streamable& s)
    {
        return s.read(is);
    }
}