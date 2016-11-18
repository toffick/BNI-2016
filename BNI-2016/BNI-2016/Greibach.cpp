#include "stdafx.h"
#include "Greibach.h"
#include "Error.h"
#include "string.h"
#define GRB_ERROR_SERIES 600

namespace GRB {
#define NS(n) Rule::Chain::N(n)
#define TS(n) Rule::Chain::T(n)

	// ---------- ���������� ������� ----------

	Greibach greibach(
		NS('S'), TS('$'),                     // ��������� ������, ��� �����
		6,									  // ���������� ������
		Rule(
			NS('S'), GRB_ERROR_SERIES + 0,    // �������� ��������� ���������
			6,                                // S->m{NrE;}; | tfi(F){NrE;};S | m{NrE;};S | tfi(F){NrE;}; | m{N}; | tfi(F){N};
			Rule::Chain(14, TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}'), TS(';'), NS('S')),
			Rule::Chain(13, TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}'), TS(';')),
			Rule::Chain(8, TS('m'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}'), TS(';')),
			Rule::Chain(9, TS('m'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}'), TS(';'), NS('S')),
			Rule::Chain(5, TS('m'), TS('{'), NS('N'), TS('}'), TS(';')),
			Rule::Chain(10, TS('t'), TS('f'), TS('i'), TS('('), NS('N'), TS(')'), TS('{'), NS('N'), TS('}'), TS(';'))
			),
		Rule(
			NS('N'), GRB_ERROR_SERIES + 1,    // ��������� ��������
			14,                               // N->dti; | rE; | i=E; | dtfi(F); | dtiN | rE;N | i=E;N | dtfi(F);N |
			Rule::Chain(4, TS('d'), TS('t'), TS('i'), TS(';')),
			Rule::Chain(3, TS('r'), NS('E'), TS(';')),
			Rule::Chain(4, TS('i'), TS('='), NS('E'), TS(';')),
			Rule::Chain(8, TS('d'), TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS(';')),
			Rule::Chain(3, TS('p'), TS('i'), TS(';')),
			Rule::Chain(3, TS('p'), TS('l'), TS(';')),
			Rule::Chain(3, TS('p'), NS('E'), TS(';')),
			Rule::Chain(5, TS('d'), TS('t'), TS('i'), TS(';'), NS('N')),
			Rule::Chain(4, TS('r'), NS('E'), TS(';'), NS('N')),
			Rule::Chain(5, TS('i'), TS('='), NS('E'), TS(';'), NS('N')),
			Rule::Chain(9, TS('d'), TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS(';'), NS('N')),
			Rule::Chain(4, TS('p'), TS('i'), TS(';'), NS('N')),
			Rule::Chain(4, TS('p'), TS('l'), TS(';'), NS('N')),
			Rule::Chain(4, TS('p'), NS('E'), TS(';'), NS('N'))
			),
		Rule(
			NS('E'), GRB_ERROR_SERIES + 2,    // ������ � ���������
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
			NS('F'), GRB_ERROR_SERIES + 3,    // ������ � ���������� �������
			2,                                // F? ti | ti,F
			Rule::Chain(2, TS('t'), TS('i')),
			Rule::Chain(4, TS('t'), TS('i'), TS(','), NS('F'))
			),
		Rule(
			NS('W'), GRB_ERROR_SERIES + 4,    // ������ � ���������� ���������� ������� 
			4,                                // W? i | l | i,W | l,W 
			Rule::Chain(1, TS('i')),
			Rule::Chain(1, TS('l')),
			Rule::Chain(3, TS('i'), TS(','), NS('W')),
			Rule::Chain(3, TS('l'), TS(','), NS('W'))
			),
		Rule(
			NS('M'), GRB_ERROR_SERIES + 5,    // ???
			2,								  // M ? vE | vEM
			Rule::Chain(2, TS('v'), NS('E')),
			Rule::Chain(3, TS('v'), NS('E'), NS('M'))
			)
		);
	//Greibach greibach(
	//	NS('S'), TS('$'),                     // ��������� ������, ��� �����
	//	6,									  // ���������� ������
	//	Rule(
	//		NS('S'), GRB_ERROR_SERIES + 0,    // �������� ��������� ���������
	//		4,                                // S->m{NrE;}; | tfi(F){NrE;};S | m{NrE;};S | tfi(F){NrE;};
	//		Rule::Chain(8, TS('m'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}'), TS(';')),
	//		Rule::Chain(14, TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}'), TS(';'), NS('S')),
	//		Rule::Chain(9, TS('m'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}'), TS(';'), NS('S')),
	//		Rule::Chain(13, TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}'), TS(';'))
	//		),
	//	Rule(
	//		NS('N'), GRB_ERROR_SERIES + 1,    // ��������� ��������
	//		8,                                // N->dti; | rE; | i=E; | dtfi(F); | dtiN | rE;N | i=E;N | dtfi(F);N
	//		Rule::Chain(4, TS('d'), TS('t'), TS('i'), TS(';')),
	//		Rule::Chain(3, TS('r'), NS('E'), TS(';')),
	//		Rule::Chain(4, TS('i'), TS('='), NS('E'), TS(';')),
	//		Rule::Chain(8, TS('d'), TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS(';')),
	//		Rule::Chain(5, TS('d'), TS('t'), TS('i'), TS(';'), NS('N')),
	//		Rule::Chain(4, TS('r'), NS('E'), TS(';'), NS('N')),
	//		Rule::Chain(5, TS('i'), TS('='), NS('E'), TS(';'), NS('N')),
	//		Rule::Chain(9, TS('d'), TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS(';'), NS('N'))
	//		),
	//	Rule(
	//		NS('E'), GRB_ERROR_SERIES + 2,    // ������ � ���������
	//		8,                                // E?i | l | (E) | i(W) | iM | lM | (E)M | i(W)M
	//		Rule::Chain(1, TS('i')),
	//		Rule::Chain(1, TS('l')),
	//		Rule::Chain(3, TS('('), NS('E'), TS(')')),
	//		Rule::Chain(4, TS('i'), TS('('), NS('W'), TS(')')),
	//		Rule::Chain(2, TS('i'), NS('M')),
	//		Rule::Chain(2, TS('l'), NS('M')),
	//		Rule::Chain(4, TS('('), NS('E'), TS(')'), NS('M')),
	//		Rule::Chain(5, TS('i'), TS('('), NS('W'), TS(')'), NS('M'))
	//		),
	//	Rule(
	//		NS('F'), GRB_ERROR_SERIES + 3,    // ������ � ���������� �������
	//		2,                                // F? ti | ti,F
	//		Rule::Chain(2, TS('t'), TS('i')),
	//		Rule::Chain(4, TS('t'), TS('i'), TS(','), NS('F'))
	//		),
	//	Rule(
	//		NS('W'), GRB_ERROR_SERIES + 4,    // ������ � ���������� ���������� ������� 
	//		4,                                // W? i | l | i,W | l,W 
	//		Rule::Chain(1, TS('i')),
	//		Rule::Chain(1, TS('l')),
	//		Rule::Chain(3, TS('i'), TS(','), NS('W')),
	//		Rule::Chain(3, TS('l'), TS(','), NS('W'))
	//		),
	//	Rule(
	//		NS('M'), GRB_ERROR_SERIES + 5,    // ???
	//		2,								  // M ? vE | vEM
	//		Rule::Chain(2, TS('v'), NS('E')),
	//		Rule::Chain(3, TS('v'), NS('E'), NS('M'))
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
		/*for (int z = 0; i < chains[nchain].size; z++,i++) {
			b[i] = GRB::Rule::Chain::alphabet_to_char(chains[nchain].nt[z]);
		}*/
		chains[nchain].getChain(tmp);
		//strcat(b, tmp);
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