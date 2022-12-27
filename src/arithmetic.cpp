#include "arithmetic.h"

const string TArithmetic::Lexem::Get() const
{
	return lex;
}
const double TArithmetic::Lexem::Value() const
{
	return value;
}
const string TArithmetic::Lexem::what() const
{
	return label;
}

TArithmetic::Lexem::~Lexem()
{

}

TArithmetic::Operation::Operation(const char& data)
{
	label = "Operation";
	lex = data;
	SetValue(lex);
}

void TArithmetic::Operation::SetValue(const string& val)
{
	if (val == "(" || val == ")")
	{
		value = 0.0;
	}
	else if (val == "+" || val == "-")
	{
		value = 1.0;
	}
	else if (val == "*" || val == "/")
	{
		value = 2.0;
	}
	else if (val == "~")
	{
		value = 3.0;
	}
	else
	{
		value = 4.0;
	}
}

double TArithmetic::Operand::in_Numerical(const string& strlex)
{
	double degree_ind = 0.0;
	double set_value = 0.0;
	double sign = 1.0;
	double e_degree_ind = 0.0;
	string after_e = "";

	if (strlex[0] == '-')
	{
		sign *= -1.0;
		degree_ind--;
	}
	else if (strlex[0] == '+')
	{
		degree_ind--;
	}
	if (strlex.find('.') == string::npos)
	{
		if (strlex.find('e') != string::npos)
		{
			degree_ind += strlex.find('e');
		}
		else
		{
			degree_ind += strlex.size();
		}
	}
	else
	{
		degree_ind += strlex.find('.');

	}
	if (strlex.find('e') != string::npos)
	{
		for (int i = strlex.find('e') + 1; i < strlex.size(); i++)
		{
			after_e += strlex[i];
		}
		e_degree_ind = in_Numerical(after_e);
	}
	for (const char symb : strlex)
	{
		if (symb == 'e')
		{
			break;
		}
		else if (symb != '-' && symb != '+' && symb != '.')
		{
			set_value += (symb - '0') * pow(10.0, --degree_ind);
		}
	}
	if (strlex.find('e') != string::npos)
	{
		set_value *= pow(10.0, e_degree_ind);
	}
	return sign * set_value;
}

void TArithmetic::Constant::SetValue(const string& val)
{
	value = in_Numerical(val);
}

TArithmetic::Constant::Constant(const string& data)
{
	label = "Constant";
	lex = data;
	SetValue(lex);
}

TArithmetic::Variable::Variable(const string& data)
{
	label = "Variable";
	lex = data;
	value = 0;
}

void TArithmetic::Variable::SetValue(const string& val)
{
	value = in_Numerical(val);
}

bool TArithmetic::find_operation(const char& tmplex)
{
	char operations[7] = { '(', ')', '+', '-', '*', '/' };
	for (const char lex : operations)
	{
		if (lex == tmplex)
		{
			return true;
		}
	}
	return false;
}

bool TArithmetic::aNumber(const char& tmplex)
{
	return (tmplex >= '0') && (tmplex <= '9');
}

bool TArithmetic::isAlpha(const char& tmplex)
{
	return (tmplex >= 'a') && (tmplex <= 'z');
}

