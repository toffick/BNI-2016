﻿#pragma once
#include "stdafx.h"
#include "LT.h"

namespace LT {
	LexTable Create(int size){
		LexTable *p = new LexTable;					//создание экзмепляра тадилцы лексем
		p->maxize = size;							//задание максимлаьнго размера
		p->size = 0;								//начальный размер равен нулю
		p->table = new Entry[size];					//создание масссива строк таблицы лексем
		memset(p->table, 255, 255);					//заполнение экземпляров таблицы строк на 255
		return *p;								
	}

	Entry Add(LexTable& lextable, Entry entry) {
		return(lextable.table[lextable.size++] = entry);			//оабвление на позицию текущего размера таблицы лексем элемента таблицы тсрок лексем
	}

	Entry GetEtry(LexTable& lextable, int n) {
		return (lextable.table[n]);
	}
	 
	void Delete(LexTable& lextable) {
		delete [] lextable.table;
	}
}

