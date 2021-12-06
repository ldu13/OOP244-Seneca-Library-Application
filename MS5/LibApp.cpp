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
#include <iomanip>
#include <iostream>
#include <cstring>
#include <fstream>
#include <stdlib.h>
#include "LibApp.h"

using namespace std;

namespace sdds
{
	bool LibApp::confirm(const char* message)
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
			}

			if (m_PPA[i])
			{
				filein >> *m_PPA[i];
				m_NOLP++;
				//m_LLRN = m_PPA[i]->getRef();
			}
		}
		m_LLRN = m_PPA[m_NOLP - 1]->getRef();
	}


	void LibApp::save()
	{
		cout << "Saving Data" << endl << endl;
		ofstream fileout(m_fileName);
		for (int i = 0; i < m_NOLP; i++)
		{
			if (m_PPA[i]->getRef() != 0)
			{
				fileout << *m_PPA[i] << endl;
			}
			/*if (m_PPA[i]->getRef() != 0)
			{
				m_PPA[i]->write(fileout);
				fileout << endl;
			}*/
		}
	}

	int LibApp::search(int mode)
	{
		int select = m_typeMenu.run();
		int libRef = 0;
			
		cout << "Publication Title: ";
		char title[256]{};
		cin.getline(title, 255, '\n');
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
			if (mode == 1)
			{
				for (int i = 0; i < m_NOLP; i++)
				{
					if (m_PPA[i]->getRef() != 0 && m_PPA[i]->type() == 'B' && strstr(*m_PPA[i], title))
					{
						ps << m_PPA[i];
					}
				}
			}
			else if (mode == 2)
			{
				for (int i = 0; i < m_NOLP; i++)
				{
					if (m_PPA[i]->onLoan() && m_PPA[i]->getRef() != 0 && m_PPA[i]->type() == 'B' && strstr(*m_PPA[i], title))
					{
						ps << m_PPA[i];
					}
				}
			}
			else if (mode == 3)
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
				/*getPub(libRef)->write(cout);
				cout << endl;*/
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
		bool res = confirm("Return Publication?");
		Date today;
		if (libRef != 0)
		{
			if (res)
			{
				int onLoanDay = today - getPub(libRef)->checkoutDate();
				int exceedingDay = onLoanDay - SDDS_MAX_LOAN_DAYS;
				if (onLoanDay > SDDS_MAX_LOAN_DAYS)
				{
					double penalty = exceedingDay * 0.5;
					cout.setf(ios::fixed);
					cout.precision(2);
					cout << "Please pay $" << penalty << " for being " << exceedingDay << " days late!" << endl;
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
			cout << "Adding new publication to library" << endl;
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
				//cin >> ppa[0];
			}
			else if (select == 3)
			{
				ppa = new Publication;
				//cin >> ppa[0];
			}

			if (ppa)
			{
				cin >> *ppa;
				if (!cin)
				{
					delete ppa;
					cin.clear();
					cin.ignore(1000, '\n');
					cout << "Aborted!" << endl << endl;
				}
				else
				{
					bool res = confirm("Add this publication to the library?");
					if (res)
					{
						if (*ppa)
						{
							m_PPA[m_NOLP] = ppa;
							m_LLRN++;
							m_PPA[m_NOLP]->setRef(m_LLRN);

							m_NOLP++;
							m_changed = true;
							cout << "Publication added" << endl << endl;
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
			}
		}
	}

	void LibApp::removePublication()
	{
		cout << "Removing publication from library" << endl;
		int libRef = search(SEARCH_ALL);
		bool res = confirm("Remove this publication from the library?");
		if (libRef != 0)
		{
			if (res)
			{
				getPub(libRef)->setRef(0);
				m_changed = true;
				cout << "Publication removed" << endl << endl;
			}
			else
			{
				cout << "Aborted!" << endl << endl;
			}
		}
	}

	void LibApp::checkOutPub()
	{
		cout << "Checkout publication from the library";
		int libRef = search(SEARCH_AVAILABLE);
		int number = 0;
		bool res = confirm("Check out publication?");
		bool invalid = false;
		if (libRef != 0)
		{
			if (res)
			{
				cout << "Enter Membership number: ";
				do
				{
					invalid = false;
					cin >> number;
					if (!cin || number > 999999 || number < 10000)
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
			else
			{
				cout << "Aborted!" << endl << endl;
			}
		}
	}

	LibApp::LibApp(const char* fileName) :m_mainMenu("Seneca Library Application"), m_exitMenu("Changes have been made to the data, what would you like to do?"), m_typeMenu("Choose the type of publication:")
	{
		m_mainMenu << "Add New Publication" << "Remove Publication" << "Checkout publication from library" << "Return publication to library";
		m_exitMenu << "Save changes and exit" << "Cancel and go back to the main menu";
		m_typeMenu << "Book" << "Publication";

		m_NOLP = 0;
		m_LLRN = 0;
		m_changed = false;
		strcpy(m_fileName, fileName);
		load();
	}

	LibApp::~LibApp()
	{
		for (int i = 0; i < m_NOLP; i++)
		{
			delete m_PPA[i];
			m_PPA[i] = nullptr;
		}
	}

	void LibApp::run()
	{
		int select;
		bool flag = false;
		do
		{
			flag = false;
			select = m_mainMenu.run();
			if (select == 0)
			{
				if (m_changed == false)
				{
					terminateProgram();
				}
				else
				{
					int sel = m_exitMenu.run();
					switch (sel)
					{
					case 1:
						save();
						terminateProgram();
						break;
					case 2:
						flag = true;
						cout << endl;
						run();
						break;
					case 0:
						bool res = confirm("This will discard all the changes are you sure?");
						if (!res)
						{
							flag = true;
						}
						else
						{
							terminateProgram();
						}
						break;
					}
				}
			}
			else
			{
				flag = true;
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
				}
			}
		} while (flag);
	}

	void LibApp::terminateProgram()
	{
		cout << endl;
		cout << "-------------------------------------------" << endl;
		cout << "Thanks for using Seneca Library Application" << endl;
	}

	Publication* LibApp::getPub(int libRef)
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
}
