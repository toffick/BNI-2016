
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

	struct RELATION {					//ребро: символ - > графа переходов КА
		char symbol;					//символ перехода
		short nnode;					//нмоер смежной вершины
		RELATION(char c = 0x00,
			short ns = NULL);
	};
	struct NODE						//вершина графа перезродов 
	{
		short n_relation;				//количество идентичных ребер
		RELATION* relations;			//инцидентые ребра
		NODE();
		NODE(short n,					//кол-во инцидентных ребер
			RELATION rel,				//список ребер
			...);	//
	};
	struct FST						//недетерминированный конечный автомат
	{
		char lexema;
		FST_INDEX ind;					//доп значение автомата
		int line;
		int pos;
		char* string;				//цепочка (строка завершается 0х00)
		short position;				//текущая позиция в цепочке
		short nstates;				//количество состояний автомата
		NODE* nodes;				//граф переходов: [0] - начальное состояние, [nstate-1] - конечное 
		short* rstates;				//возможные состояния автомата на данный позиции
		FST(
			char* s,
			char lex,//цепочка(строка завершается 0х00)
			short ns,				//кол-во состояний автомата
			NODE n, ...);			//список состояний(графа переходов)
		FST(
			char* s,
			char lex,//цепочка(строка завершается 0х00)
			FST_INDEX ind,				//доп значение автомата(для сепараторов/типа)
			short ns,				//кол-во состояний автомата
			NODE n, ...);
		FST();

		//FST(FST&);//copy constructor
		//FST& operator=(const FST&);
	};			//недетерменированный конечный автомат
	bool execute(					//выполнить распознавание цепочки
		FST& fst);					//недетерминированный КА
	bool step(FST&, short*&);
	FST* crfsts();					//создать массив конечных автоматов
	NODE alllit();					//функция для узла КА со стринговым литералом
};
