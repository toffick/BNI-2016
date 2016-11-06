// BNI-2016.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include "Parm.h"
#include "Error.h"
#include "In.h"
#include "Log.h"



int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "rus");
	Error::Errors errors;
	try 
	{
		Parm::PARM parm = Parm::getparm(argc, argv,errors);
		In::IN in = In::getin(parm.in,errors);
		Log::LOG log = Log::getlog(parm.log,errors);
		Log::WriteLog(log);
		Log::WriteParm(log,parm);
		Log::WriteError(log, errors);		//вывести в протокол информациб об ошибке

	}
	catch (Error::ERROR e)
	{
		std::cout << e.id << ": " << e.message << std::endl << std::endl;
	//	Log::WriteError(log, e);
	}
	return 0;
}

