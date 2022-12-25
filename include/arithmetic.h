// объ€вление функций и классов дл€ вычислени€ арифметических выражений
#pragma once
#include <string>
#include <map>
#include <vector>
#include <set>
#include <math.h>
#include <cmath>
#include <functional>
#include <stdio.h>
#include <iostream>

#define DELIMITER '.'

using namespace std;

class TPostfixException :public exception
{
	const pair<int, int> pos;
public:
	TPostfixException(const char *message,pair<int,int> pos):exception(message), pos(pos) {}
	TPostfixException(char* message,int pos):exception(message),pos(make_pair(pos,pos)) {}

	string what()
	{
		if (pos.first == pos.second)
			return "Something went wrong, position of mistake " + to_string(pos.first) + "\n" + exception::what();
		else
			return "Something went wrong, range of mistake " + to_string(pos.first+1)+" "+to_string(pos.second+1)+"\n" + exception::what();
	}

	pair<int, int> GetPos() { return pos; }
};

class Lexeme
{
	const pair<int, int> pos;
public:
	Lexeme(pair<int, int> pos):pos(pos) {}
	pair<int, int> GetPos() { return pos; }

	virtual const bool isOperation() const noexcept = 0;
	virtual const string GetName() const = 0;
};

class Operation :public Lexeme
{
	const string name;
public:
	Operation(string _name, pair<int, int> pos):Lexeme(pos),name(_name){}
	const bool isOperation() const noexcept override { return true; }
	const string GetName() const { return name; }
};

class Operand :public Lexeme
{
public:
	Operand(pair<int, int> pos):Lexeme(pos){}
	const bool isOperation() const noexcept override { return false; }
	virtual double GetValue() const = 0;
};

class Variable :public Operand
{
	const string name;
	map<string, double> &var_map;
public:
	Variable(string _name ,map<string, double>& variables, pair<int, int> pos):Operand(pos),name(_name), var_map(variables) {};

	double GetValue() const override 
	{ 
		if (name == "e") return 2.7182818284;
		if (name == "pi") return 3.141592653589793;

		return var_map[name]; 
	}
	const string GetName() const override { return name; }
};

class Constant :public Operand
{
	const double value;
	const string name;
public:
	Constant(double value,string name,pair<int, int> pos):Operand(pos), value(value),name(name) {}

	double GetValue() const noexcept override { return value; }
	const string GetName() const override{ return name; }
};

class TPostfix
{
private:
	string infix;
	map<string, std::function<double(double x)>> funcs;
	map<string, std::function<double (double x, double y)>> ops;

	vector<Lexeme*> postfix;
	map<string, double> variable_map;

	Lexeme* CreateLexeme(string str, int start, int stop);

	double GetNum(string num);
	double StrToNum(string str);
	unsigned int GetPriority(Operation op);

	void Parse();
	void ToPostfix();
public:
	TPostfix(const string& str);

	void SetInfix(const string& str);

	string GetInfixStr() const;

	string GetPostfixStr() const;

	double Calculate();

	static void ShowInfo();

	~TPostfix();
};