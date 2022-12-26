// реализация функций и классов для вычисления арифметических выражений

#include <iostream>
#include <map>
#include <cmath>
#include "../include/arithmetic.h"
#include "../include/stack.h"

std::map<std::string, double> valueVar;
std::map<std::string, double>* valueVarPtr = &valueVar;

Lexems::Lexems() { }

Lexems::~Lexems() { }

/*-----------------------------------------------------------------------*/

Operator::Operator(char _lex) : Lexems()
{
	lex = _lex;
	if (_lex == '~')
		this->priority = 1;
	else if (_lex == '*' || _lex == '/')
		this->priority = 2;
	else if (_lex == '+' || _lex == '-')
		this->priority = 3;
	else if (_lex == '(' || _lex == ')')
		this->priority = 0;
	else
		throw std::exception("error");
}

std::string Operator::whatis()
{
	return "Operator";
}

void Operator::ToDo(Stack<double>& S)
{
	const double r_value = S.pop();
	double l_value;
	if (lex == "~")
	{
		S.push((-1) * r_value);
	}
	else if (lex == "*")
	{
		l_value = S.pop();
		S.push(l_value * r_value);
	}
	else if (lex == "+")
	{
		l_value = S.pop();
		S.push(l_value + r_value);
	}
	else if (lex == "-")
	{
		l_value = S.pop();
		S.push(l_value - r_value);
	}
	else if (lex == "/")
	{
		l_value = S.pop();
		if (r_value == 0)
			throw std::exception("division by zero");
		S.push(l_value / r_value);
	}
	else
	{
		throw std::exception("error");
	}
}

size_t Operator::prioritet()
{
	return priority;
}

std::string Operator::show()
{
	return lex;
}

Operator::~Operator() { }

/*-----------------------------------------------------------------------*/

Operand::Operand(std::string _lex) : Lexems()
{
	lex = _lex;
}

std::string Operand::whatis()
{
	return "Operand";
}

void Operand::ToDo(Stack<double>& S)
{
	S.push(convert(lex));
}

size_t Operand::prioritet()
{
	return 0;
}

std::string Operand::show()
{
	return lex;
}

Operand::~Operand() { }

/*-----------------------------------------------------------------------*/

Var::Var(char _lex) : Lexems()
{
	lex = _lex;
}

std::string Var::whatis()
{
	return "Var";
}

void Var::ToDo(Stack<double>& S)
{
	if ((*valueVarPtr).find(lex) == (*valueVarPtr).end())
	{
		double val;
		std::cout << "Enter value for " << lex << ":\n";
		std::cin >> val;
		(*valueVarPtr).insert(std::pair<std::string, double>(lex, val));
	}
	S.push((*valueVarPtr).at(lex));
}

size_t Var::prioritet()
{
	return 0;
}

std::string Var::show()
{
	return lex;
}

Var::~Var() { }

/*-----------------------------------------------------------------------*/

TPostfix::TPostfix(std::string eq)
{
	infix_form = new Lexems* [eq.size()];
	this->infix_size = eq.size();
	postfix_form = new Lexems * [eq.size()];
	this->postfix_size = infix_size;
	start_eq = eq;
	this->init_infix();
	this->init_postfix();
}

