

#include "stdafx.h"
#include "FST.h"
#include <string.h>
#include <iostream>
#include "LT.h"

namespace FST {
	RELATION::RELATION(char c, short ns) {
		symbol = c;					//символ перехода
		nnode = ns;					//номер узла перехода
	}
	NODE::NODE() {
		n_relation = 0;
		RELATION *relations = NULL;
	}
	NODE::NODE(short n, RELATION rel, ...) {
		n_relation = n;						//кол-во ребер
		RELATION* buf = &rel;				//первый из разного кол-во параметров
		relations = new RELATION[n];		//массив ребер
		for (int i = 0; i < n_relation; i++) {		//заполнение массива ребер
			relations[i] = buf[i];
		}
	}
	FST::FST() {};
	FST::FST(char* s, char lex, short ns, NODE n, ...) {
		lexema = lex;
		line = 0;
		pos = 0;
		ind = FST_NOIND;
		string = s;							//входная цепочка
		nstates = ns;						//общее кол-во состояний ка
		position = -1;
		NODE* buf = &n;
		nodes = new NODE[ns];
		for (int i = 0; i < ns; i++) {		//заполнение графа узлами	
			nodes[i] = buf[i];
		}
		rstates = new short[ns];			//массив возможных состочяний ка на позиции
		rstates[0] = 0;
	}

	FST::FST(char* s, char lex, FST_INDEX val, short ns, NODE n, ...) {
		lexema = lex;
		line = 0;
		pos = 0;
		ind = val;
		string = s;							//входная цепочка
		nstates = ns;						//общее кол-во состояний ка
		position = -1;
		NODE* buf = &n;
		nodes = new NODE[ns];
		for (int i = 0; i < ns; i++) {		//заполнение графа узлами	
			nodes[i] = buf[i];
		}
		rstates = new short[ns];			//массив возможных состочяний ка на позиции
		rstates[0] = 0;
	}

	bool execute(FST& fst)
	{
		short* rstates = new short[fst.nstates];		//массив размером кол-ва состояний
		memset(rstates, 0xff, sizeof(short)*fst.nstates);
		size_t lstring = strlen(fst.string);				//длина входной цепочки
		bool rc = true;
		for (size_t i = 0; i < lstring && rc; i++)
		{
			fst.pos++;
			fst.position++;
			if (fst.string[fst.position] == IN_CODE_SEP) {
				fst.line++;
				fst.pos = 0;
			}
			rc = step(fst, rstates);
		}

		delete[] rstates;
		return (rc ? (fst.rstates[fst.nstates - 1] == lstring) : rc);	//true, если последний элемент массива равен
	}																   //кол-ву значимых символов входной цепочки

	bool step(FST& fst, short* &rstetes) {		//ка, массив возможных состочяний ка на позиции
		bool rc = false;
		std::swap(rstetes, fst.rstates);		//замена массива местами
		for (short i = 0; i < fst.nstates; i++)// проверка всех узлов(вершин)
		{
			if (rstetes[i] == fst.position)		//если у нас возможно взождение в узел по текущей позиции
			{
				for (short j = 0; j < fst.nodes[i].n_relation; j++)		//проверка всех ребер этого узла
				{
					if (fst.nodes[i].relations[j].symbol == fst.string[fst.position])		//если символ равен символу перехода
					{
						fst.rstates[fst.nodes[i].relations[j].nnode] = fst.position + 1; //заполнение массива узло на позиции i для след итерации
						rc = true;
					}
				}
			}
		}
		return rc;
	}

