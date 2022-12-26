#pragma once

#include <iostream>
#include <map>
#include <cmath>
#include <string>
#include "stack.h"

using std::string;

class TArithmetic
{
private:
	class Lexem
	{
	protected:
		string label;
		string lex;
		double value;

	public:
		const string Get() const;
		const double Value() const;
		const string what() const;
		virtual void SetValue(const string& val) = 0;
		virtual ~Lexem();
	};

	class Operation : public Lexem
	{
	private:
		void SetValue(const string& val) override;

	public:
		Operation(const char& data);
	};

	class Operand : public Lexem
	{
	protected:
		double toNumeric(const string& strlex);
	};

	class Constant : public Operand
	{
	private:
		void SetValue(const string& val) override;

	public:
		Constant(const string& data);
	};

	class Variable : public Operand
	{
	public:
		Variable(const string& data);
		void SetValue(const string& val) override;
	};

	string infix;
	Lexem** lexems;
	Lexem** postfix;

	bool find_operation(const char& tmplex);
	bool isDigit(const char& tmplex);
	bool isAlpha(const char& tmplex);

	const string find_error();
	void parser();
	void toPostfix();
	bool check_input(const string& inp);

	int lexems_count = 0;
	int operations_count = 0;
	int postfix_count = 0;

public:
	TArithmetic(const string& inf);
	const string GetPostfix() const;
	const double Calculate();
	~TArithmetic();

};
