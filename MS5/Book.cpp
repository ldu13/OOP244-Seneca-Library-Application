/*
	==================================================
	Final Project (Milestone 5):
	==================================================
	Name   :           Lei Du
	Seneca email:      ldu13@myseneca.ca
	Seneca Student ID: 047587134
	Date:              December 5, 2021
	Section:           NCC
*/
// I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <cstring>
#include "Book.h"

using namespace std;

namespace sdds
{
	Book::Book(){}

	Book::Book(const Book& CP) :Publication(CP)
	{
		Utils::alloCopy(m_authorName, CP.m_authorName);
	}

	Book& Book::operator=(const Book& RO)
	{
		Publication::operator=(RO);
		if (this != &RO && RO)
		{
			Utils::alloCopy(m_authorName, RO.m_authorName);
		}
		return *this;
	}

	Book::~Book()
	{
		delete[] m_authorName;
	}

	char Book::type() const
	{
		return 'B';
	}

	std::ostream& Book::write(std::ostream& os) const
	{
		Publication::write(os);
		if (conIO(os))
		{
			os << ' ';
			if (strlen(m_authorName) <= SDDS_AUTHOR_WIDTH)
			{
				os.width(SDDS_AUTHOR_WIDTH);
				os.fill(' ');
				os.setf(ios::left);
				os << m_authorName;
				os.fill(' ');
				os.unsetf(ios::left);
			}
			else
			{
				for (int i = 0; i < SDDS_AUTHOR_WIDTH; i++)
				{
					os << m_authorName[i];
				}
			}
			os << " |";
		}
		else
		{
			os << '\t' << m_authorName;
		}
		return os;
	}

	std::istream& Book::read(std::istream& is)
	{
		char authorName[255];
		Publication::read(is);
		delete[] m_authorName;
		m_authorName = nullptr;
		if (conIO(is))
		{
			Utils::extractChar(is, '\n');
			cout << "Author: ";
			is.get(authorName, 256);
		}
		else
		{
			Utils::extractChar(is, '\t');
			is.get(authorName, 256);
		}
		if (is)
		{
			Utils::alloCopy(m_authorName, authorName);
		}
		return is;
	}

	void Book::set(int member_id)
	{
		Publication::set(member_id);
		Publication::resetDate();
	}

	Book::operator bool() const
	{
		return (m_authorName && m_authorName[0] && Publication::operator bool() == true);
	}
}