
#pragma once
#include "stdafx.h"
#include "LexAnalize.h"






namespace LEX
{

	void AddStdFunc(LEX::Lex& lex)
	{
		IT::Entry e1;
		strcpy(e1.id, "strl");
		e1.value.parmvalue = 1;     // int fun strlen(take str a)
		e1.idtype = IT::F;
		e1.iddatatype = IT::INT;
		e1.idxfirstLE = TI_NULLIDX;
		e1.value.parmtype[0] = IT::STR;
		IT::Add(lex.idtable, e1);

	
		IT::Entry e2;
		strcpy(e2.id, "ipow");
		e2.value.parmvalue = 2;     // int fun strlen(take str a)
		e2.idtype = IT::F;
		e2.iddatatype = IT::INT;
		e2.idxfirstLE = TI_NULLIDX;
		e2.value.parmtype[0] = IT::INT;
		e2.value.parmtype[1] = IT::INT;
		IT::Add(lex.idtable, e2);

	};

	void CreatId(int line, FST::FST& fst, Error::Errors& ers, Lex& lex)
	{
		static IT::Entry ItE;											// формируемая строка ТИ
		static char  prefix[TI_PREFIX_MAX_SIZE];						// имя текущей функции (префикс)
		static bool param;												// ссчитываем ли параметры функции
		static bool rc=true;											// проверка на очистку стрки ти 
		if (rc)															
		{		
			RestartItE(ItE);											//очистка добавляемой строки ТИ
			rc = false;
		}
		switch (fst.ind)
		{
			case FST::FST_INT: 
				ItE.iddatatype = IT::INT;
				if(param) 
					ItE.idtype = IT::P;
				break;
			case FST::FST_STR: 
				ItE.iddatatype = IT::STR;
				if (param)
					ItE.idtype = IT::P;
				break;
			case FST::FST_VAR:  
				ItE.idtype = IT::V;   
				break;
			case FST::FST_FUNC: 
				ItE.idtype = IT::F;
				param = true;
				break;
			case FST::FST_STD_LIB:
				rc = newId(prefix, fst.string, ItE, ers, lex, line);
				break;
			case FST::FST_ARIPH:    
				ItE.idtype = IT::O;   
				rc=newId(prefix, fst.string, ItE, ers, lex, line);
				break;
			case FST::FST_MAIN: 
				ItE.iddatatype = IT::INT;
				ItE.idtype = IT::F;
				rc=newId(prefix, fst.string, ItE, ers, lex, line);
				lex.idtable.table[lex.idtable.size - 1].id[strlen(lex.idtable.table[lex.idtable.size - 1].id) - 1] = 0x00;
				break;
			case FST::FST_ID:
				rc=newId(prefix, fst.string, ItE, ers, lex,line);
				break;
			
			case FST::FST_ILIT:
				ItE.idtype = IT::L;
				ItE.iddatatype = IT::INT;
				rc = newId(prefix, fst.string, ItE, ers, lex, line);
				break;
			case FST::FST_SLIT:
				ItE.idtype = IT::L; 
				ItE.iddatatype = IT::STR;
				rc = newId(prefix, fst.string, ItE, ers, lex, line);
				break;

			case FST::FST_RIGHTHESIS:
				param = false;																		//вышли из параметров
				break;
			
		};
	};

