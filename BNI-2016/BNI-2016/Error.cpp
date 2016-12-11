#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h" 
#include <string.h>
#include "Error.h"
#include <iostream>
#include <iomanip>

namespace Error
{
	//	серии ошибок:	0	-	99	-	системные ошибки
	//	100	-	109	-	ошибки парметров
	//	110	-	119	-	ошибки открытия и	чтения файлов
	//	120 -   200 -	ошибки лексическог анализа
	//  600 -   700 -   ошибки синтаксического анализа
	ERROR errors[ERROR_MAX_ENTRY] = //таблица ошибок
	{
		ERROR_ENTRY(0, "SYSTEM: Недопустимый код ошибки"), // код ошибки вне диапазона 0 - ERROR_MAX_ENTRY
		ERROR_ENTRY(1, "SYSTEM: Системный сбой"),
		ERROR_ENTRY(2, "SYSTEM: Недопустимое количество ошибок"),
		ERROR_ENTRY(3, "SYSTEM: "),
		ERROR_ENTRY_NODEF(4), ERROR_ENTRY_NODEF(5),
		ERROR_ENTRY_NODEF(6), ERROR_ENTRY_NODEF(7), ERROR_ENTRY_NODEF(8), ERROR_ENTRY_NODEF(9),
		ERROR_ENTRY_NODEF10(10), ERROR_ENTRY_NODEF10(20), ERROR_ENTRY_NODEF10(30), ERROR_ENTRY_NODEF10(40), ERROR_ENTRY_NODEF10(50),
		ERROR_ENTRY_NODEF10(60), ERROR_ENTRY_NODEF10(70), ERROR_ENTRY_NODEF10(80), ERROR_ENTRY_NODEF10(90),
		ERROR_ENTRY(100, "PARM: Параметр -in должен быть задан"),
		ERROR_ENTRY_NODEF(101), ERROR_ENTRY_NODEF(102),ERROR_ENTRY_NODEF(103),
		ERROR_ENTRY(104, "PARM: Превышена длина входного параметра"),
		ERROR_ENTRY(105, "PARM: Неизвестный параметр"),
		ERROR_ENTRY_NODEF(106), ERROR_ENTRY_NODEF(107),
		ERROR_ENTRY_NODEF(108), ERROR_ENTRY_NODEF(109),
		ERROR_ENTRY(110, "IN: Ошибка при открытии файла с исходным кодом (-in)"),
		ERROR_ENTRY(111, "IN: Недопустимый символ в исходном файле (-in)"),
		ERROR_ENTRY(112, "LOG: Ошибка при создании файла протокола(-log)"),
		ERROR_ENTRY(113, "LOG: Ошибка при создании файла с исходным кодом (-out)"),
		ERROR_ENTRY(114, "FST: Цепочка не разобрана"),
		ERROR_ENTRY(115,"IN: Отсуствует закрывающая кавычка"),
		ERROR_ENTRY(116, "IN: Недопустимая конструкция в файле исходного кода"),
		ERROR_ENTRY_NODEF(117), ERROR_ENTRY_NODEF(118), ERROR_ENTRY_NODEF(119),
		ERROR_ENTRY(120,"LA: Дублирование идентификатора"),
		ERROR_ENTRY(121, "LA: Нет функции main"),
		ERROR_ENTRY(122, "LA: Идентификатор не определен"),
		ERROR_ENTRY(123, "LA: Недопустимое объявление"),
		ERROR_ENTRY(124, "LA: Ошибка в лексическом анализе"),
		ERROR_ENTRY_NODEF(125),ERROR_ENTRY_NODEF(126),ERROR_ENTRY_NODEF(127),ERROR_ENTRY_NODEF(128),
		ERROR_ENTRY_NODEF(129),
		ERROR_ENTRY_NODEF10(130), ERROR_ENTRY_NODEF10(140), ERROR_ENTRY_NODEF10(150),
		ERROR_ENTRY_NODEF10(160), ERROR_ENTRY_NODEF10(170), ERROR_ENTRY_NODEF10(180), ERROR_ENTRY_NODEF10(190),
		ERROR_ENTRY_NODEF100(200), ERROR_ENTRY_NODEF100(300), ERROR_ENTRY_NODEF100(400), ERROR_ENTRY_NODEF100(500),
		ERROR_ENTRY(600, "Неверная структура программы"),
		ERROR_ENTRY(601, "Ошибочный оператор"),
		ERROR_ENTRY(602, "Ошибка в выражении"),
		ERROR_ENTRY(603, "Ошибка в параметрах функции"),
		ERROR_ENTRY(604, "Ошибка в параметрах вызываемой функции"),
		ERROR_ENTRY(605, "Ошибка знака в выражении"),
		ERROR_ENTRY(606, "CA: Ошибка в синтаксическом анализе"),

		ERROR_ENTRY_NODEF(607),ERROR_ENTRY_NODEF(608),ERROR_ENTRY_NODEF(609),
		ERROR_ENTRY_NODEF10(610),ERROR_ENTRY_NODEF10(620),ERROR_ENTRY_NODEF10(630),ERROR_ENTRY_NODEF10(640),
		ERROR_ENTRY_NODEF10(650),ERROR_ENTRY_NODEF10(660),ERROR_ENTRY_NODEF10(670),ERROR_ENTRY_NODEF10(680),
		ERROR_ENTRY_NODEF10(690),



		ERROR_ENTRY(700, "СмА: Ошибка в семантическом анализе"),
		ERROR_ENTRY(701, "СмА: Отсуствует главная функция"),
		ERROR_ENTRY(702, "СмА: Oшибочный тип операндов в выражении"),
		ERROR_ENTRY(703, "СмА: Попытка применить арифметическую операцию к строке"),
		ERROR_ENTRY(704, "CмА: Oшибочный тип возврата функции"),
		ERROR_ENTRY(705, "CмА: Неверный тип параметра"),
		ERROR_ENTRY(706, "CA: Ошибка в синтаксическом анализе"),
		ERROR_ENTRY(707, "CмА: Наличие нескольких главных функций"),
		ERROR_ENTRY_NODEF(708),ERROR_ENTRY_NODEF(709),
		ERROR_ENTRY_NODEF10(710),ERROR_ENTRY_NODEF10(720),ERROR_ENTRY_NODEF10(730),ERROR_ENTRY_NODEF10(740),
		ERROR_ENTRY_NODEF10(750),ERROR_ENTRY_NODEF10(760),ERROR_ENTRY_NODEF10(770),ERROR_ENTRY_NODEF10(780),
		ERROR_ENTRY_NODEF10(790),
		ERROR_ENTRY_NODEF100(800), ERROR_ENTRY_NODEF100(900)
	};

