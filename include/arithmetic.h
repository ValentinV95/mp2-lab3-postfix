// объ€вление функций и классов дл€ вычислени€ арифметических выражений
#include "stack.h"
#include <map>
#include <string>
#include <iostream>
using std::map;
using std::string;

class Lexema {
protected:
	string lexema;
public:
	Lexema(string _str);
	~Lexema();
	virtual void show() = 0;
};
class Operand : public Lexema {
public:
	Operand(string _str);
	void show() override;
	~Operand();
};
class Operation : public Lexema {
protected:

public:
	int priority;
	Operation(char _str);
	void show() override;
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
	map <char, double> valOfvar;
public:
	Variable(char _str);
	~Variable();
};
class Arithmetic_expression {
private:
	string infix;
	Lexema** lexems;
	Lexema** postfix;
	size_t size;
	void Parse();
	void ToPostfix();
public:
	Arithmetic_expression(string expr);
	~Arithmetic_expression();
	bool IsOperation(char symb);
	void show();
};
