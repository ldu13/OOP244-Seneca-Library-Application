#ifndef SDDS_UTILS_H__
#define SDDS_UTILS_H__
#include <iostream>

namespace sdds
{
    class Utils
    {
    public:
        Utils() = delete;
        
        static void alloCopy(char*& des, const char* src);
        static void extractChar(std::istream& is, char ch);
        static char* readInput(std::istream& is, char delimeter = '\n');
    };
    int intCheck(std::istream& istr, int maxValue);
}
#endif
