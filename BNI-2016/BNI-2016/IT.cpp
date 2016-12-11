#pragma once
#include "stdafx.h"
#include "IT.h"

namespace IT {
	IdTable Create(int size) {
		IdTable* p = new IdTable;
		p->maxsize = size;
		p->size = 0;
		p->table = new Entry[size];
	//	for (int i = 0; i < size; i++)
	//		memset(p->table[i].value.vstr.str, '\0', TI_STR_MAXSIZE);
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
	int IsLiteral(IdTable& idtable, char* value, IT::Entry& ItE)
	{
		bool rc = false;
		int i;

		for (i = 0; i < idtable.size; i++)
		{
			if(idtable.table[i].idtype==IT::L){
				switch (ItE.iddatatype)
				{
				case IT::STR:
				{
					if (!strcmp(idtable.table[i].value.vstr.str, value))
					{
						return i;
					}
					break;

				}
				case IT::INT:
				{
					if (idtable.table[i].value.vind == /*(strchr(value, '\'') ? -1 :*/ atoi(value))
					{
						return i;
					}
					break;

				}
				
				}
			}
		}; 

		return  TI_NULLIDX;
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
	Entry getEntry(IdTable & idtable, int value)
	{
		return idtable.table[value];
	}
	short getIdxTI(char l, IT::IdTable& it)
	{
		return (l == LEX_LITERAL || l == LEX_ID || l == LEX_ARIPH) ? it.size : TI_NULLIDX;
	};
}

