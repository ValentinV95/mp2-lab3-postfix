// реализация функций и классов для вычисления арифметических выражений
#include <arithmetic.h>
#include <stack.h>

std::string Lex::LexType()
{
	return name;
}
std::string Lex::GetLex()
{
	return lexem;
}

int Lex::GetPrior()
{
	return pr;
}

double Lex::value()
{
	return double_spot;
}

operations::operations(char op)
{
	if (op == '(' || op == ')') {
		name = "brackets";

	}
	if (op == '+' || op == '-' || op == '*' || op == '/') {
		name = "binary";

	}
	if (op == '~') {
		name = "unary";

	}
	lexem = op;
	SetPrior(op);
}
void operations::SetPrior(char op)
{
	if (op == '+' || op == '-')
	{
		pr = 1;
	}
	else if (op == '*' || op == '/')
	{
		pr = 2;
	}
	else if (op == '~')
	{
		pr = 3;
	}
	else if (op == '(' || op == ')')
	{
		pr = 0;
	}
	else
	{
		std::cout << "unacceptable symbols";
	}
}

void operands::SetPrior(char op)
{
	pr = 2;
}

Num::Num(std::string lex)
{
	name = "digit";
	lexem = lex;
	double_spot = NumConv(lex);
	pr = 2;
}

Num::Num(double value)
{
	name = "digit";
	pr = 2;
	double_spot = value;
}

Num::Num()
{
	name = "digit";
	double_spot = 0.;

}

Var::Var(std::string lex)
{
	name = "Var";
	pr = 2;
	lexem = lex;
}

double conv(std::string place)
{
	double res = 0.0;
	double pow = 0;
	for (int i = place.size()-1; i>=0; i--,pow+=1)
	{
		res += (place[i] - '0') * std::pow(10.0, pow);
	}
	return res;
}

double operands::NumConv(std::string strlex)
{
	if (strlex.size() == 0)
	{
		std::string lng = "incorrect digit form";
		throw(lng);
	}
	if (strlex[0] == '+')
		return NumConv(strlex.substr(1, strlex.size()));
	if (strlex[0] == '-')
	{
		return -1. * NumConv(strlex.substr(1, strlex.size()));
	}
	if (std::count(strlex.begin(), strlex.end(), '.') > 1 ||
		std::count(strlex.begin(), strlex.end(), 'E') > 1 ||
		(std::count(strlex.begin(), strlex.end(), '+') +
			std::count(strlex.begin(), strlex.end(), '-') +
			std::count(strlex.begin(), strlex.end(), '~') > 1))
	{
		std::string lng = "incorrect digit form";
		throw(lng);
	}
	int eps_ind = strlex.find('E');
	int dot_ind = strlex.find('.');

	double flag = 1.0;
	double digit = 0.0;
	std::string left_of_dot;
	std::string right_of_dot;
	std::string left_of_eps;
	std::string right_of_eps;

	if (eps_ind == std::string::npos)
	{
		if (dot_ind== std::string::npos)
		{	
			digit = conv(strlex);
			//std::cout << digit << '\n';
		}
		else
		{
			left_of_dot = lexem.substr(0, dot_ind);
			right_of_dot = lexem.substr(dot_ind + 1, lexem.size());
			if (left_of_dot.size() == 0 && right_of_dot.size() == 0)
			{
				std::string s = "incorrect digit form";
				throw (s);
			}
			int pow = -1 * right_of_dot.size();
			digit = conv(left_of_dot) + std::pow(10, pow) * conv(right_of_dot);
		}
	}
	else
	{
		if (dot_ind == std::string::npos) 
		{
			double sign = 1.;
			left_of_eps = lexem.substr(0, eps_ind);
			if (eps_ind != lexem.size() - 1 && (lexem[eps_ind + 1] == '+' || lexem[eps_ind + 1] == '-'))
			{
				if (lexem[eps_ind + 1] == '-')
					sign = -1.;
				right_of_eps = lexem.substr(eps_ind + 2, lexem.size());
			}
			else
				right_of_eps = lexem.substr(eps_ind + 1, lexem.size());
			if (right_of_eps.size() == 0 || left_of_eps.size() == 0)
			{
				std::string s = "incorrect digit form";
				throw (s);
			}
			double pow = sign * conv(right_of_eps);
			digit = conv(left_of_eps) * std::pow(10, pow);
		}
		else
		{
			left_of_eps = lexem.substr(0, eps_ind);
			right_of_eps = "1" + lexem.substr(eps_ind, lexem.size());
			digit = NumConv(left_of_eps) * NumConv(right_of_eps);
		}
	}
	return digit;
}


