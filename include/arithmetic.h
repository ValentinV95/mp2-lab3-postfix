// объ€вление функций и классов дл€ вычислени€ арифметических выражений

#include "../include/stack.h"
#include<map>
#include <cctype>
#include <algorithm>
#include<stdlib.h>
#include<math.h>
#include<iostream>
#include<string>
#include<exception>

using namespace std;

 class LEXEM
{
public:
	int type=0;						// 1-constant, 2-variable, 3-operation , type -1 "("  , type -2 ")"
	string lexem_m;
	string alter_lexem_m;

	virtual char get_char_op() = 0;
	virtual bool isOperation() = 0;
	virtual bool isOperand() = 0;
	virtual double get_double() = 0;
	virtual int get_priority() = 0;
	virtual void shop(bool alternative) = 0;

	string show();

	string get_lexem_m() { return lexem_m; }
	string get_alter_lexem_m() { return alter_lexem_m; }
	int get_type() { return type; }
};



 class Operation : public LEXEM
 {
 public:
	 char lexem_Op;
	 int priority = 10;

	 bool isOperation() { return 1; };
	 bool isOperand() {return 0;}
	 int get_priority() { return priority; }
	 char get_char_op() { return lexem_Op; }
	 double get_double() { return 0.0; }

	 Operation();
	 Operation(char a);
	 void shop(bool alternative);
	  
 };



 class Operand : public LEXEM
 {
 public:
	 bool isOperation() { return 0; };
	 bool isOperand() { return 1; }

 };



 class Const : public Operand
 {
 public:
	 double lexem_const = 0;

	 Const();
	 Const(Tstack<char>& a, Tstack<char>& save_const, int znak, bool alternative);

	 int  get_priority() { return 0; }
	 char get_char_op() { return '0'; }
	 void shop(bool alternative);
	 double get_double() { return lexem_const; }

 };



 class Var : public Operand
 {
 public:
	 char lexem_var;
	 int var_znak = 1;
	 Var();
	 Var(char var, int znak, bool alternative);

	 int get_priority() { return 0; }
	 char get_char_op() { return lexem_var; }
	 double get_double() { return var_znak; }
	 void shop(bool alternative);

 };



 string without_spaces(string infix);
 int get_priority_outside(char a);
 bool choice();

 

class TPostfix
{

public:
	int secret_operations=0;
	int infix_len;
	int c_k1, c_k2;   // number of '(' and ')'
	LEXEM** mas;
	LEXEM** postfix_mas;     // postfix form has no "()"
	int L_Size=0;
	int true_size = 0;
	map<char, double> vars;

	TPostfix(string infix,bool alternative,bool test);

	
	void search(string infix,bool alternative,bool test);
	void to_postfix_form(bool alternative, bool test);
	void checked_infix(bool alternative);
	double calculation(bool test);
	void get_full_information(bool alternative);
	void get_quick_info(bool alternative);


	int get_infix_len() { return infix_len; }
	int get_c_k1() { return c_k1; }
	int get_c_k2() { return c_k2; }
	int get_true_size() { return true_size; }
	int get_L_Size() { return L_Size; }


	~TPostfix()
	{
		delete[] mas;		
	}

};