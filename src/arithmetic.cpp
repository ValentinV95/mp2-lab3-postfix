// реализация функций и классов для вычисления арифметических выражений
#include "../include/arithmetic.h"
#include "../include/stack.h"





double string_to_double(string s)
{
	int i, LEN, flg = 1, kd = 0, ks = 0, z;
	double res = 0.0, Help = 10.0, znak = 0.0;

	LEN = s.length();

	for (i = 0; i < LEN; i++)
	{
		if ((int(s[i]) < 48 || int(s[i]) > 57) && (s[i] != '-') && (s[i] != '+') && (s[i] != 'e') && (s[i] != '.')) throw  invalid_argument("This is not double!");
		if ((flg) && (s[i] != '.') && (s[i] != 'e'))
		{
			res *= Help;
			res += (int(s[i]) - 48);

		}
		if (s[i] == '.')
		{
			kd++;
			flg = 0;
			Help = 1.0 / 10.0;
			if (kd > 1) throw  invalid_argument("Two dots!");
		}
		if (s[i] == 'e')
		{
			if (i + 1 == LEN) throw invalid_argument("Bad form of double!");
			i++;
			Help = 10.0;
			while (i < LEN)
			{
				if ((int(s[i]) < 48 && int(s[i]) > 57) && (s[i] != '-') && (s[i] != '+') && (s[i] != 'e')) throw  invalid_argument("This is not double!");
				if ((s[i] == 'e') || (s[i] == '.')) throw invalid_argument("Bad input!Dot after 'e' or 'e' after 'e'");
				else if (s[i] == '-')
				{
					ks++;
					z = -1;
					if (ks > 1) throw invalid_argument("Bad input!Two symbols of plus or substract!");
				}
				else if (s[i] == '+')
				{
					ks++;
					z = 1;
					if (ks > 1) throw invalid_argument("Bad input!Two symbols of plus or substract!");
				}
				else
				{

					znak *= Help;
					znak += int(s[i]) - 48;

				}
				i++;
			}
			res *= pow(10, z * znak);
			flg = 1;

		}
		if (flg == 0 && s[i] != '.')
		{
			res += (int(s[i]) - 48) * Help;
			Help /= 10.0;
		}



	}

	return res;
}



TPostfix::TPostfix(string str)
{
	infix = str;
	size = 0;
}

void TPostfix::infix_check()
{

	//Функция которая проверяет все возможные ошибки написания в инфиксной форме

	if (infix == "NULL") throw exception("No infix form! First you need to initialisate infix form!");
	else if (infix != "NULL")
	{
		int flg,flg2;
		char cmp;
		string error;
		TStack<int> problems;
		for (int i = 0; i < infix.length(); i++)
		{
			cmp = infix[i];
			flg2 = (cmp == '+' || cmp == '/' || cmp == '*');
			flg = (cmp > 47 && cmp < 58 || cmp == 46) || (cmp >= 97 && cmp <= 122) || flg2 || cmp=='-' || cmp == '(' || cmp == ')';
			if (cmp >= 97 && cmp <= 122)
			{
				if (i>0)
					if ((infix[i - 1] > 47 && infix[i - 1] < 58 || infix[i - 1] == 46) && (cmp != 'e'))
					{
						error = "No valid operation of multiplicate in the ";
						error += to_string(i);
						error += " and ";
						error += to_string(i + 1);
						error += " elements of the infix!  infix: ";
						error += infix;
						throw invalid_argument(error);
					}
				if (i + 1 < infix.length())
					if ((infix[i + 1] > 47 && infix[i + 1] < 58 || infix[i + 1] == 46) && (cmp != 'e') ||(cmp == 'e' && infix[i+1]!='-' && infix[i+1]!='+'))
					{
						error = "No valid operation of multiplicate in the ";
						error += to_string(i + 1);
						error += " and ";
						error += to_string(i + 2);
						error += " elements of the infix!  infix: ";
						error += infix;
						throw invalid_argument(error);
					}
			}

			if (infix.length() > i && cmp == '(')
			{
				if (infix[i + 1] == ')')
				{
					error = "Empty brackets in the ";
					error += to_string(i + 1);
					error += " and ";
					error += to_string(i + 2);
					error += " elements of the infix!  infix: ";
					error += infix;
					throw invalid_argument(error);
				}
			}
			if (!flg)
			{
				error = "Invalid character in the ";
				error += to_string(i+1);
				error += " element of the infix!  infix: ";
				error += infix;
				throw invalid_argument(error);
			}
			if (cmp == '-' && i == 0 && infix.length() > 1)
			{
				if (infix[i + 1] == '+' || infix[i + 1] == '/' || infix[i + 1] == '*')
				{
					error = "Bad operation(at start) in the ";
					error += to_string(i + 2);
					error += " element of the infix!  infix: ";
					error += infix;
					throw invalid_argument(error);
				}
			}
			else if ((flg2 || cmp == '-') && (i + 1 == infix.length()))
			{
				error = "Bad operation(at end) in the ";
				error += to_string(i + 1);
				error += " element of the infix!  infix: ";
				error += infix;
				throw invalid_argument(error);
			}
			if ((flg2 || cmp == ')') && (i == 0)) throw invalid_argument("Bad start of infix form!");
			else if ((flg2 || cmp == ')' && i > 0))
			{
				if (infix[i - 1] == '+' || infix[i - 1] == '-' || infix[i - 1] == '/' || infix[i - 1] == '*' || infix[i - 1] == '(')
				{
					error = "Bad operation in the ";
					if (cmp == ')')
						error += to_string(i);
					else
						error += to_string(i + 1);
					error += " element of the infix!  infix: ";
					error += infix;
					throw invalid_argument(error);
				}
			}
			if (cmp == '(') problems.push_back(i+1);
			if ((cmp == ')' && !problems.IsEmpty())) problems.pop();
			else if (cmp == ')' && problems.IsEmpty())
			{
				error = "Have no open bracket for bracket in the ";
				error += to_string(i);
				error += " element of the infix!  infix: ";
				error += infix;
				throw invalid_argument(error);
			}
			if (cmp == '(' && i > 0)
			{
				if (infix[i - 1] != '-' && infix[i - 1] != '+' && infix[i - 1] != '/' && infix[i - 1] != '*' && infix[i - 1] != '(')
				{
					error = "No operation between opearnd and bracket in the ";
					error += to_string(i + 1);
					error += " element of the infix!  infix: ";
					error += infix;
					throw invalid_argument(error);
				}
			}
			if (cmp == ')' && i + 1 < infix.length())
			{
				if (infix[i + 1] != '-' && infix[i + 1] != '+' && infix[i + 1] != '/' && infix[i + 1] != '*' && infix[i + 1] != ')')
				{
					error = "No operation between opearnd and bracket in the ";
					error += to_string(i + 1);
					error += " element of the infix!  infix: ";
					error += infix;
					throw invalid_argument(error);
				}
			}
		}
		if (!problems.IsEmpty())
		{
			error = "Have no close bracket for bracket in the ";
			error += to_string(problems.pop());
			error += " element of the infix!  infix: ";
			error += infix;
			throw invalid_argument(error);
		}
	}
}

