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
#include <iomanip>
#include <iostream>
#include <cstring>
#include <fstream>
#include "LibApp.h"

using namespace std;

namespace sdds
{
	bool LibApp::confirm(const char* message)const
	{
		bool res;
		Menu menu(message);
		menu << "Yes";
		int select = menu.run();
		if (select == 1)
		{
			res = true;
		}
		else
		{
			res = false;
		}
		return res;
	}

	void LibApp::load()
	{
		cout << "Loading Data" << endl;
		ifstream filein(m_fileName);
		char type{};
		int i;
		for (i = 0; filein; i++)
		{
			filein >> type;
			filein.ignore();
			cout << type << "-" << i << endl;
			if (filein)
			{
				if (type == 'P')
				{
					m_PPA[i] = new Publication;
				}
				else if (type == 'B')
				{
					m_PPA[i] = new Book;
				}
				if (m_PPA[i])
				{
					filein >> *m_PPA[i];
					m_NOLP++;					
				}
				if (!filein) cout << "filein fail" << endl;
			}			
		}
		m_LLRN = m_PPA[m_NOLP - 1]->getRef();
		cout << m_NOLP << endl;
	
	}

	void LibApp::save()const
	{
		cout << "Saving Data" << endl;
		ofstream fileout(m_fileName);
		for (int i = 0; i < m_NOLP; i++)
		{
			if (m_PPA[i]->getRef() != 0)
			{
				fileout << *m_PPA[i] << endl;
			}
		}
	}

	int LibApp::search(int mode)const
	{
		int select = m_typeMenu.run();
		int libRef = 0;			
		cout << "Publication Title: ";
		char title[256]{};
		cin.getline(title, 256);
		PublicationSelector ps("Select one of the following found matches:", 15);

		if (select == 1)
		{
			if (mode == SEARCH_ALL)
			{
				for (int i = 0; i < m_NOLP; i++)
				{					
					if (m_PPA[i]->getRef() != 0 && m_PPA[i]->type() == 'B' && strstr(*m_PPA[i], title))
					{
						ps << m_PPA[i];
					}					
				}
			}
			else if (mode == SEARCH_ONLOAN)
			{
				for (int i = 0; i < m_NOLP; i++)
				{					
					if (m_PPA[i]->onLoan() && m_PPA[i]->getRef() != 0 && m_PPA[i]->type() == 'B' && strstr(*m_PPA[i], title))
					{
						ps << m_PPA[i];
					}										
				}
			}
			else if (mode == SEARCH_AVAILABLE)
			{
				for (int i = 0; i < m_NOLP; i++)
				{					
				    if (!m_PPA[i]->onLoan() && m_PPA[i]->getRef() != 0 && m_PPA[i]->type() == 'B' && strstr(*m_PPA[i], title))
					{
						ps << m_PPA[i];
					}									
				}
			}
		}
		else if (select == 2)
		{
			if (mode == SEARCH_ALL)
			{
				for (int i = 0; i < m_NOLP; i++)
				{
					if (m_PPA[i]->getRef() != 0 && m_PPA[i]->type() == 'B' && strstr(*m_PPA[i], title))
					{
						ps << m_PPA[i];
					}
				}
			}
			else if (mode == SEARCH_ONLOAN)
			{
				for (int i = 0; i < m_NOLP; i++)
				{
					if (m_PPA[i]->onLoan() && m_PPA[i]->getRef() != 0 && m_PPA[i]->type() == 'B' && strstr(*m_PPA[i], title))
					{
						ps << m_PPA[i];
					}
				}
			}
			else if (mode == SEARCH_AVAILABLE)
			{
				for (int i = 0; i < m_NOLP; i++)
				{
					if (!m_PPA[i]->onLoan() && m_PPA[i]->getRef() != 0 && m_PPA[i]->type() == 'B' && strstr(*m_PPA[i], title))
					{
						ps << m_PPA[i];
					}
				}
			}
		}
		else
		{
			cout << "Aborted!" << endl << endl;
		}

		if (ps)
		{
			ps.sort();
			libRef = ps.run();
			if (libRef != 0)
			{
				cout << *getPub(libRef) << endl;
			}
			else
			{
				cout << "Aborted!" << endl << endl;
			}
		}
		else
		{
			cout << "No matches found!" << endl << endl;
		}

		return libRef;
	}

	void LibApp::returnPub()
	{
		cout << "Return publication to the library" << endl;
		int libRef = search(SEARCH_ONLOAN);		
		Date today;
		if (libRef != 0)
		{
			bool res = confirm("Return Publication?");
			if (res)
			{
				int onLoanDay = today - getPub(libRef)->checkoutDate();
				int exceedingDay = onLoanDay - SDDS_MAX_LOAN_DAYS;
				if (onLoanDay > SDDS_MAX_LOAN_DAYS)
				{
					double penalty = exceedingDay * 0.5;
					cout.setf(ios::fixed);
					cout.precision(2);
					cout << "Please pay $" << penalty << " penalty for being " << exceedingDay << " days late!" << endl;
				}
				getPub(libRef)->set(0);
				m_changed = true;
				cout << "Publication returned" << endl << endl;
			}
			else
			{
				cout << "Aborted!" << endl << endl;
			}
		}
	}

