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

#ifndef SDDS_BOOK_H__
#define SDDS_BOOK_H__
#include <iostream>
#include "Publication.h"
#include "Lib.h"
#include "Date.h"
#include "Utils.h"

namespace sdds
{
	class Book :public Publication
	{
	private:
		char* m_authorName{};
	public:
		Book();

		Book(const Book& CP);
		Book& operator=(const Book& RO);
		virtual ~Book();

		virtual char type()const;
		std::ostream& write(std::ostream& os) const;
		std::istream& read(std::istream& is);
		virtual void set(int member_id);
		operator bool() const;
	};
}

#endif
