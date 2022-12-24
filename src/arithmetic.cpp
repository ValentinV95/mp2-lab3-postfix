// реализация функций и классов для вычисления арифметических выражений
#include"arithmetic.h"


TPostfix::TPostfix(string expr) :inputStr(expr)
{
	this->fillFuncsMap();
	try
	{
		this->inputToLexem();
		this->inputCheck();
	}
	catch (exception& ex)
	{
		throw ex;
	}
}

double TPostfix::stringToDouble(string numStr)
{
	double res = 0.0;

	size_t ePos = numStr.find('e') != string::npos ? numStr.find('e') : numStr.size();
	size_t pointPos = numStr.find('.') != string::npos ? numStr.find('.') : ePos;

	for (size_t i = 0; i < pointPos; i++)
	{
		size_t num = static_cast<size_t>(numStr[i]) - 48;
		res += static_cast<double>(num * pow(10, numStr.size() - (numStr.size() - pointPos) - i - 1));
	}
	for (size_t i = pointPos + 1, j = 1; i < ePos; i++, j++)
	{
		size_t num = static_cast<size_t>(numStr[i]) - 48;
		res += static_cast<double>(num / pow(10, j));
	}

	size_t i = ePos + 2;

	if (i < numStr.size())
	{
		if (numStr[i - 1] == '-')
		{
			res /= pow(10, stringToDouble(numStr.substr(i, numStr.size())));
		}
		else
		{
			res *= pow(10, stringToDouble(numStr.substr(i, numStr.size())));
		}
	}
	return res;
}

Operand* TPostfix::applyOperation(Lexem* op, Operand* first, Operand* second)
{
	switch (op->show()[0])
	{
	case('+'):
		return new Const("res+", first->getValue() + second->getValue(),
			make_pair(first->getPos().first, second->getPos().second));
	case('-'):
		return new Const("res-", first->getValue() - second->getValue(),
			make_pair(first->getPos().first, second->getPos().second));
	case('*'):
		return new Const("res*", first->getValue() * second->getValue(),
			make_pair(first->getPos().first, second->getPos().second));
	case('/'):
		return new Const("res/", first->getValue() / second->getValue(),
			make_pair(first->getPos().first, second->getPos().second));
	case('^'):
		return new Const("res^", pow(first->getValue(), second->getValue()),
			make_pair(first->getPos().first, second->getPos().second));
	}
}

Operand* TPostfix::applyPrefFun(Lexem* fun, Operand* operand)
{
	return new Const("resFun", funcs[fun->show()](operand->getValue()), operand->getPos());
}

void TPostfix::fillFuncsMap()
{
	funcs["~"] = [](double x) { return -1.0 * x; };
	funcs["sqrt"] = [](double x) { return sqrt(x); };
	funcs["exp"] = [](double x) { return exp(x); };
	funcs["ln"] = [](double x) { return log(x); };
	funcs["sin"] = [](double x) { return sin(x); };
	funcs["cos"] = [](double x) { return cos(x); };
	funcs["tan"] = [](double x) { return tan(x); };
	funcs["cot"] = [](double x) { return 1 / tan(x); };
	funcs["sec"] = [](double x) { return 1 / cos(x); };
	funcs["csc"] = [](double x) { return 1 / sin(x); };
	funcs["arcsin"] = [](double x) { return asin(x); };
	funcs["arccos"] = [](double x) { return acos(x); };
	funcs["arctan"] = [](double x) { return atan(x); };
	funcs["arccot"] = [](double x) { return M_PI / 2.0 - atan(x); };
	funcs["arcsec"] = [](double x) { return acos(1.0 / x); };
	funcs["arccsc"] = [](double x) { return asin(1.0 / x); };
}

