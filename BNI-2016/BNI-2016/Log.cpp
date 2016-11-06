//#define _crt_secure_no_warnings

#pragma once
#include "stdafx.h"
#include <stdlib.h>
#include "Log.h"
#include <ctime>
#include "time.h"

namespace Log {
	LOG getlog(wchar_t logfile[],Error::Errors& e) {
		LOG* p = new LOG;
			p->stream = new std::ofstream(logfile);
			if (p->stream->fail())
				Error::adderr(104,e);
			//	throw ERROR_THROW(112);
			wcscpy_s(p->logfile, logfile);
			return *p;
		}
	void WriteLine(LOG log, char* c, ...) {
			char **p = &c;
			while (strcmp(*p, "")) {
				*(log.stream) << *p;
				p++;
			}
		}
	void WriteLine(LOG log, wchar_t* c, ...) {
			wchar_t **p = &c;
			char tmp[PARM_MAX_SIZE];
			while (wcscmp(*p, L"")) {
				wcstombs(tmp, *p, PARM_MAX_SIZE);
				*(log.stream) << tmp;
				p++;
			}
		}
	void WriteLog(LOG log) {
		WriteLine(log,"---- Протокол работы BNI-2016 ----\n","");
		time_t rawtime;
		char buffer[80];                                // строка, в которой будет храниться текущее время
		time(&rawtime);                               
		tm *k = localtime(&rawtime);
		strftime(buffer, 80, " %x %X", k);
		WriteLine(log,"  Дата: ", buffer, "\n","");
	}
	void WriteParm(LOG log, Parm::PARM parm) {
		WriteLine(log,"\n---- Параметры ----","");
		WriteLine(log,"\n -in:  ","");
		WriteLine(log,parm.in, L"");
		WriteLine(log, "\n -log: ", "");
		WriteLine(log, parm.log, L"");
		WriteLine(log, "\n -out: ", "");
		WriteLine(log, parm.log, L"");
		if (parm.it)
			WriteLine(log, "\n -it вывод таблицы идентификаторов", "");
		if (parm.lt)
			WriteLine(log, "\n -lt вывод таблицы лексем", "");
		if(parm.st)
			WriteLine(log, "\n -st вывод дерева разбора", "");
		if (parm.tr)
			WriteLine(log, "\n -tr вывод трассировки", "");
	}
//	void WriteIn(LOG log, In::IN in) {
//	/*	*(log.stream) << "---- Исходные данные ------ \n\n\n\n";
//		for (int i = 0; i<in.size; i++) {
//			
//			 (*log.stream) << in.text[i];
//		}*/
//		*(log.stream) << "\n\n\nКоличество символов: " << in.size <<
//						 "\nПроигнорировано    : " << in.ignor <<
//						 "\nКоличество строк   : " << in.lines;
//	}
	void WriteError(LOG log, Error::Errors& e) {
		if (e.size != 0) 
		{
			WriteLine(log, "\n\n---- Ошибки ----", "");

			for (int i = 0; i < e.size; i++)
			{
				*(log.stream) << "\nОшибка " << e.errors[i].id << ": " << e.errors[i].message << ", строка " <<
					e.errors[i].intext.line << " позиция " << e.errors[i].intext.col << std::endl;
			}
		}
	}
//	void WriteLexTable(LT::LexTable lextable, LOG log)
//	{
//		int k = 0;
//		*(log.stream) << "\n\nТаблица лексем\n0: ";
//		for (int i = 0; i < lextable.size; i++) {
//			if (lextable.table[i].sn != k) {
//				*(log.stream) << "\n" << lextable.table[i].sn << ": ";
//
//				k = lextable.table[i].sn;
//				*(log.stream) << lextable.table[i].lexema;
//
//			}
//			else
//				*(log.stream) << lextable.table[i].lexema;
//		}
//	}
//	void WriteIdTable(IT::IdTable idT)
//	{
//		
//		{
//			for (int i = 0; i < idT.size; i++) {
//				std::cout << "\n\nИдентификатор №" << i << ": " << idT.table[i].id;
//				//std::cout << "\nНомер в таблице идентификаторов: " << lexT.table[i].idxTI;
//				std::cout << "\nПервая строка определения: " << idT.table[i].idxfirstLE;
//				if (idT.table[i].iddatatype == IT::INT)
//					std::cout << "\nТип данных: integer";
//				else if (idT.table[i].iddatatype == IT::STR)
//					std::cout << "\nТип данных: string";
//				else
//					std::cout << "\nТип данных: operator";
//				if (idT.table[i].idtype == IT::F)
//					std::cout << "\nТип ид: F";
//				else if (idT.table[i].idtype == IT::V)
//					std::cout << "\nТип ид: V";
//				else if (idT.table[i].idtype == IT::P)
//					std::cout << "\nТип ид: P";
//				else if (idT.table[i].idtype == IT::L)
//					std::cout << "\nТип ид: L";
//				else
//					std::cout << "\nТип ид: O";
//
//				if ((idT.table[i].iddatatype == IT::INT && idT.table[i].idtype == IT::V) ||
//					(idT.table[i].iddatatype == IT::INT && idT.table[i].idtype == IT::L))
//					std::cout << "\nЗначение: " << idT.table[i].value.vind;
//				else if ((idT.table[i].iddatatype == IT::STR && idT.table[i].idtype == IT::V) ||
//					(idT.table[i].iddatatype == IT::STR && idT.table[i].idtype == IT::L))
//				{
//					if (idT.table[i].value.vstr.str[0] == NULL)
//						std::cout << "\nСтрока: NULL";
//					else {
//						std::cout << "\nСтрока: " << idT.table[i].value.vstr.str;
//						std::cout << "\nДлина строки: " << idT.table[i].value.vstr.len;
//					}
//				}
//			}
//		}
//	}
//	void WriteLAtables(LT::LexTable lextable, IT::IdTable idtable, Parm::PARM parm, LOG log)
//	{
//		if (parm.it)
//			WriteIdTable(idtable);
//		if (parm.lt)
//			WriteLexTable(lextable,log);
//	}
//	void close(LOG log) {
//		(log.stream)->close();
//		delete log.stream;
//	}
//
}