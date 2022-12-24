// объ€вление функций и классов дл€ вычислени€ арифметических выражений


#pragma once

#include <iostream>
#include <map>
#include <cmath>
#include <string>
#include "stack.h"

using std::string;

class Arithmetic
{
private:
	class Lexem
	{
	protected:
		string name;
		string lexem;
		double priority;

	public:
		const string GetLexem() const;
		const double Value() const;
		const string Type() const;
		virtual void SetPriority(const string& val) = 0;
		virtual ~Lexem();
	};

	class Operation : public Lexem
	{
	private:
		void SetPriority(const string& val) override;

	public:
		Operation(const char& data);
	};

	class Operand : public Lexem
	{
	protected:
		double Convert(const string& strlexem);
	};

	class Constant : public Operand
	{
	private:
		void SetPriority(const string& val) override;

	public:
		Constant(const string& data);
	};

	class Variable : public Operand
	{
	public:
		Variable(const string& data);
		void SetPriority(const string& val) override;
	};

	string infix;
	Lexem** lexemems;
	Lexem** postfix;

	bool FindOperation(const char& tmplexem);
	bool isDigit(const char& tmplexem);
	bool isLetter(const char& tmplexem);

	const string FindError();
	void Parser();
	void toPostfix();
	bool CheckInput(const string& inp);

	int lexemems_count = 0;
	int operations_count = 0;
	int postfix_count = 0;

public:
	Arithmetic(const string& inf);
	const string GetPostfix() const;
	const double Calculate();
	~Arithmetic();

};