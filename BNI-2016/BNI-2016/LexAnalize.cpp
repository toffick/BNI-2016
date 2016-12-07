
#pragma once
#include "stdafx.h"
#include "LexAnalize.h"

namespace LEX
{
	void CreatId(int line, FST::FST& fst, Error::Errors& ers, Lex& lex)
	{
		static IT::Entry ItE;											// формируемая строка ТИ
		static char  prefix[TI_PREFIX_MAX_SIZE];						// имя текущей функции (префикс)
		static bool param;												// ссчитываем ли параметры функции
		static bool inloop = false;										// находимся ли в нутри цикла
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
				if(inloop)
					Error::adderr(123, line, ers);
				ItE.idtype = IT::V;   
				break;
			case FST::FST_FUNC: 
				ItE.idtype = IT::F;
				param = true;
				break;
			case FST::FST_STD_LIB:
				ItE.idtype = IT::F;	
				ItE.iddatatype = IT::INT;
				rc = newId(prefix, fst.string, ItE, ers, lex, line);
				break;
			case FST::FST_ARIPH:    
				ItE.idtype = IT::O;   
				rc=newId(prefix, fst.string, ItE, ers, lex, line);
				break;
			case FST::FST_MAIN: 
				ItE.iddatatype = IT::OFF;
				ItE.idtype = IT::F;
				rc=newId(prefix, fst.string, ItE, ers, lex, line);
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
			case FST::FST_RIGHTBRACE:
				inloop = false;																		//вышли из цикла

			case FST::FST_RIGHTHESIS:
				param = false;																		//вышли из параметров
				break;
			case FST::FST_WHILE:
				inloop = true;
				break;
		};
	};

	bool newId(char* prefix, char* name, IT::Entry& ItE, Error::Errors& ers, Lex& lex,int line)
	{
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
				strncpy(prefix, name, TI_PREFIX_MAX_SIZE);
				strcat(ItE.id, prefix);
				rc = IT::IsId(lex.idtable, ItE.id);
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
				if (ItE.idtype == IT::P && IT::IsId(lex.idtable, prefix) != -1)
				{
					lex.idtable.table[IT::IsId(lex.idtable, prefix)].value.parmvalue++;
				}
				strcpy(ItE.id, prefix);
				strcat(ItE.id, name);
				IT::Add(lex.idtable, ItE);
				break;
			}
			case IT::L:
			{
				static char litnum = '0';
				rc = IT::IsLiteral(lex.idtable, name,ItE);
				if (rc == TI_NULLIDX)
				{
					ItE.id[0] = 'L';
					ItE.id[1] = litnum++;
					ItE.id[2] = 0x00;
					switch (ItE.iddatatype)
					{
					case IT::STR:
						{
							strcpy(ItE.value.vstr.str,name);
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
				int fc;
				strcpy(ItE.id, name);							
				fc = IT::IsId(lex.idtable, ItE.id);				//ид функции
				strcpy(ItE.id,prefix);
				strcat(ItE.id, name);							
				rc = IT::IsId(lex.idtable, ItE.id);				//ид переменной
				if (rc == TI_NULLIDX && fc == TI_NULLIDX)
				{
					Error::adderr(122,line,  ers);
				}
				else
				{
					if(rc!= TI_NULLIDX)
					ItE = IT::getEntry(lex.idtable, rc);
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
		Lex lex;                               
		FST::FST* fsts = FST::crfsts();  
		for (int i = 0; i < in.size; i++)
		{
			for (int j = 0; j < FST_ARR_SIZE; j++)
			{
				FST::restartFST(fsts[j], in.chains[i].chain);

				if (FST::execute(fsts[j]))
				{
					LT::Add(lex.lextable, LT::Entry(fsts[j].lexema, in.chains[i].line, IT::getIdxTI(fsts[j].lexema, lex.idtable)));
					CreatId(in.chains[i].line, fsts[j], ers, lex);
					break;
				};
			};
		}

		for (int i = 0; i < lex.lextable.size; i++)
		{
			std::cout << lex.lextable.table[i].lexema << "   ";
			std::cout << lex.lextable.table[i].idxTI;
			if (lex.lextable.table[i].idxTI != TI_NULLIDX)
				std::cout << "   "<<lex.idtable.table[lex.lextable.table[i].idxTI].id;
			std::cout << std::endl;
		}
		return lex;
	}
}

