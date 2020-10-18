
#include "fini.h"
#include <fstream>
#include <sstream>

//SSE2
#include <immintrin.h>

using namespace std;

cFINIin::cFINIin()
{
	// file is open 
	 is = false;
	 grup_index = 0;
}

bool cFINIin::open(const char* puth)
{
	ifstream fin;
	stringstream strin;

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
		return true;
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		
	}
	return false;
}

const int __bit_mask[] = { 0,1,3,7,15,31,63,127,255,511,1023,2047,4095,8191,16383,0 };

int __faind_grup_sse(string &val, string &str)
{
static	int index = 0;
static int loop_ckl = 0;
static int index_val = 0;
static int index_mask = 0;
static bool loop = false;
static	__m128i _val ;
static int bit_mask = 0;
char* stradr;
	//
	if (loop == false)
	{
		if (loop_ckl == 0) { loop_ckl = (int)val.length(); index_val = 0; }
		//
		if (loop_ckl < 0x0f) { stradr = &val[index_val]; index_mask = loop_ckl; loop_ckl = 0;}
		else
		{
			index_mask = 0x0f;
			loop_ckl -= 0xf;
			stradr = &val[index_val];
			index_val += 0x0f;
		}
		
		bit_mask = __bit_mask[index_mask];
		_val = _mm_loadu_epi8(stradr);
		loop = true;
	}
	auto faind = _mm_loadu_epi8(&str[index]);
	auto res = _mm_cmpeq_epi8(faind, _val);
	auto ms = _mm_movemask_epi8(res);

	
	if ((bit_mask == ms))
	{
		if(loop_ckl > 0) {
			loop = false;
			__faind_grup_sse(val, str);		
		}
		auto ret = index + 1; 
		index = 0;
		loop_ckl = 0;
		loop = false;
		return ret;
	}
	else
	{
		if (index != (str.size() - 15))
		{
			index++;
			__faind_grup_sse(val, str);
		}
		else {
			index = 0;
			loop = false;
			loop_ckl = 0;
			return -1;
		}
	}
	//return -1;
}


bool cFINIin::openGrup(const char* name)
{
	alignas(16) string tmp;
	 
	tmp = "";
	tmp += '[';
	tmp += name;

	

	auto res = __faind_grup_sse(tmp, this->fbuf);



	return false;
}
