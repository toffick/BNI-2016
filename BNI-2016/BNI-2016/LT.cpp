#include "stdafx.h"
#include "LT.h"

namespace LT {
	LexTable Create(int size){
		LexTable *p = new LexTable;					//�������� ���������� ������� ������
		p->maxize = size;							//������� ������������ �������
		p->size = 0;								//��������� ������ ����� ����
		p->table = new Entry[size];					//�������� �������� ����� ������� ������
		memset(p->table, 255, 255);					//���������� ����������� ������� ����� �� 255
		return *p;								
	}

	Entry Add(LexTable& lextable, Entry entry) {
		return(lextable.table[lextable.size++] = entry);			//��������� �� ������� �������� ������� ������� ������ �������� ������� ����� ������
	}

	Entry GetEtry(LexTable& lextable, int n) {
		return (lextable.table[n]);
	}
	 
	void Delete(LexTable& lextable) {
		delete [] lextable.table;
	}
}

