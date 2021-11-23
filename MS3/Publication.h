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

#ifndef SDDS_PUBLICATION_H__
#define SDDS_PUBLICATION_H__
#include <iostream>
#include "Lib.h"
#include "Date.h"
#include "Utils.h"
#include "Streamable.h"

namespace sdds
{
    class Publication:public Streamable
    {
    private:
        char* m_title{};
        char m_shelfId[SDDS_SHELF_ID_LEN + 1]{};
        int m_membership{};
        int m_libRef{-1};
        Date m_date;
    public:
        Publication();
        void setDef();
        virtual void set(int member_id);
        void setRef(int value);
        void resetDate();
        virtual char type()const;
        bool onLoan()const;
        Date checkoutDate()const;
        bool operator==(const char* title)const;
        operator const char* ()const;
        int getRef()const;
        
        bool conIO(std::ios& io)const;

        std::ostream& write(std::ostream& os) const;
        std::istream& read(std::istream& is);

        operator bool() const;

        Publication(const Publication& CP);
        Publication& operator=(const Publication& CP);
        virtual ~Publication();

    };

}

#endif