Arithmetic::Arithmetic(std::string infix)
{
	std::string symbols = infix;
	int index = symbols.find(' ');
	if (index != std::string::npos) {
		std::string error = "Space was found";
		throw error;

	}
	
	size = 6;
	lexem = new Lex * [size];
	if (symbols[0] == '-')
	{
		symbols[0] = '~';
	}
	for (size_t i = 1; i < symbols.size(); i++)
	{
		if ((symbols[i - 1] == '~'|| symbols[i - 1] == '-' || symbols[i - 1] == '*' || symbols[i - 1] == '/' || symbols[i - 1] == '+' || symbols[i - 1] == '(') && symbols[i] == '-')
		{
			symbols[i] = '~';
		}

	}
	this->infix = symbols;
	try
	{
		IncorrectSymbols();
		CheckBrackets();
	}
	catch (const std::string& error)
	{
		throw error;
	}
	
	
}

bool Arithmetic::IsOperation(char ch)
{
	if (ch == '~' || ch == '-' || ch == '+' || ch == '/' || ch == '*' || ch == '^' || ch == '(' || ch == ')')
		return true;
	else
		return false;
}

bool Arithmetic::CheckOp()
{
	for (int i = 0; i < infix.size(); i++)
		if (!IsDigit(infix[i]) && !IsOperation(infix[i]))
			return false;
	int Operands = 0, Operations = 0;
	for (int i = 0; i < infix.size(); i++)
	{
		if (infix[i] == '(' || infix[i] == ')')
		{
			i++;
			if (i == infix.size())
				break;
		}

		if (infix[i] == '-' || infix[i] == '+' || infix[i] == '/' || infix[i] == '*' || infix[i] == '^')
			Operations++;

		if (!IsOperation(infix[i]))
		{
			while (!IsOperation(infix[i]))
			{
				i++;
				if (i == infix.size())
					break;
			}
			i--;
			Operands++;
		}
	}
	if (Operands == Operations + 1)
		return true;
	else 
		return false;
}

bool Arithmetic::IsDigit(const char& dig)
{
	return (dig >= '0' && dig <= '9') || dig == '.' || dig == 'E';
}

bool Arithmetic::IsOperand(const char& lexem)
{
	if (int(lexem) >= 48 && int(lexem) <= 57)
		return true;
	else
		return false;
}

bool Arithmetic::IsNumber(std::string num)
{
	int pos_str = 0;
	if (num.size() != 0)
	{
		if (num[0] == '+' || num[0] == '-' || num[0] == '~')
		{
			pos_str = 1;
		}
		for (int i = pos_str; i < num.size(); i++)
		{
			if (!IsDigit(num[i]))
			{
				if ((num[i] == '+' || num[i] == '-') && num[i - 1] == 'E')
				{
					continue;
				}
				return false;
			}
		}
		return true;
	}
	return false;
}

bool Arithmetic::IsVar(const char& ch)
{
	return ch >= 'a' && ch <= 'z';
}

