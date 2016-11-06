#pragma once

#define ID_MAXSIZE		10			//������������ ���-�� �������� � ��������������
#define TI_INT_DEFAULT	0x00000000	//�������� �� ��������� ��� ���� integer
#define TI_STRDEFAULT	0x00		//�������� �� ��������� ��� ���� string
#define TI_NULLIDX		0xffffffff	//��� �������� ������� ���������������
#define TI_STR_MAXSIZE	225	
#define IT_MAXSIZE		4096
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
		V = 1,				//����������
		F = 2,				//�������
		P = 3, 				//��������
		L = 4,				//�������
		O = 5,				//��������
		C = 6				//����
	};   
	struct Entry
	{
		int			idxfirstLE;			//������ ������ ������ � ������� ������
		char		id[ID_MAXSIZE];		//�������������	(�������������� ��������� �� ID_MAXSIZE)
		DATATYPE	iddatatype;			//��� ������
		TYPE		idtype;				//��� ��������������
		struct
		{
			bool vbool;
			int vind;				//�������� integer
			struct {
				int len;						//����� string
				char str[TI_STR_MAXSIZE];		//������� string
			} vstr;								//�������� string
		}value;				//�������� ��������������
	};

	struct IdTable				//��������� ������� ���������������
	{
		int maxsize;							//������� ������� ��������������� < TI_MAXSIZE
		int size;								//������� ������ ������� ��������������� < maxsize
		Entry* table;							//������ ����� ������� ���������������
	};
	IdTable Create(								//������� ������� ���������������
		int size								//������� ������� ���������������
		);
	void Add(									//�������� ������ � ������� ���������������
		IdTable& idtable,					//��������� ������� ���������������
		Entry entry							//������ ������� ���������������
		);
	Entry GetEntry(							//�������� ������ ������� ���������������
		IdTable& idtable,				//��������� ������� ���������������
		int n							//����� ���������� ������
		);
	int IsId(							//�������: ����� ������(���� ����), TI_NULLIDX(���� ���)
		IdTable& idtable,				//��������� ������� ���������������
		char id[ID_MAXSIZE]				//�������������
		);
	void Delete(IdTable& idtable);
	int checkId(IdTable& idtable, char value[ID_MAXSIZE]);
	int IsDublId(IdTable& idtable, char id[ID_MAXSIZE]); //�������� �� ����������� ��
	void Add(IdTable& idtable, Entry entry);
	int checkId(IdTable& idtable, int value);//������� ������� ������
	int IsLiteral(IdTable&, char*);						//���������, ���� �� ����� ������� � ��
	void RestartId(IT::Entry& e);						//������������ �������� ����� ���������������;
};
