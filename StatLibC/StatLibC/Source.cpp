#include "stdafx.h"
#include "StatLib.h"
#include <math.h>
#include <iostream>
extern "C"
{
	int _stdcall  strl(const char* str)
	{
		return strlen(str);
	}
	int _stdcall ipow(int i, int j)
	{
		return (int)pow(i,j);
	}

	void _stdcall  writes(const char* s)
	{
		setlocale(0, "rus");
		std::cout << std::endl << s;
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

