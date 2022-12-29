// объ€вление функций и классов дл€ вычислени€ арифметических выражений
#pragma once
#include <iostream>
#include "stack.h"
#include <vector>
#include <string>
#include <map>

class Lexem
{
protected:
	char lex;
public:
	virtual char show() = 0;
	virtual bool isOperation() = 0;
};

class Operation : public Lexem
{
private:
	size_t priority;                                         // контроль 0-3
public:
	Operation(char opn);
	Operation(const Operation& op);
	char show();
	size_t getPrior();
	bool isOperation();
};

class Operand : public Lexem
{
public:
	Operand();                                   
	Operand(char opd);
	bool isOperation();                              
	virtual bool isVar() = 0;
	char show();
};

class Variable : public Operand
{
public:
	Variable(char var);
    char show();                                       
	bool isVar();
};

class Const : public Operand
{
private:
	double value;
public:
	Const(char num);
	char show();
	double getValue();
	bool isVar();
};

class Arithmetic 
{
private:
	string expression;
	vector <Lexem*> infix;
	vector <Lexem*> postfix;
	map <char, double> val_map;
	void setVarValues();
	void parse();
public:
	Arithmetic(string expr);
	void toPostfix();
	void showPostfix();
	double calculate();
};