#pragma once
#include "IT.h"
#include "LT.h"
#include <locale>
#include <iostream>
#define LEX_ZAMENA '@'
#define LEX_EQUAL '='
namespace PN {
	bool PolishNotation(int lextable_pos, LT::LexTable* lextable, IT::IdTable* idtable);
	void CallPolishNotation(LT::LexTable* lextable, IT::IdTable* idtable);
	int prior(char);
}
//true - выполнено успешно
//false - построение не выполнено