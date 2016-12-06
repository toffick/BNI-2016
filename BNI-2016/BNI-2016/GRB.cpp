#include "stdafx.h"
#include "GRB.h"
#include "Error.h"
#include "string.h"
#define GRB_ERROR_SERIES 600

namespace GRB {
#define NS(n) Rule::Chain::N(n)
#define TS(n) Rule::Chain::T(n)

	// ---------- ГРАММАТИКА ГРЕЙБАХ ----------


	Greibach greibach(
		NS('S'), TS('$'),                     // стартовый символ, дно стека
		6,									  // количество правил
		Rule(
			NS('S'), GRB_ERROR_SERIES + 0,    // неверная структура программы
			6,                                // S->m{NrE;}; | m{N}; | m{NrE;};S | tfi(F){NrE;};S |  tfi(F){NrE;}; | tfi(F){N};
			Rule::Chain(8, TS('m'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}'), TS(';')),
			Rule::Chain(14, TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}'), TS(';'), NS('S')),
			Rule::Chain(12, TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('{'), TS('r'), NS('E'), TS(';'), TS('}'), TS(';')),
			Rule::Chain(13, TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}'), TS(';')),
			Rule::Chain(13, TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('{'), TS('r'), NS('E'), TS(';'), TS('}'), TS(';'), NS('S')),
			Rule::Chain(9, TS('m'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}'), TS(';'), NS('S'))
			),
		Rule(
			NS('N'), GRB_ERROR_SERIES + 1,    // ошибочный оператор
			13,                               // N->dti; | rE; | i=E; | dtfi(F); | dtiN | rE;N | i=E;N | dtfi(F);N |
			Rule::Chain(7, TS('w'), TS('('), NS('E'), TS(')'), TS('{'), NS('N'), TS('}')),					//цикл
			Rule::Chain(4, TS('v'), TS('t'), TS('i'), TS(';')),												//объявление идентификатора
			Rule::Chain(3, TS('r'), NS('E'), TS(';')),														//возврат
			Rule::Chain(4, TS('i'), TS('='), NS('E'), TS(';')),												//присвоение значения
			Rule::Chain(3, TS('d'), NS('E'), TS(';')),														//вывод выражения 
			Rule::Chain(3, TS('i'), NS('k'), TS(';')),														//только для унарных
			Rule::Chain(8, TS('w'), TS('('), NS('E'), TS(')'), TS('{'), NS('N'), TS('}'), NS('N')),			//цикл
			Rule::Chain(4, TS('i'), NS('E'), TS(';'), NS('N')),												//только для унарных
			Rule::Chain(4, TS('i'), NS('k'), TS(';'), NS('N')),												//унарный
			Rule::Chain(5, TS('v'), TS('t'), TS('i'), TS(';'), NS('N')),									//объявления переенной
			Rule::Chain(4, TS('r'), NS('E'), TS(';'), NS('N')),												//вохврат 
			Rule::Chain(5, TS('i'), TS('='), NS('E'), TS(';'), NS('N')),									//присвоение значения		
			Rule::Chain(4, TS('d'), NS('E'), TS(';'), NS('N'))												//вывод выражения 
			),
		Rule(
			NS('E'), GRB_ERROR_SERIES + 2,    // ошибка в выражении
			8,                                // E?i | l | (E) | i(W) | iM | lM | (E)M | i(W)M
			Rule::Chain(1, TS('i')),
			Rule::Chain(1, TS('l')),
			Rule::Chain(3, TS('('), NS('E'), TS(')')),
			Rule::Chain(4, TS('i'), TS('('), NS('W'), TS(')')),
			Rule::Chain(2, TS('i'), NS('M')),
			Rule::Chain(2, TS('l'), NS('M')),
			Rule::Chain(4, TS('('), NS('E'), TS(')'), NS('M')),
			Rule::Chain(5, TS('i'), TS('('), NS('W'), TS(')'), NS('M'))
			),
		Rule(
			NS('F'), GRB_ERROR_SERIES + 3,    // ошибка в параметрах функции
			2,                                // F? ti | ti,F
			Rule::Chain(2, TS('t'), TS('i')),
			Rule::Chain(4, TS('t'), TS('i'), TS(','), NS('F'))
			),
		Rule(
			NS('W'), GRB_ERROR_SERIES + 4,    // ошибка в параметрах вызываемой функции 
			4,                                // W? i | l | i,W | l,W 
			Rule::Chain(1, TS('i')),
			Rule::Chain(1, TS('l')),
			Rule::Chain(3, TS('i'), TS(','), NS('W')),
			Rule::Chain(3, TS('l'), TS(','), NS('W'))
			),
		Rule(
			NS('M'), GRB_ERROR_SERIES + 5,    // операторы в выражениях
			2,								  // M ? aE | aEM
			Rule::Chain(2, TS('a'), NS('E')),
			Rule::Chain(3, TS('a'), NS('E'), NS('M'))
			)
		);





	//Greibach greibach(
	//	NS('S'), TS('$'),                     // стартовый символ, дно стека
	//	6,									  // количество правил
	//	Rule(
	//		NS('S'), GRB_ERROR_SERIES + 0,    // неверная структура программы
	//		6,                                // S->m{NrE;}; | m{N}; | m{NrE;};S | tfi(F){NrE;};S |  tfi(F){NrE;}; | tfi(F){N};
	//		Rule::Chain(8, TS('m'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}'), TS(';')),
	//		Rule::Chain(12, TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('{'), TS('r'), NS('E'), TS(';'), TS('}'), TS(';')),
	//		Rule::Chain(13, TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}'), TS(';')),
	//		Rule::Chain(14, TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}'), TS(';'), NS('S')),
	//		Rule::Chain(13, TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('{'),  TS('r'), NS('E'), TS(';'), TS('}'), TS(';'), NS('S')),
	//		Rule::Chain(9, TS('m'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}'), TS(';'), NS('S'))
	//		),
	//	Rule(
	//		NS('N'), GRB_ERROR_SERIES + 1,    // ошибочный оператор
	//		17,                               // N->dti; | rE; | i=E; | dtfi(F); | dtiN | rE;N | i=E;N | dtfi(F);N |
	//		Rule::Chain(7, TS('w'), TS('('), NS('E'), TS(')'), TS('{'), NS('N'), TS('}')),					//цикл
	//		Rule::Chain(4, TS('v'), TS('t'), TS('i'), TS(';')),												//объявление идентификатора
	//		Rule::Chain(3, TS('r'), NS('E'), TS(';')),														//возврат
	//		Rule::Chain(4, TS('i'), TS('='), NS('E'), TS(';')),												//присвоение значения
	//		Rule::Chain(3, TS('d'), TS('i'), TS(';')),														//вывод идентиикатора 
	//		Rule::Chain(3, TS('d'), TS('l'), TS(';')),														//вывод литерала
	//		Rule::Chain(3, TS('d'), NS('E'), TS(';')),														//вывод выражения 
	//		Rule::Chain(3, TS('i'), NS('E'), TS(';')),														//только для унарных
	//		Rule::Chain(8, TS('w'), TS('('), NS('E'), TS(')'), TS('{'), NS('N'), TS('}'), NS('N')),			//цикл
	//		Rule::Chain(4, TS('i'), NS('E'), TS(';'), NS('N')),														//только для унарных
	//		Rule::Chain(4, TS('i'), NS('E'), TS(';'), NS('N')),												//унарный
	//		Rule::Chain(5, TS('v'), TS('t'), TS('i'), TS(';'), NS('N')),									//объявления переенной
	//		Rule::Chain(4, TS('r'), NS('E'), TS(';'), NS('N')),												//вохврат 
	//		Rule::Chain(5, TS('i'), TS('='), NS('E'), TS(';'), NS('N')),									//присвоение значения
	//		Rule::Chain(4, TS('d'), TS('i'), TS(';'), NS('N')),												//вывод	идентификатора
	//		Rule::Chain(4, TS('d'), TS('l'), TS(';'), NS('N')),												//вывод литерала		
	//		Rule::Chain(4, TS('d'), NS('E'), TS(';'), NS('N'))												//вывод выражения 
	//		),
	//	Rule(
	//		NS('E'), GRB_ERROR_SERIES + 2,    // ошибка в выражении
	//		9,                                // E?i | l | (E) | i(W) | iM | lM | (E)M | i(W)M
	//		Rule::Chain(1, TS('i')),
	//		Rule::Chain(1, TS('l')),
	//		Rule::Chain(1, TS('k')),														//++ --
	//		Rule::Chain(3, TS('('), NS('E'), TS(')')),
	//		Rule::Chain(4, TS('i'), TS('('), NS('W'), TS(')')),
	//		Rule::Chain(2, TS('i'), NS('M')),
	//		Rule::Chain(2, TS('l'), NS('M')),
	//		Rule::Chain(4, TS('('), NS('E'), TS(')'), NS('M')),
	//		Rule::Chain(5, TS('i'), TS('('), NS('W'), TS(')'), NS('M'))
	//		),
	//	Rule(
	//		NS('F'), GRB_ERROR_SERIES + 3,    // ошибка в параметрах функции
	//		2,                                // F? ti | ti,F
	//		Rule::Chain(2, TS('t'), TS('i')),
	//		Rule::Chain(4, TS('t'), TS('i'), TS(','), NS('F'))
	//		),
	//	Rule(
	//		NS('W'), GRB_ERROR_SERIES + 4,    // ошибка в параметрах вызываемой функции 
	//		4,                                // W? i | l | i,W | l,W 
	//		Rule::Chain(1, TS('i')),
	//		Rule::Chain(1, TS('l')),
	//		Rule::Chain(3, TS('i'), TS(','), NS('W')),
	//		Rule::Chain(3, TS('l'), TS(','), NS('W'))
	//		),
	//	Rule(
	//		NS('M'), GRB_ERROR_SERIES + 5,    // операторы в выражениях
	//		2,								  // M ? aE | aEM
	//		Rule::Chain(2, TS('a'), NS('E')),
	//		Rule::Chain(3, TS('a'), NS('E'), NS('M'))
	//		)
	//	);

	Rule::Chain::Chain(short psize, GRBALPHABET s, ...) {
		size = psize;
		int* tmp = (int*)&s;
		nt = new GRBALPHABET[size];
		for (short i = 0; i < size; ++i)
		{
			nt[i] = (GRBALPHABET)tmp[i];
		}
	}
	Rule::Rule(GRBALPHABET pnn, int piderror, short psize, Chain c, ...) {
		nn = pnn;
		iderror = piderror;
		size = psize;
		Chain* tmp = &c;
		chains = new Chain[size];
		for (int i = 0;i < size; i++) {
			chains[i] = tmp[i];
		}
	}
	Greibach::Greibach(GRBALPHABET pstartN, GRBALPHABET pstbottomT, short psize, Rule r, ...) {
		startN = pstartN;
		stbottomT = pstbottomT;
		size = psize;
		rules = new Rule[size];
		Rule* p = &r;
		for (int i = 0; i < size; i++)
			rules[i] = p[i];
	}
////
	char* Rule::Chain::getChain(char* b) {
		
		for (int i = 0; i < Chain::size; i++)
		{
			b[i] = Chain::alphabet_to_char(nt[i]);
		}
		b[size] = 0x00;
		return b;
	}
	char* Rule::getCRule(char* b, short nchain) {
		char tmp[30];
		b[0] = GRB::Rule::Chain::alphabet_to_char(nn);
		b[1] = '-';
		b[2] = '>';
		b[3] = 0x00;
		
		chains[nchain].getChain(tmp);
		strcat_s(b,sizeof(tmp)+5,tmp);
		return b;
	}
	short Rule::getNextChain(GRBALPHABET t, Rule::Chain& pchain, short j) {
				short chainnum = -1;
  
			for (; j < size; j++)
			{
				if (chains[j].nt[0] == t)
					{
						pchain = chains[chainnum = j];
						break;
					};
			};

  return chainnum;
	}
////	
	short Greibach::getRule(GRBALPHABET pnn, Rule& prule) {
		int num=-1;
		for (int i = 0; i <size; i++)
		{
			if (rules[i].nn==pnn)
			{
				num = i;
				prule = rules[i];
			}
		}
		return num;
	}
	Rule Greibach::getRule(short n) {
		Rule p;
		if (n < size)
			p = rules[n];
		return p;
	}
	Greibach GRB::getGreibach()
	{
		return greibach;
	};


}