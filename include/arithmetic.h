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
	int size_for_postfix = 0;
	int postfix_size = 0;
	int type;						// 1-constant, 2-variable, 3-operation , type -1 "("  , type -2 ")"
	string lexem_m;

	virtual char get_char_op() = 0;
	virtual bool isOperation() = 0;
	virtual bool isOperand() = 0;
	virtual double get_double() = 0;
	virtual int get_priority() = 0;
	virtual void shop() = 0;

	string show();

	string get_lexem_m() { return lexem_m; }
	int get_type() { return type; }
	int get_size_for_postfix() { return size_for_postfix; }
	int get_postfix_size() { return postfix_size; }
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
	 void shop();
	  
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
	 Const(Tstack<char>& a, Tstack<char>& save_const, int znak);

	 int  get_priority() { return 0; }
	 char get_char_op() { return '0'; }
	 void shop();
	 double get_double() { return lexem_const; }

 };



 class Var : public Operand
 {
 public:
	 char lexem_var;
	 int var_znak = 1;
	 Var();
	 Var(char var, int znak);

	 int get_priority() { return 0; }
	 char get_char_op() { return lexem_var; }
	 double get_double() { return var_znak; }
	 void shop();

 };



 string without_spaces(string infix);
 int get_priority_outside(char a);

 

class TPostfix
{

public:
	int infix_len;
	int c_k1, c_k2;   // number of '(' and ')'
	LEXEM** mas;
	LEXEM** postfix_mas;     // postfix form has no "()"
	int L_Size=0;
	int true_size = 0;
	map<char, double> vars;

	TPostfix(string infix);

	
	void search(string infix);
	void to_postfix_form();
	void checked_infix();
	void calculation();
};