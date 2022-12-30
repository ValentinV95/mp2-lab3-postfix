// реализация функций и классов для вычисления арифметических выражений
#include "arithmetic.h"
#include "stack.h"
using namespace std;

Lexema::Lexema(string _str) {
	lexema = _str;
}

Lexema::~Lexema() {}

Operand::Operand(string _str) :Lexema(_str) {}
Operand::~Operand() {}

void Operand::show(){
	cout << lexema;
 }

int Operand::Priority() {
	throw exception("operand has not priority");
	return 0;
}

string Operand::NameOfClass() {
	return "Operand";
}

Operation::Operation(char _str) : Lexema(&_str) {
	if (_str == '~')
		priority = 1;
	if (_str == '*' || _str == '/')
		priority = 2;
	if (_str == '+' || _str == '-')
		priority = 3;
	if ((_str == '(') || (_str == ')'))
		priority = 4;
}

void Operation::Calculate(TStack <double> &Stk) {

	double left, right;
	right = Stk.Pop();

	if (lexema == "~") {
		Stk.Push((-1) * right);
	}
	else if (lexema == "*") {
		left = Stk.Pop();
		Stk.Push(left * right);
	}
	else if (lexema == "/") {
		left = Stk.Pop();
		Stk.Push(left/right);
	}
	else if (lexema == "-") {
		left = Stk.Pop();
		Stk.Push(left - right);
	}
	else if (lexema == "+") {
		left = Stk.Pop();
		Stk.Push(left + right);
	}

}

int Operation::Priority() {
	return priority;
}

string Operation::NameOfClass() {
	return "Operation";
}

void Operation::show() {
	cout << lexema;
}

Operation::~Operation() {}