void TPostfix::to_postfix()

{
	infix_check();
	postfix = new Lexem * [infix.length()*2];//(_ленивое программирование_) Лексем точно не может быть больше чем букв(умножается на 2 на всякий случай если будете писать умножение переменных без операции(ab = a*b))
	size_t j = 0, flg1 = 1, flg2 = 1, flg3 = 1, pi = 0;
	string dbl;
	char cmp;
	TStack<char> ST;
	for (auto i = infix.begin(); i != infix.end(); i++, j++)
	{
		dbl = "";
		cmp = char(infix[j]);

		if (cmp > 47 && cmp < 58 || cmp == 46) //Проверка на константу
		{
			if (infix[j] == '\0') break;
			flg1 = 1; flg2 = 1; flg3 = 1;
			while (flg2 || flg3)
			{
				if (infix[j] == '\0')
				{
					flg1 = 0;
					break;
				}
				if (j>0)
				if (infix[j] == 'e' && (infix[j-1] == 46 ||(( infix[j - 1] != '+')&& (infix[j - 1] != '-')&& (infix[j - 1] != '*')&& (infix[j - 1] != '/'))))
				{
					flg3 = 0;
					dbl.push_back(infix[j]);
					if (j + 1 < infix.length())
					{
						dbl.push_back(infix[j + 1]);
						j++;
						i++;
					}
					else break;
					j++;
					i++;
				}
				if ((infix[j] == '+' || infix[j] == '/' || infix[j] == '-' || infix[j] == '*' || infix[j] == '(' || infix[j] == ')' || infix[j] == '~'))
				{
					j--;
					i--;
					break;
				}


				dbl.push_back(infix[j]);
				j++;
				i++;
			}
			Value* s = new Value(dbl);
			size++;
			postfix[pi] = s;
			pi++;
			if (!flg1) break;
		}
		if (cmp >= 97 && cmp <= 122) //Проверка на переменную
		{
			vars[cmp] = 0.0;
			Var* s = new Var(cmp);
			size++;
			postfix[pi] = s;
			pi++;
			if (j > 0)
				if (infix[j - 1] >= 97 && infix[j - 1] <= 122)
				{
					Operation* s = new Operation('*');
					size++;
					postfix[pi] = s;
					pi++;
				}

		}
		switch (cmp) //Проверка на операцию и скобки
		{
		case '(':
		{
			ST.push_back('(');
			break;
		}
		case ')':
		{
			while (ST.show() != '(')
			{
				Operation* s = new Operation(ST.pop());
				size++;
				postfix[pi] = s;
				pi++;
			}
			ST.pop();
			break;
		}
		case '+': case '-': case '*': case '/':
		{
			if (j > 0)
			{
				if (((infix[j - 1] == '+') || (infix[j - 1] == '/') || (infix[j - 1] == '*') || (infix[j - 1] == '-') || (infix[j - 1] == '(')) && (cmp == '-')) cmp = '~';
			}
			if (infix.length() > 1 && j == 0 && cmp == '-')
				if (infix[j + 1] != '+' && infix[j + 1] != '*' && infix[j + 1] != '/')
					cmp = '~';
			if (cmp != '~' && j == 0) throw std::exception("bad operation");
			else if (((cmp == '+' || cmp == '-') && (ST.show() == '*' || ST.show() == '/')) || ((ST.show() == '~') && (cmp == '+' || cmp == '-' || cmp == '/' || cmp == '*')) || ((cmp == '+' || cmp == '-') && (ST.show() == '-' || ST.show() == '+')) || (cmp == '/'||cmp=='*')&&(ST.show()=='/' || ST.show()=='*'))
			{
				while ((!ST.IsEmpty()) && (((cmp == '+' || cmp == '-') && (ST.show() == '*' || ST.show() == '/')) || ((ST.show() == '~') && (cmp == '+' || cmp == '-' || cmp == '/' || cmp == '*')) || ((cmp == '+' || cmp == '-') && (ST.show() == '-' || ST.show() == '+')) || (cmp == '/' || cmp == '*') && (ST.show() == '/' || ST.show() == '*')))
				{
					Operation* s = new Operation(ST.pop());
					size++;
					postfix[pi] = s;
					pi++;
				}
				ST.push_back(cmp);
			}
			else
			{

				ST.push_back(cmp);
			}
			break;
		}
		}
	}
	while (!ST.IsEmpty())
	{
		Operation* s = new Operation(ST.pop());
		size++;
		postfix[pi] = s;
		pi++;
	}

	Lexem** tmp = new Lexem*[size];//удаление лишней памяти
	for (size_t i = 0; i < size; i++)
	{
		tmp[i] = postfix[i];
	}
	delete[]postfix;
	postfix = tmp;
}

