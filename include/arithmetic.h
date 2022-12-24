#ifndef __ARITHMETIC_H__
#define __ARITHMETIC_H__
#include <vector>
#include "stack.h"
#include <string>
using namespace std;

class Lexem
{
protected:
	string type;
	string data;
	int priority;
	double num;


public:
	const string GetData() const;
	const string GetType() const;
	const int GetPriority() const;
	const double GetNum() const;
	virtual void SetPriority(const string& s) = 0;
	void SetNum(const double d);
};


class Operation : public Lexem
{
private:
	void SetPriority(const string& s) override;

public:
	Operation(const string& s);

};


class Num : public Lexem
{
private:
	void StrToNum(const string& s);
	void SetPriority(const string& s) override;

public:
	Num(const string& s);

};


class Var :public Lexem
{
private:
	void SetPriority(const string& s) override;


public:

	Var(const string& s);

};





class TPostfix
{
private:
	string infix;
	string postfix;
	vector<Lexem*> infix_lexems;
	vector<Lexem*> postfix_lexems;

	int postfix_lexem_count;
	int op_count = 0;
	int lex_count = 0;

	int error_pointer;

	void parse();
	void InfixToPostfix();
	void check();
	const double Calculate();

	bool IsOperation(const char& c);
	bool IsNum(const char& c);
	bool IsVar(const char& c);



public:
	TPostfix(string inf);
	const string GetPostfix() const;

	~TPostfix();

};



#endif 

