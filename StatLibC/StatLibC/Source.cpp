#include "stdafx.h"
#include "StatLib.h"
#include <math.h>
#include <iostream>
extern "C"
{
	int _stdcall  strl(char* str)
	{
		return strlen(str);
	}
	int _stdcall ipow(int i, int j)
	{
		return pow(i,j);
	}

	void _stdcall  writes(char* s)
	{
		std::cout << s;
	}
	void _stdcall  writei(int i)
	{
		std::cout << i;
	}
	int _stdcall  sum(int a, int b)
	{
		return a + b;
	}

}
