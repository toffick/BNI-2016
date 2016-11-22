// BNI-2016.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include "Parm.h"
#include "Error.h"
#include "In.h"
#include "Log.h"
#include "LexAnalize.h"
#include "Mfst.h"
#include "GEN.h"


int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "rus");
	Error::Errors errors;
	Log::LOG log;
	try 
	{
		Parm::PARM parm = Parm::getparm(argc, argv,errors);
		log = Log::getlog(parm.log, errors);
		In::IN in = In::getin(parm.in,errors);
		Log::WriteLog(log);
		
		Log::WriteParm(log,parm);
		LEX::Lex lex = LEX::StartLA(in, errors);
		Log::WriteLAtables(lex.lextable, lex.idtable, parm, log);


		MFST::Mfst mfst(lex, GRB::getGreibach());
		mfst.start(parm);
		mfst.savededucation();
		mfst.printrules();
		Gen::StartGen(lex,mfst,log,parm);


	}
	catch (Error::ERROR e)
	{
		std::cout << e.id << ": " << e.message << std::endl << std::endl;
		
		printerr(errors);
	}
	Log::WriteError(log, errors);		//вывести в протокол информациб об ошибке
	Log::close(log);

	return 0;
}

