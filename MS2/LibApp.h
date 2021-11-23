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

#ifndef SDDS_LIBAPP_H
#define SDDS_LIBAPP_H
#include <iostream>
#include "Menu.h"
using namespace std;
namespace sdds 
{
   class LibApp 
   {
   private:
	   bool m_changed = false;
	   Menu m_mainMenu = {"Seneca Libray Application"};
	   Menu m_exitMenu = {"Changes have been made to the data, what would you like to do?"};
	   bool confirm(const char* message);
	   void load();
	   void save();
	   void search();
	   void returnPub();
	   void newPublication();
	   void removePublication();
	   void checkOutPub();
   public:
	   LibApp();
	   unsigned int run();
	   void terminateProgram();
	   void displayMainMenu();
	   void displayExitMenu();
	   void discardChanges();
   };
}
#endif // !SDDS_LIBAPP_H



