// реализация функций и классов для вычисления арифметических выражений

#include <arithmetic.h>
#include <string>
#include <iostream>
#include <math.h>
#include <locale>
#include <stack.h>
#include <map>

//BASELEXEM
std::string Arithmetic::BaseLexem::LexemType()
{
	return name;
}

std::string Arithmetic::BaseLexem::GetLexem()
{
	return lexem;
}

double Arithmetic::BaseLexem::Value()
{
	return double_performance;
}

int Arithmetic::BaseLexem::GetSatrtPos()
{
	return pos_start;
}
int Arithmetic::BaseLexem::GetEndPos()
{
	return pos_end;
}
int Arithmetic::BaseLexem::GetPriority()
{
	return priority;
}


// OPERATIONS

Arithmetic::Operation::Operation(char ch, int pos_start, int pos_end)
{
	if (ch == '+' || ch == '-' || ch == '*' || ch == '/')
	{
		name = "BinaryOperation";
		if (ch == '+' || ch == '-')
			priority = 1;
		else
			priority = 2;
	}
	else if (ch == '~')
	{
		name = "UnaryOperation";
		priority = 3;
	}
	else if (ch == ')' || ch == '(')
	{
		name = "Brackets";
		priority = 0;
	}
	lexem = ch;
	this->pos_start = pos_start;
	this->pos_end = pos_end;
}



//OPERAND

Arithmetic::Number::Number(std::string lexem, int pos_start, int pos_end)
{
	name = "Number";
	this->lexem = lexem;
	double_performance = ConvertNumber(lexem);
	priority = 4;
	this->pos_start = pos_start;
	this->pos_end = pos_end;
}

Arithmetic::Number::Number(double value, int pos_start, int pos_end)
{
	name = "Number";
	priority = 4;
	double_performance = value;
	this->pos_start = pos_start;
	this->pos_end = pos_end;
}

Arithmetic::Number::Number()
{
	name = "Number";
	priority = 4;
	double_performance = 0.;
	this->pos_start = 0;
	this->pos_end = 0;
}

Arithmetic::Var::Var(std::string lexem, int pos_start, int pos_end)
{
	name = "Var";
	priority = 4;
	this->lexem = lexem;
	this->pos_start = pos_start;
	this->pos_end = pos_end;
}

double convert(std::string part)
{
	double num = 0;
	int pow = 0;
	for (int i = part.size() - 1; i >= 0; i--, pow++)
	{
		num += (part[i] - '0') * std::pow(10.0, pow);
	}
	return num;
}

double Arithmetic::Operand::ConvertNumber(std::string lexem)
{
	setlocale(LC_ALL, "Russian");
	if (lexem.size() == 0)
	{
		std::string s = "некорректный формат числа!";
		throw (s);
	}
	if (lexem[0] == '-')
		return -1. * ConvertNumber(lexem.substr(1, lexem.size()));
	if (lexem[0] == '+')
		return ConvertNumber(lexem.substr(1, lexem.size()));
	if (std::count(lexem.begin(), lexem.end(), '.') > 1 ||
		std::count(lexem.begin(), lexem.end(), 'E') > 1 ||
		(std::count(lexem.begin(), lexem.end(), '+') +
			std::count(lexem.begin(), lexem.end(), '-') +
			std::count(lexem.begin(), lexem.end(), '~') > 1))
	{

		std::string s = "некорректный формат числа!";
		throw (s);
	}

	int point_index = lexem.find('.');
	int e_index = lexem.find('E');

	double sign = 1.;

	double number = 0.;

	std::string part_before_point;
	std::string part_after_point;
	std::string part_before_e;
	std::string part_after_e;

	if (e_index == std::string::npos)
	{
		if (point_index == std::string::npos)
		{
			number = convert(lexem);
		}
		else
		{
			part_before_point = lexem.substr(0, point_index);
			part_after_point = lexem.substr(point_index + 1, lexem.size());
			if (part_before_point.size() == 0 && part_after_point.size() == 0)
			{
				std::string s = "некорректный формат числа!";
				throw (s);
			}
			int pow = -1 * part_after_point.size();
			number = convert(part_before_point) + std::pow(10, pow) * convert(part_after_point);
		}
	}
	else
	{
		if (point_index == std::string::npos) // only E
		{
			double sign = 1.;
			part_before_e = lexem.substr(0, e_index);
			if (e_index != lexem.size() - 1 && (lexem[e_index + 1] == '+' || lexem[e_index + 1] == '-'))
			{
				if (lexem[e_index + 1] == '-')
					sign = -1.;
				part_after_e = lexem.substr(e_index + 2, lexem.size());
			}
			else
				part_after_e = lexem.substr(e_index + 1, lexem.size());
			if (part_after_e.size() == 0 || part_before_e.size() == 0)
			{
				std::string s = "некорректный формат числа!";
				throw (s);
			}
			double pow = sign * convert(part_after_e);
			number = convert(part_before_e) * std::pow(10, pow);
		}
		else
		{
			part_before_e = lexem.substr(0, e_index);
			part_after_e = "1" + lexem.substr(e_index, lexem.size());
			number = ConvertNumber(part_before_e) * ConvertNumber(part_after_e);
		}
	}
	return number;
}








