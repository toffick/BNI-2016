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
		er = ValidParmSTDValue(lex, err);
		er=Expressiondiaplayreturn(lex,err);

		if(err.size)
			throw ERROR_THROW(700);


	}
	bool IsMain(LEX::Lex lex, Error::Errors& err)
	{
		for (int i = 0; i < lex.lextable.size; i++)
		{
			if (lex.lextable.table[i].lexema == LEX_MAIN)
				return true;																		//нашли главную функцию - все хорошо
		}
		Error::adderr(701,err);
		return false;
	
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
					if ((lex.lextable.table[findexpress].lexema == LEX_ID || lex.lextable.table[findexpress].lexema == LEX_LITERAL) && lex.lextable.table[findexpress].idxTI!=TI_NULLIDX)
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
			if (lex.lextable.table[i].lexema == LEX_FUNC)														//определение функции
			{			
				typeoffunc = lex.idtable.table[lex.lextable.table[++i].idxTI].iddatatype;						//запомнить тип функции
				while (lex.lextable.table[i].lexema != LEX_RETURN)												//дойти по таблице лексем до ретурна
					i++;
				if (lex.lextable.table[i+1].idxTI!=TI_NULLIDX && lex.idtable.table[lex.lextable.table[++i].idxTI].iddatatype != typeoffunc)					//ссчитать тип ретурна
				{
					Error::adderr(704, lex.lextable.table[i].sn, err);											
					errflag = false;
					break;
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
			if (lex.lextable.table[i].lexema == LEX_FUNC)																				//поиск определения фунции
			{
				entry = lex.idtable.table[lex.lextable.table[++i].idxTI];																//элемент функции -> элемент entry
				forinsideloop = ++i;
			
				for (forinsideloop; forinsideloop < lex.lextable.size; forinsideloop++)													//цикл по ТЛ от индекса функции
				{
					if(lex.lextable.table[forinsideloop].idxTI!=TI_NULLIDX && lex.lextable.table[forinsideloop].lexema==LEX_ID)			//перебор все идентификаторов
						if (!strcmp(lex.idtable.table[lex.lextable.table[forinsideloop].idxTI].id, entry.id))							//если ид совпал с именем искомой функции, зн мы нашли вызов функции
						{
							forinsideloop += 2;																							//пропуск скобок
							int j = 0;
							while (j < entry.value.parmvalue)																			//пока не закончились параметры
							{
								if (lex.lextable.table[forinsideloop].idxTI!=TI_NULLIDX && lex.idtable.table[lex.lextable.table[forinsideloop].idxTI].iddatatype != entry.value.parmtype[j])
								{
									Error::adderr(705, lex.lextable.table[forinsideloop].sn, err);
									forinsideloop += 2;

									errflag = false;
									break;
								}
								else
								{
									j++; 
									forinsideloop += 2;
								}
							}
							
							if (lex.lextable.table[forinsideloop - 1].lexema != LEX_RIGHTHESIS)
							{
								Error::adderr(708, lex.lextable.table[forinsideloop].sn, err);
								errflag = false;
							}
						}


				}

			}



		}
		return errflag;
	}

	bool ValidParmSTDValue(LEX::Lex lex, Error::Errors& err)
	{
		bool errflag = true;
		for (int i = 0; i < 2;i++)								//перебор всех идентификатров
		{
			IT::Entry entry = lex.idtable.table[i];

			if (lex.idtable.table[i].idtype == IT::F)							//поиск функции
			{
				for (int j = 0; j < lex.lextable.size; j++)						//поиск лексемы с ид функции
				{
					
					if (lex.lextable.table[j].idxTI == i)						//нашли лексему
					{
						int numbofcurfunc = 0;
						int indinside = j+2;
						while (numbofcurfunc<entry.value.parmvalue)
						{
							if (lex.lextable.table[indinside].idxTI != TI_NULLIDX && lex.idtable.table[lex.lextable.table[indinside].idxTI].iddatatype != entry.value.parmtype[numbofcurfunc])
							{
								Error::adderr(705, lex.lextable.table[indinside].sn, err);
								errflag = false;
							}
							{
								 indinside+= 2;
								numbofcurfunc++;
							}


						}
						if (lex.lextable.table[indinside - 1].lexema != LEX_RIGHTHESIS)
						{
							Error::adderr(708, lex.lextable.table[indinside].sn, err);
							errflag = false;
						}
					}


				}



			}





		}
		return errflag;
	
	}
	bool Expressiondiaplayreturn(LEX::Lex lex, Error::Errors& err) 
	{
		bool errflag = true;
		for (int i = 0; i < lex.lextable.size; i++)
		{
			if (lex.lextable.table[i].lexema == LEX_DISPLAY || lex.lextable.table[i].lexema == LEX_RETURN)
			{
				if (lex.lextable.table[i + 2].lexema != LEX_SEMICOLON)
				{
					Error::adderr(709, lex.lextable.table[i].sn, err);
					errflag = false;
				}
			}
		}
		return errflag;	
	}

} 