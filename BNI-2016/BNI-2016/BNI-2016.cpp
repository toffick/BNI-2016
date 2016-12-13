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
#include "SemAn.h"


int _tmain(int argc, _TCHAR* argv[])
{
	time_t ttt = clock();

	setlocale(LC_ALL, "rus");
	Error::Errors errors;
	Log::LOG log;
	try 
	{
		Parm::PARM parm = Parm::getparm(argc, argv,errors);
		log = Log::getlog(parm, errors);
		Log::WriteLog(log);

		Log::WriteParm(log, parm);

		In::IN in = In::getin(parm.in,errors);

		LEX::Lex lex = LEX::StartLA(in, errors);
		Log::WriteLAtables(lex.lextable, lex.idtable, parm, log);
		MFST::Mfst mfst(lex, GRB::getGreibach());
		mfst.start(parm,log,errors);
		SA::MainSemanticAnalize(lex, log, errors);
		mfst.savededucation();
		mfst.printrules(log);
		printerr(errors);

		Gen::StartGen(lex,mfst,log,parm);


	}
	catch (Error::ERROR e)
	{
		std::cout << e.id << ": " << e.message << std::endl <<" Подробнее в журнале протокола log\n"<< std::endl;
		printerr(errors);
	}

	Log::WriteError(log, errors);		//вывести в протокол информациб об ошибке
	Log::close(log);
	time_t mmm = clock();
	std::cout << (mmm - ttt)/CLOCKS_PER_SEC;
	return 0;
}

