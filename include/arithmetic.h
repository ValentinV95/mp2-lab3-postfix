// объ€вление функций и классов дл€ вычислени€ арифметических выражений

#include <iostream>
#include "stack.h"
#include "vector"
#include "map"

using namespace std;

class Lexema
{
protected:
	string lexema;
public:
	Lexema::Lexema(string lxma) : lexema(lxma) {}
	Lexema::Lexema(char c) : lexema(1, c) {}
	Lexema::Lexema() : lexema("") {}
	virtual const bool isOperand() = 0;
	virtual string& get_lexema() = 0;
};

class Operation : public Lexema
{
public:
	Operation(string lxma) : Lexema(lxma) {}
	Operation(char c) : Lexema(c) {}
	virtual string& get_lexema()
	{
		return this->lexema;
	}
	virtual const bool isOperand()
	{
		return false;
	}
};

class Operand : public Lexema
{
public:
	Operand(string lxma) : Lexema(lxma) {}
	Operand(char c) : Lexema(c) {}
	virtual string& get_lexema() = 0;
	virtual const bool isOperand()
	{
		return true;
	}
	virtual const double get_value() = 0;
};


class Const : public Operand
{
public:
	Const(string lxma) : Operand(lxma) {}
	virtual const double get_value();
	virtual string& get_lexema()
	{
		return this->lexema;
	}
};


class Variable : public Operand
{
public:
	Variable(char c) : Operand(c) {}
	virtual string& get_lexema()
	{
		return this->lexema;
	}
	virtual const  double get_value()
	{
		return 0;
	}
};

class ArithmeticExpression
{
private:
	string infix;
	vector<Lexema*> postfix;
	vector <Lexema*> lexems;
	map<string, int> priority;
	map<string, double> operands;
public:
	ArithmeticExpression(string infx);
	void ToPostfix();
	void Parse();
	string GetInfix() const;
	string GetPostfix() const;
	vector<string> GetOperands() const;
	double Calculate(const map<string, double>& values);
};