const string TArithmetic::find_error()
{
	int open_count = 0;
	int close_count = 0;
	bool e_already_exists = false;
	bool point_already_exists = false;
	char nSym;
	string wrong_infix = "Unforessen lexem: ";

	wrong_infix += infix[0];
	if (infix[0] != '-' && !isAlpha(infix[0]) && !aNumber(infix[0]) && infix[0] != '(')
	{
		return wrong_infix + "<-";
	}
	else
	{
		for (int i = 0; i < infix.size() - 1; i++)
		{
			nSym = infix[i + 1];
			wrong_infix += nSym;

			if (infix[i] == '(')
			{
				open_count++;
				if (nSym != '(' && nSym != '-' && (!isAlpha(nSym) || nSym == 'e') && !aNumber(nSym))
				{
					return wrong_infix + "<-";
				}
			}
			else if (infix[i] == ')')
			{
				e_already_exists = false;
				point_already_exists = false;
				close_count++;
				if (nSym == '(' || !find_operation(nSym))
				{
					return wrong_infix + "<-";
				}
			}
			else if (find_operation(infix[i]))
			{
				if (i != 0 && infix[i - 1] != 'e')
				{
					e_already_exists = false;
					point_already_exists = false;
				}
				if (nSym != '-' && nSym != '(' && (!isAlpha(nSym) || nSym == 'e') && !aNumber(nSym))
				{
					return wrong_infix + "<-";
				}
			}
			else if (isAlpha(infix[i]) && infix[i] != 'e')
			{
				if (!isAlpha(nSym) && (nSym == '(' || !find_operation(nSym)))
				{
					return wrong_infix + "<-";
				}
			}
			else if (aNumber(infix[i]))
			{
				if (nSym == '.')
				{
					if (point_already_exists || e_already_exists)
					{
						return wrong_infix + "<-";
					}
				}
				else if (!aNumber(nSym) && (nSym == '(' || !find_operation(nSym)) && (nSym != 'e' || e_already_exists))
				{
					return wrong_infix + "<-";
				}
			}
			else if (infix[i] == '.')
			{
				point_already_exists = true;
				if (!aNumber(nSym) && nSym != 'e' && (!find_operation(nSym) || nSym == '('))
				{
					return wrong_infix + "<-";
				}
			}
			else if (infix[i] == 'e')
			{
				e_already_exists = true;
				if (i == 0)
				{
					return wrong_infix + "<-" + "(invalid use of 'e' lexem)";
				}
				else if (!aNumber(infix[i - 1]) && infix[i - 1] != '.' || nSym != '-' && nSym != '+' && !aNumber(nSym))
				{
					return wrong_infix + "<-" + "(invalid use of 'e' lexem)";
				}
			}
			else
			{
				return wrong_infix + "<-";
			}
		}
	}
	char lSym = infix[infix.size() - 1];
	if (lSym == ')')
	{
		close_count++;
	}
	else if ((!isAlpha(lSym) || lSym == 'e') && !aNumber(lSym) && (lSym != '.' || point_already_exists || e_already_exists))
	{
		return wrong_infix += "<-";
	}
	if (open_count != close_count)
	{
		return "Number of opening and closing brackets does not match";
	}
	return "CORRECT";
}

