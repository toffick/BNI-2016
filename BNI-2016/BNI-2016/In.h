#pragma once
#define IN_CHAIN_MAX_LEN 256
#define IN_MAX_CHAINS 2048
#define IN_UNARY_P	'+'
#define IN_UNARY_M	'-'
#define IN_N		'\n'
#include "Error.h"


//таблица проверки взодной информации, индекс = код (Windows 1251) символа
//значение IN::F - запрещенный символ, IN::T  - разрешенный символ,  IN::I - игнорировать(не вводить),
//		если 0<=значение <256 - то вводится данное значение
#define IN_CODE_TABLE {\
    IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::D, IN::D, IN::F, IN::F, IN::I, IN::F, IN::F, \
    IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, \
    IN::D, IN::S, IN::F, IN::F, IN::F, IN::S, IN::S, IN::Q, IN::S, IN::S, IN::S, IN::S, IN::S, IN::S, IN::S, IN::S/*47*/, \
    IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::S, IN::S, IN::S, IN::S, IN::S, IN::S/*63*/, \
    IN::S, IN::F/*A*/, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, \
    IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F/*Z*/, IN::S, IN::F, IN::S, IN::S, IN::F, \
    IN::F, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, \
    IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::S, IN::S, IN::S, IN::S, IN::F, \
    \
    IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::T, IN::F, IN::F, IN::I, IN::F, IN::F, \
    IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, \
    IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, \
    IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, \
    IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, \
    IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, \
    IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, \
    IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T \
    }


namespace In {
	struct IN{
		enum {Q=256,  D=512, T=1024, F=2048, I=4096, S=8192};		//Т - допустимыцй символ F - недопустимый I - игнор D - пробел/табуляция/\n S - сператор Q - кавычка S -  сепаратор 
		int size;							//размер исзодного кода
		int lines;							//кол-во строк
		int ignor;							//кол-во игнор символов	
		struct Chain
		{
			 char* chain;
			int line;
			Chain():chain(new char[IN_CHAIN_MAX_LEN]),line(0){};
		} *chains;

		int code[256]=IN_CODE_TABLE;														//таблица проврки

		IN() :size(0), lines(0), ignor(0), chains(new Chain[IN_MAX_CHAINS]) {}
	};
	IN getin(wchar_t infile[], Error::Errors&);												//ввести и прверить входной поток

};
