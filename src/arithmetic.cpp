// реализация функций и классов для вычисления арифметических выражений
#include"arithmetic.h"

double Postfix::stringToDouble(string num, string power)
{
	double res = 0.0;
	size_t pointPos = num.size();

	if (num.find('.') != string::npos)
	{
		pointPos = num.find('.');
	}

	for (size_t i = 0; i < pointPos; i++)
	{
		size_t tmp = (size_t)num[i] - '0';
		res += (double)(tmp * pow(10, pointPos - i - 1));
	}

	for (size_t i = pointPos + 1, j = 1; i < num.size(); i++, j++)
	{
		size_t tmp = (size_t)num[i] - '0';
		res += (double)(tmp / pow(10, j));
	}

	if (!power.empty())
	{
		double powNum = 0;
		for (size_t i = 2; i < power.size(); i++)
		{
			size_t tmp = (size_t)power[i] - '0';
			powNum += (double)(tmp * pow(10, power.size() - i - 1));
		}

		if (power[1] == '-')
		{
			res /= pow(10, powNum);
		}
		else
		{
			res *= pow(10, powNum);
		}
	}
	return res;
}

void Postfix::parse()
{
	string operations("+-*/");
	int bracketCount = 0;

	if (operations.find(input[0]) != string::npos && input[0] != '-')
	{
		throw exception("Operation at the beginning of a line");
	}
	else if (input[0] == ')')
	{
		throw exception(") at the beginning of a line");
	}
	if (operations.find(input[input.size() - 1]) != string::npos)
	{
		throw exception("Operation at the end of a line");
	}
	else if (input[input.size() - 1] == '(')
	{
		throw exception("( at the end of a line");
	}
	for (size_t i = 0; i < input.size(); i++)
	{
		if (input[i] >= 'a' && input[i] <= 'z')
		{
			lexems.push_back(new Var(input[i], values, i + 1, i + 1));
			values[input[i]] = 0.0;
		}
		else if (input[i] == '(' || input[i] == ')')
		{
			if (input[i] == '(')
			{
				bracketCount++;
				lexems.push_back(new Operation('(', i + 1, i + 1));
			}
			else
			{
				if (bracketCount == 0)
				{
					cout << ") in " << i + 1 << " position has no pair" << endl;
					throw exception("Bracket error");
				}
				bracketCount--;
				lexems.push_back(new Operation(')', i + 1, i + 1));
			}
		}
		else if (operations.find(input[i]) != string::npos)
		{
			if (input[i] == '-')
			{
				if (i == 0 || input[i - 1] == '(' || (operations.find(input[i - 1]) != string::npos))
				{
					lexems.push_back(new Operation('~', i + 1, i + 1));
				}
				else
				{
					lexems.push_back(new Operation('-', i + 1, i + 1));
				}
			}
			else
			{
				lexems.push_back(new Operation(input[i], i + 1, i + 1));
			}
		}
		else if((input[i] >= '0' && input[i] <= '9') || input[i] == '.')
		{
			string number;
			string power;
			int pointCount = 0;
			int startPos = i + 1;

			while ((input[i] >= '0' && input[i] <= '9') || input[i] == '.')
			{
				if (input[i] == '.')
				{
					pointCount++;
				}
				number.push_back(input[i]);
				i++;
			}
			if(pointCount == 1 && number.size() == 1)
			{
				cout << "Number in positions " << i - number.size() + 1 << " to " << i + 1<< " contains only point" << endl;
				throw exception("Error in notation of floating point number");
			}
			if (pointCount > 1)
			{
				cout << "Number in positions " << i - number.size() + 1 << " to " << i + 1 << " contains more than one point" << endl;
				throw exception("Error in notation of floating point number");
			}
			if (input[i] == 'e')
			{
				power.push_back('e');
				i++;
				if (input[i] == '+' || input[i] == '-')
				{
					power.push_back(input[i]);
					i++;
				}
				else
				{
					cout << "In position " << i + 1 << " power sign not found" << endl;
					throw exception("Error in exponential notation of floating point number");
				}
				if (input[i] < '0' && input[i] > '9')
				{
					cout << "In position " << i + 1 << " power not found" << endl;
					throw exception("Error in exponential notation of floating point number");
				}
				while (input[i] >= '0' && input[i] <= '9')
				{
					power.push_back(input[i]);
					i++;
				}
			}
			lexems.push_back(new Const(number + power, stringToDouble(number, power), startPos, i));
			i--;
		}
		else
		{
			cout << "In position " << i + 1 << endl;
			throw exception("Expression contains an invalid symbol");
		}
	}
	if (bracketCount > 0)
	{
		throw exception("Don`t find ')' for '('");
	}
}

