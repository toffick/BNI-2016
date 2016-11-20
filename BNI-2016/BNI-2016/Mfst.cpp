#include "stdafx.h"
#include "Mfst.h"
#include "LexAnalize.h"
using namespace std;
int FST_TRACE_n = - 1;

char rbuf[205], sbuf[205], lbuf[1024]; // печать

#define NS(n) GRB::Rule::Chain::N(n)
#define TS(n) GRB::Ru1e::Chain::T(n)
#define ISNS(n) GRB::Rule::Chain::isN(n)

#define MFST_TRACE1  std::cout << std::setw(4) << std::left << ++FST_TRACE_n<<": "\
                         << std::setw(20) << std::left << rule.getCRule(rbuf, nrulechain)\
                         << std::setw(30) << std::left << MFST::Mfst::getCLenta(lbuf, lenta_position)\
                         << std::setw(20) << std::left << MFST::Mfst::getCSt(sbuf)\
                         << std::endl;

#define MFST_TRACE2 std::cout << std::setw(4) << std::left << FST_TRACE_n << ": "\
						<< std::setw(20) << std::left <<" " \
						<< std::setw(30) << std::left << MFST::Mfst::getCLenta(lbuf, lenta_position)\
						<< std::setw(20) << std::left << MFST::Mfst::getCSt(sbuf)\
						<< std::endl;

#define MFST_TRACE3 std::cout << std::setw(4) << std::left << ++FST_TRACE_n << ": "\
						<< std::setw(20) << std::left << " "\
						<< std::setw(30) << std::left << MFST::Mfst::getCLenta(lbuf, lenta_position)\
						<< std::setw(20) << std::left << MFST::Mfst::getCSt(sbuf)\
						<< std::endl;

#define MFST_TRACE4(c) std::cout << std::setw(4) << std::left << ++FST_TRACE_n << ": " <<std::setw(20)<<std::left<<c<<std::endl;

#define MFST_TRACE5(c) std::cout << std :: setw(4) << std::left << FST_TRACE_n << ": "<<std::setw(20)<<std::left<<c<<std::endl;

#define MFST_TRACE6(c, k) std::cout << std::setw(4) << std::left << FST_TRACE_n << ": "<<std::setw(20)<<std::left<<c<<k<<std::endl;

#define MFST_TRACE7 std::cout << std::setw(4) << std::left << state.lenta_position << ": "\
	<< std :: setw(20) << std::left << rule.getCRule(rbuf, state.nrulechain)\
	<< std::endl;
#define MFST_TRACE_START cout<<endl<<setw( 4)<<left<<"Шаг"<<":"<<\
						setw(20)<<left<<"Правило"<<\
						setw(30)<<left<<"Входная лента"<<\
						setw(20)<<left<<"Стек"<<endl;
#define COD(x) lex_to_lenta(x)
GRBALPHABET lex_to_lenta(char t) {
	using namespace  GRB;
	{
		if (Rule::Chain::isT(t))
			return Rule::Chain::T(t);
		else 
			if(Rule::Chain::isN(t))
			return Rule::Chain::N(t);
			else return 0;
	}
}
namespace MFST
{
	MfstState::MfstState(short pposition, MFSTSTSTACK pst, short pnrulechain) {
		lenta_position = pposition;
		st = pst;
		nrulechain = pnrulechain;	
	}
	MfstState::MfstState(short pposition, MFSTSTSTACK pst, short pnrule, short pnrulechain)
		: lenta_position(pposition), nrule(pnrule), nrulechain(pnrulechain), st(pst)
	{ };
	MfstState::MfstState() {
		lenta_position = 0;
		nrulechain = -1;
		nrule = -1;
	}
	Mfst::MfstDiagnosis::MfstDiagnosis(short plenta_position, RC_STEP prc_step, short pnrule, short pnrule_chain)
	{
		lenta_position = plenta_position;
		rc_step = prc_step;
		nrule_chain = pnrule_chain;
		nrule = pnrule;
		
	}
	Mfst::MfstDiagnosis::MfstDiagnosis() 
	{
		lenta_position = -1;
		nrule_chain = -1;
		nrule = -1;
		rc_step = SURPRISE;
	
	}
	