void Arithmetic::CheckBrackets()
{
	int LeftBrackets = 0, RightBrackets = 0;
	for (int i = 0; i < infix.size(); i++)
	{
		if (infix[i] == '(')
			LeftBrackets++;
		else if (infix[i] == ')')
			RightBrackets++;
	}
	if (LeftBrackets != RightBrackets)
	{
		std::string err = "Incorrect brackets";
		throw err;
	}
}

bool Arithmetic::IsVariable(std::string num)
{
	for (size_t i = 0; i < num.size(); i++)
	{
		if (!IsVar(num[i]))
			return false;		
	}
	return true;
}

bool Arithmetic::IsBrackets(const char& ch)
{
	return ch == '(' || ch == ')';
}
//void Arithmetic::CorrectOrder()
//{
//	if (lexem[0]->GetLex() == ")" || lexem[0]->LexType() == "binary")
//	{
//		std::string error = "At the beginning of an arithmetic expression can be: unary operations or '('!");
//		throw error;
//	}
//	if (lexem[0]->LexType() == "unary")
//	{
//	
//	}
//}


void Arithmetic::resize()//new mass data*2| 
{
	Lex** data = new Lex * [size * 2];
	for (size_t j = 0; j < size; j++)
	{
		data[j] = lexem[j];
	}
	if (lexem != nullptr)
		delete[] lexem;
	size *= 2;
	lexem = data;
}

void Arithmetic::IncorrectSymbols()
{
	for (size_t i = 0; i < infix.size(); i++)
	{
		if (!IsVar(infix[i]) && !IsDigit(infix[i]) && !IsBrackets(infix[i]) && !IsOperation(infix[i]) && infix[i] != ' ');
	}
}

void Arithmetic::VarValue()
{
	std::cout << '\n';
	std::map<std::string, std::string> VarValues;

	for (size_t i = 0; i < lex_size; i++)
	{
		if (lexem[i]->LexType() == "Var")
		{
			if (!VarValues.count(lexem[i]->GetLex()))
			{
				std::string str;
				std::cout << "\n    " << lexem[i]->GetLex() << " : ";
				std::cin >> str;
				VarValues.insert({ lexem[i]->GetLex(), str });
				if (!IsNumber(str))
				{
					std::string err = "Incorrect variable value ";
					throw err;
				}
			}
			try
			{
				Lex* n = new Num(VarValues[lexem[i]->GetLex()]);
				delete lexem[i];
				lexem[i] = n;
			}
			catch (const std::string& er)
			{
				throw er;
			}

		}
	}
}

void Arithmetic::Postfix()
{
	postfix = new Lex * [size];//Videlyaemaya pamyat'
	int index = 0;
	Stack<Lex*> stack;
	Lex* elem;
	for (size_t i = 0; i < lex_size; i++)
	{
		if (lexem[i]->LexType() == "brackets")
		{
			if (lexem[i]->GetLex() == "(")
			{
				stack.Push(lexem[i]);
			}
			else
			{
				elem = stack.Pop();
				while (elem->GetLex() != "(")
				{
					postfix[index] = elem;
					index++;
					elem = stack.Pop();
				}
			}
		}
		else if (lexem[i]->LexType() == "binary")
		{
			while (!stack.IsEmpty())
			{
				elem = stack.Pop();
				if (lexem[i]->GetPrior() <= elem->GetPrior())
				{
					postfix[index] = elem;
					index++;
				}
				else
				{
					stack.Push(elem);
					break;
				}
			}
			Lex* e = lexem[i];
			stack.Push(e);
		}
		else if (lexem[i]->LexType() == "unary")
		{
			Lex* e = lexem[i];
			stack.Push(e);
		}
		else
		{
			postfix[index] = lexem[i];
			index++;
		}

	}
	while (!stack.IsEmpty())
	{
		elem = stack.Pop();
		postfix[index] = elem;
		index++;
	}
	std::cout << "\n\n Postfix form : \n";
	for (size_t i = 0; i < index; i++)
	{
		std::cout << postfix[i]->GetLex() << ' ';
	}
	postfix_size = index;
	
}


