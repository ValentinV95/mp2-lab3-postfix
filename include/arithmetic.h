//Объявление  библиотек

#include <string>
#include <iostream>
#include <math.h>
#include <locale>
#include <map>
#include <ostream>






//Реализуемые классы

class Lex
{
protected:
	std::string name;
	std::string lexem;
	double double_spot;
	int pr;
//Открытые классы
public:
	std::string LexType();
	std::string GetLex();
	virtual void SetPrior(char op) = 0;
	int GetPrior();
	double value();
};

class operations :public Lex
{
protected:
	void SetPrior(char op) override;
public:
	operations(char op);
};

class operands : public Lex
{
protected:
	double NumConv(std::string strlex);
public:
	void SetPrior(char op);
};
class Num : public operands
{
public:
	Num(std::string lex);
	Num(double value);
	Num();
};
class Var : public operands
{
public:
	Var(std::string lex);
};

class Arithmetic
{
//Приватные классы
private:
	std::string infix;
	int size;
	int postfix_size;
	int lex_size = -1;
	Lex** lexem = nullptr;
	Lex** postfix = nullptr;

	bool IsOperation(char v);
	bool CheckOp();
	bool IsOperand(const char& lexem);
	bool IsDigit(const char& ch);
	bool IsNumber(std::string num);
	bool IsVar(const char& ch);
	bool IsVariable(std::string num);
	void CheckBrackets();
	bool IsBrackets(const char& ch);


	void resize();

	void IncorrectSymbols();
	void VarValue();

	void Postfix();
	void Parser();

//Открытые классы
public:
	Arithmetic(std::string arithmetic);
	double Calculate();
	~Arithmetic();
};






