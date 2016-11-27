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

#define GEN2(b, tmp, var1,var2)	sprintf_s(b, 1024, tmp, var1,var2)
#define GEN1(b, tmp, var1)	sprintf_s(b, 1024, tmp, var1)
#define GEN0(b, tmp)		sprintf_s(b,1024,tmp)
#define T0_0 "%s PROC uses eax ebx ecx edi esi\n ;N\n pop eax\n ret\n%s ENDP\n\n"
#define T0_1 "%s PROC uses eax ebx ecx edi esi\n ;F\n ;N\n pop eax\nret\n%s ENDP \n\n"
#define T0_2 "%s PROC uses eax ebx ecx edi esi\n ;F\n pop eax\n ret\n%s ENDP  \n\n"
#define T0_3 "%s PROC uses eax ebx ecx edi esi\n ;F\n pop eax\n ret\n%s ENDP \n;S\n\n"
#define T0_4 "%s PROC uses eax ebx ecx edi esi\n ;F\n pop eax\n ret\n%s ENDP\n;S\n\n"
#define T0_5 "%s PROC uses eax ebx ecx edi esi\n pop eax\n ret\n%s ENDP\n;S\n\n"

#define T3_0 "\n ,%s: dword\n"
#define T3_1 "\n ,%s: dword\n ;F"
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
	char buf[10240];
	int k = 0;
	int id = 0;
	for (unsigned short i = 0; i < mfst.storestate.size(); i++)
	{
		state = mfst.storestate._Get_container()[i];
		rule = mfst.grebach.getRule(state.nrule);

		//где-то тут идет поиск нетерменалов
		
		switch (state.nrule)
		{
		case 0:
		{
			switch (state.nrulechain)
			{
			case 0:
				k += GEN2(buf + k, T0_0, lex.idtable.table[id].id, lex.idtable.table[id].id);
				id++;
				break;
			case 1:
				k += GEN2(buf + k, T0_1, lex.idtable.table[id].id, lex.idtable.table[id].id);
				id++;
				break;
			case 2:
				k += GEN2(buf + k, T0_2, lex.idtable.table[id].id, lex.idtable.table[id].id);
				id++;
				break;
			case 3:
				k += GEN2(buf + k, T0_3, lex.idtable.table[id].id, lex.idtable.table[id].id);
				id++;
				break;
			case 4:
				k += GEN2(buf + k, T0_4, lex.idtable.table[id].id, lex.idtable.table[id].id);
				id++;
				break;
			case 5:
				k += GEN2(buf + k, T0_5, lex.idtable.table[id].id, lex.idtable.table[id].id);
				id++;
				break;
			}
			break;
		case 3:
			switch (state.nrulechain)
			{
			case 0:
				k += GEN1(buf + k, T3_0, lex.idtable.table[id].id);
				id++;
				break;
			}
			break;
		}
		}


		//std::cout << "-----------------------------\n" << buf;

	}
	return std::string(buf);
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

//std::string Gen::CreateDatSeg(LEX::Lex lex)
//{
//	std::string tmp;
//	tmp += "\n.data\n";
//	for (int i = 0; i < lex.idtable.size; i++)
//	{
//		if (lex.idtable.table[i].idtype == IT::V)
//		{
//			tmp += lex.idtable.table[i].id;
//			tmp += DB;
//			switch (lex.idtable.table[i].iddatatype)
//			{
//			case IT::INT:
//				tmp += VAL_INT_DEFAULT;
//				break;
//			case IT::STR:
//				tmp += VAL_STR_DEFAULT;
//				break;
//			case IT::BOOL:
//				tmp += VAL_BOOL_DEFAULT;
//				break;
//			}
//			tmp += LINE_BREAK;
//		}
//	}
//	return tmp;
//}
//std::string Gen::CreateConstSeg(LEX::Lex lex)
//{
//	std::string tmp;
//	tmp += "\n.const\n";
//	for (int i = 0; i < lex.idtable.size; i++)
//	{
//		if (lex.idtable.table[i].idtype == IT::L)
//		{
//			tmp += lex.idtable.table[i].id;
//			tmp += DB;
//			switch (lex.idtable.table[i].iddatatype)
//			{
//			case IT::INT:
//				char bufint[10];
//				_itoa(lex.idtable.table[i].value.vind, bufint, 10);
//				tmp += bufint;
//				break;
//			case IT::STR:
//
//				tmp += lex.idtable.table[i].value.vstr.str;
//				tmp += ", 0";
//				break;
//			case IT::BOOL:
//				char boolint[10];
//				_itoa(lex.idtable.table[i].value.vind, boolint, 10);
//				tmp += boolint;
//				break;
//			}
//			tmp += LINE_BREAK;
//		}
//
//	}
//	return tmp;
//}