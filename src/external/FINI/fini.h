#pragma once
/*
	Класы работы с ini типами файлов 

*/

#include <iostream>
#include <string>
#include <vector>
namespace fini
{
	struct sKeys
	{
		std::string name;
		std::string value;
	};

	typedef sKeys kGrop;

	struct sGrup
	{
		std::string name;
		std::vector< sKeys> keys;
	};

	typedef sGrup INIDocument;

class cFINIin
{
	private:

		alignas(16) std::string fbuf;
		bool is;
		int grup_index;
	 std::vector<INIDocument > doc;

	public:

		cFINIin();
		//~cFINIin();
		//
		bool open(const char* puth);
		//
		bool openGrup(const char* name);
		//bool isKey(const char* name);
		//int getKey_u8(const char* name);
		//int getKey_int(const char* name);

		// DEBUG
#if _DEBUG 
		void print_fbuf() { std::cout << fbuf << std::endl; }
#else 
		void print_fbuf() {}
#endif
};

}