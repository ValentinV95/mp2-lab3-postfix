// объ€вление функций и классов дл€ вычислени€ арифметических выражений
#include <iostream>
#include <string>
#include "stack.h"
#include <map>
using std::map;
using std::string;

class Lexema {
private:
	string lexema;
public:
	Lexema(string _str);
	~Lexema();
	virtual bool IsOperand() = 0;
};
class Operand : public Lexema {
public:
	Operand(string _str);
	bool IsOperand();
	~Operand();
};
class Operation : public Lexema {
private:
	int priority;
	char name;
public:
	Operation(string _str, char _name);
	bool IsOperand();
	~Operation();
};
class Const : public Operand {
private:
	double value;
public:
	Const(string _str);
	~Const();
};
class Variable : public Operand {
private:
	char var;
	map <char,double> valOfvar;
public:
	Variable(string _str, char _var, map <char,double> _valOfvar);

	~Variable();
};
class Arithmetic_expression {
private:
	string infix;
	Lexema** lexems;
	Lexema** postfix;
	void Parse();
	void ToPostfix();
public:
	Arithmetic_expression(string expr);
	~Arithmetic_expression();
};
