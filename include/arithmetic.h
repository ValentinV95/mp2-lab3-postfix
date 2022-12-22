// объ€вление функций и классов дл€ вычислени€ арифметических выражений

#include <exception>
#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <sstream>
#include <exception>

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::map;
using std::invalid_argument;
using std::out_of_range;
using std::exception;
using std::to_string;


class Lexem
{
public:
	virtual string show() = 0;

};

class Operand:public Lexem
{};

class Var :public Operand
{
public:
	string value;
	Var(char str)
	{
		value = str;
	}
	string show()
	{

		return value;
	}
};

class Value :public Operand
{
public:
	string value;
	Value(string dbl)
	{
		value = dbl;
	}
	string show()
	{
		return value;
	}
};

class Operation :public Lexem
{
public:
	string value;
	Operation(char c)
	{
		value = c;
	}
	string show()
	{
		return value;
	}
};

class TPostfix
{
private:
	string infix = "NULL";
	Lexem** postfix = nullptr;
	size_t size;
	map<char,double> vars;
public:
	TPostfix(string str);
	void to_postfix();
	string showP();
	void set_infix(string infx);
	void infix_check();

	size_t get_size();



	double CALCULATE();
};
