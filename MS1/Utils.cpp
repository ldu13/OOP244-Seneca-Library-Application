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

/***********************************************************************
// OOP244 Utils Module
// File	Utils.cpp
// Version
// Date
// Author
// Description
//
// Revision History
// -----------------------------------------------------------
// Name            Date            Reason
//
/////////////////////////////////////////////////////////////////
***********************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Utils.h"

using namespace std;
namespace sdds
{
    int intCheck(std::istream& istr, int maxValue)
    {
        int value = 0;
        istr >> value;
        while (!istr || value<0 || value>maxValue)
        {
            istr.clear();
            istr.ignore(1000, '\n');
            cout << "Invalid Selection, try again: ";
            istr >> value;
        }
        return value;
    }
}