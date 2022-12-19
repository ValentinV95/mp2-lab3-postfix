// реализация функций и классов для вычисления арифметических выражений
#include "../include/arithmetic.h"
#include "../include/stack.h"

#include <exception>
#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <sstream>

using std::string;
using std::cout;
using std::map;
using std::invalid_argument;
using std::out_of_range;



double string_to_double(string s)
{
	int i, LEN, flg = 1, kd = 0, ks = 0, z;
	double res = 0.0, Help = 10.0, znak = 0.0;

	LEN = s.length();

	for (i = 0; i < LEN; i++)
	{
		if ((int(s[i]) < 48 || int(s[i]) > 57) && (s[i] != '-') && (s[i] != '+') && (s[i] != 'E') && (s[i] != '.')) throw  invalid_argument("This is not double!");
		if ((flg) && (s[i] != '.') && (s[i] != 'E'))
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
		if (s[i] == 'E')
		{
			i++;
			Help = 10.0;
			while (i < LEN)
			{
				if ((int(s[i]) < 48 && int(s[i]) > 57) && (s[i] != '-') && (s[i] != '+') && (s[i] != 'E')) throw  invalid_argument("This is not double!");
				if ((s[i] == 'E') || (s[i] == '.')) throw invalid_argument("Bad input!Dot after 'e' or 'e' after 'e'");
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

void TPostfix::to_postfix()

{
	postfix = new Lexem * [infix.length()];
	size_t j = 0, flg1 = 1, flg2 = 1, flg3 = 1, pi = 0;
	string dbl;
	char cmp;
	TStack<char> ST;
	for (auto i = infix.begin(); i != infix.end(); i++, j++)
	{
		dbl = "";
		cmp = char(infix[j]);

		if (cmp > 47 && cmp < 58 || cmp == 46)
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
				if (infix[j] == 'E')
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
			Value* s = new Value(string_to_double(dbl));
			size++;
			postfix[pi] = s;
			pi++;
			if (!flg1) break;
		}
		if (cmp >= 97 && cmp <= 122)
		{
			vars[cmp] = 0.0;
			Var* s = new Var(cmp);
			size++;
			postfix[pi] = s;
			pi++;

		}
		switch (cmp)
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
		case '+': case '-': case '*': case '/':case '~':
		{
			if (j > 0)
			{
				if (((infix[j - 1] == '+') || (infix[j - 1] == '/') || (infix[j - 1] == '*') || (infix[j - 1] == '-')) && (cmp == '-') || (cmp == '-') && (j == 0)) cmp = '~';
			}
			if (cmp != '~' && j == 0) throw std::exception("bad operation");
			else if (((cmp == '+' || cmp == '-') && (ST.show() == '*' || ST.show() == '/')) || ((ST.show() == '~') && (cmp == '+' || cmp == '-' || cmp == '/' || cmp == '*')) || ((cmp == '+' || cmp == '-') && (ST.show() == '-' || ST.show() == '+')))
			{
				while ((!ST.IsEmpty()) && (((cmp == '+' || cmp == '-') && (ST.show() == '*' || ST.show() == '/')) || ((ST.show() == '~') && (cmp == '+' || cmp == '-' || cmp == '/' || cmp == '*')) || ((cmp == '+' || cmp == '-') && (ST.show() == '-' || ST.show() == '+'))))
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
}

void TPostfix::showP() {
	for (size_t i = 0; i < size; i++)
	{
		cout << postfix[i]->show() << " ";
	}
}

size_t TPostfix::get_size() { return size; }

double TPostfix::CALCULATE()
{
	double ss;

	cout << "Before start calculate." << std::endl;
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
		else if (shw[0]!='x' && (shw[0] >= 97 && shw[0] <= 122) || shw == "x")
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