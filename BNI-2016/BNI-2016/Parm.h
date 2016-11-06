#pragma once
#define PARM_IN L"-in:"						//ключ для файла исходного кода
#define PARM_OUT L"-out:"					//ключ для файла объектного кода	
#define PARM_LOG L"-log:"					//ключ для файла журнала
#define PARM_LT L"-lt"						//ключ для вывода таблицы лексем
#define PARM_IT L"-it"						//ключ для вывод таблицы идентификатора
#define PARM_ST L"-st"						//ключ для дерева разбора
#define PARM_TR L"-tr"						//ключ для вывода трассировки на консоль
#define PARM_MAX_SIZE 300					//максимальная длина строки параметра
#define PARM_OUT_DEFAULT_EXT L".out"		//расширение файла объектного кода по умолчанию
#define PARM_LOG_DEFAULT_EXT L".log"		//расширение файла протокола по умолчанию
#include "Error.h"


namespace Parm
{
	struct PARM 
	{
		
		bool lt;							//таблица лексем
		bool it;							//таблица идентификаторов
		wchar_t in[PARM_MAX_SIZE];			//-in:    имя файла исходного кода
		wchar_t out[PARM_MAX_SIZE];			//-out:    имя файла объектного кода
		wchar_t log[PARM_MAX_SIZE];			//-log:    имя файла протокола
		bool tr;							//трассировка
		bool st;							//дерево разбора
	};
												//int _tmain(int argc, _TCHAR* argv[])
	PARM getparm(int argc, _TCHAR* argv[], Error::Errors&);		//сформировать struct PARM на основе параметров функции main
}