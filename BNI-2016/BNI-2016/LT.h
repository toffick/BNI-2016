#pragma once
#define LEXEMA_FIXZISE 1        //фиксированный размер лексемы
#define LT_MAXSIZE 4096			//максимальное кол-во строк в таблице лексем
#define LT_TI_NULLIDX 0xffffffff //нет элемента таблицы идентификаторов
#define LEX_INT			't'				//	integer
#define LEX_STR			't'				//	string
#define LEX_BOOL		't'				//  bool 
#define LEX_ID			'i'				//	идентификатор
#define LEX_LITERAL		'l'				//	литерал
#define LEX_FUNC		'f'				//	функци€
#define LEX_VAR			'v'				//	declare
#define LEX_RETURN		'r'				//	return
#define LEX_DISPLAY		'd'				//	display
#define LEX_MAIN		'm'				//	main
#define LEX_ARIPH	    'a'				//  знак(арифм + булевы) 
#define LEX_COND		'c'				//  условный оператор (< > ==)
#define LEX_IF			'u'				//  if
#define LEX_THEN		'h'				//	then
#define LEX_LOOP		'w'				//  цикл
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



namespace LT {								//таблица лексем
	struct Entry
	{
		char lexema;		//лексема
		int sn;								//номер строки в исходном коде
		int idxTI;							//индекс в таблице идентификаторов 
	};
	struct LexTable 
	{
		int maxize;							//емкость таблицы лексем 
		int size;							//текущий размер таблицы лексем
		Entry* table;						//массив строк табилцы лексем	
	};
	LexTable Create(						//таблица лексем
		int size							//емкость
		);
	//Entry GetEntry(LexTable& lextable,int n);
	Entry Add(								//получить строку таблицы лексем
		LexTable& lextable,					//экземпл€р таблицы
		Entry entry							//строка таблцы лексем
		);
	void Delete(LexTable& lextable);	//удалить таблицу лексем
}