string TPostfix::showP() 
{

	//Функция которая возвращает постфиксную форму записи в виде строки

	string P = "";
	if (infix != "NULL" && postfix == nullptr)
	{
		set_infix(infix);
		to_postfix();
	}
	if (postfix != nullptr)
	{
		for (size_t i = 0; i < size; i++)
		{
			P+=postfix[i]->show() + " ";
		}
		return P;
	}
	else throw invalid_argument("No infix form,or bad infix form without lexems!");
}

void TPostfix::set_infix(string infx)
{

	//Функция которая задает новую инфиксную форму

	infix = infx;
	if (postfix != nullptr)
	vars.clear();
	delete[]postfix;
	postfix = nullptr;
	size = 0;
}

size_t TPostfix::get_size()
{ 
	if (postfix != nullptr) return size;
	if (infix != "NULL")
	{
		set_infix(infix);
		to_postfix();
	}
	if (postfix == nullptr) throw invalid_argument("No infix form,or bad infix form without lexems!");
	return size; 
}

double TPostfix::CALCULATE()
{

	if (infix != "NULL")
	{
		set_infix(infix);
		to_postfix();
	}
	if (postfix == nullptr) throw invalid_argument("No infix form,or bad infix form without lexems!");
	double ss;

	for (auto i = vars.begin(); i != vars.end(); i++)
	{
		cout << "Input " << i->first << " value: " << std::endl;
		std::cin >> ss;
		vars[i->first] = ss;
	}
	double res, left, right;
	string shw;
	TStack<double> value;
	for (size_t i = 0; i < size; i++)
	{
		shw = postfix[i]->show();
		if (shw == "+")
		{
			right = value.pop();
			left = value.pop();
			value.push_back(left + right);
		}
		else if (shw == "-")
		{
			right = value.pop();
			left = value.pop();
			value.push_back(left - right);
		}
		else if (shw == "/")
		{
			right = value.pop();
			left = value.pop();
			if (fabs(right) < 10.e-16) throw exception("Division by Zero");
			value.push_back(left / right);
		}
		else if (shw == "*")
		{
			right = value.pop();
			left = value.pop();
			value.push_back(left * right);
		}
		else if (shw == "~")
		{
			value.push_back(-value.pop());
		}
		else if (shw[0] >= 97 && shw[0] <= 122)
		{
			value.push_back(vars[shw[0]]);
		}
		else
		{
			value.push_back(string_to_double(shw));
		}
	}

	res = value.pop();
	return res;
}