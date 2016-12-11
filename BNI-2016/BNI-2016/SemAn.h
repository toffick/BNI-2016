#pragma once
#include "LexAnalize.h"
#include "Log.h"
#include "Error.h"
#include "LT.h"
#include "IT.h"
namespace SA
{
	void MainSemanticAnalize(LEX::Lex, Log::LOG, Error::Errors&);
	bool IsMain(LEX::Lex, Error::Errors&);
	bool ExpressionOperandsType(LEX::Lex, Error::Errors&);
	bool ValidReturnValue(LEX::Lex, Error::Errors&);
	bool ValidParmValue(LEX::Lex, Error::Errors&);
	bool ValidParmSTDValue(LEX::Lex, Error::Errors&);

}