#pragma once
#include "stdafx.h"
#include "LexAnalize.h"

namespace LEX
{
	Lex StartLA(In::IN& in, Error::Errors& ers)  // начать лексичский анализ
	{
		Lex lex;                               
		FST::FST* fsts = FST::crfsts();  
	/*	for (int i = 0; i < in.size; i++)
		{
			std::cout << in.chains[i].chain << '_'<<std::endl;
		}*/
		for (int i = 0; i < in.size; i++)
		{
			for (int j = 0; j < FST_ARR_SIZE; j++)
			{
				FST::restartFST(fsts[j], in.chains[i].chain);

				if (FST::execute(fsts[j]))
				{
					LT::Add(lex.lextable, LT::Entry(fsts[j].lexema, in.chains[i].line, IT::getIdxTI(fsts[j].lexema, lex.idtable)));
					//handleId(in.chains[i].line, fsts[j], ers, lex);
					break;
				};
			};
		}
		int k = 0;
		std::cout << "\n\nТаблица лексем\n0: ";
		for (int i = 0; i < lex.lextable.size; i++) 
		{
			if (lex.lextable.table[i].sn != k) 
			{
				std::cout << "\n" << lex.lextable.table[i].sn << ": ";
				k = lex.lextable.table[i].sn;
				std::cout << lex.lextable.table[i].lexema;
			}
			else
				std::cout << lex.lextable.table[i].lexema;
		}
		return lex;
	}
}

