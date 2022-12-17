// реализация функций и классов для вычисления арифметических выражений

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
		value = 0;
	}
	else if (val == "+" || val == "-")
	{
		value = 1;
	}
	else if (val == "*" || val == "/")
	{
		value = 2;
	}
	else if (val == "~")
	{
		value = 3;
	}
	else
	{
		value = 4;
	}
}

double TArithmetic::Operand::toNumeric(const string& strlex)
{
	const int strlex_size = strlex.size();
	double degree_indicator = 0.0;
	double set_value = 0.0;
	double sign = 1.0;

	const int point_index = strlex.find('.');
	const int e_index = strlex.find('e');

	string after_e = "";
	double e_degree_indicator = 0;

	if (strlex[0] == '-')
	{
		sign *= -1.0;
		degree_indicator--;
	}
	else if (strlex[0] == '+')
	{
		degree_indicator--;
	}
	if (point_index == string::npos)
	{
		if (e_index != string::npos)
		{
			degree_indicator += e_index;
		}
		else
		{
			degree_indicator += strlex_size;
		}
	}
	else
	{
		degree_indicator += point_index;

	}
	if (e_index != string::npos)
	{
		for (int i = e_index + 1; i < strlex_size; i++)
		{
			after_e += strlex[i];
		}
		e_degree_indicator = toNumeric(after_e);
	}
	for (const char symb : strlex)
	{
		if (symb == 'e')
		{
			break;
		}
		else if (symb != '-' && symb != '+' && symb != '.')
		{
			set_value += (symb - '0') * pow(10.0, --degree_indicator);
		}
	}
	if (e_index != string::npos)
	{
		set_value *= pow(10.0, e_degree_indicator);
	}
	return sign * set_value;
}

