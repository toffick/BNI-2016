#pragma once
#include "LexAnalize.h"
#include "Mfst.h"
#include "Log.h"
#include "Parm.h"
#include <string>

namespace Gen
{
	void StartGen(LEX::Lex lex, MFST::Mfst mfst,Log::LOG log, Parm::PARM parm);
	std::string CreateConstSeg(LEX::Lex lex );
	std::string CreateProtSeg(LEX::Lex lex);
	std::string CreateDatSeg(LEX::Lex lex);

	std::string MainGen(LEX::Lex lex, MFST::Mfst mfst);
}