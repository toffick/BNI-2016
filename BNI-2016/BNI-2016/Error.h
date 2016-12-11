#pragma once
#define ERRORS_MAX_SIZE 10
#define ERROR_ADD(id)
#define ERROR_THROW(id) Error::geterror(id);  //throw  ERROR_THROW(id)
#define ERROR_THROW_IN(id, l, c) Error::geterrorin(id,l,c); //throw ERROR_THROW(id, строка, колонка)
#define ERROR_ENTRY(id,m) {id, m, {-1,-1}}				//элемент таблицы ошибок
#define ERROR_MAXSIZE_MESSAGE 200						//максимальная длина сообщения обшибке
#define ERROR_ENTRY_NODEF(id) ERROR_ENTRY(-id,"Неопределенная ошибка")  //1 неопределенная элемент таблицы ошибок
//10 неопределенных элементов таблицы ошибок
#define ERROR_ENTRY_NODEF10(id)   ERROR_ENTRY_NODEF(id+0),ERROR_ENTRY_NODEF(id+1),ERROR_ENTRY_NODEF(id+2),ERROR_ENTRY_NODEF(id+3), \
								  ERROR_ENTRY_NODEF(id+4),ERROR_ENTRY_NODEF(id+5),ERROR_ENTRY_NODEF(id+6),ERROR_ENTRY_NODEF(id+7), \
								  ERROR_ENTRY_NODEF(id+8),ERROR_ENTRY_NODEF(id+9)
//100 неопределенных элементов таблицы ошибок
#define ERROR_ENTRY_NODEF100(id) ERROR_ENTRY_NODEF10(id+0),ERROR_ENTRY_NODEF10(id+10),ERROR_ENTRY_NODEF10(id+20),ERROR_ENTRY_NODEF10(id+30),\
							     ERROR_ENTRY_NODEF10(id+40),ERROR_ENTRY_NODEF10(id+50),ERROR_ENTRY_NODEF10(id+60),ERROR_ENTRY_NODEF10(id+70),\
								 ERROR_ENTRY_NODEF10(id+80),ERROR_ENTRY_NODEF10(id+90)
#define ERROR_MAX_ENTRY 1000

namespace Error
{
	struct ERROR				//типы исключения для throw ERROR_THROW | ERROR_THROW_IN и catch(ERROR)
	{
		int id;										//код ошибки
		char message[ERROR_MAXSIZE_MESSAGE];		//сообщение об ошибке
		struct IN									//расширение для ошибок при обработке входных данных
		{
			short line;						       //номер строки (0,1,2,3,...)
			short col;								//номер столбца (0,1,2,3,...)
		}intext;
	};
	struct Errors																	  // все ошибки, возникшие в течение компиляции программы
	{
		int    size;																  // число ошибок
		ERROR* errors;																  // массив ошибок
		Errors(): size(0), errors(new ERROR[ERRORS_MAX_SIZE]){};
	};

	void adderr(int, Errors& );														 // добавить ошибку
	void adderr(int, int line , Errors&);
	void adderr(int id, int line, int pos, Errors& ErrArr);
	void printerr(Errors&);
	ERROR geterror(int id);															//cформировать ERROR для ERROR_THROW 
																//cформировать ERROR для ERROR_THROW 

	ERROR geterrorin(int id, int line, int col);									//сформировать ERROR для ERROR_THROW_IN

}