void TPostfix::inputCheck()
{
	TStack<Operation*> skob;
	string operations("+-*/^");

	if (operations.find(lexemVec[0]->show()[0]) != string::npos)
	{
		throw exception("An arithmetic expression cannot start with a binary operation");
	}
	for (size_t i = 0; i < lexemVec.size() - 1; i++)
	{
		const string& cur(lexemVec[i]->show());
		const string& next = lexemVec[i + 1]->show();
		pair<int, int> pos = lexemVec[i + 1]->getPos();

		if (lexemVec[i]->isOperand())
		{
			if (operations.find(next) == string::npos && next[0] != ')')
			{
				string error = "Error in position " + to_string(pos.first) +
					"\nAfter operand expected binary operation or ')'!";
				throw exception(error.c_str());
			}
		}
		else if (operations.find(cur) != string::npos)
		{
			if (!lexemVec[i + 1]->isOperand() && next[0] != '(' && (funcs.find(next) == funcs.end()))
			{
				string error = "Error in position " + to_string(pos.first) +
					"\nAfter binary operation expecetd operand, '(', '-', or function!";
				throw exception(error.c_str());
			}
		}
		else if (funcs.find(cur) != funcs.end() && cur[0] != '~')
		{
			if (lexemVec[i+1]->show()[0] != '(')
			{
				string error = "Error in position " + to_string(pos.first) +
					"\nAfter function expected '(' !";
				throw exception(error.c_str());
			}
		}
		else if (cur[0] == '~')
		{
			if (!lexemVec[i + 1]->isOperand() && next[0] != '(' && funcs.find(next) == funcs.end())
			{
				string error = "Error in position " + to_string(pos.first) +
					"\nAfter unary - expected operand, '(' or function !";
				throw exception(error.c_str());
			}
		}
		else if (cur[0] == '(')
		{
			skob.push(new Operation(string(1, '('), SKOB, lexemVec[i]->getPos()));

			if (next[0] != '(' && !lexemVec[i + 1]->isOperand() && funcs.find(next) == funcs.end())
			{
				string error = "Error in position " + to_string(pos.first) +
					"\nAfter '(' expected operand, '(' or function !";
				throw exception(error.c_str());
			}
		}
		else if (cur[0] == ')')
		{
			if (skob.isEmpty())
			{
				string error = "Error in position " + to_string(lexemVec[i]->getPos().first) +
					"\nFind ')' before which there was no '(' !";
				throw exception(error.c_str());
			}
			delete skob.top();
			skob.pop();

			if (next[0] != ')' && operations.find(next[0]) == string::npos)
			{
				string error = "Error in position " + to_string(pos.first) +
					"\nAfter ')' expected operation or ')' !";
				throw exception(error.c_str());
			}
		}
	}
	Lexem* last = lexemVec[lexemVec.size() - 1];
	if (last->show()[0] == '(')
	{
		skob.push(new Operation(string(1, '('), SKOB, last->getPos()));
	}
	else if (last->show()[0] == ')')
	{
		if (!skob.isEmpty())
		{
			delete skob.top();
			skob.pop();
		}
		else
		{
			string error = "Error at the end of the expression.\nFind ')' before which there was no ')' !";
			throw exception(error.c_str());
		}
	}
	else if (!last->isOperand())
	{
		throw exception("An arithmetic expression cannot end with an operation or function without an argument !");
	}
	if (!skob.isEmpty())
	{
		string error = "Error in position ";
		while (!skob.isEmpty())
		{
			error += to_string(skob.top()->getPos().first) + ", ";
			delete skob.top();
			skob.pop();
		}
		error += "\nFor '(' does not exist ')' !";
		throw exception(error.c_str());
	}
}

