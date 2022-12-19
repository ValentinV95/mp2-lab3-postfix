// объ€вление функций и классов дл€ вычислени€ арифметических выражений

#include <iostream>
#include "stack.h"
#include "vector"
#include "map"

using namespace std;

class Lexema
{
public:
	string lexema;
	Lexema();
	Lexema(string lxma);
	Lexema(char c);
	bool isOperation();
	bool isVariable();
	bool isConst();
	bool operator<(const Lexema& rhs) const noexcept;
};

class Operand : public Lexema
{
public:
	virtual double get_value() = 0;
};


class Const : public Operand
{
public:
	Const(Lexema _lexema);
	double get_value();
};


class Variable : public Operand
{
public:
	double get_value();
};

class ArithmeticExpression
{
private:
	string infix;
	vector <Lexema> postfix;
	vector <Lexema*> lexems;
	map<string, int> priority;
	map<Lexema, double> operands;
public:
	ArithmeticExpression(string infx);
	void ToPostfix();
	void Parse();
	string GetInfix() const;
	string GetPostfix() const;
	vector<Lexema> GetOperands() const;
	double Calculate(const map<Lexema, double>& values);
};