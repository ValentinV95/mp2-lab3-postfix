#include "arithmetic.h"

const string Arithmetic::Lexem::GetLexem() const
{
	return lexem;
}
const double Arithmetic::Lexem::Value() const
{
	return priority;
}
const string Arithmetic::Lexem::Type() const
{
	return name;
}

Arithmetic::Lexem::~Lexem()
{

}

Arithmetic::Operation::Operation(const char& data)
{
	name = "Operation";
	lexem = data;
	SetPriority(lexem);
}

void Arithmetic::Operation::SetPriority(const string& val)
{
	if (val == "(" || val == ")")
	{
		priority = 0.0;
	}
	else if (val == "+" || val == "-")
	{
		priority = 1.0;
	}
	else if (val == "*" || val == "/")
	{
		priority = 2.0;
	}
	else if (val == "~")
	{
		priority = 3.0;
	}
	else
	{
		priority = 4.0;
	}
}

double Arithmetic::Operand::Convert(const string& strlexem)
{
	double Degree = 0.0;
	double e_DegreeIndicator = 0.0;
	double set_value = 0.0;
	double sign = 1.0;
	
	string After_e = "";

	if (strlexem[0] == '+')
	{
		
		Degree--;
	}
	else if (strlexem[0] == '-')
	{
		sign *= -1.0;
		Degree--;
	}
	if (strlexem.find('.') == string::npos)
	{
		if (strlexem.find('e') != string::npos)
		{
			Degree += strlexem.find('e');
		}
		else
		{
			Degree += strlexem.size();
		}
	}
	else
	{
		Degree += strlexem.find('.');

	}
	if (strlexem.find('e') != string::npos)
	{
		for (int i = strlexem.find('e') + 1; i < strlexem.size(); i++)
		{
			After_e += strlexem[i];
		}
		e_DegreeIndicator = Convert(After_e);
	}
	for (const char symbol : strlexem)
	{
		if (symbol == 'e')
		{
			break;
		}
		else if (symbol != '-' && symbol != '+' && symbol != '.')
		{
			set_value += (symbol - '0') * pow(10.0, --Degree);
		}
	}
	if (strlexem.find('e') != string::npos)
	{
		set_value *= pow(10.0, e_DegreeIndicator);
	}
	return sign * set_value;
}

void Arithmetic::Constant::SetPriority(const string& val)
{
	priority = Convert(val);
}

Arithmetic::Constant::Constant(const string& data)
{
	name = "Constant";
	lexem = data;
	SetPriority(lexem);
}

Arithmetic::Variable::Variable(const string& data)
{
	name = "Variable";
	lexem = data;
	priority = 0;
}

void Arithmetic::Variable::SetPriority(const string& val)
{
	priority = Convert(val);
}

bool Arithmetic::FindOperation(const char& tmplexem)
{
	char operations[7] = { '(', ')', '+', '-', '*', '/' };
	for (const char lexem : operations)
	{
		if (lexem == tmplexem)
		{
			return true;
		}
	}
	return false;
}

bool Arithmetic::isDigit(const char& tmplexem)
{
	return (tmplexem >= '0') && (tmplexem <= '9');
}

bool Arithmetic::isLetter(const char& tmplexem)
{
	return (tmplexem >= 'a') && (tmplexem <= 'z');
}