	void LibApp::newPublication()
	{
		if (m_NOLP == SDDS_LIBRARY_CAPACITY)
		{
			cout << "Library is at its maximum capacity!" << endl << endl;
		}
		else
		{
			cout << "Adding new publication to the library" << endl;
			Publication* ppa{};
			int select = m_typeMenu.run();
			if (select == 0)
			{
				cout << "Aborted!" << endl << endl;
				ppa = nullptr;
			}
			else if (select == 1)
			{
				ppa = new Book;
			}
			else if (select == 2)
			{
				ppa = new Publication;
			}

			if (ppa)
			{
				cin >> *ppa;
				if (cin)
				{
					if (confirm("Add this publication to the library?"))
					{
						if (*ppa)
						{
							m_PPA[m_NOLP] = ppa;
							m_PPA[m_NOLP]->setRef(++m_LLRN);
							m_NOLP++;
							m_changed = true;
							cout << "ADDED" << endl;
						}
						else
						{
							cout << "Failed to add publication!" << endl;
							delete ppa;
						}
					}
					else
					{
						delete ppa;
						cout << "Aborted!" << endl << endl;
					}

				}
				else
				{
					delete ppa;
					cin.ignore(1000, '\n');
					cout << "Aborted!" << endl << endl;
				}
			}
		}
	}

	void LibApp::removePublication()
	{
		cout << "Removing publication from the library" << endl;
		int libRef = search(SEARCH_ALL);
		if (libRef != 0)
		{
			bool res = confirm("Remove this publication from the library?");
			if (res)
			{
				getPub(libRef)->setRef(0);
				m_changed = true;
				cout << "Publication removed" << endl << endl;
			}
		}
	}

	void LibApp::checkOutPub()
	{
		cout << "Checkout publication from the library" << endl;
		int libRef = search(SEARCH_AVAILABLE);		
		if (libRef != 0)
		{
			int number = 0;
			bool invalid = false;
			bool res = confirm("Check out publication?");			
			if (res)
			{
				cout << "Enter Membership number: ";
				do
				{
					invalid = false;
					cin >> number;
					if (!cin || number > 99999 || number < 10000)
					{
						cout << "Invalid membership number, try again: ";
						cin.clear();
						cin.ignore(1000, '\n');
						invalid = true;
					}
				} while (invalid);
				
				getPub(libRef)->set(number);
				m_changed = true;
				cout << "Publication checked out" << endl << endl;				
			}
		}
	}

	LibApp::LibApp(const char* fileName) :m_NOLP(0), m_LLRN(0), m_changed(false), m_mainMenu("Seneca Library Application"), m_exitMenu("Changes have been made to the data, what would you like to do?"), m_typeMenu("Choose the type of publication:")
	{
		strcpy(m_fileName, fileName);
		load();
		m_mainMenu << "Add New Publication" << "Remove Publication" << "Checkout publication from library" << "Return publication to library";
		m_exitMenu << "Save changes and exit" << "Cancel and go back to the main menu";
		m_typeMenu << "Book" << "Publication";
	}

	LibApp::~LibApp()
	{
		for (int i = 0; i < m_NOLP; i++)
		{
			delete m_PPA[i];
		}
	}

	void LibApp::run()
	{
		int select;
		bool flag = true;
		do
		{
			select = m_mainMenu.run();
			switch (select)
			{
			case 1:
				newPublication();
				break;
			case 2:
				removePublication();
				break;
			case 3:
				checkOutPub();
				break;
			case 4:
				returnPub();
				break;
			case 0:
				flag = exit();
				break;
			}
		} while (flag);
		cout << "-------------------------------------------" << endl;
		cout << "Thanks for using Seneca Library Application" << endl;
	}

	//void LibApp::terminateProgram()
	//{
	//	cout << endl;
	//	cout << "-------------------------------------------" << endl;
	//	cout << "Thanks for using Seneca Library Application" << endl;
	//}

	Publication* LibApp::getPub(int libRef)const
	{
		Publication* ppa{};
		for (int i = 0; i < m_NOLP && !ppa; i++)
		{
			if (m_PPA[i]->getRef() == libRef)
			{
				ppa = m_PPA[i];
			}
		}
		return ppa;
	}


	bool LibApp::exit()const
	{
		bool exit = false;
		if (m_changed)
		{
			switch (m_exitMenu.run())
			{
			case 1:
				save();
				break;
			case 2:
				exit = true;
				break;
			case 0:
				exit = !confirm("This will discard all the changes are you sure?");
				break;
			}
		}
		cout << endl;
		return exit;
	}




}



