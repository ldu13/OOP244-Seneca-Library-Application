/* Citation and Sources...
Final Project Milestone ?
Module: Whatever
Filename: Whatever.cpp
Version 1.0
Author	John Doe
Revision History
-----------------------------------------------------------
Date      Reason
2020/?/?  Preliminary release
2020/?/?  Debugged DMA
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/

#ifndef SDDS_MENU_H__
#define SDDS_MENU_H__
#include <iostream>

#include "Utils.h"

namespace sdds
{
	const unsigned int MAX_MENU_ITEMS = 20;
	class Menu;
	class MenuItem
	{
		char* m_menuItem{};
		friend class Menu;
		void setItem(const char* item);
		MenuItem(const char* item=nullptr);
		MenuItem(const MenuItem& menuitem) = delete;
		MenuItem& operator=(const MenuItem& menuitem) = delete;
		~MenuItem();
		operator bool() const;		
		operator const char* () const;		
		std::ostream& display(std::ostream& ostr) const;
	};
	class Menu
	{		
		MenuItem m_title;
		MenuItem* m_menuItems[MAX_MENU_ITEMS]{};
		int m_noOfItem;
	public:		
		Menu();
		Menu(const char* title);
		Menu(const Menu& menu) = delete;
		Menu& operator=(const Menu& menu) = delete;
		~Menu();
		std::ostream& displayTitle(std::ostream& ostr) const;
		std::ostream& displayMenu(std::ostream& ostr) const;
		unsigned int run() const;
		unsigned int operator~() const;
		Menu& operator<<(const char* menuitemContent);		
		operator int() const;
		operator unsigned int() const;
		operator bool() const;
		char* operator[](int index) const;
	};
	std::ostream& operator<<(std::ostream& ostr, const Menu& m);	
}
#endif