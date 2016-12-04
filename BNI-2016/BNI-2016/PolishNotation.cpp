#pragma once
#include "stdafx.h"
#include "PolishNotation.h"
#include <fstream>
#include<stack>
namespace PN {

	LT::Entry* PolishNotation(LT::Entry* outstr, int lextable_pos, LT::LexTable lextable, IT::IdTable idtable) {
		std::stack<LT::Entry> st;
		std::stack<LT::Entry> parmstack;
		//LT::Entry* outstr=new LT::Entry[200];
		int len = 0,																				//общая длина
			lenout = 0;																			//длина выходной строки
		char t,sign=0x00,skob=0;																		//текущий символ/знак оператора/кол-во скобок
		int indoffunk;																			//индекс для замены на элемент с функцией
	for (int i = lextable_pos; lextable.table[i].lexema != LEX_SEMICOLON; i++)
	{
			len=i;
	}
		len++;
		for (int i = lextable_pos; i < len; i++) {
			t = lextable.table[i].lexema;
			if(lextable.table[i].lexema== LEX_ARIPH)
				sign = idtable.table[lextable.table[i].idxTI].id[0];
			if (t == LEX_RIGHTHESIS)						//выталкивание всего до другой левой скобки
			{				
				while (st.top().lexema != LEX_LEFTHESIS) {
					outstr[lenout++] = st.top();				//записываем в выходную строку очередной символ между скобками
					skob++;
					st.pop();								//удаляем вершину стека
				}
				st.pop();									//удаляем левую скобку в стеке
			}
			if (t == LEX_ID || t == LEX_LITERAL) {
				if (lextable.table[i+1].lexema == LEX_LEFTHESIS) {
					indoffunk = i;
					i+=2;
					while (lextable.table[i].lexema != LEX_RIGHTHESIS) {								//пока внутри аргументов функции, переписываем их в строку
						if (lextable.table[i].lexema!=LEX_COMMA) 
						{
							parmstack.push(lextable.table[i++]);
						}
						else
						{
							skob++;
							i++;
						}					
					}
					while (parmstack.size())
					{
						outstr[lenout++] = parmstack.top();
						parmstack.pop();
					}
					outstr[lenout++] = lextable.table[indoffunk];
					skob += 2;
				}
				else 
					outstr[lenout++] = lextable.table[i];				
			}
			if (t == LEX_LEFTHESIS)
			{
				st.push(lextable.table[i]);							//помещаем в стек левую скобку
				skob++;
			}

			if (sign == '+' || sign == '-' || sign == '/' || sign == '*') {
				if (!st.size())
					st.push(lextable.table[i]);
				else {
					int pr,id;
					if (st.top().lexema == '(' || st.top().lexema == ')') 
						pr = 1;
					else {
						id = st.top().idxTI;
						 pr = prior(idtable.table[id].id[0]);
					}
					if (prior(sign)>pr)								//если приоритет добавляемой операции больше операции на вершине стека
						st.push(lextable.table[i]);																				//добавляем операции в стек
					else {
						while (st.size() && prior(sign) <= prior(idtable.table[id].id[0]))			//если меньше, то записываем в строку все операции с большим или равным приоритетом
						{
							outstr[lenout] = st.top();
							st.pop();
							lenout++;
						}
						st.push(lextable.table[i]);
					}
				}	
			}
			sign = NULL;				//обнуляем поле знака
		}
		while (st.size()) 
		{
			outstr[lenout++] = st.top();														//вывод в строку всех знаков из стека
			st.pop();
		}

		return outstr;
	}
	int prior(char l) {
		if (l == ')' || l == '(')
			return 1;
		if (l == '+' || l == '-')
			return 2;
		if (l == '*' || l == '/')
			return 3;	
	}
}	