	Mfst::Mfst() {
		lenta_position = 0;
		lenta_size = 0;
		nrule = -1;
		nrulechain = -1;
		lenta = NULL;

	
	}
	Mfst::Mfst(LEX::Lex plex, GRB::Greibach pgrebach)
	{
		lex = plex;
		grebach = pgrebach;
		nrule = -1;
		lenta = new GRBALPHABET[lex.lextable.size];
		lenta_size = lex.lextable.size;
		for (int i = 0; i < lenta_size; i++)					//перекодирование ленты
			lenta[i] = GRB::Rule::Chain::T(lex.lextable.table[i].lexema);
		lenta_position = 0;
		st.push(grebach.stbottomT);
		st.push(grebach.startN);
		nrulechain = -1;
	}

	
	char* Mfst::getCSt(char* buf) {
		for (int i = st.size()-1, j=0; i>=0; --i,j++)
		{
			buf[j] = GRB::Rule::Chain::alphabet_to_char(st._Get_container()[i]);	//заполнение буфера содержимым стека
		}
		buf[st.size()] = '\0';
		return buf;
	
	
	}
	char* Mfst::getCLenta(char* buf, short pos, short n)
	{
		short i, k = (pos + n < lenta_size) ? pos + n : lenta_size;
		for (i = pos; i < k; i++)
			buf[i - pos] = GRB::Rule::Chain::alphabet_to_char(lenta[i]);
		buf[i - pos] = 0x00;
		return buf;
	}
	bool Mfst::saveState(Parm::PARM parm) {

		storestate.push(MfstState(lenta_position, st,nrule, nrulechain));	//сохраняет текущее положение мпка в стек ка
		if (parm.tr)
		MFST_TRACE6("SAVESTATE: ", storestate.size());
		return true;
	}
	bool Mfst::push_chain(GRB::Rule::Chain chain)
	{
		for (int i = chain.size-1; i >= 0;i--)
			st.push(chain.nt[i]);
		return true;
	}
	bool Mfst::reststate(Parm::PARM parm) 
	{
		bool rc;
		MfstState tmp;
		if (!storestate.empty()) {
			tmp = storestate.top();
			nrule = tmp.nrule;
			lenta_position =tmp.lenta_position;
			nrulechain = tmp.nrulechain;
			st = tmp.st;
			storestate.pop();
			rc = true;
			if (parm.tr)
			{
				MFST_TRACE5("RESTATE");
				MFST_TRACE2;
			}
		}
		else
			rc = false;
		return rc;
	}
	char* Mfst::getDiagnosis(short n, char* buf)
	{
		char *rc = "";
		int errid = 0;
		int lpos = -1;
		if (n < MFST_DIAGN_NUMBER && (lpos = diagnosis[n].lenta_position) >= 0)
		{
			errid = grebach.getRule(diagnosis[n].nrule).iderror;
			Error::ERROR err = Error::geterror(errid);
			sprintf_s(buf,MFST_DIAGN_MAXSIZE, "%d: строка %d, %s", err.id, lex.lextable.table[lpos].sn, err.message);
			rc = buf;
		}
		return buf;

	}
	bool Mfst::savediagnosis(RC_STEP pprc_step){
		bool rc = false;
		short t = 0;
		while (t < MFST_DIAGN_NUMBER && lenta_position <= diagnosis[t].lenta_position)
			t++;
		if (rc = (t < MFST_DIAGN_NUMBER)) {
			diagnosis[t] = MfstDiagnosis(lenta_position, pprc_step, nrule, nrulechain);
			for (short j = t + 1; j < MFST_DIAGN_NUMBER; j++) 
				diagnosis[j].lenta_position = -1;
		}
	
		return rc;
	}
	void Mfst::printrules()
	{
		MfstState state;
		GRB::Rule rule;
		std::cout << "\nДерево разбора\n";
		for (unsigned short k = 0; k < storestate.size(); k++)
		{
			state = storestate._Get_container()[k];
			rule = grebach.getRule(state.nrule);
			
			MFST_TRACE7
		}
	}

