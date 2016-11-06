#pragma once
#include "stdafx.h"
#include "IT.h"

namespace IT {
	IdTable Create(int size) {
		IdTable* p = new IdTable;
		p->maxsize = size;
		p->size = 0;
		p->table = new Entry[size];
		for (int i = 0; i < size; i++)
			memset(p->table[i].value.vstr.str, '\0', size);
		return (*p);
	
	
	}

	void Add(IdTable& idtable, Entry entry) {
		idtable.table[idtable.size++] = entry;	
	}

	Entry GetEntry(IdTable& idtable, int n) {
		return (idtable.table[n]);
	
	}
	void IT::RestartId(IT::Entry& e)											//преехагрузка элемента таблиц идентификаторов
	{
		e.id[0] = 0x00;
		e.iddatatype = IT::DATATYPE::OFF;
		e.idtype = IT::TYPE::N;
		e.idxfirstLE = 0;
		e.value.vind = 0;
		e.value.vstr.len = 0;
		e.value.vstr.str[0] = 0;
	};
	int IsId(IdTable& idtable, char id[ID_MAXSIZE]) {
		for (int i = 0; i < idtable.size; i++) {
			if (strcmp(idtable.table[i].id,id)==0)
				return i;		
		}
		return TI_NULLIDX;
	}
	int IT::IsLiteral(IdTable& idtable, char* value)
	{
		bool rc = false;
		int i;

		for (i = 0; i < idtable.size; i++)
		{
			if (idtable.table[i].idtype == IT::TYPE::L)
			{
				if (!strcmp(idtable.table[i].value.vstr.str, value) )
				{
					rc = true;
					break;
				}
				else if (idtable.table[i].value.vind == /*(strchr(value, '\'') ? -1 :*/ atoi(value))
				{
					rc = true;
					break;
				}
			}
		};

		return rc ? i : TI_NULLIDX;
	};
	int IsDublId(IdTable& idtable, char id[ID_MAXSIZE]) {
		for (int i = 0; i < idtable.size-1; i++) {
			if (strcmp(idtable.table[i].id, id) == 0)
				return i;
		}
		return TI_NULLIDX;
	}
	int checkId(IdTable& idtable, char value[ID_MAXSIZE]) {
		bool rc = false;
		int i;
		for (i = 0; i<idtable.size; i++) {
			if (strcmp(idtable.table[i].value.vstr.str, value) == 0) {
				rc = true;
				break;
			}
		}
		return rc ? i : TI_NULLIDX;
	}
	int checkId(IdTable& idtable, int value) {
		bool rc = false;
		int i;
		for (i = 0; i<idtable.size; i++) {
			if (idtable.table[i].value.vind == value) {
				rc = true;
				break;
			}
		}
		return rc ? i : TI_NULLIDX;
	}
}

