#pragma once
#include <fstream>
#include "In.h"
#include "Parm.h"
#include "Error.h"

namespace Log {
	struct LOG {
		wchar_t logfile[PARM_MAX_SIZE];
		std::ofstream* stream;
		LOG():stream(NULL)
		{
			wcscpy_s(logfile, L"");
		}
	};
//	static const LOG INITLOG = { L"", NULL };			
	LOG getlog(wchar_t logfile[], Error::Errors&);						//��������� ������������� LOG
	void WriteLine(LOG log, char* c, ...);				//������������ ��������� LOG
	void WriteLine(LOG log, wchar_t* c, ...);
	void WriteLog(LOG log);								//������� � �������� ������������ �����
	void WriteParm(LOG log, Parm::PARM parm);			//������� � �������� ���������� � ������� ������
	void WriteIn(LOG log, In::IN in);					//������� � �������� ���������� � ������� ������
	void WriteError(LOG log, Error::Errors&);		//������� � �������� ���������� �� ������
	//void WriteLexTable(LT::LexTable, LOG);
	//void WriteIdTable(IT::IdTable);
	//void WriteLAtables(LT::LexTable, IT::IdTable, Parm::PARM, LOG);
	void close(LOG log);								//������� ��������
};