const string Arithmetic::FindError()
{
	int open_count = 0;
	int close_count = 0;
	bool e_already_exists = false;
	bool point_already_exists = false;
	char nSym;  // next
	string Wrong = "Unexpected lexemem: ";

	Wrong += infix[0];
	if (infix[0] != '-' && !isLetter(infix[0]) && !isDigit(infix[0]) && infix[0] != '(')
	{
		return Wrong;
	}
	else
	{
		for (int i = 0; i < infix.size() - 1; i++)
		{
			nSym = infix[i + 1];
			Wrong += nSym;

			if (infix[i] == '(')
			{
				open_count++;
				if (nSym != '(' && nSym != '-' && (!isLetter(nSym) || nSym == 'e') && !isDigit(nSym))
				{
					return Wrong;
				}
			}
			else if (infix[i] == ')')
			{
				e_already_exists = false;
				point_already_exists = false;
				close_count++;
				if (nSym == '(' || !FindOperation(nSym))
				{
					return Wrong;
				}
			}
			else if (FindOperation(infix[i]))
			{
				if (i != 0 && infix[i - 1] != 'e')
				{
					e_already_exists = false;
					point_already_exists = false;
				}
				if (nSym != '-' && nSym != '(' && (!isLetter(nSym) || nSym == 'e') && !isDigit(nSym))
				{
					return Wrong;
				}
			}
			else if (isLetter(infix[i]) && infix[i] != 'e')
			{
				if (!isLetter(nSym) && (nSym == '(' || !FindOperation(nSym)))
				{
					return Wrong;
				}
			}
			else if (isDigit(infix[i]))
			{
				if (nSym == '.')
				{
					if (point_already_exists || e_already_exists)
					{
						return Wrong;
					}
				}
				else if (!isDigit(nSym) && (nSym == '(' || !FindOperation(nSym)) && (nSym != 'e' || e_already_exists))
				{
					return Wrong;
				}
			}
			else if (infix[i] == '.')
			{
				point_already_exists = true;
				if (!isDigit(nSym) && nSym != 'e' && (!FindOperation(nSym) || nSym == '('))
				{
					return Wrong;
				}
			}
			else if (infix[i] == 'e')
			{
				e_already_exists = true;
				if (i == 0)
				{
					return Wrong + "(invalid use of 'e' lexemem)";
				}
				else if (!isDigit(infix[i - 1]) && infix[i - 1] != '.' || nSym != '-' && nSym != '+' && !isDigit(nSym))
				{
					return Wrong + "(invalid use of 'e' lexemem)";
				}
			}
			else
			{
				return Wrong;
			}
		}
	}
	char lSym = infix[infix.size() - 1];
	if (lSym == ')')
	{
		close_count++;
	}
	else if ((!isLetter(lSym) || lSym == 'e') && !isDigit(lSym) && (lSym != '.' || point_already_exists || e_already_exists))
	{
		return Wrong;
	}
	if (open_count != close_count)
	{
		return "Number of opening and closing brackets doesn't match";
	}
	return "correct";
}

