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

#define _CRT_SECURE_NO_WARNINGS
#include <iomanip>
#include <iostream>
#include <ctime>
#include "Menu.h"
#include "Utils.h"
using namespace std;
namespace sdds
{
	MenuItem::MenuItem(const char* item)
	{
		setItem(item);
	}

	void MenuItem::setItem(const char* item)
	{
		if (item != nullptr)
		{
			m_menuItem = new char[strlen(item) + 1];
			strcpy(m_menuItem, item);
		}
	}

	MenuItem::~MenuItem()
	{
		delete[] m_menuItem;
	}

	MenuItem::operator bool() const
	{
		return !(m_menuItem == nullptr);
	}
	MenuItem::operator const char* () const
	{
		return m_menuItem;
	}


	std::ostream& MenuItem::display(std::ostream& ostr) const
	{
		if (*this)
		{
			ostr << m_menuItem;
		}
		return ostr;
	}

	// A Menu is always created empty; with no MenuItems, with or without a title.
	Menu::Menu()
	{
		m_noOfItem = 0;
	}
	Menu::Menu(const char* title)
	{
		m_noOfItem = 0;
		m_title.setItem(title);

	}

	// Looping through the MenuItems array of pointers, it deletes each pointer up to the number of menu items in the menu.
	Menu::~Menu()
	{
		for (int i = 0; i < m_noOfItem; i++)
		{
			delete m_menuItems[i];
			
		}
	}

	std::ostream& Menu::displayTitle(std::ostream& ostr) const
	{		
		return m_title.display(ostr);
	}

	std::ostream& Menu::displayMenu(std::ostream& ostr) const
	{
		if (m_title)
		{
			displayTitle(ostr);
			ostr << ":" << endl;

			
		}
		for (int i = 0; i < m_noOfItem; i++)
		{
			ostr.width(2);
			ostr.setf(ios::right);
			ostr << i + 1 << "- ";
			m_menuItems[i]->display(ostr);
			ostr << endl;
			
		}
		ostr << " 0- Exit" << endl << "> ";
		ostr.unsetf(ios::right);
		return ostr;
	}

	unsigned int Menu::run() const
	{		
		displayMenu(cout);
		return intCheck(cin, m_noOfItem);		
	}


	// Overload operator~ to do exactly what the run function does (two different ways to run the menu)
	unsigned int Menu::operator~() const
	{
		displayMenu(cout);
		return intCheck(cin, m_noOfItem);
	}

	Menu& Menu::operator<<(const char* menuitemContent)
	{
		if (m_noOfItem < MAX_MENU_ITEMS)
		{
			m_menuItems[m_noOfItem] = new MenuItem(menuitemContent);
			m_noOfItem++;
		}
		return *this;
	}

	Menu::operator int() const
	{
		return m_noOfItem;	
	}

	Menu::operator unsigned int() const
	{
		return m_noOfItem;
	}

	Menu::operator bool() const
	{
		bool res;
		if (m_noOfItem > 0)
		{
			res = true;
		}
		else
		{
			res = false;
		}
		return res;
	}


	char* Menu::operator[](int index) const
	{
		int indexNo = index % m_noOfItem;
		return m_menuItems[indexNo]->m_menuItem;
	}

	std::ostream& operator<<(std::ostream& ostr, const Menu& m)
	{
		return m.displayTitle(ostr);
	}

}