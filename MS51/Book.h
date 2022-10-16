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