Const::Const(string _str) : Operand(_str) {

	int i = 0;
	int pow = 10;
	value = int(_str[0]) - 48;

	for(i = 1;i<_str.size() && _str!=",";i++) {
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

void Const::Calculate(TStack <double>& Stk) {
	Stk.Push(value);
}

Const::~Const() {}

Variable::Variable(char _str) : Operand(&_str) {}

void Variable::Calculate(TStack <double>& Stk){
	Stk.Push(value);
}


void Variable::Inicialize(double val) {
	value = val;
}

Variable::~Variable() {}

Arithmetic_expression::Arithmetic_expression(string expr) : infix(expr) {
	size = expr.size();
	size_postfix = size;
	lexems = new Lexema * [size];
	postfix = new Lexema * [size];
	Parse();
	ToPostfix();
};


bool Arithmetic_expression::IsOperation(char symb) {
	if ((symb == '+') || (symb == '-') || (symb == '*') || (symb == '/')|| (symb == ')') || (symb == '('))
		return true;
	else return false;
}

Arithmetic_expression::~Arithmetic_expression() {}

void Arithmetic_expression::Parse() {

	int j = 0;
	int brackets_count = 0;

	for (int i = 0; i < infix.size(); i++) {
		
		if (infix[i] == '(') {
			brackets_count++;
		}

		if (infix[i] == ')') {
			brackets_count--;
		}

		if (int(infix[i]) >= 48 && int(infix[i]) <= 57) {
			string operand;
			int points = 0;
			while ((int(infix[i]) >= 48 && int(infix[i]) <= 57) || (infix[i] == ',')) {
				operand += infix[i];
				i++;
			}
			lexems[j] = new Const(operand);
			j++; i--;
		}

		else if (infix[i] >= 97 && infix[i] <= 122) {
			lexems[j] = new Variable(infix[i]);
			j++;
		}

		else if (IsOperation(infix[i])) {
			if ((infix[i] == '-') && ((i == 4) || (IsOperation(infix[i - 1]) && (infix[i - 1] != ')')))) {
				lexems[j] = new Operation('~');
				j++;
			}
			else {
				lexems[j] = new Operation(infix[i]);
				j++;
			}
		}
	
	}
	size = j;
	if (brackets_count != 0) {
		throw exception("error");
	}
}


void Arithmetic_expression::show() {
	for (int i = 0; i < size; i++) {
		lexems[i]->show();
		cout << " ";
	}
	cout << "\n";
}

void Arithmetic_expression::ToPostfix() {
	TStack <Lexema*> Stk(size);
	int j = 0;
	int i = 0;
	for (i = 0; i < size; i++) {
		if (lexems[i]->NameOfClass() == "Operand") {
			postfix[j] = lexems[i];
			j++;
		}
	
		else if (lexems[i]->lexema == "(") {
			Stk.Push(lexems[i]);
		}

		else if (lexems[i]->lexema == ")") {
			while (Stk.TopElem()->lexema != "(") {
				postfix[j] = Stk.Pop();
				j++;
			}
			Stk.Pop();
		}

	else if (lexems[i]->Priority() != 0 && lexems[i]->NameOfClass() == "Operation") {
			while ((!Stk.IsEmpty()) && (Stk.TopElem()->Priority() <= lexems[i]->Priority())) {
				postfix[j] = Stk.Pop();
				j++;
			}
			Stk.Push(lexems[i]);
		}
	}
	while (!Stk.IsEmpty()) {
		postfix[j] = Stk.Pop();
		j++;
	}

	size_postfix = j;
}


void Arithmetic_expression::show_postfix() {
	for (int i = 0; i < size_postfix; i++) {
		postfix[i]->show();
		cout << " ";
	}
}

void Arithmetic_expression::Input() {
	map <char, double> value;
	for (int i = 0; i < size_postfix+1; i++) {
		if (lexems[i]->lexema[0] >= 97 && lexems[i]->lexema[0] <= 122) {
			if (value.find(lexems[i]->lexema[0]) == value.end()) {
				double input;
				cout << "enter" << lexems[i]->lexema <<"value";
				cin >> input;
				value.insert(std::pair<char,double>(lexems[i]->lexema[0],input));
			}
			lexems[i]->Inicialize(value.at(lexems[i]->lexema[0]));
		}
	}
}

double Arithmetic_expression::Calculate() {
	TStack <double> Stk;
	for (int i = 0; i < size_postfix; i++) {
		postfix[i]->Calculate(Stk);
	}
	return Stk.Pop();
}


void Arithmetic_expression::Checking_Correct() {

	int j = 0;

	for (int i = 0; i < size; i++) {

		if (infix[i] == '(' && ((infix[i + 1] == '+') || (infix[i + 1] == '*') || (infix[i + 1] == '/')))
			throw exception("uncorrect notation");

		if (infix[i] == ')' && ((infix[i + 1] == '+') || (infix[i + 1] == '*') || (infix[i + 1] == '/') || (infix[i + 1] == '-')))
			throw exception("uncorrect notation");

		if (lexems[j]->Priority() == 1 && ((infix[i + 1] == '+') || (infix[i + 1] == '*') || (infix[i + 1] == '/') || (infix[i + 1] == '-') || (infix[i + 1] == ')'))) {
			throw exception("uncorrect notation");
			j++;
		}

		if ((lexems[j]->Priority() == 2 || lexems[j]->Priority() == 3) && (j == 0 || j == infix.size())) {
			throw exception("uncorrect notation");
			j++;
		}


		if ((lexems[j]->Priority() == 2 || lexems[j]->Priority() == 3) && ((infix[i + 1] == '+') || (infix[i + 1] == '*') || (infix[i + 1] == '/') || infix[i + 1] != '(' || infix[i + 1] != '-')) {
			throw exception("uncorrect notation");
			j++;
		}
		if ((lexems[j]->Priority() == 2 || lexems[j]->Priority() == 3) && ((infix[i - 1] == '+') || (infix[i - 1] == '*') || (infix[i - 1] == '/') || infix[i - 1] != ')')) {
			throw exception("uncorrect notation");
			j++;
		}
	}
}

void Const::Inicialize(double val){}

void Operand::Calculate(TStack <double> &Stk) {}

void Operation::Inicialize(double val){}

int Const::Priority() {
	return 0;
}

int Variable::Priority() {
	return 0;
}