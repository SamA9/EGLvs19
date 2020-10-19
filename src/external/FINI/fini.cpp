
#include "fini.h"
#include <fstream>
#include <sstream>

//SSE2
#include <immintrin.h>

using namespace std;

namespace fini
{

	cFINIin::cFINIin()
	{
		// file is open 
		is = false;
		grup_index = 0;
		doc.resize(0); //
	}

	bool cFINIin::open(const char* puth)
	{
		ifstream fin;
		stringstream strin;

		doc.resize(0); //

		// ensures ifstream objects can throw exceptions:
		fin.exceptions(std::ifstream::badbit);
		try
		{
			//
			fin.open(puth);
			if (fin.is_open()) {
				strin << fin.rdbuf();
				fin.close();
				//
				this->fbuf = strin.str();
				// ok
				this->is = true;
			}	
			/*
				|***************************************************************|
				|**********      parsing ini file to structure         *********| 
				|***************************************************************|


		    */	
			int buflen = (int)this->fbuf.length();
			sGrup _newGrup;
			int _grup_index = 0;
			int i = 0;
			if (buflen > 5)
			{
				while (true)
				{
					_newGrup.name = "";
					_newGrup.keys.resize(0);
					// FAIND Grup
					while (fbuf[i] != '[') { if (fbuf[i++] == '\0') return false; }
					i++;
					//copy name gup
					while (fbuf[i] != ']') {
						if (fbuf[i] == '\0') return false;
						_newGrup.name += fbuf[i++];
					}
					/* Name Grup read redy */
					/* faind new line */
					while (fbuf[i] != '\n') { if (fbuf[i++] == '\0') return false; }
					// open grup
					sKeys Key;

					while (true)
					{
						/* loop find key */
						Key.name = "";
						Key.value = "";
						/* Faind Key */
						while ((fbuf[i] == ';') || (fbuf[i] == '\n') || (fbuf[i] == '\t'))
						{
							/* faind new line */
							if ((fbuf[i] != '\t')) {
								while (fbuf[i++] != '\n') { if (fbuf[i] == '\0') return false; }
							}
							else { i++; }

						}
						if (fbuf[i] == '\0') { doc.push_back(_newGrup); fbuf = ""; return false; }
						if (fbuf[i] == '[') {
							doc.push_back(_newGrup); 
							break;
						}
						// if =
						while (fbuf[i] != '=')
						{
							if (fbuf[i] == '\0') return false;
							Key.name += fbuf[i++];
						}
						/* if simbol " to copy text to value */

						/* */
						i++;
						while ((fbuf[i] != '\n') && (fbuf[i] != ';'))
						{
							if (fbuf[i] == '"')
							{
								i++;
								Key.value = "";
								while (fbuf[i] != '"')
								{
									if (fbuf[i] == '\0') {fbuf = ""; return false;}
									Key.value += fbuf[i++];
								}
								break;
							}
							Key.value += fbuf[i++];
							if (fbuf[i] == '\0')
							{
								_newGrup.keys.push_back(Key);
								doc.push_back(_newGrup);
								fbuf = "";
								return false; // out 
							}
						}
						i++;
						/* faind new line */
						while ((fbuf[i] == '\n') && (fbuf[i] != '[') && (fbuf[i] != ';') && (fbuf[i] != ' '))
						{
							while (fbuf[i++] != '\n') { if (fbuf[i] == '\0') 
								/* close grup */
								_newGrup.keys.push_back(Key);
							    doc.push_back(_newGrup);
								fbuf = "";
								return false; }
						}
						if (fbuf[i] == '[')
						{
							/* close grup */
							_newGrup.keys.push_back(Key);
							doc.push_back(_newGrup);
							break;
						}
						_newGrup.keys.push_back(Key);
					}
				}
			}
			return true;
		}
		catch (std::ifstream::failure e)
		{
			std::cout << "ERROR::FILE_NOT_SUCCESFULLY_READ" << std::endl;

		}
		return false;
	}

	const int __bit_mask[] = { 0,1,3,7,15,31,63,127,255,511,1023,2047,4095,8191,16383,0 };

	//int __faind_grup_sse(string& val, string& str)
	//{
	//	static	int index = 0;
	//	static int loop_ckl = 0;
	//	static int index_val = 0;
	//	static int index_mask = 0;
	//	static bool loop = false;
	//	static	__m128i _val;
	//	static int bit_mask = 0;
	//	char* stradr;
	//	//
	//	if (loop == false)
	//	{
	//		if (loop_ckl == 0) { loop_ckl = (int)val.length(); index_val = 0; }
	//		//
	//		if (loop_ckl < 0x0f) { stradr = &val[index_val]; index_mask = loop_ckl; loop_ckl = 0; }
	//		else
	//		{
	//			index_mask = 0x0f;
	//			loop_ckl -= 0xf;
	//			stradr = &val[index_val];
	//			index_val += 0x0f;
	//		}

	//		bit_mask = __bit_mask[index_mask];
	//		_val = _mm_loadu_epi8(stradr);
	//		loop = true;
	//	}
	//	auto faind = _mm_loadu_epi8(&str[index]);
	//	auto res = _mm_cmpeq_epi8(faind, _val);
	//	auto ms = _mm_movemask_epi8(res);


	//	if ((bit_mask == ms))
	//	{
	//		if (loop_ckl > 0) {
	//			loop = false;
	//			__faind_grup_sse(val, str);
	//		}
	//		auto ret = index + 1;
	//		index = 0;
	//		loop_ckl = 0;
	//		loop = false;
	//		return ret;
	//	}
	//	else
	//	{
	//		if (index != (str.size() - 15))
	//		{
	//			index++;
	//			__faind_grup_sse(val, str);
	//		}
	//		else {
	//			index = 0;
	//			loop = false;
	//			loop_ckl = 0;
	//			return -1;
	//		}
	//	}
	//	//return -1;
	//}


	bool cFINIin::openGrup(const char* name)
	{
		alignas(16) string tmp;

		tmp = "";
		tmp += '[';
		tmp += name;



		//auto res = __faind_grup_sse(tmp, this->fbuf);



		return false;
	}

}