void TPostfix::inputToLexem()
{
	string operations("+-*/^");
	for (size_t i = 0; i < inputStr.size(); i++)
	{
		if (inputStr[i] == '(' || inputStr[i] == ')')
		{
			lexemVec.push_back(new Operation(string(1, inputStr[i]), SKOB, make_pair(i, i)));
		}
		else if (inputStr[i] == '+')
		{
			lexemVec.push_back(new Operation(string(1, '+'), ADD_SUB, make_pair(i, i)));
		}
		else if (inputStr[i] == '-')
		{
			if (i == 0 || operations.find(inputStr[i - 1]) != string::npos || inputStr[i - 1] == '(')
			{
				lexemVec.push_back(new Operation(string(1, '~'), UNMIN, make_pair(i, i)));
			}
			else
			{
				lexemVec.push_back(new Operation(string(1, '-'), ADD_SUB, make_pair(i, i)));
			}
		}
		else if (inputStr[i] == '*' || inputStr[i] == '/')
		{
			lexemVec.push_back(new Operation(string(1, inputStr[i]), MUL_DIV, make_pair(i, i)));
		}
		else if (inputStr[i] == '^')
		{
			lexemVec.push_back(new Operation(string(1, '^'), POW, make_pair(i, i)));
		}
		else if (inputStr[i] >= 'a' && inputStr[i] <= 'z')
		{
			if (inputStr[i+1] < 'a' || inputStr[i+1] > 'z')
			{
				if (vars.find(inputStr[i]) == string::npos)
				{
					vars.push_back(inputStr[i]);
				}
				lexemVec.push_back(new Var(string(1, inputStr[i]), varsValues, make_pair(i, i)));
			}
			else
			{
				string substr;

				while (inputStr[i] >= 'a' && inputStr[i] <= 'z')
				{
					substr.push_back(inputStr[i]);
					i++;
				}
				if (funcs.find(substr) == funcs.end())
				{
					string error = "Error in positions " + to_string(i - substr.length()) +
						" to " + to_string(i - 1) + "\nFunction with this name not found !";
					throw exception(error.c_str());
				}
				lexemVec.push_back(new Operation(substr, FUNC, make_pair(i - substr.length(), i - 1)));
				i--;
			}
		}
		else if (inputStr[i] >= '0' && inputStr[i] <= '9')
		{
			string substr;
			string posSymInNum("0123456789.e+-");
			int pointCount = 0;
			while (posSymInNum.find(inputStr[i]) != string::npos)
			{
				if (inputStr[i] == '.')
				{
					pointCount++;
				}
				if (inputStr[i] == 'e')
				{
					if (i == inputStr.size() || ((inputStr[i + 1] != '+') && (inputStr[i + 1] != '-')))
					{
						string error = "Error in positions " + to_string(i - substr.length()) + " to " +
							to_string(i - 1) + "\nError in exponential form of number, after e expected + or - !";
						throw exception(error.c_str());
					}
				}
				if (inputStr[i] == '+' || inputStr[i] == '-')
				{
					if (inputStr[i - 1] != 'e')
					{
						break;
					}
					if (i == inputStr.size() || (inputStr[i + 1] > '9') || (inputStr[i + 1] < '0'))
					{
						string error = "Error in positions " + to_string(i - substr.length()) + " to " +
							to_string(i + 1) + "\nError in exponential form of number, after e and +/- expected power !";
						throw exception(error.c_str());
					}
				}
				substr.push_back(inputStr[i]);
				i++;
			}
			if (pointCount > 1)
			{
				string error = "Error in positions " + to_string(i - substr.length()) + " to " +
					to_string(i - 1) + "\nError in floatpoint form of number, more than one '.' found !";
				throw exception(error.c_str());
			}
			if ((pointCount == 1 == substr.size()) || (substr[0] == '.' && substr[1] == 'e'))
			{
				string error = "Error in positions " + to_string(i - substr.length()) + " to " +
					to_string(i - 1) + "\nError in floatpoint form of number, this form can`t have only '.' !";
				throw exception(error.c_str());
			}
			lexemVec.push_back(new Const(substr, stringToDouble(substr), make_pair(i - substr.length(), i - 1)));
			i--;
		}
		else
		{
			string error = "Error in position " + to_string(i) +
				"\nInvalid character in string !";
			throw exception(error.c_str());
		}
	}
}

void TPostfix::toPostfix()
{
	TStack<Operation*> operations;

	for (auto& lexem : lexemVec)
	{
		if (lexem->isOperand())
		{
			postfix.push_back(lexem);
		}
		else
		{
			if (lexem->show() == string(1, '('))
			{
				operations.push((Operation*)lexem);
			}
			else if (lexem->show() == string(1, ')'))
			{
				Operation* top = operations.top();
				while (top->show() != string(1, '('))
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
					while (top->priority() >= ((Operation*)lexem)->priority())
					{
						if (top->priority() == ((Operation*)lexem)->priority() && top->priority() == UNMIN)
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
				operations.push((Operation*)lexem);
			}
		}
	}
	while (!operations.isEmpty())
	{
		postfix.push_back(operations.top());
		operations.pop();
	}
	isPostfix = true;
}

double TPostfix::calculatePostfix()
{
	string binOpers("+-*/^");
	TStack<Operand*> operands;
	for (auto& var : vars)
	{
		cout << "Enter value of " << var << ": ";
		cin >> varsValues[var];
	}
	for (auto& lexem : postfix)
	{
		if (lexem->isOperand())
		{
			operands.push((Operand*)lexem);
		}
		else
		{
			if (binOpers.find(lexem->show()) != string::npos)
			{
				Lexem* op = lexem;
				Operand* second = operands.top();
				operands.pop();
				Operand* first = operands.top();
				operands.pop();
				operands.push(applyOperation(op, first, second));
				if(first->show().find("res") != string::npos)
				{
					delete first;
				}
				if (second->show().find("res") != string::npos)
				{
					delete second;
				}
			}
			else
			{
				Lexem* fun = lexem;
				Operand* operand = operands.top();
				operands.pop();
				operands.push(applyPrefFun(fun, operand));
				if (operand->show().find("res") != string::npos)
				{
					delete operand;
				}
			}
		}
	}
	double res = operands.top()->getValue();
	if (operands.top()->show().find("res") != string::npos)
	{
		delete operands.top();
	}
	return res;
}

double TPostfix::calculate()
{
	if (isPostfix)
		return calculatePostfix();
	else
		throw exception("Can`t calculate expression without translate to postfix!");
}

string TPostfix::getPostfixStr()
{
	string res;
	for(auto &lexem : postfix)
	{
		res += lexem->show();
	}
	return res;
}
