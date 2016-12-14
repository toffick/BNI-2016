#include "stdafx.h"
#include "GEN.h"
#include <iostream>
#define SDW " SDWORD "
#define BYTE " BYTE "
#define DW  " DWORD "
#define VAL_INT_DEFAULT " 0 "
#define VAL_STR_DEFAULT " ?"
#define SPACE ' '
#define PROTO "PROTO"
#define PROT_PARM_I ":SDWORD"
#define PROT_PARM_S ":DWORD"
#define STACK ".stack 4096\n"
#define DATA ".data"
#define CONST ".const"

#define LINE_BREAK "\n"
#define DBLINE_BREAK "\n\n"

#define TITLE ".586\n\
.model flat, stdcall\n\
\n\
includelib kernel32.lib\n\
includelib libucrt.lib\n\
includelib StatLibC.lib\n\
\n\
ExitProcess      PROTO : DWORD\n\
\n\
SetConsoleTitleA PROTO :DWORD\n\
GetStdHandle     PROTO : DWORD\n\
writei PROTO : SDWORD\n\
writes PROTO : DWORD\n\
strl   PROTO : DWORD\n\
ipow   PROTO : DWORD, : DWORD\n\
sum    PROTO : DWORD, : DWORD\n\
"
#define CODE ".code"
#define END_MAIN "\nend main"

#define GEN2(str, var1,var2)	fmt::format(str, var1, var2)
#define GEN1(str, var1)			fmt::format(str, var1)
#define GEN0(str)				fmt::format(str)

#define T0_0 "\n{0} PROC \n push offset csname\n call SetConsoleTitleA\n ;N\n\ jmp EXIT\nEXIT_div_on_NULL:\n\
 push offset DIV_NULL\n\
 call writes\n\
 push - 1\n\ call ExitProcess\n\nEXIT_overflow:\n\
 push offset Overflow\n\
 call writes\n\
 push - 2\n\
 call ExitProcess\n\nEXIT:\n ;E\n call ExitProcess\n\n\n{0} ENDP\n\n"
#define T0_1 "\n{0} PROC ;F\n;N\n;E\n pop edx\n \n jmp EXIT\nEXIT_div_on_NULL:\n\
 push offset DIV_NULL\n\
 call writes\n\
 push - 1\n\ call ExitProcess\n\nEXIT_overflow:\n\
 push offset Overflow\n\
 call writes\n\
 push - 2\n\
 call ExitProcess\n\nEXIT: \n ret \n\n{0} ENDP \n\n ;S\n"

#define T0_4 "\n{0} PROC ;F\n;E\n pop edx\n  \n jmp EXIT\nEXIT_div_on_NULL:\n\
 push offset DIV_NULL\n\
 call writes\n\
 push - 1\n\ call ExitProcess\n\nEXIT_overflow:\n\
 push offset Overflow\n\
 call writes\n\
 push - 2\n\
 call ExitProcess\n\nEXIT: \n ret \n\n{0} ENDP\n;S\n\n"
//#define T0_5 "\n{0} PROC \n push offset csname\n call SetConsoleTitleA\n ;N\n ;E\n\n\n  call ExitProcess\n\n{0} ENDP\n;S\n\n"

#define T1_3  " pop {0}\n"
#define T1_9  " pop {0}\n\n;N "

#define T1_4_S  ";E  call writes\n"
#define T1_4_I  ";E  call writei\n"

#define T1_6_S " push offset newline\n call writes\n"
#define T1_6_SN " push offset newline\n call writes\n;N\n"


#define T1_12_S  ";E  call writes\n;N \n"
#define T1_12_I  ";E  call writei\n;N \n"

#define T3_0_I " {0}:SDWORD\n"
#define T3_0_S " {0}:DWORD\n"

#define T3_1_I "{0}:SDWORD, ;F\n"
#define T3_1_S "{0}:DWORD, ;F\n"

#define ID_LIT_I " push {0}\n"
#define ID_LIT_S_I " push {0}\n"
#define ID_LIT_S_L " push offset {0}\n"

#define CALL " call {0}\n push edx\n"

#define EXPR_INT_PLUS " pop eax\n pop ebx\n add eax,ebx\n jo EXIT_overflow\n push eax\n"
#define EXPR_INT_IMUL " pop eax\n pop ebx\n imul eax,ebx\n jo EXIT_overflow\n push eax\n"
#define EXPR_SUB_IMUL " pop ebx\n pop eax\n sub eax,ebx\n jo EXIT_overflow\n push eax\n"
#define EXPR_DIV_IMUL " pop ebx\n pop eax\n test ebx, ebx\n\
 jz EXIT_div_on_NULL\n\
 cdq\n idiv ebx\n push eax\n"

