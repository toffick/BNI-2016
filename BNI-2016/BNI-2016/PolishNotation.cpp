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
		int len = 0,																				//����� �����
			lenout = 0;																			//����� �������� ������
		char t,sign=0x00,skob=0;																		//������� ������/���� ���������/���-�� ������
		int indoffunk;																			//������ ��� ������ �� ������� � ��������
	for (int i = lextable_pos; lextable.table[i].lexema != LEX_SEMICOLON; i++)
	{
			len=i;
	}
		len++;
		for (int i = lextable_pos; i < len; i++) {
			t = lextable.table[i].lexema;
			if(lextable.table[i].lexema== LEX_ARIPH)
				sign = idtable.table[lextable.table[i].idxTI].id[0];
			if (t == LEX_RIGHTHESIS)						//������������ ����� �� ������ ����� ������
			{				
				while (st.top().lexema != LEX_LEFTHESIS) {
					outstr[lenout++] = st.top();				//���������� � �������� ������ ��������� ������ ����� ��������
					skob++;
					st.pop();								//������� ������� �����
				}
				st.pop();									//������� ����� ������ � �����
			}
			if (t == LEX_ID || t == LEX_LITERAL) {
				if (lextable.table[i+1].lexema == LEX_LEFTHESIS) {
					indoffunk = i;
					i+=2;
					while (lextable.table[i].lexema != LEX_RIGHTHESIS) {								//���� ������ ���������� �������, ������������ �� � ������
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
				st.push(lextable.table[i]);							//�������� � ���� ����� ������
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
					if (prior(sign)>pr)								//���� ��������� ����������� �������� ������ �������� �� ������� �����
						st.push(lextable.table[i]);																				//��������� �������� � ����
					else {
						while (st.size() && prior(sign) <= prior(idtable.table[id].id[0]))			//���� ������, �� ���������� � ������ ��� �������� � ������� ��� ������ �����������
						{
							outstr[lenout] = st.top();
							st.pop();
							lenout++;
						}
						st.push(lextable.table[i]);
					}
				}	
			}
			sign = NULL;				//�������� ���� �����
		}
		while (st.size()) 
		{
			outstr[lenout++] = st.top();														//����� � ������ ���� ������ �� �����
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