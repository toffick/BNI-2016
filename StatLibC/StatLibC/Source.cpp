#include "stdafx.h"
#include "StatLib.h"
#include <math.h>
#include <iostream>
extern "C"
{
	/*int _stdcall  strl(char* str)
	{
		return strlen(str);
	}*/
	//int _stdcall ipow(int i, int j)
	//{
	//	return (int)pow(i,j);
	//}

	void   writes(char* s)
	{
		std::cout << s;
		// printf("%s", s);
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

//
//x = 1 + fi(2,3)
//
//1 3 2 fi +
//