void Gen::StartGen(LEX::Lex lex, MFST::Mfst mfst, Log::LOG log, Parm::PARM parm)
{
	std::string gencode;
	std::cout << "\n________________________________\n";
	gencode += TITLE;
	//gencode += LINE_BREAK;
//	gencode += CreateProtSeg(lex);
	gencode += STACK;
	gencode += LINE_BREAK;
	
	CreateDatSeg(gencode, lex);

	CreateConstSeg(gencode, lex);
	gencode += STACK;
	gencode += DBLINE_BREAK;
	gencode += CODE;
	gencode += DBLINE_BREAK;

	MainGen(gencode,lex, mfst);
	//gencode += CreateDatSeg(lex);
	//gencode += CreateConstSeg(lex);



	gencode += END_MAIN;
	std::cout << "-----------------------------\n";

std::cout << gencode;
*(log.stream_out) << gencode;

}


std::string Gen::MainGen(std::string& tmp, LEX::Lex lex, MFST::Mfst mfst)
{
	tmp += ";S";
	int k = 0;
	int id = 0;
	int sizeofstackremove = 0;
	for (unsigned short i = 0; i < mfst.deducation.size; i++)
	{


		MFST::MfstState state;
		GRB::Rule rule;

		state = mfst.storestate._Get_container()[i];
		rule = mfst.grebach.getRule(state.nrule);

		//_______________________________________________________________________

		std::string notermforfind(";");
		notermforfind.push_back(GRB::Rule::Chain::alphabet_to_char(rule.nn));
		int firstOfNoTerminal = tmp.find(notermforfind);					//поиск позиции нетерменала текущего правила в строке
		switch (mfst.deducation.nrules[i])
		{
	/*программные конструкции*/
		case 0:
		{
			tmp.erase(firstOfNoTerminal, 3);

			switch (mfst.deducation.nrulechains[i])
			{
			case 0:

				tmp.insert(firstOfNoTerminal, GEN1(T0_0, lex.idtable.table[lex.lextable.table[mfst.deducation.lp[i]].idxTI].id));
				break;
			case 1:
				tmp.insert(firstOfNoTerminal, GEN1(T0_1, lex.idtable.table[lex.lextable.table[mfst.deducation.lp[i] + 2].idxTI].id));
				break;

			case 4:
				tmp.insert(firstOfNoTerminal, GEN1(T0_4, lex.idtable.table[lex.lextable.table[mfst.deducation.lp[i] + 2].idxTI].id));
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
			case 3:/*N-> i=E;*/
			{
				//tmp
				tmp.erase(firstOfNoTerminal, 3);
				tmp.insert(firstOfNoTerminal, CreateExpression(lex, mfst, &i)+ GEN1(T1_3, lex.idtable.table[lex.lextable.table[mfst.deducation.lp[i]].idxTI].id));
				break;
			}
			case 4:/*N-> dE;*/
			{
				
				tmp.erase(firstOfNoTerminal, 3);
				if(lex.idtable.table[lex.lextable.table[mfst.deducation.lp[i+1]].idxTI].iddatatype==IT::STR)
				tmp.insert(firstOfNoTerminal, GEN0(T1_4_S));
				else 
					tmp.insert(firstOfNoTerminal, GEN0(T1_4_I));

				break;
			}
			case 5:/*N-> d;*/
			{

				tmp.erase(firstOfNoTerminal, 3);
				tmp.insert(firstOfNoTerminal, GEN0(T1_6_S));
				
					

				break;
			}
			case 11:/*N-> dE;N*/
			{
			
				tmp.erase(firstOfNoTerminal, 3);
				if (lex.idtable.table[lex.lextable.table[mfst.deducation.lp[i+1 ]].idxTI].iddatatype == IT::STR)
					tmp.insert(firstOfNoTerminal, GEN0(T1_12_S));
				else
					tmp.insert(firstOfNoTerminal, GEN0(T1_12_I));		
				break;
			}
			case 10: /*N-> i=E;N*/
			{
				tmp.erase(firstOfNoTerminal, 3);
				std::string mm = GEN1(T1_9, lex.idtable.table[lex.lextable.table[mfst.deducation.lp[i]].idxTI].id);
				std::string ll = CreateExpression(lex, mfst, &i);

				tmp.insert(firstOfNoTerminal, ll + mm);
				break;
			}
			case 12: /*N-> d;N*/
			{
			
				tmp.erase(firstOfNoTerminal, 3);
				tmp.insert(firstOfNoTerminal, GEN0(T1_6_SN));
				break;
			}
			}
			break;
		}
		case 2:
		{
			switch (mfst.deducation.nrulechains[i])
			{
			case 0: 
			case 1:
			{
				tmp.erase(firstOfNoTerminal, 3);
				std::string k;
				if(lex.idtable.table[lex.lextable.table[mfst.deducation.lp[i]].idxTI].iddatatype==IT::INT)
				k = GEN1(ID_LIT_I, lex.idtable.table[lex.lextable.table[mfst.deducation.lp[i]].idxTI].id);
				else 
					if(ID_LIT_I, lex.idtable.table[lex.lextable.table[mfst.deducation.lp[i]].idxTI].idtype==IT::L)
						k = GEN1(ID_LIT_S_L, lex.idtable.table[lex.lextable.table[mfst.deducation.lp[i]].idxTI].id);
					else 
						k = GEN1(ID_LIT_S_I, lex.idtable.table[lex.lextable.table[mfst.deducation.lp[i]].idxTI].id);

				tmp.insert(firstOfNoTerminal, k);

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
				if(lex.idtable.table[lex.lextable.table[mfst.deducation.lp[i] + 1].idxTI].iddatatype==IT::INT)
				tmp.insert(firstOfNoTerminal, GEN1(T3_0_I, lex.idtable.table[lex.lextable.table[mfst.deducation.lp[i]+1].idxTI].id));
				else
				tmp.insert(firstOfNoTerminal, GEN1(T3_0_S, lex.idtable.table[lex.lextable.table[mfst.deducation.lp[i] + 1].idxTI].id));
				break;

			case 1:
				if (lex.idtable.table[lex.lextable.table[mfst.deducation.lp[i] + 1].idxTI].iddatatype == IT::INT)
					tmp.insert(firstOfNoTerminal, GEN1(T3_1_I, lex.idtable.table[lex.lextable.table[mfst.deducation.lp[i] + 1].idxTI].id));
				else
					tmp.insert(firstOfNoTerminal, GEN1(T3_1_S, lex.idtable.table[lex.lextable.table[mfst.deducation.lp[i] + 1].idxTI].id));
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

			std::cout << "\n" << tmp<<"\n-----------------------------\n";
	}
//------------------------------------	
	return tmp;
}

std::string Gen::CreateExpression(LEX::Lex lex, MFST::Mfst mfst, unsigned short* IdIndex)
{
	std::string tmp;
	int i;
	LT::Entry* Expression = new LT::Entry[100];

	PN::PolishNotation(Expression,mfst.deducation.lp[*IdIndex] + 2, lex.lextable, lex.idtable);
	for (i = 0; Expression[i].sn > 0;i++)
	{	
		switch (Expression[i].lexema)
		{
		case LEX_LITERAL:
		case LEX_ID:
			switch (lex.idtable.table[Expression[i].idxTI].idtype)
			{
			case IT::P:
			case IT::V:
				if (lex.idtable.table[Expression[i].idxTI].iddatatype == IT::INT)
					tmp += GEN1(ID_LIT_I, lex.idtable.table[Expression[i].idxTI].id);
				else
					tmp += GEN1(ID_LIT_S_I, lex.idtable.table[Expression[i].idxTI].id);
				break;
			case IT::L:
				if (lex.idtable.table[Expression[i].idxTI].iddatatype == IT::INT)
					tmp += GEN1(ID_LIT_I, lex.idtable.table[Expression[i].idxTI].id);
				else
					tmp += GEN1(ID_LIT_S_L, lex.idtable.table[Expression[i].idxTI].id);
				break;
			case IT::F:

				tmp += GEN1(CALL, lex.idtable.table[Expression[i].idxTI].id);
				break;
			}
			break;
		case LEX_ARIPH:
			switch (lex.idtable.table[Expression[i].idxTI].id[0])
			{
			case '+':
				tmp += EXPR_INT_PLUS;
				break;
			case '*':
				tmp += EXPR_INT_IMUL;
				break;
			case '-':
				tmp += EXPR_SUB_IMUL;
				break;
			case '/':
				tmp += EXPR_DIV_IMUL;
				break;
			}
			break;
		}
	}
	int line = lex.lextable.table[mfst.deducation.lp[*IdIndex]].sn;
	while (line == lex.lextable.table[mfst.deducation.lp[*IdIndex]].sn)
		(*IdIndex)++;
	(*IdIndex)--;

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
				tmp += DW;
				tmp += VAL_STR_DEFAULT;
				break;
			}
			tmp += LINE_BREAK;
		}
	}
	return tmp;
}
std::string Gen::CreateConstSeg(std::string& tmp, LEX::Lex lex)
{
	tmp += DBLINE_BREAK;
	tmp += CONST;
	tmp += LINE_BREAK;
	tmp += "csname db 'BNI-2016', 0\n\
Overflow db 'ERROR overflow', 0\n\
DIV_NULL db 'ERROR DBN', 0\n\
newline db ' ',0\n";
for (int i = 0; i < lex.idtable.size; i++)
 {
	 if (lex.idtable.table[i].idtype == IT::L)
	 {
	tmp += lex.idtable.table[i].id;
	switch (lex.idtable.table[i].iddatatype)
		 {
		case IT::INT:
			tmp += SDW;
			tmp += SPACE;
			tmp += to_string(lex.idtable.table[i].value.vind);
			break;

		case IT::STR:
			tmp += BYTE;
			tmp += SPACE;
			tmp += lex.idtable.table[i].value.vstr.str;
			tmp += ", 0";
			break;
					}
	tmp += LINE_BREAK;
	}

}
return tmp;
}