	ERROR geterror(int id) {
		if ((id > 0) && (id < ERROR_MAX_ENTRY)) {
			return errors[id];
		}
		else 
		{
			return errors[0];
		}
		
	}
	ERROR geterrorin(int id, int line = -1, int col = -1) {
		if ((id > 0) && (id < ERROR_MAX_ENTRY)) {
			errors[id].intext.line = line;
			errors[id].intext.col = col;
			return errors[id];	 
		}
		else {
			errors[0].intext.line = line;
			errors[0].intext.col = col;
			return errors[0];
		}
	}
	void adderr(int id, Errors& e)
	{
		if (e.size < ERRORS_MAX_SIZE)
			e.errors[e.size++] = ERROR_THROW(id)
		else throw ERROR_THROW(2);													//превышен лимит колв аошбиок 
	};
	void adderr(int id,int line, int pos,  Errors& e)
	{
		if (e.size < ERRORS_MAX_SIZE)
			e.errors[e.size++] = ERROR_THROW_IN(id, line, pos)
		else throw ERROR_THROW(2);
	};
	void adderr(int id, int line, Errors& e)
	{
		if (e.size < ERRORS_MAX_SIZE)
			e.errors[e.size++] = ERROR_THROW_IN(id, line,-1)
		else throw ERROR_THROW(2);
	};
	void printerr(Errors& e)
	{
		for (int i = 0; i < e.size; i++)
		{
			std::cout <<  "[id " << e.errors[i].id << ']'<< std::setw(1) << std::left <<" "<< e.errors[i].message
				<< " строка "<< e.errors[i].intext.line<< " позиция "
				<< e.errors[i].intext.col<< std::endl << std::endl;
		}
	}
};