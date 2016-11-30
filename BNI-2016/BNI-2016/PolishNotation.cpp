#pragma once
#include "stdafx.h"
#include "PolishNotation.h"
#include <fstream>
#include<stack>
namespace PN {
	void CallPolishNotation(LT::LexTable* lextable, IT::IdTable* idtable) {

		for (int i = 0; i < lextable->size; i++) {
			if (lextable->table[i].lexema == LEX_EQUAL) {
				PolishNotation(++i, lextable, idtable);
			}
		}
	}
	bool PolishNotation(int lextable_pos, LT::LexTable* lextable, IT::IdTable* idtable) {
		std::stack<LT::Entry> st;
		LT::Entry outstr[200];
		int len=0,																				//общая длина
			lenout=0,																			//длина выходной строки
			semicolonid;																		//ид для элемента таблицы с точкой с запятой
		char t,znak,skob=0;																		//текущий символ/знак оператора/кол-во скобок
		int indoffunk;																			//индекс для замены на элемент с функцией
	for (int i = lextable_pos; lextable->table[i].lexema != LEX_SEMICOLON; i++)
	{
			len=i;
			semicolonid = i + 1;
	}
		len++;
		for (int i = lextable_pos; i < len; i++) {
			t = lextable->table[i].lexema;
			if(lextable->table[i].lexema== LEX_ARIPH)
				znak = idtable->table[lextable->table[i].idxTI].id[0];
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
				if (lextable->table[i+1].lexema == LEX_LEFTHESIS) {
					indoffunk = i;
					i+=2;
					while (lextable->table[i].lexema != LEX_RIGHTHESIS) {								//пока внутри аргументов функции, переписываем их в строку
						if (lextable->table[i].lexema!=LEX_COMMA) {
							outstr[lenout++] = lextable->table[i++];
						}
						else
						{
							skob++;
							i++;
						}					
					}			
					outstr[lenout++] = lextable->table[indoffunk];
					outstr[lenout - 1].lexema = LEX_ZAMENA;
					skob += 2;
				}
				else 
					outstr[lenout++] = lextable->table[i];				
			}
			if (t == LEX_LEFTHESIS) {
				st.push(lextable->table[i]);							//помещаем в стек левую скобку
				skob++;
			}

			if (znak == '+' || znak == '-' || znak == '/' || znak == '*') {
				if (!st.size())
					st.push(lextable->table[i]);
				else {
					int pr,id;
					if (st.top().lexema == '(' || st.top().lexema == ')') 
						pr = 1;
					else {
						id = st.top().idxTI;
						 pr = prior(idtable->table[id].id[0]);
					}
					if (prior(znak)>pr)								//если приоритет добавляемой операции больше операции на вершине стека
						st.push(lextable->table[i]);																				//добавляем операции в стек
					else {
						while (st.size() && prior(znak) <= prior(idtable->table[id].id[0]))			//если меньше, то записываем в строку все операции с большим или равным приоритетом
						{
							outstr[lenout] = st.top();
							st.pop();
							lenout++;
						}
						st.push(lextable->table[i]);
					}
				}	
			}
			znak = NULL;				//обнуляем поле знака
		}
		while (st.size()) {
			outstr[lenout++] = st.top();														//вывод в строку всех знаков из стека
			st.pop();
		}
		for (int i = lextable_pos,k=0; i < lextable_pos + lenout; i++,k++) {
			lextable->table[i] = outstr[k];														//запись в таблицу польской записи
		}
		lextable->table[lextable_pos + lenout] = lextable->table[semicolonid];					//вставка элемента с точкой с запятой
		for (int i = 0;i<skob; i++)
		{
			for (int j = lextable_pos + lenout+1; j <lextable->size; j++)						//сдвигаем на лишнее место
			{
				lextable->table[j] = lextable->table[j + 1];
			}
			lextable->size--;	
		}	
		return 1;
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