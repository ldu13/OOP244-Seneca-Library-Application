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

#ifndef SDDS_UTILS_H__
#define SDDS_UTILS_H__
#include <iostream>

namespace sdds
{
    class Utils
    {
    public:
        Utils() = delete;
        //static int intLength(int num);
        static void alloCopy(char*& des, const char* src);
        static void extractChar(std::istream& is, char ch);
        static char* readInput(std::istream& is, char delimeter='\n');
    };
}
#endif