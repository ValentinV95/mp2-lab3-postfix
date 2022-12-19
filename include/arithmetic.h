// объ€вление функций и классов дл€ вычислени€ арифметических выражений

#include <string>
#include <iostream>
#include <map>
#include <sstream>
using std::string;
using std::cout;
using std::map;


using std::invalid_argument;


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
	double value;
	Value(double dbl)
	{
		value = dbl;
	}
	string show()
	{
		std::ostringstream strs;
		strs << value;
		std::string str = strs.str();
		return str;
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
	string infix;
	Lexem** postfix;
	size_t size;
	map<char,double> vars;
public:
	TPostfix(string str);
	void to_postfix();
	void showP();


	size_t get_size();



	double CALCULATE();
};
