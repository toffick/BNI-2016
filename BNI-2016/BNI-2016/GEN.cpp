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
#define DATA ".data"
#define CONST ".const"
#define LINE_BREAK '\n'
#define TITLE ".586\n.model flat, stdcall\n\nincludelib kernel32.lib\n"

#define GEN2(str, var1,var2)	fmt::format(str, var1, var2)
#define GEN1(str, var1)			fmt::format(str, var1)
#define GEN0(str)				fmt::format(str)

#define T0_0 "{0} PROC uses eax ebx ecx edi esi\n ;N\n ;E\n pop eax\n ret\n{0} ENDP\n\n"
#define T0_1 "{0} PROC uses eax ebx ecx edi esi\n ;F\n ;E\n ;N\n pop eax\nret\n{0} ENDP \n\n"
#define T0_2 "{0} PROC uses eax ebx ecx edi esi\n ;F\n ;E\n pop eax\n ret\n{0} ENDP  \n\n"
#define T0_3 "{0} PROC uses eax ebx ecx edi esi\n ;F\n ;E\n pop eax\n ret\n{0} ENDP \n;S\n\n"
#define T0_4 "{0} PROC uses eax ebx ecx edi esi\n ;F\n ;E\n pop eax\n ret\n{0} ENDP\n;S\n\n"
#define T0_5 "{0} PROC uses eax ebx ecx edi esi\n ;E\n pop eax\n ret\n{0} ENDP\n;S\n\n"


#define T1_1 "{0} "
#define T3_0 "\n ,{0}: dword\n"
#define T3_1 "\n ,{0}: dword\n ;F"
void Gen::StartGen(LEX::Lex lex, MFST::Mfst mfst, Log::LOG log, Parm::PARM parm)
{
	std::string gencode;
	std::cout << "________________________________\n";
	gencode += TITLE;
	gencode += LINE_BREAK;
	gencode += CreateProtSeg(lex);
	gencode += LINE_BREAK;
	gencode += STACK;
	gencode += LINE_BREAK;
	gencode += LINE_BREAK;

	gencode += MainGen(lex, mfst);
	//gencode += CreateDatSeg(lex);
	//gencode += CreateConstSeg(lex);



	

std::cout << gencode;
*(log.stream) << "\n\n\nКод асм\n\n\n" << gencode;

}
std::string Gen::MainGen(LEX::Lex lex, MFST::Mfst mfst)
{
	MFST::MfstState state;
	GRB::Rule rule;
	std::string tmp;
	tmp += ";S";
	int k = 0;
	int id = 0;

	for (unsigned short i = 0; i < mfst.storestate.size(); i++)
	{
		state = mfst.storestate._Get_container()[i];
		rule = mfst.grebach.getRule(state.nrule);

		int mm = tmp.find_first_of(';');
	
		switch (state.nrule)
		{
		case 0:
		{
			switch (state.nrulechain)
			{
			case 0:
			
				tmp.erase(mm, 2);
				tmp.insert(mm, GEN1(T0_0, lex.idtable.table[id++].id));
				break;
			case 1:

				tmp.erase(mm, 2);
				tmp.insert(mm, GEN1(T0_1, lex.idtable.table[id++].id));
				break;
			case 2:
				tmp.erase(mm, 2);
				tmp.insert(mm, GEN1(T0_2, lex.idtable.table[id++].id));
				break;
			case 3:

				tmp.erase(mm, 2);
				tmp.insert(mm, GEN1(T0_3, lex.idtable.table[id++].id));
				break;
			case 4:
				tmp.erase(mm, 2);
				tmp.insert(mm, GEN1(T0_4, lex.idtable.table[id++].id));
				break;
			case 5:
				tmp.erase(mm, 2);
				tmp.insert(mm, GEN1(T0_5, lex.idtable.table[id++].id));
				break;
			}
			break;
		case 3:
			switch (state.nrulechain)
			{
			case 0:
				tmp.erase(mm,2);
				tmp.insert(mm, GEN1(T3_0, lex.idtable.table[id++].id));
				break;
			}
			break;
		}
		}

	//	std::cout << "-----------------------------\n" << tmp;
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
