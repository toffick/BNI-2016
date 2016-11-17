#pragma once
#include "stdafx.h"
#include "Error.h"
#include "In.h"
#include <fstream>

//организован алгоритм разбора исходного кода на отдельные цепочки

namespace In {
	In::IN getin(wchar_t infile[], Error::Errors& errarr) {

		std::ifstream par(infile);
		if (par.fail())
		{
			throw ERROR_THROW(110);
		}
		else
		{
			IN ret;
			int chain_len = 0;
			int pos = 0;
			int ind;
			char pt = 0x00;																		//предыдущий символ
			bool unary = false;																	//ожидание унарного оператора
			for (char t = par.get(); t != EOF; t = par.get())
			{
				ind = (int)t;
				switch (ret.code[ind]) {
					case IN::D:
					{
						if (chain_len)												//прверка на наличие символов в буферной строке, для незаписи в нее пробела
						{
							ret.chains[ret.size++].chain[chain_len] = 0x00;
							chain_len = 0;
						}
						if (t == IN_N)																					//если перенос строки
						{
							pos = 0;
							ret.lines++;
						}
						break;
					}
					case IN::T:
					{
						ret.chains[ret.size].chain[chain_len++] = t;
						break;
					}
					case IN::S:																
					{
						if (unary && ((t == IN_UNARY_M && t == pt) || (t == IN_UNARY_P && t == pt)))					//ожидаем ли унарную операцию + проверка на унарный символ
						{
							ret.chains[ret.size - 1].chain[1] = t;
							ret.chains[ret.size - 1].chain[2] = 0x00;
							chain_len = 0;
							ret.chains[ret.size-1].line = ret.lines;

							unary = false;
						}
						else {																							//иначе обрываем строку на сепараторе
							if (chain_len)																				
							{																							///предотвращение записи пустой строки
								ret.chains[ret.size++].chain[chain_len] = 0x00;
								chain_len = 0;
							}
							if (!unary && (t == IN_UNARY_M || t == IN_UNARY_P))											//потенциально унарная операция
								unary = true;
							ret.chains[ret.size].line = ret.lines;														//задаем новую цепочку с сепаратором и номерои его стркоки  
							ret.chains[ret.size].chain[chain_len++] = t;
							ret.chains[ret.size++].chain[chain_len] = 0x00;
							chain_len = 0;
						}
						break;
					}
					case IN::F:
					{
						Error::adderr(111, ret.lines, pos, errarr);
						break;
					}
					case IN::I:
					{
						ret.ignor++;
						break;
					}
					case IN::Q:																			//ссчитывание строки между кавычками
					{
						ret.chains[ret.size].chain[chain_len++] = t;									//помещаем кавычку в номер строки
						t = par.get();																	//ссчитываем очередной символ
						while (ret.code[(int)t] != IN::Q)												//записываем литералам между кавыками
						{				
							ret.chains[ret.size].chain[chain_len++] = t;
							t = par.get();
						}
						ret.chains[ret.size].chain[chain_len++] = t;									//дописываем кавычку 
						ret.chains[ret.size++].chain[chain_len] = 0x00;
						chain_len = 0;
						break;
					}
					default: 
						Error::adderr(111, ret.lines, pos, errarr);
						break;
				}
				pt = t;																					//предыдущий  символ
				ret.chains[ret.size].line=ret.lines;													//запись в текущую цепочку номера строки 
				pos++;
			}
			if (chain_len)																				//костыль: если есть строка на конце файла, то записываем ее в массив 
				ret.chains[ret.size++].chain[chain_len] = 0x00;
			par.close();
			return ret;
		}
	}
};
