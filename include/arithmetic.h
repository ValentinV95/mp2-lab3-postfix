// объ€вление функций и классов дл€ вычислени€ арифметических выражений

#include <iostream>
#include <stack.h>
#include<string>
#include<math.h>
#include<map>

using namespace std;

class Lexema
{
protected:
	int _size_for_postfix = 0;
	int _postfix_size = 0;
	string _type;
	string _lexem_m;
	bool isOperation;
public:
	virtual void SetVal(string val) { _lexem_m = val; }
	string GetLexeme() { return _lexem_m; }
	string GetType() { return _type; }
	int GetLexSz() { return _lexem_m.size(); }
	int GetSizeFPST() { return _size_for_postfix; }
	int GetPstSize() { return _postfix_size; }

	string show();


	virtual void _print() { cout << " " << _lexem_m; }
	virtual bool IsOperation() { return 0; }
	virtual double GetValue() { return 0.0; }
	virtual int GetPriority() { return 0; }
	virtual char GetOperation() { return '0'; }
};


class Operation : public Lexema
{
private:
	char Operation_name;
	short int Priority;
public:
	bool isOperation() { return 1; }
	int GetPriority() { return Priority; }
	char GetOperation() { return Operation_name; }

	Operation();
	Operation(char op);
	void _print() { cout << Operation_name; }
};

//операнды:
class _Operand : public Lexema
{
public:
	bool isOperation() { return 0; }
};

class _Constant : public _Operand
{
private:
	double Value;
public:
	_Constant();
	_Constant(TStack<char>& a, int znak);

	void _print() { cout << Value; }

	double GetValue() { return Value; }

};

class _Variable : public _Operand
{
protected:
	char _Var;
	int sign;
public:
	_Variable();
	_Variable(char var, int sign);
	char _GetOperation() { return _Var; }
};

class TPostfix
{
private:
	Lexema** mas;
	Lexema** postfix;
	string _pstfx;
	int postfix_size;
public:
	int L_Size = 0;
	int true_size = 0;
	map<char, double> vars;

	TPostfix(string infix);
	string _GetPostfix() { return _pstfx; }


	void search(string infix);
	double Calculate();
};