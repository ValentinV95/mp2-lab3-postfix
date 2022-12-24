// объ€вление функций и классов дл€ вычислени€ арифметических выражений
#include"stack.h"
#include<iostream>
#include<string>
#include<map>
#include<vector>

class Lexem
{
protected:
	int startPos = -1;
	int endPos = -1;
public:

	Lexem() = default;

	Lexem(int startPos, int endPos)
	{
		this->startPos = startPos;
		this->endPos = endPos;
	}

	~Lexem() = default;

	virtual string show() = 0;

	virtual bool isOperand() = 0;

	int getStartPos() 
	{ 
		return this->startPos; 
	}

	int getEndPos() 
	{ 
		return this->endPos; 
	}
};

class Operation : public Lexem
{
private:
	char opName;
public:
	Operation(char opName, int startPos, int endPos) :Lexem(startPos, endPos), opName(opName) {}

	~Operation() = default;

	bool isOperand() 
	{ 
		return false; 
	}

	const int getPriority()
	{
		if (opName == '~')
		{
			return 3;
		}
		if (opName == '/' || opName == '*')
		{
			return 2;
		}
		if (opName == '+' || opName == '-')
		{
			return 1;
		}
		return 0;
	}

	string show() 
	{ 
		return string(1, opName); 
	}
};

class Operand : public Lexem
{
public:
	Operand(int startPos, int endPos) :Lexem(startPos, endPos) {}

	~Operand() = default;

	bool isOperand() 
	{ 
		return true; 
	}

	virtual const double getValue() = 0;
};

class Var : public Operand
{
private:
	char name;
	map<char, double>& values;
public:
	Var(char name, map<char, double>& values, int startPos, int endPos)
		:Operand(startPos, endPos), name(name), values(values) {}

	~Var() = default;

	const double getValue() 
	{ 
		return values[name]; 
	}

	string show() 
	{ 
		return string(1, name); 
	}
};

class Const : public Operand
{
private:
	string str;
	double value;
public:
	Const(string s, double val, int startPos, int endPos)
		:Operand(startPos, endPos), str(s), value(val) {}

	~Const() = default;

	const double getValue() 
	{ 
		return value; 
	}

	string show() 
	{ 
		return str; 
	}
};

class Postfix
{
private:

	string input;
	vector<Lexem*> lexems;
	vector<Lexem*> postfix;

	bool isConverted = false;

	map<char, double> values;

	double stringToDouble(string num, string pow);

	void parse();

	void orderCheck();

	void toPostfix();

	Operand* performCalculations(Operation* op, Operand* first, Operand* second);

	double calculate();

public:
	Postfix(string expression) :input(expression) 
	{ 
		parse(); 
		orderCheck(); 
	}

	~Postfix()
	{
		for (size_t i = 0; i < lexems.size(); i++)
		{
			delete lexems[i];
		}
	}

	void convertToPostfix()
	{
		toPostfix();
		isConverted = true;
	}

	double getRes()
	{
		if (isConverted)
		{
			return calculate();
		}
		else
		{
			throw exception("Can`t calculate expression without convertation");
		}
	}

	string getPostfix()
	{
		string res;
		for(auto& lexem: postfix)
		{
			res += lexem->show();
		}
		return res;
	}
};