	bool Mfst::savededucation()															
	{
		MfstState state;
		GRB::Rule rule;
		deducation.nrules = new short[deducation.size = storestate.size()];
		deducation.nrulechains = new short[deducation.size];
		for (unsigned short k = 0; k < storestate.size(); k++)
		{

			state = storestate._Get_container()[k];
			deducation.nrules[k] = state.nrule;
			deducation.nrulechains[k] = state.nrulechain;
		}
		return true;
		
	}
	Mfst::RC_STEP Mfst::step(Parm::PARM parm)
	{
		RC_STEP rc = SURPRISE;

		if (lenta_position < lenta_size)
		{
			if (ISNS(st.top()))
			{
				GRB::Rule rule;
				if ((nrule = grebach.getRule(st.top(), rule)) >= 0)
				{
					GRB::Rule::Chain chain;
					if ((nrulechain = rule.getNextChain(lenta[lenta_position], chain, nrulechain + 1)) >= 0)
					{
						if(parm.tr)
							MFST_TRACE1;
						saveState(parm);
						st.pop();
						push_chain(chain);
						rc = NS_OK;
						if (parm.tr)
							MFST_TRACE2;
					}
					else
					{
						if (parm.tr)
							MFST_TRACE4("TNS_NORULECHAIN/NS_NORULE");
						savediagnosis(NS_NORULECHAIN);
						rc = reststate(parm) ? NS_NORULECHAIN : NS_NORULE;
					};
				}
				else
				{
					rc = NS_ERROR;
				};
			}
			else if ((st.top() == lenta[lenta_position]))
			{
				lenta_position++;
				st.pop();
				nrulechain = -1;
				rc = TS_OK;
				if (parm.tr)
					MFST_TRACE3;
			}
			else
			{
				if (parm.tr)
					MFST_TRACE4("TS_NOK/NS_NORULECHAIN");
				rc = reststate(parm) ? TS_NOK : NS_NORULECHAIN;
			};
		}
		else
		{
			rc = LENTA_END;
		};

		return rc;
	};
	
	bool Mfst::start(Parm::PARM parm)
	{
		if(parm.tr)
			MFST_TRACE_START;

		bool rc = false;
		RC_STEP rc_step = SURPRISE;
		char buf[MFST_DIAGN_MAXSIZE];
		rc_step = step(parm);
		while (rc_step == NS_OK || rc_step == NS_NORULECHAIN || rc_step == TS_OK || rc_step == TS_NOK)
			rc_step = step(parm);
		switch (rc_step)
		{
		case LENTA_END: 
			if (parm.tr)
			{
				MFST_TRACE4("--------->LENTA_END")
					std::cout << "---------------------------------------------------------------------------------------\n";
				sprintf_s(buf, MFST_DIAGN_MAXSIZE, "%d: всего строк %d, синтаксический анализ выполнен без ошибокб", 0, lenta_size);
				std::cout << std::setw(4) << std::left << 0 << ": всего строк" << lenta_size << ", синтаксический анализ выполнен без ошибок\n";
			}
				rc = true;
				break;
		case NS_NORULE: { 
			if (parm.tr)
			{
				std::cout << "NS_NORULE";
				std::cout << getDiagnosis(0, buf) << std::endl;
				std::cout << getDiagnosis(1, buf) << std::endl;
				std::cout << getDiagnosis(2, buf) << std::endl;
			}
			break;
		}
		case NS_NORULECHAIN:
			if (parm.tr)
				std::cout << "NS_NORULECHAIN"; break;
		case NS_ERROR: 
			if (parm.tr)
				std::cout << "NS_ERROR"; break;
		case SURPRISE: 
			if (parm.tr)
				std::cout << "SURPRISE"; break;
		}
		return rc;
	}
	
	
	
	
	
}