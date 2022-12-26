#include <string>
#include <iostream>
#include <math.h>
#include <locale>
#include <map>
#include <ostream>

class Lex
{
protected:
	std::string name;
	std::string lexem;
	double double_spot;
	int pr;

public:
	std::string LexType();//vozvrashaet tip lexem
	std::string GetLex();//vozvrashaet lexem
	virtual void SetPrior(char op) = 0;
	int GetPrior();
	double value();
};

class operations :public Lex
{
protected:
	void SetPrior(char op) override;//prioretet operaciy + - prior 1; * / prior =2 ;~ prior 3
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
private:
	std::string infix;
	int size;//videlyaemaya pamyat'
	int postfix_size;//kol-vo elem v postfix'e
	int lex_size = -1;//kol-vo elem v lexem 
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
	//void CorrectOrder();

	void resize();

	void IncorrectSymbols();
	void VarValue();

	void Postfix();
	void Parser();

public:
	Arithmetic(std::string arithmetic);
	double Calculate();
	~Arithmetic();
};
