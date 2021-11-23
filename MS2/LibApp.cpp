/*
	==================================================
	Final Project (Milestone 2):
	==================================================
	Name   :           Lei Du
	Seneca email:      ldu13@myseneca.ca
	Seneca Student ID: 047587134
	Date:              November 14, 2021
*/
// I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#define _CRT_SECURE_NO_WARNINGS
#include <iomanip>
#include <iostream>
#include <string.h>
#include "LibApp.h"
using namespace std;
namespace sdds {
	bool LibApp::confirm(const char* message)
	{
		bool res;
		Menu menu(message);
		menu << "Yes";
		int val = menu.run();
		if (val == 1)
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
	}
	void LibApp::save()
	{
		cout << "Saving Data" << endl;
	}
	void LibApp::search()
	{
		cout << "Searching for publication" << endl;
	}
	void LibApp::returnPub()
	{
		search();
		cout << "Returning publication" << endl;
		cout << "Publication returned" << endl << endl;
		m_changed = true;
		displayMainMenu();
	}
	void LibApp::newPublication()
	{
		cout << "Adding new publication to library" << endl;
		bool res = confirm("Add this publication to library?");
		if (res)
		{
			m_changed = true;
			cout << "Publication added" << endl;
		}
		else
		{			
			cout << endl;
			displayMainMenu();
		}

	}
	void LibApp::removePublication()
	{
		cout << "Removing publication from library" << endl;
		search();
		bool res = confirm("Remove this publication from the library?");
		if (res)
		{
			m_changed = true;
			cout << "Publication removed" << endl << endl;
			displayMainMenu();
		}
	}
	void LibApp::checkOutPub()
	{
		search();
		bool res = confirm("Check out publication?");
		if (res)
		{
			m_changed = true;
			cout << "Publication checked out" << endl << endl;
			displayMainMenu();
		}
	}
	LibApp::LibApp()
	{
		load();
		m_changed = false;
	}

	unsigned int LibApp::run()
	{
		displayMainMenu();
		int select;
		do
		{
			cin >> select;
			if (select == 0)
			{
				if (m_changed == false)
					terminateProgram();
				else
				{
					int sel;
					displayExitMenu();
					cin >> sel;
					if (sel == 0)
						discardChanges();
					else if (sel == 1)
					{
						save();
						terminateProgram();
					}
					else if (sel == 2)
					{
						cout << endl;
						run();
					}					
				}
			}
			else if (select == 1)
				newPublication();				
			else if (select == 2)
				removePublication();
			else if (select == 3)
				checkOutPub();
			else if (select == 4)
				returnPub();				
			cin.ignore(1000, '\n');
		} while (select != 0);
		return select;
	}

	void LibApp::terminateProgram()
	{
		cout << endl;
		cout << "-------------------------------------------" << endl;
		cout << "Thanks for using Seneca Library Application" << endl;
	}

	void LibApp::displayMainMenu() 
	{
		Menu m_mainMenu = { "Seneca Library Application" };
		m_mainMenu << "Add New Publication" << "Remove Publication" << "Checkout publication from library" << "Return publication to library";
		m_mainMenu.displayMenu(cout);
	}

	void LibApp::displayExitMenu() 
	{
		Menu m_exitMenu = { "Changes have been made to the data, what would you like to do?" };
		m_exitMenu << "Save changes and exit" << "Cancel and go back to the main menu";
		m_exitMenu.displayMenu(cout);
	}

	void sdds::LibApp::discardChanges() 
	{		
		bool res = confirm("This will discard all the changes are you sure?");
		if (res)
		{			
			terminateProgram();
		}
	}
}
