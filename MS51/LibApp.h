#ifndef SDDS_LIBAPP_H
#define SDDS_LIBAPP_H
#include <iostream>
#include "Lib.h"
#include "Menu.h"
#include "Date.h"
#include "Streamable.h"
#include "Publication.h"
#include "Book.h"
#include "PublicationSelector.h"
#include "Utils.h"

using namespace std;
namespace sdds
{
	class LibApp
	{
	private:
		bool m_changed = false;
		Menu m_mainMenu = { "Seneca Libray Application" };
		Menu m_exitMenu = { "Changes have been made to the data, what would you like to do?" };

		char m_fileName[256]{};
		Publication* m_PPA[SDDS_LIBRARY_CAPACITY]{}; //Publication Pointers Array
		int m_NOLP{}; //Number Of Loaded Publications
		int m_LLRN{}; //Last Library Reference Number
		Menu m_typeMenu = { "Choose the type of publication:" };

		bool confirm(const char* message)const;
		void load();
		void save()const;
		int search(int mode)const;
		bool exit()const;
		Publication* getPub(int libRef)const;
		void returnPub();
		void newPublication();
		void removePublication();
		void checkOutPub();

	public:
		LibApp(const char* fileName);
		LibApp(const LibApp& CP) = delete;
		LibApp& operator=(const LibApp& RO) = delete;
		~LibApp();

		void run();
		//void terminateProgram();

	
	};
}
#endif // !SDDS_LIBAPP_H




