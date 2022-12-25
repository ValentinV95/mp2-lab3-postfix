// реализация функций и классов для вычисления арифметических выражений
#include "stack.h"
#include "arithmetic.h"

string TPostfix::GetInfixStr() const {return infix;}

string TPostfix::GetPostfixStr() const 
{ 
	string res= "|";
	for (int i = 0; i < postfix.size(); i++)
		res += postfix[i]->GetName() + "|";
	return res;
}

void TPostfix::SetInfix(const string &str)
{
	infix = str;
	Parse();
	ToPostfix();
}

TPostfix::TPostfix(const string &str):infix(str)
{
	ops["+"] = [](double a, double b) { return a + b; };
	ops["-"] = [](double a, double b) { return a - b; };
	ops["~"] = [](double a, double b) { return a - b; };
	ops["*"] = [](double a, double b) { return a * b; };
	ops["/"] = [](double a, double b)
	{
		if (b == 0)
			throw exception("An error occurred during the calculations\nDivision by sero\n");
		else
			return a / b;
	};

	funcs["sin"] = [](double a) { return sin(a); };
	funcs["cos"] = [](double a) { return cos(a); };
	funcs["ln"] = [](double a) { return log(a); };

	Parse();
	ToPostfix();
}

double TPostfix::GetNum(string num)
{
	double res = 0.0;
	int step = num.length() - 1;

	for (int i = 0; i < num.length(); i++)
	{
		res += (((int)num[i]) - 48) * pow(10, step--);
	}

	return res;
}

double TPostfix::StrToNum(string str)
{
	int dot = 0, exp = str.size(), step = 0, i = 0;
	double res = 0.0, sign = 1;

	while (exp == str.size() && i < str.size())
	{
		if (str[i] == DELIMITER && !dot && i != 0)
		{
			dot = i;
		}
		else if (str[i] == 'e')
		{
			exp = i;
			if ((((int)str.size()) - exp) < 2 && (str[exp + 1] != '-' || str[exp + 1] != '+'))
				throw exception("Incorrect num format");
			if (str[exp + 1] == '-')
				sign = -1;
		}
		else if ((int)str[i] - 48 > 9 || (int)str[i] - 48 < 0)
			if (dot || i == 0)
				throw exception("To much '.' in number");
			else
				throw exception("Num string contains invalid charakters");

		i++;
	}

	if (exp != str.size() && str[exp + 1] != '-' && str[exp + 1] != '+')
		throw exception("Incorrect num format");

	if (dot)
		res += GetNum(str.substr(0, dot)) + GetNum(str.substr(dot + 1, str.length() - exp - 2)) * pow(10, -(exp - dot - 1));
	else
		res += GetNum(str.substr(0, exp));

	if (exp != str.length())
		return res * pow(10, sign * StrToNum(str.substr(exp + 2, str.length() - exp - 2)));

	return 	res;
}

Lexeme* TPostfix::CreateLexeme(string str,int start,int stop)
{
	if (funcs.count(str) != 0 || ops.count(str) != 0 || str == "(" || str == ")")
		return (Lexeme*)new Operation(str,make_pair(start,stop));

	if (str[0] >= '0' && str[0] <= '9')
		return (Lexeme*)new Constant(StrToNum(str),str,make_pair(start, stop));

	if(str!="e" && str!="pi")
		variable_map.insert(std::make_pair(str,0.0));
	return (Lexeme*)new Variable(str, variable_map, make_pair(start, stop));
}

unsigned int TPostfix::GetPriority(Operation op)
{
	string name = op.GetName();

	if (funcs.count(name) != 0 || name == "~") return 4;
	if (name == "*" || name == "/") return 3;
	if (name == "+" || name == "-") return 2;
	if (name == "(") return 1;
	if (name == ")") return 0;
}

