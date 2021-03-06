﻿#pragma once
#include <fstream>
#include "In.h"
#include "Parm.h"
#include "Error.h"
#include "LT.h"
#include "IT.h"
#include "LexAnalize.h"


namespace Log {
	struct LOG {
		wchar_t logfile[PARM_MAX_SIZE];
		wchar_t outfile[PARM_MAX_SIZE];
		std::ofstream* stream;
		std::ofstream* stream_out;

		LOG():stream(NULL)
		{
			wcscpy_s(outfile, L"");
			wcscpy_s(logfile, L"");
			stream = NULL;
			stream_out = NULL;
		}
	};
//	static const LOG INITLOG = { L"", NULL };			
	LOG getlog(Parm::PARM parm, Error::Errors&);						//начальная инициализация LOG
	void WriteLine(LOG log, char* c, ...);				//сформировать структуру LOG
	void WriteLine(LOG log, wchar_t* c, ...);
	void WriteLog(LOG log);								//вывести в протокол конкатенацию строк
	void WriteParm(LOG log, Parm::PARM parm);			//вывести в протокол информацию о входных данных
	void WriteError(LOG log, Error::Errors&);		//вывести в протокол информациб об ошибке
	void WriteLexTable(LT::LexTable, LOG);
	void WriteIdTable(IT::IdTable, LOG);
	void WriteLAtables(LT::LexTable, IT::IdTable, Parm::PARM, LOG);

	void close(LOG log);								//закрыть протокол
};