bool Arithmetic::CheckInput(const string& inp)
{
	char nSym;
	char pSym;
	bool e_already_exists = false;
	bool point_already_exists = false;

	if (inp[0] != '-' && !isDigit(inp[0]))
	{
		return false;
	}
	for (int i = 1; i < inp.size() - 1; i++)
	{
		nSym = inp[i + 1];
		pSym = inp[i - 1];

		if (isDigit(inp[i]))
		{
			if (!isDigit(nSym) && nSym != '.' && nSym != 'e')
			{
				return false;
			}
		}
		else if (inp[i] == '.')
		{
			if (point_already_exists || e_already_exists || !isDigit(pSym) || !isDigit(nSym) && nSym != 'e')
			{
				return false;
			}
			point_already_exists = true;
		}
		else if (inp[i] == 'e')
		{
			if (e_already_exists || !isDigit(pSym) && pSym != '.' || !isDigit(nSym) && nSym != '-' && nSym != '+')
			{
				return false;
			}
			e_already_exists = true;
		}
		else if (inp[i] == '-' || inp[i] == '+')
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
	if (!isDigit(inp[inp.size() - 1]) && (inp[inp.size() - 1] != '.' || point_already_exists || e_already_exists))
	{
		return false;
	}
	return true;
}

void Arithmetic::Parser()
{
	string multilexem = "_";
	int j = -1;
	for (int i = 0; i < infix.size(); i++)
	{
		if (FindOperation(infix[i]) && multilexem[multilexem.size() - 1] != 'e')
		{
			if (infix[i] == '-' && (i == 0 || (FindOperation(infix[i - 1]) && infix[i - 1] != ')')))
			{
				lexemems[++j] = new Operation('~');
			}
			else
			{
				if (infix[i] == '(' || infix[i] == ')')
				{
					postfix_count--;
				}
				if (i != 0 && infix[i - 1] != ')' && infix[i] != '(') 
				{                                                      
					if (isDigit(infix[i - 1]) || infix[i - 1] == '.')
					{
						lexemems[++j] = new Constant(multilexem);
					}
					else
					{
						lexemems[++j] = new Variable(multilexem);
					}
					multilexem = "_";
				}
				lexemems[++j] = new Operation(infix[i]);
			}
			operations_count++;
		}
		else
		{
			if (multilexem == "_")
			{
				multilexem = infix[i];
			}
			else
			{
				multilexem += infix[i];
			}
		}
	}
	if (infix[infix.size() - 1] != ')')
	{
		if (isDigit(infix[infix.size() - 1]) || infix[infix.size() - 1] == '.')
		{
			lexemems[++j] = new Constant(multilexem);
		}
		else
		{
			lexemems[++j] = new Variable(multilexem);
		}
	}
	lexemems_count = j + 1;
	postfix_count += lexemems_count;
}

void Arithmetic::toPostfix()
{
	const int operations_size = (operations_count == 0) ? 1 : operations_count;  // Stack size does not be zero
	Stack<Lexem*> operations(operations_size);
	int j = -1;
	for (int i = 0; i < lexemems_count; i++)
	{
		if (lexemems[i]->Type() == "Operation")
		{
			if (!operations.IsEmpty())
			{
				if (lexemems[i]->GetLexem() == ")")
				{
					operations_count -= 2;
					while (operations.Top()->GetLexem() != "(")
					{
						postfix[++j] = operations.Pop();
					}
					operations.Pop();  // Pop "("
				}
				else if (lexemems[i]->GetLexem() != "(" && lexemems[i]->GetLexem() != "~")
				{
					while (!operations.IsEmpty() && operations.Top()->Value() >= lexemems[i]->Value())
					{
						postfix[++j] = operations.Pop();
					}
				}
			}
			if (lexemems[i]->GetLexem() != ")")
			{
				operations.Push(lexemems[i]);
			}
		}
		else
		{
			postfix[++j] = lexemems[i];
		}
	}
	while (!operations.IsEmpty())
	{
		postfix[++j] = operations.Pop();
	}
}

Arithmetic::Arithmetic(const string& inf) : infix(inf)
{
	const string check = FindError();
	if (check != "correct")  
	{
		throw "Incorrect infix form! " + check;
	}
	lexemems = new Lexem * [infix.size()];
	Parser();
	postfix = new Lexem * [postfix_count];
	toPostfix();
}

const string Arithmetic::GetPostfix() const
{
	string tmp = postfix[0]->GetLexem();
	for (int i = 1; i < postfix_count; i++)
	{
		if (postfix[i]->GetLexem() == "~")
		{
			tmp += " -";
		}
		else
		{
			tmp += " " + postfix[i]->GetLexem();
		}
	}
	return tmp;
}

const double Arithmetic::Calculate()
{
	Stack<double> values(postfix_count - operations_count);
	std::map<string, string> operands;
	string input_value;
	int i;
	for (i = 0; i < postfix_count; i++)
	{
		if (postfix[i]->Type() == "Variable")
		{
			if (!operands.count(postfix[i]->GetLexem()))
			{
				std::cout << std::endl << postfix[i]->GetLexem() << " = ";
				std::getline(std::cin, input_value);  // space-controlled input

				if (!CheckInput(input_value))
				{
					throw "Incorrect input: " + input_value;
				}
				operands.insert({ postfix[i]->GetLexem(), input_value });
			}
			postfix[i]->SetPriority(operands[postfix[i]->GetLexem()]);
		}
	}
	double rvalue;
	double lvalue;
	for (i = 0; i < postfix_count; i++)
	{
		if (postfix[i]->Type() == "Constant" || postfix[i]->Type() == "Variable")
		{
			values.Push(postfix[i]->Value());
		}
		else
		{
			if (postfix[i]->GetLexem() == "~")
			{
				values.Push(-values.Pop());
			}
			else if (postfix[i]->GetLexem() == "+")
			{
				values.Push(values.Pop() + values.Pop());
			}
			else if (postfix[i]->GetLexem() == "-")
			{
				values.Push(-values.Pop() + values.Pop());  // like '+' but with a MINUS for the first priority
			}
			else if (postfix[i]->GetLexem() == "*")
			{
				values.Push(values.Pop() * values.Pop());
			}
			else if (postfix[i]->GetLexem() == "/")
			{
				rvalue = values.Pop();
				if (rvalue == 0.0)
				{
					string ZeroDivisionError = "ERROR: Division by zero";
					throw ZeroDivisionError;
				}
				lvalue = values.Pop();
				values.Push(lvalue / rvalue);
			}
		}
	}
	return values.Pop();
}

Arithmetic::~Arithmetic()
{
	for (int i = 0; i < lexemems_count; i++)
	{
		delete lexemems[i];
	}
	delete[] lexemems;
	delete[] postfix;
}