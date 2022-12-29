// объ€вление функций и классов дл€ вычислени€ арифметических выражений
#include "stack.h"
#include <map>
#include <string>
#include <iostream>
using std::map;
using std::string;

class Lexema {
protected:

public:
	string lexema;
	Lexema(string _str);
	~Lexema();
	virtual void show() = 0;
	virtual int Priority() = 0;
	virtual string NameOfClass() = 0;
	virtual void Inicialize(double val) = 0;
	virtual void Calculate(TStack <double>& Stk);
};
class Operand : public Lexema {
public:
	Operand(string _str);
	void show() override;
	int Priority() override;
	~Operand();
	string NameOfClass() override;
	void Inicialize(double val) override;
	void Calculate(TStack <double>& Stk) override;
};
class Operation : public Lexema {
protected:
	int priority;
public:
	Operation(char _str);
	void show() override;
	~Operation();
	int Priority() override;
	string NameOfClass() override;
	void Inicialize(double val) override;
	void Calculate(TStack <double>& Stk) override;
};
class Const : public Operand {
private:
	double value;
public:
	Const(string _str);
	void Inicialize(double val) override;
	void Calculate(TStack <double>& Stk) override;
	~Const();
};
class Variable : public Operand {
private:
	char var;
	double value;
public:
	Variable(char _str);
	void Inicialize(double val) override;
	void Calculate(TStack <double>& Stk) override;
	~Variable();
};
class Arithmetic_expression {
private:
	string infix;
	Lexema** lexems;
	Lexema** postfix;
	size_t size;
	size_t size_postfix;
	void Parse();
	void ToPostfix();
public:
	Arithmetic_expression(string expr);
	~Arithmetic_expression();
	void show_postfix();
	bool IsOperation(char symb);
	void Input();
	double Calculate();
	void show();
};