void TArithmetic::Constant::SetValue(const string& val)
{
	value = toNumeric(val);
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
	value = toNumeric(val);
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

bool TArithmetic::isDigit(const char& tmplex)
{
	if (tmplex >= '0' && tmplex <= '9')
	{
		return true;
	}
	return false;
}

bool TArithmetic::isAlpha(const char& tmplex)
{
	if (tmplex >= 'a' && tmplex <= 'z')
	{
		return true;
	}
	return false;
}

const string TArithmetic::find_error()
{
	const int max_i = infix.size() - 1;

	int open_count = 0;
	int close_count = 0;

	char sym = infix[0];
	char nSym;
	string wrong_infix = "Unexpected lexem: ";

	wrong_infix += sym;
	if (sym != '-' && !isAlpha(sym) && !isDigit(sym) && sym != '(')
	{
		return wrong_infix + "<-";
	}
	else
	{
		for (int i = 0; i < max_i; i++)
		{
			sym = infix[i];
			nSym = infix[i + 1];
			wrong_infix += nSym;

			if (sym == '(')
			{
				open_count++;
				if (nSym != '(' && nSym != '-' && (!isAlpha(nSym) || nSym == 'e') && !isDigit(nSym))
				{
					return wrong_infix + "<-";
				}
			}
			else if (sym == ')')
			{
				close_count++;
				if (nSym == '(' || !find_operation(nSym))
				{
					return wrong_infix + "<-";
				}
			}
			else if (find_operation(sym))
			{
				if (nSym != '-' && nSym != '(' && (!isAlpha(nSym) || nSym == 'e') && !isDigit(nSym))
				{
					return wrong_infix + "<-";
				}
			}
			else if (isAlpha(sym) && sym != 'e')
			{
				if (!isAlpha(nSym) && (nSym == '(' || !find_operation(nSym)))
				{
					return wrong_infix + "<-";
				}
			}
			else if (isDigit(sym))
			{
				if (!isDigit(nSym) && nSym != '.' && (nSym == '(' || !find_operation(nSym)) && nSym != 'e')
				{
					return wrong_infix + "<-";
				}
			}
			else if (sym == '.')
			{
				if (!isDigit(nSym))
				{
					return wrong_infix + "<-";
				}
			}
			else if (sym == 'e')
			{
				if (i == 0)
				{
					return wrong_infix + "<-" + "(invalid use of 'e' lexem)";
				}
				else if (!isDigit(infix[i - 1]) || nSym != '-' && nSym != '+' && !isDigit(nSym))
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
	sym = infix[max_i];
	if (sym == ')')
	{
		close_count++;
	}
	else if ((!isAlpha(sym) || sym == 'e') && !isDigit(sym))
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
	const int max_i = inp.size() - 1;
	char sym = inp[0];
	char nSym;
	char pSym;

	if (sym != '-' && !isDigit(sym))
	{
		return false;
	}
	for (int i = 1; i < max_i; i++)
	{
		sym = inp[i];
		nSym = inp[i + 1];
		pSym = inp[i - 1];

		if (isDigit(sym))
		{
			if (!isDigit(nSym) && nSym != '.' && nSym != 'e')
			{
				return false;
			}
		}
		else if (sym == '.')
		{
			if (!isDigit(pSym) || !isDigit(nSym))
			{
				return false;
			}
		}
		else if (sym == 'e')
		{
			if (!isDigit(pSym) || !isDigit(nSym) && nSym != '-' && nSym != '+')
			{
				return false;
			}
		}
		else if (sym == '-' || sym == '+')
		{
			if (pSym != 'e' || !isDigit(nSym))
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	if (!isDigit(inp[max_i]))
	{
		return false;
	}
	return true;
}

void TArithmetic::parser()
{
	const int infix_size = infix.size();
	string multilex = "_";  // a constant or variable name will be built here, '_' as empty lexem
	int j = -1;
	char lex;

	for (int i = 0; i < infix_size; i++)
	{
		lex = infix[i];

		if (find_operation(lex) && multilex[multilex.size() - 1] != 'e')
		{
			if (lex == '-' && (i == 0 || (find_operation(infix[i - 1]) && infix[i - 1] != ')')))
			{
				lexems[++j] = new Operation('~');
			}
			else
			{
				if (lex == '(' || lex == ')')
				{
					postfix_count--;  // postfix form does not contain brackets
				}
				if (i != 0 && infix[i - 1] != ')' && lex != '(')  // if we encountered a binary operation,
				{                                                 // then there was an operand or bracket before that
					if (isDigit(infix[i - 1]) || lex == '.')
					{
						lexems[++j] = new Constant(multilex);
					}
					else
					{
						lexems[++j] = new Variable(multilex);
					}
					multilex = "_";
				}
				lexems[++j] = new Operation(lex);
			}
			operations_count++;
		}
		else
		{
			if (multilex == "_")
			{
				multilex = lex;
			}
			else
			{
				multilex += lex;
			}
		}
	}
	if (lex != ')')
	{
		if (isDigit(lex))
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
	const int operations_size = (operations_count == 0) ? 1 : operations_count;  // Stack size does not be zero
	Stack<Lexem*> operations(operations_size);

	Lexem* this_top;
	Lexem* lex;

	int j = -1;

	for (int i = 0; i < lexems_count; i++)
	{
		if (lexems[i]->what() == "Operation")
		{
			lex = lexems[i];
			if (!operations.isEmpty())
			{
				this_top = operations.show_top();
				if (lex->Get() == ")")
				{
					operations_count -= 2;
					while (this_top->Get() != "(")
					{
						postfix[++j] = operations.pop();
						this_top = operations.show_top();
					}
					operations.pop();  // pop "("
				}
				else if (lex->Get() != "(" && lex->Get() != "~")
				{
					while (this_top->Value() >= lex->Value())
					{
						postfix[++j] = operations.pop();
						if (operations.isEmpty())
						{
							break;
						}
						else
						{
							this_top = operations.show_top();
						}
					}
				}
			}
			if (lex->Get() != ")")
			{
				operations.push(lex);
			}
		}
		else
		{
			postfix[++j] = lexems[i];
		}
	}
	while (!operations.isEmpty())
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
	Lexem* this_lex;
	int i;

	for (i = 0; i < postfix_count; i++)
	{
		this_lex = postfix[i];

		if (this_lex->what() == "Variable")
		{
			if (!operands.count(this_lex->Get()))
			{
				std::cout << std::endl << this_lex->Get() << " = ";
				std::getline(std::cin, input_value);  // space-controlled input

				if (!check_input(input_value))
				{
					throw "Bad input: " + input_value;
				}
				operands.insert({ this_lex->Get(), input_value });
			}
			postfix[i]->SetValue(operands[this_lex->Get()]);
		}
	}

	double rvalue;
	double lvalue;
	for (i = 0; i < postfix_count; i++)
	{
		this_lex = postfix[i];

		if (this_lex->what() == "Constant" || this_lex->what() == "Variable")
		{
			values.push(this_lex->Value());
		}
		else
		{
			if (this_lex->Get() == "~")
			{
				values.push(-values.pop());
			}
			else if (this_lex->Get() == "+")
			{
				values.push(values.pop() + values.pop());
			}
			else if (this_lex->Get() == "-")
			{
				values.push(-values.pop() + values.pop());  // like '+' but with a MINUS for the first value
			}
			else if (this_lex->Get() == "*")
			{
				values.push(values.pop() * values.pop());
			}
			else if (this_lex->Get() == "/")
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
