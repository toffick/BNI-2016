#pragma once

#include "IT.h"
#include "LT.h"
#include "Log.h"
#include "FST.h"

namespace LEX
{
	struct Lex                 // ��������� ���������� ������ ������������ �����������
	{
		LT::LexTable lextable;   // ������� ������
		IT::IdTable  idtable;    // ������� ��������������

		Lex()
			: lextable(LT::Create(LT_MAXSIZE)), idtable(IT::Create(IT_MAXSIZE))
		{

		};
	};

	void newLexem(int line, char lex, Lex& lexer);                // ������������ ������ ��� ��
	void newId(char* prefix, char* name, IT::Entry& itEntry, Error::Errors& ers, Lex& lex);

	void newVariable(char* prefix, char* name, IT::Entry& itEntry, Error::Errors& ers, Lex& lex);
	void newFunction(char* prefix, char* name, IT::Entry& itEntry, Error::Errors& ers, Lex& lex);
	void newParameter(char* prefix, char* name, IT::Entry& itEntry, Error::Errors& ers, Lex& lex);
	void newLiteral(char* prefix, char* name, IT::Entry& itEntry, Error::Errors& ers, Lex& lex);
	void newOperator(char* prefix, char* name, IT::Entry& itEntry, Error::Errors& ers, Lex& lex);

	void handleId(FST::FST& fst, Error::Errors& ers, Lex& lex);   // ������������ ������ ��� ��

	Lex LexicalAnalysis(In::IN& in, Error::Errors& ers);  // ������ ���������� ������
};