void Postfix::orderCheck()
{
	string operations("+-*/");

	for (size_t i = 0; i < lexems.size() - 1; i++)
	{
		if (lexems[i]->isOperand())
		{
			if (operations.find(lexems[i + 1]->show()) == string::npos && lexems[i + 1]->show()[0] != ')')
			{
				cout << "Error in position " << lexems[i + 1]->getStartPos() <<
					" after operand expected binary operation or ')'";
				throw exception("Order error");
			}
		}
		else if (operations.find(lexems[i]->show()) != string::npos)
		{
			if (lexems[i + 1]->show()[0] != ')' && operations.find(lexems[i + 1]->show()) != string::npos)
			{
				cout << "Error in position " << lexems[i + 1]->getStartPos() <<
					" after binary operation expecetd operand, '(' or '-'";
				throw exception("Order error");
			}
		}
		else if (lexems[i]->show()[0] == '~')
		{
			if (!lexems[i + 1]->isOperand() && lexems[i + 1]->show()[0] != '~' && lexems[i + 1]->show()[0] != '(')
			{
				cout << "Error in position " << lexems[i + 1]->getStartPos() <<
					" after unary '-' expected operand or '('";
				throw exception("Order error");
			}
		}
		else if (lexems[i]->show()[0] == '(')
		{
			if (lexems[i + 1]->show()[0] != '(' && !lexems[i + 1]->isOperand() && lexems[i + 1]->show()[0] != '~')
			{
				cout << "Error in position " << lexems[i + 1]->getStartPos() <<
					" after '(' expected operand, '(' or '-' ";
				throw exception("Order error");
			}
		}
		else if (lexems[i]->show()[0] == ')')
		{
			if (lexems[i + 1]->show()[0] != ')' && operations.find(lexems[i + 1]->show()) == string::npos)
			{
				cout << "Error in position " << lexems[i + 1]->getStartPos() <<
					" after ')' expected operation or ')' ";
				throw exception("Order error");
			}
		}
	}
}

void Postfix::toPostfix()
{
	TStack<Operation*> operations;

	for (auto& lexem : lexems)
	{
		if (lexem->isOperand())
		{
			postfix.push_back(lexem);
		}
		else
		{
			Operation* oper = (Operation*)lexem;
			if (oper->show()[0] == '(')
			{
				operations.push(oper);
			}
			else if (oper->show()[0] == ')')
			{
				Operation* top = operations.top();
				while (top->show()[0] != '(')
				{
					postfix.push_back(top);
					operations.pop();
					top = operations.top();
				}
				operations.pop();
			}
			else
			{
				if (!operations.isEmpty())
				{
					Operation* top = operations.top();
					while (top->getPriority() >= (oper)->getPriority())
					{
						if (top->getPriority() == (oper)->getPriority() && top->getPriority() == 3)
						{
							break;
						}
						postfix.push_back(top);
						operations.pop();
						if (operations.isEmpty())
						{
							break;
						}
						top = operations.top();
					}
				}
				operations.push(oper);
			}
		}
	}
	while (!operations.isEmpty())
	{
		postfix.push_back(operations.top());
		operations.pop();
	}
}

Operand* Postfix::performCalculations(Operation* op, Operand* first, Operand* second)
{
	switch (op->show()[0])
	{
	case('+'):
		return new Const("res", first->getValue() + second->getValue(), first->getStartPos(), second->getEndPos());
	case('-'):
		return new Const("res", first->getValue() - second->getValue(), first->getStartPos(), second->getEndPos());
	case('*'):
		return new Const("res", first->getValue() * second->getValue(), first->getStartPos(), second->getEndPos());
	case('/'):
		if (second->getValue() < 1.0e-15)
		{
			cout << "Error in " << op->getEndPos() << " position";
			throw exception("\nZero division");
		}
		return new Const("res", first->getValue() / second->getValue(), first->getStartPos(), second->getEndPos());
	case('~'):
		return new Const("res", first->getValue() - second->getValue(), second->getStartPos(), second->getEndPos());
	}
}

double Postfix::calculate()
{
	string binOpers("+-*/");
	TStack<Operand*> operands;
	for (auto& var : values)
	{
		cout << "Enter value of " << var.first << ": ";
		cin >> values[var.first];
	}
	for (auto& lexem : postfix)
	{
		if (lexem->isOperand())
		{
			operands.push((Operand*)lexem);
		}
		else
		{
			Operation* op = (Operation*)lexem;
			Operand* second = operands.top();
			operands.pop();
			if (op->show()[0] == '~')
			{
				operands.push(new Const(string("res"), 0.0, -1, -1));
			}
			Operand* first = operands.top();
			operands.pop();
			operands.push(performCalculations(op, first, second));
			if (first->show() == string("res"))
			{
				delete first;
			}
			if (second->show() == string("res"))
			{
				delete second;
			}
		}
	}
	double res = operands.top()->getValue();
	if (operands.top()->show() == string("res"))
	{
		delete operands.top();
	}
	return res;
}
