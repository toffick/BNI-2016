#include "stdafx.h"
#include "GEN.h"

#define TITLE ".586\n .model flat, stdcall\n includelib kernel32.lib"

void Gen::StartGen(LEX::Lex lex, MFST::Mfst mfst, Log::LOG log, Parm::PARM parm)
{
	std::string gencode;
	gencode += TITLE;
	//для начала создадим области переменных и констант + шапку(с прототипами функций) 

}
