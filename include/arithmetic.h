// объ€вление функций и классов дл€ вычислени€ арифметических выражений
#include <string>
#include "stack.h"
#include <map>
using std::string;
class Lexema {
private:
	string lexem;
public:
	Lexema(string _str);
	~Lexema();
	virtual bool IsOperand() = 0;
};
class Operand : public Lexema {
public:
	Operand(string _str) : Lexema(_str);
	bool IsOperand() {};
	~Operand();
};
class Operation : public Lexema {
private:
	int priority;
public:
	Operation(string _str) : Lexema(_str);
	bool IsOperand() {};
	~Operation();
};
class Const : public Operand {
private:
	double value;
public:
	Const(string _str) : Operand(_str);
	~Const();
};
class Variable : public Operand {
private:
	char var;
public:
	Variable(string _str) : Operand(_str);
};
class Arithmetic_expression {
private:
	string infix;
	Lexema** lexems;
	Lexema** postfix;
	void Parse() {};
	void ToPostfix() {};
public:
	Arithmetic_expression(string expr) : infix(expr);
	~Arithmetic_expression();
};