	bool newId(char* prefix, char* name, IT::Entry& ItE, Error::Errors& ers, Lex& lex,int line)
	{
		char separ[2] = "0";
		ItE.idxfirstLE = line;
		int rc;
			switch (ItE.idtype)
			{
			case IT::V:
			{
				strcpy(ItE.id, prefix);
				strncat(ItE.id, name,10);
				rc = IT::IsId(lex.idtable, ItE.id);
				if (rc == TI_NULLIDX) {
					switch (ItE.iddatatype)
					{
					case IT::INT:
					{
						ItE.value.vind = TI_INT_DEFAULT;
						break;
					}
					case IT::STR:
					{
						strcpy(ItE.value.vstr.str, TI_STRDEFAULT);
						ItE.value.vstr.len = 0;
						break;
					}
					
					}
					lex.lextable.table[lex.lextable.size - 1].idxTI = lex.idtable.size;						//если нет такого ид в таблице ид
				
					IT::Add(lex.idtable, ItE);
				}
				else
				{

					Error::adderr(120, line, ers);
				}			
				break;
			}
			case IT::F:
			{
				strncpy(ItE.id, name, 10);
				strcat(ItE.id, separ);
				strcpy(prefix,ItE.id);
				rc = IT::IsId(lex.idtable, ItE.id);				//ид функции
				if(!strcmp(name,"ipow") || !strcmp(name, "strl"))
					Error::adderr(120, line, ers);

				if (rc == TI_NULLIDX)
				{
					lex.lextable.table[lex.lextable.size - 1].idxTI = lex.idtable.size;						//если нет такого ид в таблице ид
					IT::Add(lex.idtable, ItE);
				}
				else
				{
					Error::adderr(120, line, ers);
				}
				break;
			}
			case IT::P:
			{
				strcpy(ItE.id, prefix);
				strncat(ItE.id, name, 10);

				int indfc = IT::IsId(lex.idtable, prefix);
				if(indfc!=TI_NULLIDX)
					lex.idtable.table[indfc].value.parmtype[lex.idtable.table[indfc].value.parmvalue++]=ItE.iddatatype;

				rc = IT::IsId(lex.idtable, ItE.id);
				if (rc == TI_NULLIDX)
				{
					IT::Add(lex.idtable, ItE);
				}
				else
				{

					Error::adderr(120, line, ers);
				}
				break;
			}
			case IT::L:
			{
				static int koko = 0;
				char buf[10];
				rc = IT::IsLiteral(lex.idtable, name,ItE);
				if (rc == TI_NULLIDX)
				{
					_itoa(koko++,buf,10);	
					strcpy(ItE.id, "L");
					strcat(ItE.id, buf);
						switch (ItE.iddatatype)
					{
					case IT::STR:
						{
							strncpy(ItE.value.vstr.str,name,TI_STR_MAXSIZE);
							ItE.value.vstr.len = strlen(name)-2;
							break;
						}
					case IT::INT:
					{
						ItE.value.vind = atoi(name);
						
						break;
					}
					}
					lex.lextable.table[lex.lextable.size - 1].idxTI = lex.idtable.size;						//если нет такого ид в таблице ид
					IT::Add(lex.idtable, ItE);
				}
				break;
			}
			case IT::O:
			{
				strncat(ItE.id, name, 5);
				rc = IT::IsId(lex.idtable, ItE.id);
				if (rc == TI_NULLIDX)
				{
					IT::Add(lex.idtable, ItE);
				}
				
					//lex.lextable.table[lex.lextable.size - 1].idxTI = IT::IsId(lex.idtable, name);
				break;

			}

			default:										//когда пришел ид без параметров
			{
				
				
				strncpy(ItE.id, name,10);
				strcat(ItE.id, separ);
				int fc = IT::IsId(lex.idtable, ItE.id);				//ид функции

				strcpy(ItE.id, name);
				int std = IT::IsId(lex.idtable, ItE.id);				//ид  стандартной функции
				

				strcpy(ItE.id,prefix);
				strcat(ItE.id, name);		
			
				rc = IT::IsId(lex.idtable, ItE.id);				//ид переменной
				if (rc == TI_NULLIDX && fc == TI_NULLIDX && std==TI_NULLIDX)
				{
					Error::adderr(122,line,  ers);
				}
				else
				{
					if(rc!= TI_NULLIDX)
					ItE = IT::getEntry(lex.idtable, rc);
					else
						if (std != TI_NULLIDX)
						ItE = IT::getEntry(lex.idtable, std);
						else
							ItE = IT::getEntry(lex.idtable, fc);
				}
				break;
			}		
			}		
			if (ItE.idtype != IT::L)
			{
				lex.lextable.table[lex.lextable.size - 1].idxTI = IT::IsId(lex.idtable, ItE.id);
			}
			else
			{
				lex.lextable.table[lex.lextable.size - 1].idxTI = IT::IsLiteral(lex.idtable, name,ItE);
			};
		
		return true;
	}

	void RestartItE(IT::Entry& ItE) {	
		ItE.idxfirstLE = 0;
		ItE.value.vind = 0;
		ItE.value.vstr.len = 0;
		ItE.value.vstr.str[0] = 0;
		ItE.value.parmvalue = 0;
		ItE.id[0] = 0x00;
		ItE.iddatatype = IT::OFF;
		ItE.idtype = IT::N;
	}

	Lex StartLA(In::IN& in, Error::Errors& ers)  // начать лексичский анализ
	{
		int er_numb = ers.size;
		Lex lex;  
		bool chain = false;
		AddStdFunc(lex);
		FST::FST* fsts = FST::crfsts();  
		for (int i = 0; i < in.size; i++)
		{
			for (int j = 0; j < FST_ARR_SIZE; j++)
			{
				FST::restartFST(fsts[j], in.chains[i].chain);

				if (chain=FST::execute(fsts[j]))
				{
					LT::Add(lex.lextable, LT::Entry(fsts[j].lexema, in.chains[i].line, IT::getIdxTI(fsts[j].lexema, lex.idtable)));
					CreatId(in.chains[i].line, fsts[j], ers, lex);
					break;
				};
			};
			if (!chain)
			{
				Error::adderr(114, in.chains[i].line, ers);
			}
		}

	/*	for (int i = 0; i < lex.lextable.size; i++)
		{
			std::cout << std::endl << lex.lextable.table[i].lexema;
			if (lex.lextable.table[i].idxTI != LT_TI_NULLIDX)
				std::cout << "   " << lex.idtable.table[lex.lextable.table[i].idxTI].id << "  " << lex.lextable.table[i].idxTI;
		}
*/
		return lex;
	}
}

