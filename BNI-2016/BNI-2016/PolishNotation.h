#pragma once
#include "IT.h"
#include "LT.h"
#include <locale>
#include <iostream>
#define LEX_ZAMENA '@'
#define LEX_EQUAL '='
namespace PN {
	LT::Entry* PolishNotation(LT::Entry*, int lextable_pos, LT::LexTable lextable, IT::IdTable idtable);
	//void CallPolishNotation(LT::LexTable* lextable, IT::IdTable* idtable);
	int prior(char);
}
//true - ��������� �������
//false - ���������� �� ���������