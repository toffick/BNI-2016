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
	void StartGen(LEX::Lex lex, MFST::Mfst mfst,Log::LOG log, Parm::PARM parm);
	std::string CreateProtSeg(LEX::Lex lex);
	std::string CreateDatSeg(std::string&, LEX::Lex lex);
	std::string CreateConstSeg(std::string&, LEX::Lex lex);
	std::string MainGen(std::string&, LEX::Lex lex, MFST::Mfst mfst);
}