	NODE alllit() {
		NODE p;
		p.relations = new RELATION[316];
		p.n_relation = 316;
		int k = 0;
		for (int i = 0x20; i < 0x7F; i++)
		{
			if (i == 0x27) continue;

			p.relations[k].symbol = (char)i;
			p.relations[k].nnode = 2;
			k++;
			p.relations[k].symbol = (char)i;
			p.relations[k].nnode = 1;
			k++;
		};
		for (int i = 0xC0; i <= 0xFF; i++)
		{

			p.relations[k].symbol = (char)i;
			p.relations[k].nnode = 2;
			k++;
			p.relations[k].symbol = (char)i;
			p.relations[k].nnode = 1;
			k++;
		};
		p.n_relation = k;
		return p;

	}
	FST* crfsts()
	{
		FST fst_strlit("", LEX_LITERAL, FST_STR, 4,
			NODE(1, RELATION((char)0x27, 1)),
			alllit(),
			NODE(1, RELATION((char)0x27, 3)),
			NODE()
			);

		FST fst_intlit("", LEX_LITERAL, FST_INT, 2,
			NODE(20,
				RELATION('0', 1), RELATION('0', 0),
				RELATION('1', 1), RELATION('1', 0),
				RELATION('2', 1), RELATION('2', 0),
				RELATION('3', 1), RELATION('3', 0),
				RELATION('4', 1), RELATION('4', 0),
				RELATION('5', 1), RELATION('5', 0),
				RELATION('6', 1), RELATION('6', 0),
				RELATION('7', 1), RELATION('7', 0),
				RELATION('8', 1), RELATION('8', 0),
				RELATION('9', 1), RELATION('9', 0)),
			NODE()
			);
		FST fst_true("", LEX_LITERAL, FST_BLIT, 5,
			NODE(1, RELATION('t', 1)),
			NODE(1, RELATION('r', 2)),
			NODE(1, RELATION('u', 3)),
			NODE(1, RELATION('e', 4)),
			NODE()
			);
		FST fst_false("", LEX_LITERAL, FST_BLIT, 6,
			NODE(1, RELATION('f', 1)),
			NODE(1, RELATION('a', 2)),
			NODE(1, RELATION('l', 3)),
			NODE(1, RELATION('s', 4)),
			NODE(1, RELATION('e', 5)),
			NODE()
			);



		FST fst_int("", LEX_INT, FST_INT, 4,
			NODE(1, RELATION('i', 1)),
			NODE(1, RELATION('n', 2)),
			NODE(1, RELATION('t', 3)),
			
			NODE()
			);					//ка для интовых литералов




		FST fst_str("", LEX_STR, FST_STR, 4,
			NODE(1, RELATION('s', 1)),
			NODE(1, RELATION('t', 2)),
			NODE(1, RELATION('r', 3)),
			
			NODE()
			);


		FST fst_bool("", LEX_BOOL, FST_BOOL, 5,
			NODE(1, RELATION('b', 1)),
			NODE(1, RELATION('o', 2)),
			NODE(1, RELATION('o', 3)),
			NODE(1, RELATION('l', 4)),
			NODE()
			);



		FST fst_var("", LEX_VAR,FST_VAR, 8,
			NODE(1, RELATION('d', 1)),
			NODE(1, RELATION('e', 2)),
			NODE(1, RELATION('c', 3)),
			NODE(1, RELATION('l', 4)),
			NODE(1, RELATION('a', 5)),
			NODE(1, RELATION('r', 6)),
			NODE(1, RELATION('e', 7)),
			NODE()
			);

		FST fst_ret("", LEX_RETURN, FST_RETURN, 7,
			NODE(1, RELATION('r', 1)),
			NODE(1, RELATION('e', 2)),
			NODE(1, RELATION('t', 3)),
			NODE(1, RELATION('u', 4)),
			NODE(1, RELATION('r', 5)),
			NODE(1, RELATION('n', 6)),
			NODE()
			);

		FST fst_func("", LEX_FUNC, FST_FUNC, 5,
			NODE(1, RELATION('f', 1)),
			NODE(1, RELATION('u', 2)),
			NODE(1, RELATION('n', 3)),
			NODE(1, RELATION('c', 4)),
			NODE()
			);

		FST fst_main("", LEX_MAIN,FST_MAIN, 5,
			NODE(1, RELATION('m', 1)),
			NODE(1, RELATION('a', 2)),
			NODE(1, RELATION('i', 3)),
			NODE(1, RELATION('n', 4)),
			NODE()
			);

		FST fst_display("", LEX_DISPLAY, FST_DISPLAY,6,
			NODE(1, RELATION('p', 1)),
			NODE(1, RELATION('r', 2)),
			NODE(1, RELATION('i', 3)),
			NODE(1, RELATION('n', 4)),
			NODE(1, RELATION('t', 5)),
			NODE()
			);

		FST fst_semicolon("", LEX_SEMICOLON,FST_SEMICOLON, 2,
			NODE(1, RELATION(';', 1)),
			NODE());

		FST fst_comma("", LEX_COMMA,FST_COMMA, 2,
			NODE(1, RELATION(',', 1)),
			NODE());

		FST fst_leftbrace("", LEX_LEFTBRACE,FST_LEFTBRACE, 2,
			NODE(1, RELATION('{', 1)),
			NODE());

		FST fst_rightbrace("", LEX_RIGHTBRACE, FST_RIGHTBRACE, 2,
			NODE(1, RELATION('}', 1)),
			NODE());

		FST fst_lefthesis("", LEX_LEFTHESIS,FST_LEFTHESIS, 2,
			NODE(1, RELATION('(', 1)),
			NODE());

		FST fst_righthesis("", LEX_RIGHTHESIS, FST_RIGHTHESIS, 2,
			NODE(1, RELATION(')', 1)),
			NODE());

		FST fst_cmp("", LEX_CMP, FST_CMP, 2,
			NODE(1, RELATION('~', 1)),
			NODE());

		FST fst_assig("", LEX_ASSIG, FST_ASSIG, 2,
			NODE(1, RELATION('=', 1)),
			NODE());
		
		FST fst_less("", LEX_LESS, FST_LESS, 2,
			NODE(1, RELATION('<', 1)),
			NODE());

		FST fst_larger("", LEX_LARGER, FST_LARGER, 2,
			NODE(1, RELATION('>', 1)),
			NODE());
		FST fst_ariph("", LEX_ARIPH, FST_ARIPH, 2,
			NODE(6,
				RELATION('+', 1),
				RELATION('-', 1),
				RELATION('*', 1),
				RELATION('/', 1),
				RELATION('&', 1),
				RELATION('|', 1)),
			NODE());

		FST fst_id("", LEX_ID, FST_ID, 2,
			NODE(52,
				RELATION('a', 0), RELATION('a', 1),
				RELATION('b', 0), RELATION('b', 1),
				RELATION('c', 0), RELATION('c', 1),
				RELATION('d', 0), RELATION('d', 1),
				RELATION('e', 0), RELATION('e', 1),
				RELATION('f', 0), RELATION('f', 1),
				RELATION('g', 0), RELATION('g', 1),
				RELATION('h', 0), RELATION('h', 1),
				RELATION('i', 0), RELATION('i', 1),
				RELATION('j', 0), RELATION('j', 1),
				RELATION('k', 0), RELATION('k', 1),
				RELATION('l', 0), RELATION('l', 1),
				RELATION('m', 0), RELATION('m', 1),
				RELATION('n', 0), RELATION('n', 1),
				RELATION('o', 0), RELATION('o', 1),
				RELATION('p', 0), RELATION('p', 1),
				RELATION('q', 0), RELATION('q', 1),
				RELATION('r', 0), RELATION('r', 1),
				RELATION('s', 0), RELATION('s', 1),
				RELATION('t', 0), RELATION('t', 1),
				RELATION('u', 0), RELATION('u', 1),
				RELATION('v', 0), RELATION('v', 1),
				RELATION('w', 0), RELATION('w', 1),
				RELATION('x', 0), RELATION('x', 1),
				RELATION('y', 0), RELATION('y', 1),
				RELATION('z', 0), RELATION('z', 1)),
			NODE()
			);

		FST* mas = new FST[FST_ARR_SIZE];


		return mas;
	}
}