void TPostfix::Parse()
{
	int i = 0, j = 0, counter = 0;
	
	//Ловлю простые ошибки
	for (int i = 0; i < infix.length(); i++)
	{
		string str = string(1, infix[i]);

		if (ops.count(str) == 0
			&& infix[i] != '(' && infix[i] != ')'
			&& !(infix[i] >= '0' && infix[i] <= '9') //Не число
			&& infix[i] != DELIMITER
			&& !(infix[i] >= 'a' && infix[i] <= 'z')) //Не буква
			throw TPostfixException("Invalid character in a row", i + 1);

		if (infix[i] == '(')
			counter++;

		if (infix[i] == ')')
		{
			if (counter >= 0)
				counter--;
			else
				throw TPostfixException("Count of '(' and ')' is not equall", i);
		}
	}

	if (counter != 0)
		throw TPostfixException("Count of '(' and ')' is not equall", infix.size());

	//Нарезаю выражение
	while (i < infix.length())
	{
		string str = string(1, infix[i]);
		if (ops.count(str))
		{
			if (!(infix.substr(j, i - j)[0] >= '0' && infix.substr(j, i - j)[0] <= '9' && infix.substr(j, i - j)[i - j - 1] == 'e'))
			{
				if (i != j)
					postfix.push_back(CreateLexeme(infix.substr(j, i - j), j, i));

				postfix.push_back(CreateLexeme(infix.substr(i, 1), i, i));
				j = i + 1;
			}
		}
		else if (infix[i] == '(')
		{
			if (i != j)
				postfix.push_back(CreateLexeme(infix.substr(j, i - j), j, i));

			postfix.push_back(CreateLexeme(infix.substr(i, 1), i, i));
			j = i + 1;
		}
		else if (infix[i] == ')')
		{
			if (i != j)
				postfix.push_back(CreateLexeme(infix.substr(j, i - j), j, i));

			postfix.push_back(CreateLexeme(infix.substr(i, 1), i, i));
			j = i + 1;
		}

		i++;
	}

	if (i != j)
		postfix.push_back(CreateLexeme(infix.substr(j, i - j), j, i));

	enum prev_name { Num_Or_Var, Op, Func, Scobka_Open, Scobka_Close };
	short int prev = Scobka_Open;

	//Lexeme analysis
	for (size_t i = 0; i < postfix.size(); i++)
	{
		Lexeme* lex = postfix[i];
		if (lex->isOperation())
		{
			if (prev == Op && ((Operation*)lex)->GetName() != "-" && ((Operation*)lex)->GetName() != "(" && funcs.count(((Operation*)lex)->GetName()) == 0)//После операции операция и это не - 
				throw TPostfixException("After operation '-',variable,constant or '(' was excepted", lex->GetPos());

			if (prev == Scobka_Open && ((Operation*)lex)->GetName() != "-" && funcs.count(((Operation*)lex)->GetName()) == 0 && ((Operation*)lex)->GetName() != "(")
				throw TPostfixException("After '(' number,variable,function or '-' was excepted", lex->GetPos());

			if (prev == Scobka_Open && ((Operation*)lex)->GetName() == "-" || prev == Op && ((Operation*)lex)->GetName() == "-")
				postfix[i] = new Operation("~", postfix[i]->GetPos());

			if (prev == Func && ((Operation*)lex)->GetName() != "(")//После функции ожидается (
				throw TPostfixException("After function name '(' was excepted", lex->GetPos());

			if (prev == Num_Or_Var && ((Operation*)lex)->GetName() != ")" && ops.count(((Operation*)lex)->GetName()) == 0)
				throw TPostfixException("After number or wariable - operation or ')' was excepted", lex->GetPos());

			prev = Op;

			if (funcs.count(((Operation*)lex)->GetName()) != 0)
				prev = Func;

			if (((Operation*)lex)->GetName() == "(")
				prev = Scobka_Open;

			if (((Operation*)lex)->GetName() == ")")
				prev = Scobka_Close;
		}
		else
		{
			if (prev == Scobka_Close)
				throw TPostfixException("After ')' operation was excepted but constant or variable found", lex->GetPos());

			prev = Num_Or_Var;
		}
	}

	if (prev == Op)
		throw exception("Operation in the end of string was found", infix.size());
}

void TPostfix::ToPostfix()
{
	////To revers polish notation convertation
	vector<Lexeme*> tmp = postfix;
	postfix.clear();
	Stack<Lexeme*> op;

	for (size_t i = 0; i < tmp.size(); i++)
	{
		if (tmp[i]->isOperation())
		{
			if (op.isEmpty() || ((Operation*)tmp[i])->GetName() == "(" || ((Operation*)tmp[i])->GetName() == "~" &&  ((Operation*)op.head())->GetName() == "~")
			{
				op.push(tmp[i]);
			}
			else if (((Operation*)tmp[i])->GetName() ==")")
			{
				while ((*(Operation*)(op.head())).GetName() != "(")
				{
					postfix.push_back(op.head());
					op.pop();
				}

				op.pop();
			}
			else
			{
				while (!op.isEmpty() && GetPriority(*(Operation*)(op.head())) >= GetPriority(*(Operation*)(tmp[i])))
				{
					postfix.push_back(op.head());
					op.pop();
				}

				op.push(tmp[i]);
			}
		}
		else
		{
			postfix.push_back(tmp[i]);
		}
	}

	while (!op.isEmpty())
	{
		postfix.push_back(op.head());
		op.pop();
	}
}

double TPostfix::Calculate()
{
	Stack<double> res;
	pair<int, int> cur_pos=make_pair(0,0);

	for (auto& var : variable_map)
	{
		cout << "  Enter variable " << var.first <<": ";
		cin >> var.second;
	}

	try
	{
		for (int i = 0; i < postfix.size(); i++)
		{
			if (postfix[i]->isOperation())
			{
				double x = res.head();
				cur_pos = postfix[i]->GetPos();
				res.pop();
				if (funcs.count(((Operation*)postfix[i])->GetName()) != 0)
				{
					res.push(funcs[((Operation*)postfix[i])->GetName()](x));
				}
				else if (((Operation*)postfix[i])->GetName() == "~")
				{
					res.push(ops["~"](0.0, x));
				}
				else
				{
					x = ops[((Operation*)(postfix[i]))->GetName()](res.head(), x);
					res.pop();
					res.push(x);
				}
			}
			else
			{
				cur_pos.second = postfix[i]->GetPos().second;
				res.push(((Operand*)(postfix[i]))->GetValue());
			}
		}
	}
	catch(const exception &exc)
	{
		throw TPostfixException(exc.what(), cur_pos);
	}

	return res.head();
}

void TPostfix::ShowInfo()
{
	cout << "\n------------INFO---------------------------\n";
	cout << "You may use  a-z letter and 0-9 numbers\n";
	cout << "Functions: cos(), sin(), ln()";
	cout << "\nOperations: +, -, /, - ,unary -";
	cout << "\n------------INFO----------------------------\n";
}

TPostfix::~TPostfix()
{
	for (int i = 0; i < postfix.size(); i++)
		delete[] postfix[i];
}