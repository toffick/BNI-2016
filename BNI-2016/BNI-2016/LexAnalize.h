#pragma once

#include "IT.h"
#include "LT.h"
#include "Log.h"
#include "FST.h"
namespace LEX
{
	struct Lex                 // структура результата работы лексического анализатора
	{
		LT::LexTable lextable;   // таблица лексем
		IT::IdTable  idtable;    // таблица идентиикаторов

		Lex():lextable(LT::Create(LT_MAXSIZE)), idtable(IT::Create(IT_MAXSIZE)){};
	};

	bool newId(char* prefix, char* name, IT::Entry& ItE, Error::Errors& ers, Lex& lex, int line);
	void CreatId(int line, FST::FST& fst, Error::Errors& ers, Lex& lex);   // сформировать запись для ТИ
	Lex StartLA(In::IN& in, Error::Errors& ers);  // начать лексичский анализ
	void RestartItE(IT::Entry& ItE);

};
