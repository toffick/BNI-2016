#include "stdafx.h"
#include "StatLib.h"
#include <math.h>
#include <iostream>
extern "C"
{
	int _stdcall  strl(const char* str)
	{
		int i = strlen(str);
		_asm
		{
			mov edx, i
		}
		return i;
	}
	int _stdcall ipow(int i, int j)
	{
		int o = (int)pow(i,j);
		_asm
		{
			mov edx, o
		}
		return o;
	}

	void _stdcall  writes(const char* s)
	{
		setlocale(0, "rus");
		if (s != nullptr)
		std::cout << std::endl << s;
		else 
			std::cout << "\n_bad string value_\n" << s;

	}
	void _stdcall  writei(int i)
	{
		std::cout << i << std::endl;
	}
	int _stdcall  sum(int a, int b)
	{
		return a + b;
	}

}

