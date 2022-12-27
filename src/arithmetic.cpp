// реализация функций и классов для вычисления арифметических выражений
#include "arithmetic.h"


Lexema::Lexema(string _str) {
	string lexema = _str;
}

Lexema::~Lexema() {}

Operand::Operand(string _str):Lexema(_str){}
Operand::~Operand() {}

bool Operand::IsOperand() {
	return true;
}

Operation::Operation(string _str, char _name) : Lexema(_str), name(_name) {
	if(_name == '~')
		priority = 1;
	if(_name == '*' || _name == '/')
		priority = 2;
	if (_name == '+' || _name == '-')
		priority = 3;
}

bool Operation::IsOperand() {
	return false;
}

Operation::~Operation() {}

Const::Const(string _str) : Operand(_str) {
	int pow = 10;
	int i = 0;
	value = int(_str[i]) - 48;
	int i = 1;
	for (; i < _str.size() && _str[i] != ','; i++) {
		if (int(_str[i]) >= 48 && int(_str[i]) <= 57)
		{
			value = value * pow + (int(_str[i]) - 48);
		}
	}
	i++;
	for (; i < _str.size(); i++) {
		if (int(_str[i]) >= 48 && int(_str[i]) <= 57)
		{
			value = value + (int(_str[i]) - 48) / pow;
			pow = pow * 10;
		}
	}

}

Const::~Const() {}

Variable::Variable(string _str, char _var, map <char, double> _valOfvar) : Operand(_str), var(_var), valOfvar(_valOfvar) {}

Variable::~Variable() {}

Arithmetic_expression::Arithmetic_expression(string expr) : infix(expr) {
	Lexema** lexems = new Lexema * [expr.size()];
	Lexema** postfix = new Lexema * [expr.size()];
	void Parse();
};

Arithmetic_expression::~Arithmetic_expression() {}

void Arithmetic_expression::Parse() {
	string operand;
	int brackets = 0;
	for (int i = 0; i < infix.size(); i++) {
		if ((infix[i] >= 48 && infix[i] <= 57) || (infix[i] = ',')) {
			int points = 0;
			while ((infix[i] >= 48 && infix[i] <= 57) || (infix[i] = ',')) {
				if (infix[i] = ',') points++;
				else {
					postfix[i] = new Operand(operand);
				}
				i++;
			}
		}
		if (infix[i] >= 97 && infix[i] <= 122) {
			infix[i] = new Variable(var);
		}
	}
}