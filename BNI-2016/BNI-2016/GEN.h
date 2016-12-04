#pragma once
#include "LexAnalize.h"
#include "Mfst.h"
#include "Log.h"
#include "Parm.h"
#include <string>
#include "format.h"
#include "PolishNotation.h"
namespace Gen
{
	void StartGen(LEX::Lex , MFST::Mfst ,Log::LOG , Parm::PARM );
	std::string CreateProtSeg(LEX::Lex );
	std::string CreateDatSeg(std::string&, LEX::Lex );
	std::string CreateConstSeg(std::string&, LEX::Lex );
	std::string MainGen(std::string&, LEX::Lex , MFST::Mfst );
std::string CreateExpression(LEX::Lex, MFST::Mfst, unsigned short*);

}