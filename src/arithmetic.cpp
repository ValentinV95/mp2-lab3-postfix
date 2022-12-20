// реализация функций и классов для вычисления арифметических выражений

#include "arithmetic.h"

const double Const::get_value()
{
	double value = 0, pokaz = 0, point = 0, pokaz_point = 0;
	int flag = 0, pokaz_flag = 0, counter = 0, pokaz_counter = 0, i = 0;
	while (lexema[i] >= '0' && lexema[i] <= '9' || lexema[i] == '.' || lexema[i] == 'e')
	{
		if (lexema[i] == '.')
		{
			if (flag == 2)
			{
				flag = 4;
				i++;
				while (lexema[i] >= '0' && lexema[i] <= '9')
				{
					pokaz_point *= 10;
					pokaz_point += lexema[i++];
					pokaz_point -= '0';
					pokaz_counter++;
				}
				break;
			}
			flag = 1;
			i++;
			while (lexema[i] >= '0' && lexema[i] <= '9')
			{
				point *= 10;
				point += lexema[i++];
				point -= '0';
				counter++;
			}
			if (lexema[i] == 'e')
				continue;
			break;
		}
		if (lexema[i] == 'e')
		{
			if (flag == 1)
				flag = 2;
			else
				flag = 3;
			i++;
			while (lexema[i] >= '0' && lexema[i] <= '9' || lexema[i] == '-' || lexema[i] == '+')
			{
				if (lexema[i] == '-')
				{
					pokaz_flag = 1;
					i++;
				}
				else if (lexema[i] == '+')
					i++;
				if (lexema[i] == '.')
					break;
				else
					pokaz *= 10;
				pokaz += lexema[i++];
				pokaz -= '0';
			}
			if (lexema[i] == '.')
				continue;
			break;
		}
		value *= 10;
		value += lexema[i++];
		value -= '0';
	}

	if (flag == 1)
		value = value + point / pow(10, counter);
	if (flag == 2)
	{
		value = value + point / pow(10, counter);
		if (pokaz_flag == 1)
			pokaz *= -1;
		value = value * pow(10, pokaz);
	}
	if (flag == 3)
	{
		if (pokaz_flag == 1)
			pokaz *= -1;
		value = value * pow(10, pokaz);
	}
	if (flag == 4)
	{
		value = value + point / pow(10, counter);
		pokaz = pokaz + pokaz_point / pow(10, pokaz_counter);
		if (pokaz_flag == 1)
			pokaz *= -1;
		value = value * pow(10, pokaz);
	}
	return value;
}


