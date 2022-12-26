#include <iostream>
#include "../include/arithmetic.h"



const string Lexem::GetData() const
{
	return data;
}

const string Lexem::GetType() const
{
	return type;
}

const int Lexem::GetPriority() const
{
	return priority;
}

const double Lexem::GetNum() const
{
	return num;
}


void Operation::SetPriority(const string& s)
{
	if ((s == "(") || (s == ")")) {
		priority = 0;
	}
	else if ((s == "+") || (s == "-"))
	{
		priority = 1;
	}
	else if ((s == "*") || (s == "/")) {
		priority = 2;
	}
}


Operation::Operation(const string& s)
{
	type = "Operation";
	data = s;
	SetPriority(s);
	num = NULL;
}



void Num::StrToNum(const string& s)
{
	int point = 0;
	int size = s.size();
	double result = 0;

	for (int i = 0; i < size; i++) {
		if (s[i] == '.')
		{
			point = i;
		}
	}
	if (point != 0) {
		for (int i = 0; i < size; i++) {
			if ((s[i] != '.') && (i < point)) {
				result += (s[i] - '0') * (pow(10, point - i - 1));
			}
			else if ((s[i] != '.') && (i > point)) {
				result += (s[i] - '0') * (pow(10, point - i));
			}
		}
	}
	else if (point == 0) {
		for (int i = 0; i < size; i++) {
			result += (s[i] - '0') * pow(10, size - i - 1);
		}
	}
	num = result;
}

Num::Num(const string& s)
{
	type = "Num";
	SetPriority(s);
	StrToNum(s);
	data = s;
}

void Num::SetPriority(const string& s)
{
	priority = -1;
}
void Var::SetPriority(const string& s)
{
	priority = -1;
}
Var::Var(const string& s)
{
	type = "Var";
	SetPriority(s);
	data = s;

}




TPostfix::TPostfix(string inf)
{
	infix = inf;
	check();
	parse();
	InfixToPostfix();
	cout << Calculate() << endl;
}

bool TPostfix::IsOperation(const char& c)
{
	char available_operations[6] = { '(', ')', '+', '-', '*', '/' };
	for (int i = 0; i < 6; i++) {
		if (c == available_operations[i]) {
			return 1;
		}
	}
	return 0;
}

bool TPostfix::IsNum(const char& c)
{
	if (((c >= '0') && (c <= '9')) || (c == '.')) {
		return 1;
	}
	return 0;
}

bool TPostfix::IsVar(const char& c)
{
	if ((c >= 'a') && (c <= 'z'))
	{
		return 1;
	}
	return 0;
}

void TPostfix::parse()
{
	const int infix_size = infix.size();
	std::string lex;
	for (int i = 0; i < infix_size; i++) {
		lex = infix[i];
		if (IsNum(infix[i]) && (IsNum(infix[i + 1]) == 0)) {
			infix_lexems.push_back(new Num(lex));
			lex_count += 1;
		}
		else if (IsNum(infix[i]) && IsNum(infix[i + 1])) {
			while (IsNum(infix[i + 1])) {
				lex += infix[i + 1];
				i += 1;
			}
			infix_lexems.push_back(new Num(lex));
			lex_count += 1;
		}
		else if (IsOperation(infix[i])) {
			op_count += 1;
			infix_lexems.push_back(new Operation(lex));
			lex_count += 1;
		}
		else if (IsVar(infix[i]) && (IsVar(infix[i + 1]) == 0)) {
			infix_lexems.push_back(new Var(lex));
			lex_count += 1;
		}
		else if (IsVar(infix[i]) && IsVar(infix[i + 1])) {
			while (IsVar(infix[i + 1])) {
				lex += infix[i + 1];
				i += 1;
			}
			infix_lexems.push_back(new Var(lex));
			lex_count += 1;
		}
	}

}

