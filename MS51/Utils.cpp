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
#include <cstring>
#include "Utils.h"
using namespace std;

namespace sdds
{
    
    void Utils::alloCopy(char*& des, const char* src)
    {
        delete[] des;
        des = nullptr;
        if (src)
        {
            des = new char[strlen(src) + 1];
            strcpy(des, src);
        }
    }

    void Utils::extractChar(std::istream& is, char ch)
    {
        if (is.peek() == ch)
        {
            is.get();
        }
    }

    char* Utils::readInput(std::istream& is, char delimeter)
    {
        char* str{};
        if (is)
        {
            const int bufferSize = 20;
            int bufferNo = 1;
            char* buffer = new char[bufferSize];
            str = buffer;
            bool done = false;
            do
            {
                is.getline(str, bufferSize, delimeter);
                if (!is)
                {
                    bufferNo++;
                    char* temp = new char[(bufferSize - 1) * bufferNo + 1];
                    strcpy(temp, buffer);
                    delete[] buffer;
                    buffer = temp;
                    str = buffer + (bufferSize - 1) * (bufferNo - 1);
                    is.clear();
                }
                else
                {
                    done = true;
                }
            } while (!done);
            str = new char[strlen(buffer) + 1];
            strcpy(str, buffer);
            delete[] buffer;
        }
        return str;
    }

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
        istr.ignore(1000, '\n');
        return value;
    }
}