void TPostfix::init_infix()
{
	size_t index = 0;
	int counter_bracket = 0;
	int error_index;
	for (size_t i = 0; i < infix_size; )
	{
		if (isOperand(start_eq[i]) || start_eq[i] == ',')
		{
			std::string operand;
			bool e_index = false;
			while (isOperand(start_eq[i]) || start_eq[i] == ',' || start_eq[i] == 'e' || (start_eq[i] == '-' && e_index))
			{
				if (start_eq[i] == 'e')
					e_index = true;
				operand += start_eq[i];
				i++;
			}
			if ((isVar(start_eq[i]) && (isVar(start_eq[i + 1]) || isOperand(start_eq[i + 1]))) || (isOperand(start_eq[i]) && isVar(start_eq[i + 1])))
				throw lexException("no correct operand", start_eq, i + 1);
			infix_form[index++] = new Operand(operand);
		}
		else if (isOperator(start_eq[i]))
		{
			if (start_eq[i] == '(' || int(start_eq[i]) == ')')
			{
				counter_bracket += (int(start_eq[i]) - 41) + (int(start_eq[i]) - 40);
				error_index = i;
			}

			if (start_eq[i] == '-' && (i == 0 || (!isOperand(start_eq[i - 1]) && !isVar(start_eq[i - 1]) && start_eq[i-1] != ')')))
				infix_form[index] = new Operator('~');
			else
				infix_form[index] = new Operator(start_eq[i]);

			correctChecker(i, index);

			index++;
			i++;
		}
		else if (isVar(start_eq[i]))
		{
			if (i != 0)
				if (isVar(start_eq[i - 1]) || isOperand(start_eq[i - 1]))
					throw lexException("no correct var", start_eq, i - 1);
			if (i >= infix_size)
				if (isVar(start_eq[i + 1]) || isOperand(start_eq[i + 1]))
					throw lexException("no correct var", start_eq, i + 1);
			infix_form[index++] = new Var(start_eq[i]);
			i++;
		}
		else
		{
			throw lexException("unidentified lexem", start_eq, i);
		}
	}

	if (counter_bracket != 0)
		throw lexException("no correct set bracket", start_eq, error_index);

	infix_size = index;
}

void TPostfix::correctChecker(const size_t& i, const size_t index)
{
	if (start_eq[i] == '(' && !isOperand(start_eq[i + 1]) && !isVar(start_eq[i + 1]) && start_eq[i + 1] != '(' && start_eq[i + 1] != '-')
		throw lexException("no correct set bracket", start_eq, i);
	if (start_eq[i] == ')' && !isOperand(start_eq[i - 1]) && !isVar(start_eq[i - 1]) && start_eq[i - 1] != ')')
		throw lexException("no correct set bracket", start_eq, i);
	if (infix_form[index]->prioritet() == 1 && !isOperand(start_eq[i + 1]) && !isVar(start_eq[i + 1]) && start_eq[i + 1] != '(')
		throw lexException("no correct unary operator", start_eq, i + 1);
	if ((infix_form[index]->prioritet() == 2 || infix_form[index]->prioritet() == 3) && (index == 0 || index == start_eq.size()))
		throw lexException("no correct binary operator", start_eq, i);
	if ((infix_form[index]->prioritet() == 2 || infix_form[index]->prioritet() == 3) && !isOperand(start_eq[i + 1]) && !isVar(start_eq[i + 1]) && start_eq[i + 1] != '(' && start_eq[i+1] != '-')
		throw lexException("no correct binary operator", start_eq, i + 1);
	if ((infix_form[index]->prioritet() == 2 || infix_form[index]->prioritet() == 3) && !isOperand(start_eq[i - 1]) && !isVar(start_eq[i - 1]) && start_eq[i - 1] != ')')
		throw lexException("no correct binary operator", start_eq, i - 1);
}

void TPostfix::init_postfix()
{
	Stack<Lexems*> S(postfix_size);
	size_t i = 0;         //колво лексем в постфиксной форме
	size_t index = 0;     //кол-во лексем в исходном уравнении
	while (index < infix_size && i < postfix_size)
	{
		if (infix_form[index]->whatis() == "Operand" || infix_form[index]->whatis() == "Var")
		{
			postfix_form[i++] = infix_form[index];
			index++;
		}

		else if (infix_form[index]->prioritet() != 0 && infix_form[index]->whatis() == "Operator")
		{
			while (!S.isEmpty() && S.view_top()->prioritet() != 0 && S.view_top()->prioritet() <= infix_form[index]->prioritet())
			{
				postfix_form[i++] = S.pop();
			}	
			S.push(infix_form[index++]);
		}

		else if (!S.isEmpty() && infix_form[index]->show() == ")")
		{
			while (S.view_top()->show() != "(")
			{
				postfix_form[i++] = S.pop();
			}
			S.pop();
			index++;
		}

		else
		{
			S.push(infix_form[index++]);
		}
	}

	while (!S.isEmpty())
	{
		postfix_form[i++] = S.pop();
		index++;
	}

	postfix_size = i;
}

