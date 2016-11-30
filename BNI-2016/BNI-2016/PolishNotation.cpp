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
		int len=0,																				//����� �����
			lenout=0,																			//����� �������� ������
			semicolonid;																		//�� ��� �������� ������� � ������ � �������
		char t,znak,skob=0;																		//������� ������/���� ���������/���-�� ������
		int indoffunk;																			//������ ��� ������ �� ������� � ��������
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
				if (lextable->table[i+1].lexema == LEX_LEFTHESIS) {
					indoffunk = i;
					i+=2;
					while (lextable->table[i].lexema != LEX_RIGHTHESIS) {								//���� ������ ���������� �������, ������������ �� � ������
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
				st.push(lextable->table[i]);							//�������� � ���� ����� ������
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
					if (prior(znak)>pr)								//���� ��������� ����������� �������� ������ �������� �� ������� �����
						st.push(lextable->table[i]);																				//��������� �������� � ����
					else {
						while (st.size() && prior(znak) <= prior(idtable->table[id].id[0]))			//���� ������, �� ���������� � ������ ��� �������� � ������� ��� ������ �����������
						{
							outstr[lenout] = st.top();
							st.pop();
							lenout++;
						}
						st.push(lextable->table[i]);
					}
				}	
			}
			znak = NULL;				//�������� ���� �����
		}
		while (st.size()) {
			outstr[lenout++] = st.top();														//����� � ������ ���� ������ �� �����
			st.pop();
		}
		for (int i = lextable_pos,k=0; i < lextable_pos + lenout; i++,k++) {
			lextable->table[i] = outstr[k];														//������ � ������� �������� ������
		}
		lextable->table[lextable_pos + lenout] = lextable->table[semicolonid];					//������� �������� � ������ � �������
		for (int i = 0;i<skob; i++)
		{
			for (int j = lextable_pos + lenout+1; j <lextable->size; j++)						//�������� �� ������ �����
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