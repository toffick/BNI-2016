#include "stdafx.h"
#include "SemAn.h"

namespace SA
{

	

	void MainSemanticAnalize(LEX::Lex lex, Log::LOG log, Error::Errors& err)
	{
		bool er = true;
		er = IsMain(lex,err);
		er = ExpressionOperandsType(lex, err);
		er = ValidReturnValue(lex, err);
		er = ValidParmValue(lex, err);

		if(err.size)
			throw ERROR_THROW(700);


	}
	bool IsMain(LEX::Lex lex, Error::Errors& err)
	{
		int mainnumb=0;
		for (int i = 0; i < lex.lextable.size; i++)
		{
			if (lex.lextable.table[i].lexema == LEX_MAIN)
				mainnumb++;																		//нашли главную функцию - все хорошо
		}
		if (!mainnumb)																			//ни одной главной функции 
		{
			Error::adderr(701, err);
			return false;
		}
		else
			if (mainnumb > 1)																	//несколько главных функций
			{
				Error::adderr(707, err);
				return false;
			}
			else 
				return true;																	
	
	}
	bool ExpressionOperandsType(LEX::Lex lex, Error::Errors& err)
	{
		int findexpress;																
		int typeofleftvalue;
		int plusi = 0;
		bool errflag = true;
		bool strrightfalue=false;
		for (int i = 0; i < lex.lextable.size; i++)
		{
			if (lex.lextable.table[i].lexema == LEX_ASSIG)																					//нашли присваивание													
			{
				findexpress = i + 1;
				typeofleftvalue = lex.idtable.table[lex.lextable.table[ i - 1].idxTI].iddatatype;											//переменная для типа левостороннего значения
				while (lex.lextable.table[findexpress].lexema != LEX_SEMICOLON)
				{
					if (lex.lextable.table[findexpress].lexema == LEX_ID || lex.lextable.table[findexpress].lexema == LEX_LITERAL)			
					{
						if (lex.idtable.table[lex.lextable.table[findexpress].idxTI].iddatatype == IT::STR)									//строковый тип в выражении	
							strrightfalue = true;																							//нашли строковый тип(не можем далее использовать его с арифм. операциями)
						if (lex.idtable.table[lex.lextable.table[findexpress].idxTI].iddatatype != typeofleftvalue)							//данный ид/лит нет равен типу левого значения
						{
							Error::adderr(702,lex.lextable.table[findexpress].sn, err);														//ошибка несоответствия
							errflag = false;
							break;
						//	return false;
						}
						else
							if (lex.lextable.table[findexpress].idxTI != TI_NULLIDX && lex.idtable.table[lex.lextable.table[findexpress].idxTI].idtype == IT::F)			//пропуск литералов на кол-во параметров + скобки
								findexpress += lex.idtable.table[lex.lextable.table[findexpress].idxTI].value.parmvalue * 2+1;	
					}
					else
						if (lex.lextable.table[findexpress].lexema == LEX_ARIPH && strrightfalue)														//строковый тип + арифм знак = ошибка
						{
							Error::adderr(703, lex.lextable.table[findexpress].sn, err);
							errflag = false;
							break;
						//	return false;
						}

					findexpress++;
				}
				strrightfalue = false;
			}
		}
	
	
		return errflag;
	}
	bool ValidReturnValue(LEX::Lex lex, Error::Errors& err)
	{
		bool errflag = true;
		int typeoffunc;
		for (int i = 0; i < lex.lextable.size; i++)
		{
			if (lex.lextable.table[i].lexema == LEX_FUNC)
			{			
				typeoffunc = lex.idtable.table[lex.lextable.table[++i].idxTI].iddatatype;
				while (lex.lextable.table[i].lexema != LEX_RETURN)
					i++;
				if (lex.idtable.table[lex.lextable.table[++i].idxTI].iddatatype != typeoffunc)
				{
					Error::adderr(704, lex.lextable.table[i].sn, err);
					errflag = false;
					break;
					//return false;
				}
			}
		}
		return errflag;
	}
	bool ValidParmValue(LEX::Lex lex, Error::Errors& err) 
	{
		bool errflag = true;
		IT::Entry entry;
		int forinsideloop;
		for (int i = 0; i < lex.lextable.size; i++)
		{
			if (lex.lextable.table[i].lexema == LEX_FUNC)
			{
				entry = lex.idtable.table[lex.lextable.table[++i].idxTI];
				forinsideloop = ++i;
			
				for (forinsideloop; forinsideloop < lex.lextable.size; forinsideloop++)
				{
					if(lex.lextable.table[forinsideloop].idxTI!=TI_NULLIDX &&lex.lextable.table[forinsideloop].lexema==LEX_ID)
						if (!strcmp(lex.idtable.table[lex.lextable.table[forinsideloop].idxTI].id, entry.id))
						{
							forinsideloop += 2;
							int j = 0;
							while (j < entry.value.parmvalue)
							{
								if (lex.lextable.table[forinsideloop].idxTI!=TI_NULLIDX && lex.idtable.table[lex.lextable.table[forinsideloop].idxTI].iddatatype != entry.value.parmtype[j])
								{
									Error::adderr(705, lex.lextable.table[forinsideloop].sn, err);
									errflag = false;
									break;
								//	return false;
								}
								else
								{
									j++; 
									forinsideloop += 2;
								}
							}
						}


				}

			}



		}
		return errflag;
	}


}