void TPostfix::InfixToPostfix()
{
	TStack<Lexem*> stack(op_count);


	for (int i = 0; i < infix_lexems.size(); i++) {
		if (infix_lexems[i]->GetType() == "Num") {

			postfix += infix_lexems[i]->GetData();
			postfix_lexems.push_back(infix_lexems[i]);

		}
		else if (infix_lexems[i]->GetType() == "Var") {
			postfix += infix_lexems[i]->GetData();
			postfix_lexems.push_back(infix_lexems[i]);

		}
		else if (infix_lexems[i]->GetData() == "(") {

			stack.push(infix_lexems[i]);

		}
		else if (infix_lexems[i]->GetData() == ")") {

			while (stack.get_top()->GetData() != "(") {

				postfix += stack.get_top()->GetData();
				postfix_lexems.push_back(stack.pop());

			}

			stack.pop();

		}
		else if ((infix_lexems[i]->GetType() == "Operation") && (infix_lexems[i]->GetData() != "(") && (infix_lexems[i]->GetData() != ")")) {
			if (stack.IsEmpty())
			{
				stack.push(infix_lexems[i]);
			}
			else {
				if (stack.get_top()->GetPriority() >= infix_lexems[i]->GetPriority()) {
					postfix += stack.get_top()->GetData();
					postfix_lexems.push_back(stack.pop());
					i -= 1;
				}
				else {
					stack.push(infix_lexems[i]);
				}
			}
		}
	}

	while (!stack.IsEmpty()) {

		postfix += stack.get_top()->GetData();
		postfix_lexems.push_back(stack.pop());

	}

	cout <<"postfix form: " << postfix << endl;

}

void Lexem::SetNum(const double d)
{
	if (type == "Var") {
		num = d;
	}
}

void TPostfix::check()
{
	int open_bracket_count = 0;
	int closing_bracket_count = 0;
	for (int i = 0; i < infix.size(); i++) {
		if (infix[i] == '(')
		{
			open_bracket_count += 1;
		}
		else if (infix[i] == ')') {
			closing_bracket_count += 1;
		}
		else if (IsOperation(infix[i]) && (infix[i] != '(') && (infix[i] != ')') && (infix[i + 1] != ')') && (infix[i - 1] != ')') && (infix[i + 1] != '(') && (infix[i - 1] != '(')) {
			if (((IsNum(infix[i + 1]) && IsNum(infix[i - 1])) || (IsVar(infix[i + 1]) && IsVar(infix[i - 1])) || (IsVar(infix[i - 1]) && IsNum(infix[i + 1])) || (IsNum(infix[i - 1]) && IsVar(infix[i + 1]))) == 0) {
				throw exception("wrong binary operation enter");
			}
		}
	}
	if (closing_bracket_count != open_bracket_count) {
		throw exception("wrong count of brackets");
	}
}

const double TPostfix::Calculate()
{
	TStack<double> stack(postfix_lexems.size() - op_count + 1);

	for (int i = 0; i < postfix_lexems.size(); i++) {
		double first, second;
		if (postfix_lexems[i]->GetType() == "Var") {
			double d;
			cout << "enter variable: " << postfix_lexems[i]->GetData() << " = ";
			cin >> d;
			postfix_lexems[i]->SetNum(d);
			stack.push(postfix_lexems[i]->GetNum());

		}
		else if (postfix_lexems[i]->GetType() == "Num") {

			stack.push(postfix_lexems[i]->GetNum());
		}
		else if (postfix_lexems[i]->GetType() == "Operation") {
			if (postfix_lexems[i]->GetData() == "+") {
				second = stack.pop();
				first = stack.pop();
				stack.push(first + second);

			}
			else if (postfix_lexems[i]->GetData() == "-") {
				second = stack.pop();
				first = stack.pop();
				stack.push(first - second);

			}
			else if (postfix_lexems[i]->GetData() == "*") {
				second = stack.pop();
				first = stack.pop();
				stack.push(first * second);
			}
			else if (postfix_lexems[i]->GetData() == "/") {
				second = stack.pop();
				first = stack.pop();
				if (second == 0) {
					throw exception("division by zero");
				}
				stack.push(first / second);
			}
		}
	}
	result = stack.get_top();
	return stack.pop();
}

const double TPostfix::GetResult() const
{
	return result;
}

TPostfix::~TPostfix()
{
	for (int i = 0; i < infix_lexems.size(); i++) {
		delete infix_lexems[i];
	}
}
