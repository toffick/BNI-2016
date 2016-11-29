#pragma once
#include <stack>
#include "LexAnalize.h"
#include "GRB.h"
#include "Parm.h"

#define MFST_DIAGN_MAXSIZE 2*ERROR_MAXSIZE_MESSAGE
#define MFST_DIAGN_NUMBER 3



#define MFST_TRACE_START cout<<endl<<setw( 4)<<left<<"Шаг"<<":"<<\
						setw(20)<<left<<"Правило"<<\
						setw(30)<<left<<"Входная лента"<<\
						setw(20)<<left<<"Стек"<<endl;



typedef std::stack<short> MFSTSTSTACK;
namespace MFST
{
	struct MfstState 
	{
		short lenta_position;
		short nrulechain;
		short nrule;
		MFSTSTSTACK st;
		MfstState();
		MfstState(short pposition, MFSTSTSTACK pst, short pnrulechain);
		MfstState(                    // конструктор с аргументами
			short pposition,          // позиция на ленте
			MFSTSTSTACK pst,             // стек автомата
			short pnrule,             // номер текущего правила
			short pnrulechain        // номер текущей цепочки
			);
	};
	struct Mfst 
	{
		enum RC_STEP {					//код возврата функции step
						NS_OK,			//найдено правило и цепочка, цепочка записана в стек
						NS_NORULE,		//не найдено прввило грамматики(ошибка в грамматике)
						NS_NORULECHAIN,	//не найдена подходящая цепочка правила(ошибка в исходном коде)
						NS_ERROR,		//неизвестный нетерминальный символ грамматики
						TS_OK,			//тек. символ ленты == вершине стека, продвиналась лента, pop(0) стека
						TS_NOK,			//тек. символ ленты != вершине стек, восстановлено расстояние 
						LENTA_END,		//текущая позиция ленты >= lenta_size
						SURPRISE		//деожиданно код возврата (ошибка в step)
		};
		struct MfstDiagnosis
		{
			short lenta_position;
			RC_STEP rc_step;
			short nrule;
			short nrule_chain;
			MfstDiagnosis();
			MfstDiagnosis(short plenta_position, RC_STEP prc_step, short pnrule,  short pnrule_chain);
		}diagnosis[MFST_DIAGN_NUMBER];
		GRBALPHABET* lenta;
		short lenta_position;
		short nrule;
		short nrulechain;
		short lenta_size;
		GRB::Greibach grebach;
		LEX::Lex lex;
		MFSTSTSTACK st;
		std::stack<MfstState> storestate;
		Mfst();
		Mfst(LEX::Lex plex,GRB::Greibach pgrebach);
		char* getCSt(char* buf);
		char* getCLenta(char* buf, short pos, short n = 25);
		char* getDiagnosis(short n, char* buf);
		bool saveState(Parm::PARM);
		bool reststate(Parm::PARM);
		bool push_chain(GRB::Rule::Chain chain);
		RC_STEP step(Parm::PARM);
		bool start(Parm::PARM);
		bool savediagnosis(RC_STEP pprc_step);
		void printrules();						//напечатать дерево разбора
		struct Deducation
		{
			short size;							//кол-во шагов в выводе
			short* nrules;						//номер правила грамматики
			short* nrulechains;					//номер цепочек правил грамматики(nrules)
			int* lp;							//lenta position
			Deducation() { size = 0; nrules = 0; nrulechains = 0; };
		}deducation;
		bool savededucation();					//созхранитьдерево разбора	
	};
}