//ARITHMETIC

Arithmetic::Arithmetic(const std::string& infix)
{
	std::string str = infix;
	while (str.find(' ') != std::string::npos)
	{
		str.erase(str.find(' '), 1);
	}
	this->infix = str;
	size = 5;
	lexems = new BaseLexem * [size];
	try
	{
		FindIncorrectSymbols();
		Parser();
		CheckLexemOrder();
	}
	catch (const std::string& err)
	{
		throw err;
	}
}

Arithmetic::~Arithmetic()
{
	for (int i = 0; i <= last; i++)
	{
		if (lexems[i] != nullptr)
			delete lexems[i];
	}
	if (lexems != nullptr)
		delete[] lexems;
	if (postfix != nullptr)
		delete[] postfix;
}


bool Arithmetic::IsOperation(const char& ch)
{
	std::string operations = "+-*/()~";
	return operations.find(ch) != std::string::npos;
}


bool Arithmetic::IsNumber(const char& ch)
{
	return (ch >= '0' && ch <= '9') || ch == '.' || ch == 'E';
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
			if (!IsNumber(num[i]))
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

bool Arithmetic::IsVar(std::string num)
{
	if (num.size() != 0)
	{
		for (size_t i = 0; i < num.size(); i++)
		{
			if (!(num[i] >= 'a' && num[i] <= 'z'))
				return false;
		}
		return true;
	}
	return false;
}



void Arithmetic::resize()
{
	BaseLexem** tmp = new BaseLexem * [size * 2];
	for (size_t j = 0; j < size; j++)
	{
		tmp[j] = lexems[j];
	}
	if (lexems != nullptr)
		delete[] lexems;
	size *= 2;
	lexems = tmp;
}

std::string Arithmetic::ShowError(int index, std::string text)
{


	std::string str_(infix.size(), '-');
	str_[index] = '^';
	std::string s = "\n" + infix + "\n" + str_ + "\n" + text;
	return s;
}

std::string Arithmetic::ShowError(int index1, int index2, std::string text)
{


	std::string str_(infix.size(), '-');
	for (size_t i = index1; i <= index2; i++)
	{
		str_[i] = '^';
	}
	std::string s = "\n" + infix + "\n" + str_ + "\n" + text;
	return s;
}


void Arithmetic::CheckLexemOrder()
{
	setlocale(LC_ALL, "Russian");
	int open = 0; int close = 0; int pos_last = 0;

	if (lexems[0]->GetLexem() == ")" || lexems[0]->LexemType() == "BinaryOperation")
	{
		throw ShowError(0, "В начале арифметического выражения могут находится : унарные операции или '('!");
	}
	if (lexems[last]->LexemType() != "Number" && lexems[last]->LexemType() != "Var" && lexems[last]->GetLexem() != ")")
	{
		throw ShowError(lexems[last]->GetSatrtPos(), "В конце арифметического выражения могут находится : числа, константы или ')'!");
	}
	if (lexems[0]->GetLexem() == "(")
		open++;


	for (size_t i = 1; i <= last; i++)
	{
		if (lexems[i]->GetLexem() == "(")
			open++;
		if (lexems[i]->GetLexem() == ")")
		{
			close++;
			pos_last = lexems[i]->GetEndPos();
		}
		if (lexems[i]->GetLexem() == "(" && (lexems[i - 1]->LexemType() == "Number" || lexems[i - 1]->LexemType() == "Var" || lexems[i - 1]->GetLexem() == ")"))
		{
			throw ShowError(lexems[i - 1]->GetEndPos(), "Перед '(' не могут находиться : числа, переменные и ')'!");
		}
		if (lexems[i]->LexemType() == "Number" && (lexems[i - 1]->LexemType() == "Var" || lexems[i - 1]->GetLexem() == ")"))
		{
			throw ShowError(lexems[i - 1]->GetEndPos(), "Перед числом не могут находиться : переменные и ')'!");
		}
		if (lexems[i]->LexemType() == "Var" && (lexems[i - 1]->LexemType() == "Number" || lexems[i - 1]->GetLexem() == ")"))
		{
			throw ShowError(lexems[i - 1]->GetEndPos(), "Перед переменной не могут находиться : числа и ')'!");
		}
		if (lexems[i]->LexemType() == "BinaryOperation" && (lexems[i - 1]->LexemType() != "Number" && lexems[i - 1]->LexemType() != "Var" && lexems[i - 1]->GetLexem() != ")"))
		{
			throw ShowError(lexems[i - 1]->GetEndPos(), "Перед бинарной операцией могут находиться только : числа, переменные или ')'!");
		}
		if (lexems[i]->LexemType() == "UnaryOperation" && (lexems[i - 1]->LexemType() == "Number" || lexems[i - 1]->LexemType() == "Var" || lexems[i - 1]->GetLexem() == ")"))
		{
			throw ShowError(lexems[i - 1]->GetEndPos(), "Перед унарной операцией не могут находиться : числа, переменные или ')'!");
		}
		if (lexems[i]->GetLexem() == ")" && (lexems[i - 1]->LexemType() != "Number" && lexems[i - 1]->LexemType() != "Var" && lexems[i - 1]->GetLexem() != ")"))
		{
			throw ShowError(lexems[i - 1]->GetEndPos(), "Перед ')' могут находиться только: числа, переменные и ')'!");
		}
	}
	if (open > close)
	{
		throw ShowError(infix.find('('), infix.size() - 1, "Нет соответсвующей ')'!");
	}
	if (close > open)
	{
		throw ShowError(0, pos_last, "Нет соответсвующей '('!");
	}
}


void Arithmetic::FindIncorrectSymbols()
{
	setlocale(LC_ALL, "Russian");
	for (size_t i = 0; i < infix.size(); i++)
	{
		if (infix[i] != ' ' &&
			!IsOperation(infix[i]) &&
			!IsNumber(infix[i]) &&
			!IsVar(infix[i]))
		{
			std::string s1 = "Некорректный символ";
			std::string s = ShowError(i, s1);
			throw (s);
		}
	}
}

void Arithmetic::Parser()
{
	setlocale(LC_ALL, "Russian");
	if (infix[0] == '-')
		infix[0] = '~';
	for (size_t i = 1; i < infix.size(); i++)
	{
		if (infix[i] == '-' && (infix[i - 1] == '(' || infix[i - 1] == '~' ||
			infix[i - 1] == '+' || infix[i - 1] == '-' || infix[i - 1] == '*' ||
			infix[i - 1] == '/'))
		{
			infix[i] = '~';
		}
	}
	last = -1;
	std::string lex = "";
	for (int i = 0; i < infix.size(); i++)
	{

		if (infix[i] == ' ')
			continue;

		if (IsOperation(infix[i]))
		{
			std::string str_(1, infix[i]);
			if (i >= 1 && (infix[i] == '+' || infix[i] == '-') && infix[i - 1] == 'E')
			{
				lex += infix[i];
				continue;
			}
			if (i == 0 && infix[i] == '+')
			{
				lex += infix[i];
				continue;
			}

			if (lex.size() != 0)
			{
				if (last == size - 1)
					resize();

				if (IsNumber(lex))
				{
					try
					{
						Number n(lex, i - lex.size(), i - 1);
						std::cout << n.GetLexem() << '\t' << n.LexemType() << '\n';
					}
					catch (std::string& err)
					{
						std::string s = ShowError(i - lex.size(), i - 1, err);
						throw (s);
					}
					lexems[++last] = new Number(lex, i - 1 - lex.size(), i - 1);
				}
				else if (IsVar(lex))
				{
					Var n(lex, i - lex.size(), i - 1);
					std::cout << n.GetLexem() << '\t' << n.LexemType() << '\n';
					lexems[++last] = new Var(lex, i - 1 - lex.size(), i - 1);
				}
				else
				{
					throw (ShowError(i - lex.size(), i - 1, "Некорректная запись : " + lex));
				}
				lex = "";
			}

			if (last == size - 1)
				resize();
			Operation op(infix[i], i, i);
			std::cout << op.GetLexem() << '\t' << op.LexemType() << '\n';
			lexems[++last] = new Operation(infix[i], i, i);
		}
		else
		{
			if (lex.size() != 0 && IsVar(lex) && !IsVar(infix[i]))
			{
				std::string s = ShowError(i, "После переменной не может идти чило (используйте * )!");
				throw (s);
			}
			else if (lex.size() != 0 && IsNumber(lex) && IsVar(infix[i]))
			{

				throw ShowError(i, "После числа не может идти переменная (используйте * )!");

			}
			else
			{
				lex += infix[i];
			}
		}
	}

	if (lex.size() != 0)
	{
		if (last == size - 1)
			resize();
		if (IsNumber(lex))
		{
			try
			{
				Number n(lex, infix.size() - lex.size(), infix.size() - 1);
				std::cout << n.GetLexem() << '\t' << n.LexemType() << '\n';
			}
			catch (std::string& err)
			{
				std::string s = ShowError(infix.size() - lex.size(), infix.size() - 1, err);
				throw (s);
			}
			lexems[++last] = new Number(lex, infix.size() - 1 - lex.size(), infix.size() - 1);
		}
		else if (IsVar(lex))
		{
			Var n(lex, infix.size() - lex.size(), infix.size() - 1);
			std::cout << n.GetLexem() << '\t' << n.LexemType() << '\n';
			lexems[++last] = new Var(lex, infix.size() - 1 - lex.size(), infix.size() - 1);
		}
		else
		{
			throw (ShowError(infix.size() - lex.size(), infix.size() - 1, "Некорректная запись : " + lex));
		}
		lex = "";
	}


	std::cout << "\n\nАрифметическое выражение : \n";
	for (size_t i = 0; i <= last; i++)
	{
		std::cout << lexems[i]->GetLexem();
	}


	std::cout << '\n';
}

void Arithmetic::InputVarValue()
{
	std::cout << '\n';
	std::map<std::string, std::string> VarValues;

	for (size_t i = 0; i <= last; i++)
	{
		if (lexems[i]->LexemType() == "Var") //идём по лексемам т.к. в lexems** и  postfix** храняться одни и те же указатели на BaseLexem*, отличается только порядок
		{
			if (!VarValues.count(lexems[i]->GetLexem()))
			{
				std::string s;
				do
				{
					std::cout << "\n  Введите значение переменной " << lexems[i]->GetLexem() << " : ";
					std::cin >> s;
				} while (!IsNumber(s));
				VarValues.insert({ lexems[i]->GetLexem(), s });
			}
			BaseLexem* n = new Number(VarValues[lexems[i]->GetLexem()], lexems[i]->GetSatrtPos(), lexems[i]->GetEndPos());
			delete lexems[i];
			lexems[i] = n;
		}
	}
}

void Arithmetic::Postfix()
{
	setlocale(LC_ALL, "Russian");
	postfix = new BaseLexem * [last + 1];
	int index = -1;
	Stack<BaseLexem*> st;
	BaseLexem* StackItem;
	for (size_t i = 0; i <= last; i++) 
	{
		if (lexems[i]->LexemType() == "Brackets")
		{
			if (lexems[i]->GetLexem() == "(")
			{
				st.Push(lexems[i]);
			}
			else
			{
				StackItem = st.Pop();
				while (StackItem->GetLexem() != "(")
				{
					postfix[++index] = StackItem;
					StackItem = st.Pop();
				}
			}
		}
		else if (lexems[i]->LexemType() == "BinaryOperation") 
		{
			while (!st.IsEmpty())
			{
				StackItem = st.Pop();
				if (lexems[i]->GetPriority() <= StackItem->GetPriority())
				{
					postfix[++index] = StackItem;
				}
				else
				{
					st.Push(StackItem);
					break;
				}
			}
			st.Push(lexems[i]);
		}
		else if (lexems[i]->LexemType() == "UnaryOperation")
		{
			st.Push(lexems[i]);
		}
		else
		{
			postfix[++index] = lexems[i];
		}

	}
	while (!st.IsEmpty())
	{
		StackItem = st.Pop();
		postfix[++index] = StackItem;
	}
	std::cout << "\n\nПостфиксная форма : \n";
	for (size_t i = 0; i <= index; i++)
	{
		std::cout << postfix[i]->GetLexem() << ' ';
	}
	postfix_size = index;
}

double Arithmetic::Calculate()
{
	setlocale(LC_ALL, "Russian");

	try
	{
		InputVarValue();
		Postfix();
	}
	catch (const std::string& err)
	{
		throw err;
	}


	Stack<Number> data; // к этому моменту все Var заменены на Number, поэтому чтобы чистить память используем Number, а не BaseLexem*

	for (size_t i = 0; i <= postfix_size; i++)
	{
		if (postfix[i]->LexemType() == "Number")
		{
			BaseLexem* operand = postfix[i];
			// std::cout << '\n' << operand->Value();
			double num = operand->Value();
			Number n = Number(num, operand->GetSatrtPos(), operand->GetEndPos()); // чтобы был с-шный формат вывода
			data.Push(n);
		}
		else
		{
			std::string op = postfix[i]->GetLexem();
			if (op == "~")
			{
				Number operand = data.Pop();
				// std::cout << '\n' << operand->Value();
				double num = -1 * operand.Value();
				Number n = Number(num, operand.GetSatrtPos(), operand.GetEndPos());
				data.Push(n);
			}
			else if (op == "+")
			{
				Number operand_r = data.Pop(); Number operand_l = data.Pop();
				// std::cout << '\n' << operand_r->Value();

				double num_r = operand_r.Value(); double num_l = operand_l.Value();
				Number n = Number(num_l + num_r, operand_l.GetSatrtPos(), operand_r.GetEndPos());
				data.Push(n);
			}
			else if (op == "-")
			{
				Number operand_r = data.Pop(); Number operand_l = data.Pop();
				// std::cout << '\n' << operand_r->Value();
				double num_r = operand_r.Value(); double num_l = operand_l.Value();
				Number n = Number(num_l - num_r, operand_l.GetSatrtPos(), operand_r.GetEndPos());
				data.Push(n);
			}
			else if (op == "*")
			{
				Number operand_r = data.Pop(); Number operand_l = data.Pop();
				// std::cout << '\n' << operand_r->Value();
				double num_r = operand_r.Value(); double num_l = operand_l.Value();
				Number n = Number(num_r * num_l, operand_l.GetSatrtPos(), operand_r.GetEndPos());
				data.Push(n);
			}
			else if (op == "/")
			{
				Number operand_r = data.Pop(); Number operand_l = data.Pop();
				// std::cout << '\n' << operand_r->Value();
				double num_r = operand_r.Value(); double num_l = operand_l.Value();
				// std::cout << num_r << '\n';
				if (num_r <= 0.000000001 && num_r >= -0.000000001)
				{
					throw ShowError(operand_r.GetSatrtPos(), operand_r.GetEndPos(), "деление на 0!");
				}
				else
				{
					Number n = Number(num_l / num_r, operand_l.GetSatrtPos(), operand_r.GetEndPos());
					data.Push(n);
				}
			}
		}
	}
	std::cout << "\n\nРезультат : " << data.Top().Value() << "\n\n";

	for (size_t i = 0; i <= last; i++)
	{
		if (lexems[i]->LexemType() == "Number" || lexems[i]->LexemType() == "Var")
			std::cout << lexems[i]->Value();
		else
			std::cout << lexems[i]->GetLexem();
	}
	std::cout << "=" << data.Top().Value() << "\n\n";
	return data.Pop().Value();
}