#pragma once
#include "LexAnalize.h"
#include "Mfst.h"
#include "Log.h"
#include "Parm.h"
#include <string>

namespace Gen
{
	void StartGen(LEX::Lex lex, MFST::Mfst mfst,Log::LOG log, Parm::PARM parm);

}