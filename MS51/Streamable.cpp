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
