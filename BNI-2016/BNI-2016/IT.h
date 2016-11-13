#pragma once

#define ID_MAXSIZE		10			//максимальное кол-во символов в идентификаторе
#define TI_INT_DEFAULT	0x00000000	//значение по умолчанию для типа integer
#define TI_STRDEFAULT	"\0"		//значение по умолчанию для типа string
#define TI_NULLIDX		0xffffffff	//нет элемента таблицы идентификаторов
#define TI_STR_MAXSIZE	225	
#define IT_MAXSIZE		4096
#define TI_PREFIX_MAX_SIZE	5
#define TI_BOOL_DEFAULT false
#include "LT.h"
namespace IT
{
	enum DATATYPE 
	{	OFF = 0, 
		INT = 1,
		STR = 2,
		BOOL = 3
	};
	enum TYPE
	{
		N = 0,				//null
		V = 1,				//переменная
		F = 2,				//функция
		P = 3, 				//параметр
		L = 4,				//литерал
		O = 5,				//оператор
	};   
	struct Entry
	{
		int			idxfirstLE;			//индекс первой строки в таблице лексем
		char		id[ID_MAXSIZE];		//идентификатор	(автоматические усекается до ID_MAXSIZE)
		DATATYPE	iddatatype;			//тип данных
		TYPE		idtype;				//тип идентификатора
		struct
		{
			int vbool;
			int vind;				//значение integer
			struct {
				int len;						//длина string
				char str[TI_STR_MAXSIZE];		//символы string
			} vstr;								//значение string
		}value;				//значение идентификатора
	};

	struct IdTable				//экземпляр таблицы идентификаторов
	{
		int maxsize;							//емкость таблицы идентификаторов < TI_MAXSIZE
		int size;								//текущий размер таблицы идентификаторов < maxsize
		Entry* table;							//массив строк таблицы идентификаторов
	};
	IdTable Create(								//создать таблицу идентификаторов
		int size								//емкость таблицы идентификаторов
		);
	void Add(									//добавить строку в таблицу идентификаторов
		IdTable& idtable,					//экземпляр таблицы идентификаторов
		Entry entry							//строка таблицы идентификаторов
		);
	Entry GetEntry(							//получить строку таблицы идентификаторов
		IdTable& idtable,				//экземпляр таблицы идентификаторов
		int n							//номер получаемой строки
		);
	int IsId(							//возврат: номер строки(если есть), TI_NULLIDX(если нет)
		IdTable& idtable,				//экземпляр таблицы идентификаторов
		char id[ID_MAXSIZE]				//идентафикатор
		);
	void Delete(IdTable& idtable);
	int checkId(IdTable& idtable, char value[ID_MAXSIZE]);
	int IsDublId(IdTable& idtable, char id[ID_MAXSIZE]);		//проверка на дублирвание ид
	void Add(IdTable& idtable, Entry entry);
	int checkId(IdTable& idtable, int value);					//удалить таблицу лексем
	int IsLiteral(IdTable&, char*, IT::Entry& ItE);								//проверяет, есть ли такой литерал в ТИ
	void RestartId(IT::Entry& e);								//перезагрузка элемента таилц идентификаторов;
	short   getIdxTI(char l, IT::IdTable& it);					// получить индекс ТИ

};
