#include "stdafx.h"
#include "GEN.h"
#include <iostream>
#define SDW " SDWORD "
#define BT " BYTE "
#define VAL_INT_DEFAULT " 0 "
#define VAL_STR_DEFAULT "\'\',0"
#define VAL_BOOL_DEFAULT "0"
#define SPACE ' '
#define PROTO "PROTO"
#define PROT_PARM ":DWORD"
#define STACK ".stack 4096\n"
#define DATA ".data"
#define CONST ".const"
#define LINE_BREAK "\n"
#define DBLINE_BREAK "\n\n"

#define TITLE ".586\n.model flat, stdcall\n\nincludelib kernel32.lib\nExitProcess PROTO :DWORD\n"
#define CODE ".code"

#define GEN2(str, var1,var2)	fmt::format(str, var1, var2)
#define GEN1(str, var1)			fmt::format(str, var1)
#define GEN0(str)				fmt::format(str)

#define T0_0 "{0} PROC uses eax ebx ecx edi esi\n ;N\n ;E\n push 0\ncall ExitProcess\n {0} ENDP\n\n"
#define T0_1 "{0} PROC uses eax ebx ecx edi esi\n ;F\n ;E\n ;N\n pop eax\nret\n{0} ENDP \n\n"
#define T0_2 "{0} PROC uses eax ebx ecx edi esi\n ;F\n ;E\n pop eax\n ret\n{0} ENDP  \n\n"
#define T0_3 "{0} PROC uses eax ebx ecx edi esi\n ;F\n ;E\n pop eax\n ret\n{0} ENDP \n;S\n\n"
#define T0_4 "{0} PROC uses eax ebx ecx edi esi\n ;F\n ;E\n pop eax\n ret\n{0} ENDP\n;S\n\n"
#define T0_5 "{0} PROC uses eax ebx ecx edi esi\n ;E\n push 0\ncall ExitProcess\n{0} ENDP\n;S\n\n"




#define T3_0 "\n ,{0}: dword\n"
#define T3_1 "\n ,{0}: dword\n ;F"


//1. переписать правило для главной функции и шаблоны для них
//2. переделать удаление замененных нетерменалов
void Gen::StartGen(LEX::Lex lex, MFST::Mfst mfst, Log::LOG log, Parm::PARM parm)
{
	std::string gencode;
	std::cout << "\n________________________________\n";
	gencode += TITLE;
	gencode += LINE_BREAK;
	gencode += CreateProtSeg(lex);
	gencode += LINE_BREAK;
	gencode += CONST;
	gencode += DBLINE_BREAK;
	
	CreateDatSeg(gencode, lex);
	gencode += STACK;
	gencode += DBLINE_BREAK;
	gencode += CODE;
	gencode += DBLINE_BREAK;



	gencode += MainGen(gencode,lex, mfst);
	//gencode += CreateDatSeg(lex);
	//gencode += CreateConstSeg(lex);



	
	std::cout << "-----------------------------\n";

std::cout << gencode;
*(log.stream) << "\n\n\nКод асм\n\n\n" << gencode;

}
std::string Gen::MainGen(std::string& tmp, LEX::Lex lex, MFST::Mfst mfst)
{
	tmp += ";S";
	int k = 0;
	int id = 0;

	for (unsigned short i = 0; i < mfst.deducation.size; i++)
	{


		MFST::MfstState state;
		GRB::Rule rule;

		state = mfst.storestate._Get_container()[i];
		rule = mfst.grebach.getRule(state.nrule);

		//_______________________________________________________________________

		std::string tempforfind(";");
		tempforfind.push_back(GRB::Rule::Chain::alphabet_to_char(rule.nn));
		int firstOfNoTerminal = tmp.find(tempforfind);					//поиск позиции нетерменала текущего правила в строке
		switch (mfst.deducation.nrules[i])
		{
	/*программные конструкции*/
		case 0:
		{
			tmp.erase(firstOfNoTerminal, 3);
			switch (mfst.deducation.nrulechains[i])
			{
			case 0:

				tmp.insert(firstOfNoTerminal, GEN1(T0_0, lex.idtable.table[id++].id));
				break;
			case 1:
				tmp.insert(firstOfNoTerminal, GEN1(T0_1, lex.idtable.table[id++].id));
				break;
			case 2:
				tmp.insert(firstOfNoTerminal, GEN1(T0_2, lex.idtable.table[id++].id));
				break;
			case 3:
				tmp.insert(firstOfNoTerminal, GEN1(T0_3, lex.idtable.table[id++].id));
				break;
			case 4:
				tmp.insert(firstOfNoTerminal, GEN1(T0_4, lex.idtable.table[id++].id));
				break;
			case 5:
				tmp.insert(firstOfNoTerminal, GEN1(T0_5, lex.idtable.table[id++].id));
				break;
			}
			break;
		}
	/*основные конструкции*/
		case 1: 
		{
			switch (mfst.deducation.nrulechains[i])
			{
			case 1: /*N->dti;*/
			{
				tmp.erase(firstOfNoTerminal, 3);
				break;
			}

			}
			break;
		}
	/*параметры функции*/
		case 3:
		{
			tmp.erase(firstOfNoTerminal, 3);
			switch (mfst.deducation.nrulechains[i])
			{
			case 0:
				tmp.insert(firstOfNoTerminal, GEN1(T3_0, lex.idtable.table[id++].id));
				break;
			case 1:
				tmp.insert(firstOfNoTerminal, GEN1(T3_1, lex.idtable.table[id++].id));
				break;
			}
			break;
		}
		}

//------------------------------------
		char rbuf[205];
 std::cout <<"*********"<<std::endl<< std::setw(4) << std::left\
	<< std :: setw(5) << std::left << rule.getCRule(rbuf, state.nrulechain)\
	<<"-----------------------------" << std::endl << "*********\n";

			std::cout << "\n" << tmp;
	}
//------------------------------------	
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
			tmp[tmp.size()-1] = '\n';
		}
	}
	return tmp;
}
std::string Gen::CreateDatSeg(std::string& tmp, LEX::Lex lex)
{
	tmp += DBLINE_BREAK;
	tmp += DATA;
	tmp += LINE_BREAK;
	for (int i = 0; i < lex.idtable.size; i++)
	{
		if (lex.idtable.table[i].idtype == IT::V)
		{
			tmp += lex.idtable.table[i].id;
			
			switch (lex.idtable.table[i].iddatatype)
			{
			case IT::INT:
				tmp += SDW;
				tmp += VAL_INT_DEFAULT;
				break;
			case IT::STR:
				tmp += BT;
				tmp += VAL_STR_DEFAULT;
				break;
			case IT::BOOL:
				tmp += BT;
				tmp += VAL_BOOL_DEFAULT;
				break;
			}
			tmp += LINE_BREAK;
		}
	}
	return tmp;
}