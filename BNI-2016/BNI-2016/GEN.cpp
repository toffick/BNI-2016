#include "stdafx.h"
#include "GEN.h"
#include <iostream>
#define DW " DW "
#define DB " DB "
#define VAL_INT_DEFAULT " 0 "
#define VAL_STR_DEFAULT "\'\',0"
#define VAL_BOOL_DEFAULT "0"
#define SPACE ' '
#define PROTO "PROTO"
#define PROT_PARM ":DWORD"
#define STACK ".stack 4096\n"
#define LINE_BREAK '\n'
#define TITLE ".586\n.model flat, stdcall\n\nincludelib kernel32.lib\n"
#define GEN1(tt) sprintf_s()
#define GEN2(tt, val) std::string(tt)+std::string(val)
#define T0_0 

#define r "ret"

void Gen::StartGen(LEX::Lex lex, MFST::Mfst mfst, Log::LOG log, Parm::PARM parm)
{
	std::string gencode;
	gencode += GEN2("fi", "koko");
	gencode += TITLE;
	gencode += LINE_BREAK;
	gencode += CreateProtSeg(lex);
	gencode += LINE_BREAK;
	gencode += STACK;
	gencode += SPACE;
	//gencode += CreateDatSeg(lex);
	//gencode += CreateConstSeg(lex);


	MFST::MfstState state;
	GRB::Rule rule;
	std::cout << "\nДерево разбора\n";
	char rbuf[205];

	for (unsigned short k = 0; k < mfst.storestate.size(); k++)
	{
		state = mfst.storestate._Get_container()[k];
		rule = mfst.grebach.getRule(state.nrule);
		std::cout << rule.getCRule(rbuf, state.nrulechain);
	}
	

std::cout << gencode;
*(log.stream) << "\n\n\nКод асм\n\n\n" << gencode;

}
std::string MainGen(LEX::Lex lex, MFST::Mfst mfst)
{
	MFST::MfstState state;
	GRB::Rule rule;
	std::string tmp;
	for (unsigned short k = 0; k < mfst.storestate.size(); k++)
	{
		state = mfst.storestate._Get_container()[k];
		rule = mfst.grebach.getRule(state.nrule);

		switch (state.nrule)
		{
		case 0:
		{
			switch (state.nrulechain)
			{
			case 0:
				//tmp += 
				//тут вставляем шаблон для 0 правила 0 цепочки
				break;
			}
			break;

		}
		}



	}
	return tmp;
}

std::string Gen::CreateDatSeg(LEX::Lex lex)
{
	std::string tmp;
	tmp += "\n.data\n";
	for (int i = 0; i < lex.idtable.size; i++)
	{
		if (lex.idtable.table[i].idtype == IT::V)
		{
			tmp += lex.idtable.table[i].id;
			tmp += DB;
			switch (lex.idtable.table[i].iddatatype)
			{
			case IT::INT:
				tmp += VAL_INT_DEFAULT;
				break;
			case IT::STR:
				tmp += VAL_STR_DEFAULT;
				break;
			case IT::BOOL:
				tmp += VAL_BOOL_DEFAULT;
				break;
			}
			tmp += LINE_BREAK;
		}
	}
	return tmp;
}
std::string Gen::CreateConstSeg(LEX::Lex lex)
{
	std::string tmp;
	tmp += "\n.const\n";
	for (int i = 0; i < lex.idtable.size; i++)
	{
		if (lex.idtable.table[i].idtype == IT::L)
		{
			tmp += lex.idtable.table[i].id;
			tmp += DB;
			switch (lex.idtable.table[i].iddatatype)
			{
			case IT::INT:
				char bufint[10];
				_itoa(lex.idtable.table[i].value.vind,bufint,10);
				tmp += bufint;
				break;
			case IT::STR:
				
				tmp += lex.idtable.table[i].value.vstr.str;
				tmp += ", 0";
				break;
			case IT::BOOL:
				char boolint[10];
				_itoa(lex.idtable.table[i].value.vind, boolint, 10);
				tmp += boolint;
				break;
			}
			tmp += LINE_BREAK;
		}
			
	}
	return tmp;
}
std::string Gen::CreateProtSeg(LEX::Lex lex)
{
	std::string tmp;
	for (int i = 0; i < lex.idtable.size; i++)
	{
		if (lex.idtable.table[i].idtype == IT::F && strcmp(lex.idtable.table[i].id, "main"))
		{
			tmp += lex.idtable.table[i++].id;
			tmp += SPACE;
			tmp += PROTO;
			tmp += SPACE;
			while (lex.idtable.table[i++].idtype == IT::P)
			{
				tmp += PROT_PARM;
				tmp += ',';
			}
			tmp[tmp.size()-1] = LINE_BREAK;
		}
	}
	return tmp;

}
