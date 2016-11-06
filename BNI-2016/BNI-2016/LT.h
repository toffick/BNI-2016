#pragma once
#define LEXEMA_FIXZISE 1        //������������� ������ �������
#define LT_MAXSIZE 4096			//������������ ���-�� ����� � ������� ������
#define LT_TI_NULLIDX 0xffffffff //��� �������� ������� ���������������
#define LEX_INT			't'				//	integer
#define LEX_STR			't'				//	string
#define LEX_BOOL		't'				//  bool 
#define LEX_ID			'i'				//	�������������
#define LEX_LITERAL		'l'				//	�������
#define LEX_FUNC		'f'				//	�������
#define LEX_VAR			'v'				//	declare
#define LEX_RETURN		'r'				//	return
#define LEX_DISPLAY		'd'				//	display
#define LEX_MAIN		'm'				//	main
#define LEX_ARIPH	    'a'				//  ����(����� + ������) 
#define LEX_COND		'c'				//  �������� �������� (< > ==)
#define LEX_IF			'u'				//  if
#define LEX_THEN		'h'				//	then
#define LEX_LOOP		'w'				//  ����
#define LEX_SEMICOLON	';'				//	;
#define LEX_COMMA		','				//	,
#define LEX_LEFTBRACE	'{'				//	{
#define LEX_RIGHTBRACE	'}'				//	}
#define LEX_LEFTHESIS	'('				//	(
#define LEX_RIGHTHESIS	')'				//	)
#define LEX_CMP			'~'				//  ==
#define LEX_ASSIG		'='				//  =
#define LEX_LESS		'<'				//	<
#define LEX_LARGER		'>'				//	>



namespace LT {								//������� ������
	struct Entry
	{
		char lexema;		//�������
		int sn;								//����� ������ � �������� ����
		int idxTI;							//������ � ������� ��������������� 
	};
	struct LexTable 
	{
		int maxize;							//������� ������� ������ 
		int size;							//������� ������ ������� ������
		Entry* table;						//������ ����� ������� ������	
	};
	LexTable Create(						//������� ������
		int size							//�������
		);
	//Entry GetEntry(LexTable& lextable,int n);
	Entry Add(								//�������� ������ ������� ������
		LexTable& lextable,					//��������� �������
		Entry entry							//������ ������ ������
		);
	void Delete(LexTable& lextable);	//������� ������� ������
}