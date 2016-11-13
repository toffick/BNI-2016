
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
			if(param) ItE.idtype = IT::P;
			break;
		case FST::FST_STR: 
			ItE.iddatatype = IT::STR;
			if (param) ItE.idtype = IT::P;
			break;
		case FST::FST_BOOL:
			ItE.iddatatype = IT::BOOL; 
			if (param) ItE.idtype = IT::P;
			break;
		case FST::FST_VAR:  
			ItE.idtype = IT::V;   
			break;
		case FST::FST_FUNC: 
			ItE.idtype = IT::F;
			param = true;
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

		case FST::FST_BLIT:
			ItE.idtype = IT::L; 
			ItE.iddatatype = IT::BOOL;
			rc = newId(prefix, fst.string, ItE, ers, lex, line);
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
			param = false;
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
				strcat(ItE.id, name);
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
					case IT::BOOL:
					{
						ItE.value.vbool = TI_BOOL_DEFAULT;
						break;
					}

					}
					lex.lextable.table[lex.lextable.size - 1].idxTI = lex.idtable.size;						//если нет такого ид в таблице ид
					IT::Add(lex.idtable, ItE);
				}
				else
				{
					std::cout << "dubl";
					//ошибка дублирования ида
				}

				
				break;
			}
			case IT::F:
			{
				strncpy(prefix, name, TI_PREFIX_MAX_SIZE);
				strcat(ItE.id, name);
				rc = IT::IsId(lex.idtable, ItE.id);
				if (rc == TI_NULLIDX)
				{
					

					lex.lextable.table[lex.lextable.size - 1].idxTI = lex.idtable.size;						//если нет такого ид в таблице ид
					IT::Add(lex.idtable, ItE);
				}


				break;
			}
			case IT::P:
			{
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
					case IT::BOOL:
					{	
						if (!strcmp(name, LEX_TRUE_LIT))
							ItE.value.vbool = true;
						if(!strcmp(name, LEX_FALSE_LIT))
							ItE.value.vbool = false;
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
				rc = IT::IsId(lex.idtable, name);
				if (rc == TI_NULLIDX)
				{
					strcpy(ItE.id, name);
					IT::Add(lex.idtable, ItE);
				}
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
					std::cout << "dont";

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
		ItE.value.vbool = -1;
		ItE.value.vstr.len = 0;
		ItE.value.vstr.str[0] = 0;
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
			std::cout << std::endl<< lex.lextable.table[i].lexema;
			if (lex.lextable.table[i].idxTI != LT_TI_NULLIDX)
				std::cout <<"   "<< lex.idtable.table[lex.lextable.table[i].idxTI].id<< "  "<< lex.lextable.table[i].idxTI;
		}


		int k = 0;
		std::cout << "\n\nТаблица лексем\n0: ";
		for (int i = 0; i < lex.lextable.size; i++) 
		{
			if (lex.lextable.table[i].sn != k) 
			{
				std::cout << "\n" << lex.lextable.table[i].sn << ": ";
				k = lex.lextable.table[i].sn;
				std::cout << lex.lextable.table[i].lexema;
			}
			else
				std::cout << lex.lextable.table[i].lexema;
		}



		for (int i = 0; i < lex.idtable.size; i++) {
				std::cout << "\n\nИдентификатор №" << i << ": " << lex.idtable.table[i].id;
				//std::cout << "\nНомер в таблице идентификаторов: " << lexT.table[i].idxTI;
				std::cout << "\nПервая строка определения: " << lex.idtable.table[i].idxfirstLE;
				if (lex.idtable.table[i].iddatatype == IT::INT)
					std::cout << "\nТип данных: integer";
				else
					if (lex.idtable.table[i].iddatatype == IT::BOOL)
						std::cout << "\nТип данных: bool";
				else if (lex.idtable.table[i].iddatatype == IT::STR)
					std::cout << "\nТип данных: string";
				else
					std::cout << "\nТип данных: operator";
				if (lex.idtable.table[i].idtype == IT::F)
					std::cout << "\nТип ид: F";
				else if (lex.idtable.table[i].idtype == IT::V)
					std::cout << "\nТип ид: V";
				else if (lex.idtable.table[i].idtype == IT::P)
					std::cout << "\nТип ид: P";
				else if (lex.idtable.table[i].idtype == IT::L)
					std::cout << "\nТип ид: L";
				else if(lex.idtable.table[i].idtype == IT::O)
					std::cout << "\nТип ид: O";


				if ((lex.idtable.table[i].iddatatype == IT::BOOL && lex.idtable.table[i].idtype == IT::V) ||
					(lex.idtable.table[i].iddatatype == IT::BOOL && lex.idtable.table[i].idtype == IT::L))
					std::cout << "\nЗначение: " << lex.idtable.table[i].value.vbool;

				else if ((lex.idtable.table[i].iddatatype == IT::INT && lex.idtable.table[i].idtype == IT::V) ||
					(lex.idtable.table[i].iddatatype == IT::INT && lex.idtable.table[i].idtype == IT::L))
					std::cout << "\nЗначение: " << lex.idtable.table[i].value.vind;
				else if ((lex.idtable.table[i].iddatatype == IT::STR && lex.idtable.table[i].idtype == IT::V) ||
					(lex.idtable.table[i].iddatatype == IT::STR && lex.idtable.table[i].idtype == IT::L))
				{
					if (lex.idtable.table[i].value.vstr.str[0] == NULL)
						std::cout << "\nСтрока: NULL";
					else {
						std::cout << "\nСтрока: " << lex.idtable.table[i].value.vstr.str;
						std::cout << "\nДлина строки: " << lex.idtable.table[i].value.vstr.len;
					}
				}
			}


		return lex;
	}
}