void Arithmetic::Parser()
{
	std::string lex = "";
	lex_size = 0;
	for (size_t i = 0; i < infix.size(); i++)
	{
		if (IsOperation(infix[i]))
		{
			if ((infix[i] == '+' || infix[i] == '-') && infix[i - 1] == 'E')
			{
				lex += infix[i];

			}
			else
			{
				if (lex != "")
				{
					if (size == lex_size)
						resize();
					if (IsNumber(lex))
					{
						lexem[lex_size] = new Num(lex);
						lex_size++;
					}
					if (IsVariable(lex))
					{
						lexem[lex_size] = new Var(lex);
						lex_size++;
					}
					if (!IsNumber(lex) && (!IsVariable(lex)))
					{
						std::string error="incorrect form";
						throw error;
					}
					lex = "";
				}
				if (size == lex_size)
					resize();
				lexem[lex_size] = new operations(infix[i]);
				lex_size++;
			}

		}
		else
		{
			lex += infix[i];
		}
	}
	if (lex != "")
	{
		if (size == lex_size)
			resize();
	}
	if (lex != "")
	{
		if (size == lex_size)
			resize();
		if (IsNumber(lex))
		{
			lexem[lex_size] = new Num(lex);
			lex_size++;
		}
		if (IsVariable(lex))
		{
			lexem[lex_size] = new Var(lex);
			lex_size++;
		}
		if (!IsNumber(lex) && (!IsVariable(lex)))
		{
			std::string error = "incorrect form";
			throw error;
		}

	}

}

double Arithmetic::Calculate()
{
	try
	{
		Parser();
		VarValue();
		Postfix();

	}
	catch (const std::string& er)
	{
		throw er;
	}
	//Идешь циклом по постфикс(и)
	//Если встречается число закидываем в стек
	//Если встречается переменная, то делаем сравнения 
	//Если это унарная операция(~) тогда изымаем из стека 1 элемент *-1 закидываем в стек новое число 
	//Если это бинарная операция из стека достаем сначала правый операнд потом левый операнд 
	//right = steck.pop() - указатель на базовую лексему Lex*
	//После верхней записи left = stack.pop() 
	//Постфиксная форма не меняет порядок чисел она меняет порядок знаков
	//Чем раньше попал тем раньше ушел
	//В конце в стеке останется 1 элемент - это ответ , арифметическое выражение 
	Stack<double> stack;

	for (size_t i = 0; i < postfix_size; i++)
	{
		if (postfix[i]->LexType() == "digit")
		{
			Lex* op = postfix[i];
			double smth = op->value();
			stack.Push(smth);
		}
		else
		{
			std::string oper = postfix[i]->GetLex();
			if (oper == "+")
			{
				double right_op = stack.Pop();
				double left_op = stack.Pop();
				stack.Push(right_op + left_op);
			}
			else if (oper == "-")
			{
				double right_op = stack.Pop();
				double left_op = stack.Pop();
				stack.Push(left_op - right_op);
			}
			else if (oper == "*")
			{
				double right_op = stack.Pop();
				double left_op = stack.Pop();
				stack.Push(left_op * right_op);
			}
			else if (oper == "/")
			{
				double right_op = stack.Pop();
				double left_op = stack.Pop();
				if(right_op<=1e-5&&right_op>=-1e-5)
				{
					std::string lng = "0 div";
					throw(lng);
				}
				stack.Push(left_op / right_op);
			}
			else if (oper == "~")
			{	
				double right_op = stack.Pop();
				stack.Push(-1*right_op);
			}
		}	


	}
	return stack.Pop();
}



Arithmetic::~Arithmetic()
{
	for (int i = 0; i < lex_size; i++)
	{
		if(lexem[i] != nullptr)
			delete lexem[i];

	}
	if (lexem != nullptr)
		delete[] lexem;
	if (postfix != nullptr)
		delete[] postfix;
}