bool TArithmetic::check_input(const string& inp)
{
	char nSym;
	char pSym;
	bool e_already_exists = false;
	bool point_already_exists = false;

	if (inp[0] != '-' && !aNumber(inp[0]))
	{
		return false;
	}
	for (int i = 1; i < inp.size() - 1; i++)
	{
		nSym = inp[i + 1];
		pSym = inp[i - 1];

		if (aNumber(inp[i]))
		{
			if (!aNumber(nSym) && nSym != '.' && nSym != 'e')
			{
				return false;
			}
		}
		else if (inp[i] == '.')
		{
			if (point_already_exists || e_already_exists || !aNumber(pSym) || !aNumber(nSym) && nSym != 'e')
			{
				return false;
			}
			point_already_exists = true;
		}
		else if (inp[i] == 'e')
		{
			if (e_already_exists || !aNumber(pSym) && pSym != '.' || !aNumber(nSym) && nSym != '-' && nSym != '+')
			{
				return false;
			}
			e_already_exists = true;
		}
		else if (inp[i] == '-' || inp[i] == '+')
		{
			if (pSym != 'e' || !aNumber(nSym))
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	if (!aNumber(inp[inp.size() - 1]) && (inp[inp.size() - 1] != '.' || point_already_exists || e_already_exists))
	{
		return false;
	}
	return true;
}

void TArithmetic::parser()
{
	string multilex = "_";
	int j = -1;
	for (int i = 0; i < infix.size(); i++)
	{
		if (find_operation(infix[i]) && multilex[multilex.size() - 1] != 'e')
		{
			if (infix[i] == '-' && (i == 0 || (find_operation(infix[i - 1]) && infix[i - 1] != ')')))
			{
				lexems[++j] = new Operation('~');
			}
			else
			{
				if (infix[i] == '(' || infix[i] == ')')
				{
					postfix_count--;
				}
				if (i != 0 && infix[i - 1] != ')' && infix[i] != '(')
				{
					if (aNumber(infix[i - 1]) || infix[i - 1] == '.')
					{
						lexems[++j] = new Constant(multilex);
					}
					else
					{
						lexems[++j] = new Variable(multilex);
					}
					multilex = "_";
				}
				lexems[++j] = new Operation(infix[i]);
			}
			operations_count++;
		}
		else
		{
			if (multilex == "_")
			{
				multilex = infix[i];
			}
			else
			{
				multilex += infix[i];
			}
		}
	}
	if (infix[infix.size() - 1] != ')')
	{
		if (aNumber(infix[infix.size() - 1]) || infix[infix.size() - 1] == '.')
		{
			lexems[++j] = new Constant(multilex);
		}
		else
		{
			lexems[++j] = new Variable(multilex);
		}
	}
	lexems_count = j + 1;
	postfix_count += lexems_count;
}

void TArithmetic::toPostfix()
{
	const int operations_size = (operations_count == 0) ? 1 : operations_count;
	Stack<Lexem*> operations(operations_size);
	int j = -1;
	for (int i = 0; i < lexems_count; i++)
	{
		if (lexems[i]->what() == "Operation")
		{
			if (!operations.Empty())
			{
				if (lexems[i]->Get() == ")")
				{
					operations_count -= 2;
					while (operations.show_top()->Get() != "(")
					{
						postfix[++j] = operations.pop();
					}
					operations.pop();  // pop "("
				}
				else if (lexems[i]->Get() != "(" && lexems[i]->Get() != "~")
				{
					while (!operations.Empty() && operations.show_top()->Value() >= lexems[i]->Value())
					{
						postfix[++j] = operations.pop();
					}
				}
			}
			if (lexems[i]->Get() != ")")
			{
				operations.push(lexems[i]);
			}
		}
		else
		{
			postfix[++j] = lexems[i];
		}
	}
	while (!operations.Empty())
	{
		postfix[++j] = operations.pop();
	}
}

TArithmetic::TArithmetic(const string& inf) : infix(inf)
{
	const string check = find_error();
	if (check != "CORRECT")  // if error exists
	{
		throw "Incorrect infix form! " + check;
	}
	lexems = new Lexem * [infix.size()];
	parser();
	postfix = new Lexem * [postfix_count];
	toPostfix();
}

const string TArithmetic::GetPostfix() const
{
	string tmp = postfix[0]->Get();
	for (int i = 1; i < postfix_count; i++)
	{
		if (postfix[i]->Get() == "~")
		{
			tmp += " -";
		}
		else
		{
			tmp += " " + postfix[i]->Get();
		}
	}
	return tmp;
}

const double TArithmetic::Calculate()
{
	Stack<double> values(postfix_count - operations_count);
	std::map<string, string> operands;
	string input_value;
	int i;
	for (i = 0; i < postfix_count; i++)
	{
		if (postfix[i]->what() == "Variable")
		{
			if (!operands.count(postfix[i]->Get()))
			{
				std::cout << std::endl << postfix[i]->Get() << " = ";
				std::getline(std::cin, input_value);

				if (!check_input(input_value))
				{
					throw "Bad input: " + input_value;
				}
				operands.insert({ postfix[i]->Get(), input_value });
			}
			postfix[i]->SetValue(operands[postfix[i]->Get()]);
		}
	}
	double rvalue;
	double lvalue;
	for (i = 0; i < postfix_count; i++)
	{
		if (postfix[i]->what() == "Constant" || postfix[i]->what() == "Variable")
		{
			values.push(postfix[i]->Value());
		}
		else
		{
			if (postfix[i]->Get() == "~")
			{
				values.push(-values.pop());
			}
			else if (postfix[i]->Get() == "+")
			{
				values.push(values.pop() + values.pop());
			}
			else if (postfix[i]->Get() == "-")
			{
				values.push(-values.pop() + values.pop());
			}
			else if (postfix[i]->Get() == "*")
			{
				values.push(values.pop() * values.pop());
			}
			else if (postfix[i]->Get() == "/")
			{
				rvalue = values.pop();
				if (rvalue == 0.0)
				{
					string ZeroDivisionError = "ERROR: Division by zero";
					throw ZeroDivisionError;
				}
				lvalue = values.pop();
				values.push(lvalue / rvalue);
			}
		}
	}
	return values.pop();
}

TArithmetic::~TArithmetic()
{
	for (int i = 0; i < lexems_count; i++)
	{
		delete lexems[i];
	}
	delete[] lexems;
	delete[] postfix;
}