ArithmeticExpression::ArithmeticExpression(string infx) : infix(infx)
{
	priority = { {"+", 1}, {"-", 1}, {"*", 2}, {"/", 2}, {"~", 3} };
	int brackets_check = 0;
	if (infix[0] == ')' || infix[0] == '+' || infix[0] == '*' || infix[0] == '/')
	{
		cout << "Error in index " << 1 << endl;
		throw exception();
	}
	if (infix[infix.length() - 1] == '(' || infix[infix.length() - 1] == '+' || infix[infix.length() - 1] == '-' || infix[infix.length() - 1] == '*' || infix[infix.length() - 1] == '/' ||
		infix[infix.length() - 1] == '.' || (infix[infix.length() - 1] == 'e' && (infix[infix.length() - 2] >= '0' && infix[infix.length() - 2] <= '9' || infix[infix.length() - 2] == '.')))
	{
		cout << "Error in index " << infix.length() << endl;
		throw exception();
	}
	for (size_t i = 0; i < infix.length(); i++)
	{
		if (!((infix[i] >= '0' && infix[i] <= '9') || (infix[i] >= 'a' && infix[i] <= 'z') || infix[i] == '+' ||
			infix[i] == '-' || infix[i] == '*' || infix[i] == '/' || infix[i] == '~' || infix[i] == '.' || infix[i] == '(' || infix[i] == ')'))
		{
			cout << "Error in index " << i + 1 << endl;
			throw exception();
		}
		if (infix[i] == '(')
			brackets_check++;
		if (infix[i] == ')')
			brackets_check--;
	}
	if (brackets_check != 0)
	{
		cout << "The number of brackets does not match" << endl;
		throw exception("The number of brackets does not match");
	}
	ToPostfix();
}
void ArithmeticExpression::ToPostfix()
{
	Parse();
	if (lexems[0]->get_lexema() == "-")
		lexems[0]->get_lexema() = "~";
	Stack<string> st;
	string stackItem("");
	size_t i = 0;
	for (i = 0; i < lexems.size(); i++)
	{
		if (lexems[i]->get_lexema() == "(")
			st.push(lexems[i]->get_lexema());
		else if (lexems[i]->get_lexema() == ")")
		{
			stackItem = st.top();
			st.pop();
			while (stackItem != "(")
			{
				postfix.push_back(new Operation(stackItem));
				stackItem = st.top();
				st.pop();
			}
		}
		else if (!lexems[i]->isOperand())
		{
			if (lexems[i]->get_lexema() == "-" && (lexems[i - 1]->get_lexema() == "(" || !lexems[i - 1]->isOperand()))
				lexems[i]->get_lexema() = "~";
			while (!st.isEmpty())
			{
				stackItem = st.top();
				st.pop();
				if (lexems[i]->get_lexema() != "~")
				{
					if (priority[lexems[i]->get_lexema()] <= priority[stackItem])
						postfix.push_back(new Operation(stackItem));
					else
					{
						st.push(stackItem);
						break;
					}
				}
				else
				{
					if (priority[lexems[i]->get_lexema()] < priority[stackItem])
						postfix.push_back(new Operation(stackItem));
					else
					{
						st.push(stackItem);
						break;
					}
				}
			}
			st.push(lexems[i]->get_lexema());
		}
		else
		{
			Operand* operand = (Operand*)lexems[i];
			operands.insert({ operand->get_lexema(), operand->get_value() });
			postfix.push_back(operand);
		}
	}
	while (!st.isEmpty())
	{
		stackItem = st.top();
		st.pop();
		postfix.push_back(new Operation(stackItem));
	}
	for (i = 0; i < lexems.size() - 1; i++)
	{
		if ((lexems[i]->isOperand()) && !(!lexems[i + 1]->isOperand() && lexems[i + 1]->get_lexema() != "(" && lexems[i + 1]->get_lexema() != "~"))
		{
			cout << "Error in " << i + 2 << " lexema " << lexems[i + 1]->get_lexema() << endl;
			throw exception();
		}
		if ((lexems[i]->get_lexema() == "~") && !(lexems[i + 1]->get_lexema() == "~" || lexems[i + 1]->isOperand() || lexems[i + 1]->get_lexema() == "("))
		{
			cout << "Error in " << i + 2 << " lexema " << lexems[i + 1]->get_lexema() << endl;
			throw exception();
		}
		if ((!lexems[i]->isOperand() && lexems[i]->get_lexema() != "~" && lexems[i]->get_lexema() != "(" && lexems[i]->get_lexema() != ")") &&
			!(lexems[i + 1]->isOperand() || lexems[i + 1]->get_lexema() == "~" || lexems[i + 1]->get_lexema() == "("))
		{
			cout << "Error in " << i + 2 << " lexema " << lexems[i + 1]->get_lexema() << endl;
			throw exception();
		}
		if ((lexems[i]->get_lexema() == "(") && !(lexems[i + 1]->get_lexema() == "~" || lexems[i + 1]->isOperand() || lexems[i + 1]->get_lexema() == "("))
		{
			cout << "Error in " << i + 2 << " lexema " << lexems[i + 1]->get_lexema() << endl;
			throw exception();
		}
		if ((lexems[i]->get_lexema() == ")") && !(!lexems[i + 1]->isOperand() && lexems[i + 1]->get_lexema() != "(" && lexems[i + 1]->get_lexema() != "~"))
		{
			cout << "Error in " << i + 2 << " lexema " << lexems[i + 1]->get_lexema() << endl;
			throw exception();
		}
	}
}
void ArithmeticExpression::Parse()
{
	for (size_t i = 0; i < infix.size(); i++)
	{
		if ((infix[i] >= '0' && infix[i] <= '9') || infix[i] == '.')
		{
			string tmp;
			{
				while ((infix[i] >= '0' && infix[i] <= '9') || infix[i] == '.' || infix[i] == 'e' && i < infix.size())
				{
					if (infix[i] == 'e')
					{
						tmp.push_back(infix[i]);
						i++;
					}
					tmp.push_back(infix[i]);
					i++;
				}
				int e_counter = 0;
				for (size_t j = 0; j < tmp.length() - 1; j++)
				{
					if (tmp[j] == '.' && (tmp[j + 1] == '.' || tmp[j + 1] == 'e' || tmp[j + 1] == '+' || tmp[j + 1] == '-'
						|| tmp[j + 1] == '*' || tmp[j + 1] == '/' || tmp[j + 1] == '(' || tmp[j + 1] == ')'))
					{
						cout << "Error in " << lexems.size() + 1 << " lexema " << tmp << " in " << j + 2 << " index" << endl;
						throw exception();
					}
					if (tmp[j] == 'e')
					{
						e_counter++;
						if (!(tmp[j + 1] == '+' || tmp[j + 1] == '-' ||
							(tmp[j + 1] >= '0' && tmp[j + 1] <= '9') || tmp[j + 1] == '.'))
						{
							cout << "Error in " << lexems.size() + 1 << " lexema " << tmp << " in " << j + 2 << " index" << endl;
							throw exception();
						}
					}
					if (e_counter > 1)
					{
						cout << "Error in " << lexems.size() + 1 << " lexema - too many 'e'" << endl;
						throw exception();
					}
				}
				lexems.push_back(new Const(tmp));
				if (i == infix.size())
					break;
			}
			tmp = "";
		}
		if (infix[i] == '+' || infix[i] == '-' || infix[i] == '*' || infix[i] == '/' || infix[i] == '(' || infix[i] == ')')
		{
			lexems.push_back(new Operation(infix[i]));
			continue;
		}
		else if (infix[i] >= 'a' && infix[i] <= 'z')
		{
			lexems.push_back(new Variable(infix[i]));
			continue;
		}
	}
}
string ArithmeticExpression::GetInfix() const
{
	return infix;
}
string ArithmeticExpression::GetPostfix() const
{
	string s_postfix = "|";
	for (size_t i = 0; i < postfix.size(); i++)
	{
		s_postfix.append(postfix[i]->get_lexema());
		s_postfix.append("|");
	}
	return s_postfix;
}
vector<string> ArithmeticExpression::GetOperands() const
{
	vector<string> op;
	for (const auto& item : operands)
		if (item.first >= "a" && item.first <= "z")
			op.push_back(item.first);
	return op;
}
double ArithmeticExpression::Calculate(const map<string, double>& values)
{
	for (auto& val : values)
	{
		try
		{
			operands.at(val.first) = val.second;
		}
		catch (out_of_range& e) {}
	}
	Stack<double> st;
	double leftOperand, rightOperand;
	for (size_t i = 0; i < postfix.size(); i++)
	{
		if (postfix[i]->get_lexema() == "+")
		{
			rightOperand = st.top();
			st.pop();
			leftOperand = st.top();
			st.pop();
			st.push(leftOperand + rightOperand);
		}
		else if (postfix[i]->get_lexema() == "-")
		{
			rightOperand = st.top();
			st.pop();
			leftOperand = st.top();
			st.pop();
			st.push(leftOperand - rightOperand);
		}
		else if (postfix[i]->get_lexema() == "*")
		{
			rightOperand = st.top();
			st.pop();
			leftOperand = st.top();
			st.pop();
			st.push(leftOperand * rightOperand);
		}
		else if (postfix[i]->get_lexema() == "/")
		{
			rightOperand = st.top();
			st.pop();
			leftOperand = st.top();
			st.pop();
			if (rightOperand == 0)
				throw exception("Can't divide by zero");
			st.push(leftOperand / rightOperand);
		}
		else if (postfix[i]->get_lexema() == "~")
		{
			leftOperand = st.top();
			st.pop();
			st.push(0 - leftOperand);
		}
		else
			st.push(operands[postfix[i]->get_lexema()]);
	}
	return st.top();
}