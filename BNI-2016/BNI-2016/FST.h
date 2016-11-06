
#include "stdafx.h"
#define IN_CODE_SEP ';'
#define FST_ARR_SIZE 26

namespace FST {

	enum FST_INDEX
	{

		FST_NOIND = 0,
		FST_INT = 1,
		FST_STR = 2,
		FST_BOOL = 3,
		FST_VAR = 4,
		FST_ID = 5,
		FST_ILIT = 6,
		FST_SLIT = 7,
		FST_FUNC = 8,
		FST_DISPLAY = 9,
		FST_MAIN = 10,
		FST_RETURN = 11,
		FST_COND = 12,
		FST_THEN = 13,
		FST_IF = 14,
		FST_COMMA = 15,
		FST_LEFTBRACE = 16,
		FST_RIGHTBRACE = 17,
		FST_RIGHTHESIS = 18,
		FST_LEFTHESIS = 19,
		FST_ARIPH = 20,
		FST_SEMICOLON = 21,
		FST_ASSIG = 22,
		FST_BLIT = 23,
		FST_CMP = 24,
		FST_LESS = 25,
		FST_LARGER = 26
	};

	struct RELATION {					//�����: ������ - > ����� ��������� ��
		char symbol;					//������ ��������
		short nnode;					//����� ������� �������
		RELATION(char c = 0x00,
			short ns = NULL);
	};
	struct NODE						//������� ����� ���������� 
	{
		short n_relation;				//���������� ���������� �����
		RELATION* relations;			//���������� �����
		NODE();
		NODE(short n,					//���-�� ����������� �����
			RELATION rel,				//������ �����
			...);	//
	};
	struct FST						//������������������� �������� �������
	{
		char lexema;
		FST_INDEX ind;					//��� �������� ��������
		int line;
		int pos;
		char* string;				//������� (������ ����������� 0�00)
		short position;				//������� ������� � �������
		short nstates;				//���������� ��������� ��������
		NODE* nodes;				//���� ���������: [0] - ��������� ���������, [nstate-1] - �������� 
		short* rstates;				//��������� ��������� �������� �� ������ �������
		FST(
			char* s,
			char lex,//�������(������ ����������� 0�00)
			short ns,				//���-�� ��������� ��������
			NODE n, ...);			//������ ���������(����� ���������)
		FST(
			char* s,
			char lex,//�������(������ ����������� 0�00)
			FST_INDEX ind,				//��� �������� ��������(��� �����������/����)
			short ns,				//���-�� ��������� ��������
			NODE n, ...);
		FST();

		//FST(FST&);//copy constructor
		//FST& operator=(const FST&);
	};			//������������������� �������� �������
	bool execute(					//��������� ������������� �������
		FST& fst);					//������������������� ��
	bool step(FST&, short*&);
	FST* crfsts();					//������� ������ �������� ���������
	NODE alllit();					//������� ��� ���� �� �� ���������� ���������
};