double TPostfix::resolve()
{
	Stack<double> S(postfix_size);
	for (size_t i = 0; i < postfix_size; i++)
		postfix_form[i]->ToDo(S);

	return S.pop();
}

std::string TPostfix::get_infixLexem()
{
	std::cout << "your infix form:" << std::endl;
	std::string out;
	for (size_t i = 0; i < infix_size; i++)
		out += infix_form[i]->show();

	return out;
}

std::string TPostfix::get_postfixLexem()
{
	std::cout << "your postfixfix form:" << std::endl;
	std::string out;
	for (size_t i = 0; i < postfix_size; i++)
		out += postfix_form[i]->show();

	return out;
}

TPostfix::~TPostfix()
{
	for (size_t i = 0; i < infix_size; i++)
		delete infix_form[i];
	delete[] infix_form;
	delete[] postfix_form;
}

/*-----------------------------------------------------------------------*/

bool isOperand(const char& lexema) noexcept
{
	if (int(lexema) >= 48 && int(lexema) <= 57)
		return true;
	else
		return false;
}

bool isOperator(const char& lexema) noexcept  // ~, *, +, -, /, (, )
{
	return (lexema == '*' || lexema == '+' || lexema == '-' || lexema == '/' || lexema == '~' || lexema == '(' || lexema == ')');
}

bool isVar(const char& lexema) noexcept
{
	return ((int(lexema) >= 65 && int(lexema) <= 90) || (int(lexema) >= 97 && int(lexema) <= 122)); //a-z; A-Z;
}

double convert(const std::string strOperand)
{
	size_t i = 0;
	double result = 0;
	int sign = 1;
	if (strOperand[i] == '-')
	{
		sign *= -1;
		i++;
	}

	size_t power = 10;
	for ( ; strOperand[i] != ',' && i < strOperand.size(); i++)     //integer part
	{
		if (isOperand(strOperand[i]))
		{
			result = result * power + (double(strOperand[i]) - 48);
		}
		else
		{
			i--;
			break;
		}
	}

	if ((i + 2) >= strOperand.size() && strOperand[i] == ',' && strOperand[i + 1] == 'e')
		throw lexException("no correct number", strOperand, i + 1);

	if ((i+1) >= strOperand.size() && strOperand[i] == ',')
		throw lexException("no correct number", strOperand, i);

	i++;

	for (; i < strOperand.size() && strOperand[i] != 'e'; i++)    //tail
	{
		if (isOperand(strOperand[i]))
		{
			result += (double(strOperand[i]) - 48) / power;
			power *= 10;
		}
		else
			throw lexException("no correct number", strOperand, i-1);
	}

	if (i >= strOperand.size() && strOperand[i-1] == 'e')
		throw lexException("no correct number", strOperand, i);

	if (i >= strOperand.size())
		return result * sign;

	i++;

	int sign_num = 1;
	double power_num = 0;
	if (strOperand[i] == '-')
	{
		sign_num = -1;
		i++;
	}
	power = 1;
	
	while (i < strOperand.size())
	{
		if (isOperand(strOperand[i]))
		{
			power_num = power_num * power + (double(strOperand[i]) - 48);
			power *= 10;
			i++;
		}
		else
			throw lexException("no correct number", strOperand, i-1);
	}
	result *= std::pow(10, power_num*sign_num);

	return result * sign;
}
