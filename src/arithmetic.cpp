// реализация функций и классов для вычисления арифметических выражений

#include "arithmetic.h"

using namespace std;

	Lexema::Lexema(string lxma) : lexema(lxma) {}
	Lexema::Lexema(char c) : lexema(1, c) {}
	Lexema::Lexema() {}
	bool Lexema::isOperation()
	{
		return (lexema == "+" || lexema == "-" || lexema == "*" || lexema == "/" || lexema == "~");
	}
	bool Lexema::isVariable()
	{
		return (lexema >= "a" && lexema <= "z");
	}
	bool Lexema::isConst()
	{
		return !(isVariable() || isOperation() || lexema == "(" || lexema == ")");
	}
	bool Lexema::operator<(const Lexema& rhs) const noexcept
	{
		return this->lexema < rhs.lexema;
	}


	Const::Const(Lexema _lexema)
	{
		this->lexema = _lexema.lexema;
	}
	double Const::get_value()
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


	double Variable::get_value()
	{
		return 0;
	}


	ArithmeticExpression::ArithmeticExpression(string infx) : infix(infx)
	{
		priority = { {"+", 1}, {"-", 1}, {"*", 2}, {"/", 2}, {"~", 3} };
		int check = 0;
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
				check++;
			if (infix[i] == ')')
				check--;
		}
		if (check != 0)
		{
			cout << "The number of brackets does not match" << endl;
			throw exception("The number of brackets does not match");
		}
		ToPostfix();
	}
	void ArithmeticExpression::ToPostfix()
	{
		Parse();
		if (lexems[0]->lexema == "-")
			lexems[0]->lexema = "~";
		int e_counter = 0;
		Stack<Lexema> st;
		Lexema stackItem("");
		size_t i = 0;
		for (i = 0; i < lexems.size(); i++)
		{
			if (lexems[i]->lexema == "(")
				st.push(*lexems[i]);
			else if (lexems[i]->lexema == ")")
			{
				stackItem = st.top();
				st.pop();
				while (stackItem.lexema != "(")
				{
					postfix.push_back(stackItem.lexema);
					stackItem = st.top();
					st.pop();
				}
			}
			else if (lexems[i]->isOperation())
			{
				if (lexems[i]->lexema == "-" && (lexems[i - 1]->lexema == "(" || lexems[i - 1]->isOperation()))
					lexems[i]->lexema = "~";
				while (!st.isEmpty())
				{
					stackItem = st.top();
					st.pop();
					if (lexems[i]->lexema != "~")
					{
						if (priority[lexems[i]->lexema] <= priority[stackItem.lexema])
							postfix.push_back(stackItem.lexema);
						else
						{
							st.push(stackItem);
							break;
						}
					}
					else
					{
						if (priority[lexems[i]->lexema] < priority[stackItem.lexema])
							postfix.push_back(stackItem.lexema);
						else
						{
							st.push(stackItem);
							break;
						}
					}
				}
				st.push(*lexems[i]);
			}
			else
			{
				Const c = *lexems[i];
				Operand* operand = (Operand*)lexems[i];
				operand = &c;
				operands.insert({ *operand, operand->get_value() });
				postfix.push_back(lexems[i]->lexema);
			}
		}
		while (!st.isEmpty())
		{
			stackItem = st.top();
			st.pop();
			postfix.push_back(stackItem.lexema);
		}
		for (i = 0; i < lexems.size() - 1; i++)
		{
			e_counter = 0;
			if (lexems[i]->isConst())
				for (size_t j = 0; j < lexems[i]->lexema.length() - 1; j++)
				{
					if (lexems[i]->lexema[j] == '.' && (lexems[i]->lexema[j + 1] == '.' || lexems[i]->lexema[j + 1] == 'e' || lexems[i]->lexema[j + 1] == '+' || lexems[i]->lexema[j + 1] == '-'
						|| lexems[i]->lexema[j + 1] == '*' || lexems[i]->lexema[j + 1] == '/' || lexems[i]->lexema[j + 1] == '(' || lexems[i]->lexema[j + 1] == ')'))
					{
						cout << "Error in " << i + 1 << " lexema " << lexems[i]->lexema << " in " << j + 2 << " index" << endl;
						throw exception();
					}
					if (lexems[i]->lexema[j] == 'e')
					{
						e_counter++;
						if (!(lexems[i]->lexema[j + 1] == '+' || lexems[i]->lexema[j + 1] == '-' ||
							(lexems[i]->lexema[j + 1] >= '0' && lexems[i]->lexema[j + 1] <= '9') || lexems[i]->lexema[j + 1] == '.'))
						{
							cout << "Error in " << i + 1 << " lexema " << lexems[i]->lexema << " in " << j + 2 << " index" << endl;
								throw exception();
						}
					}
					if (e_counter > 1)
					{
						cout << "Error in " << i + 1 << " lexema - too many 'e'" << endl;
						throw exception();
					}
				}
			if ((lexems[i]->isConst() || lexems[i]->isVariable()) && !((lexems[i + 1]->isOperation() && lexems[i + 1]->lexema != "~") || lexems[i + 1]->lexema == ")"))
			{
				cout << "Error in " << i + 2 << " lexema " << lexems[i + 1]->lexema << endl;
				throw exception();
			}
			if ((lexems[i]->lexema == "~") && !(lexems[i + 1]->lexema == "~" || lexems[i + 1]->isConst() || lexems[i + 1]->isVariable() || lexems[i + 1]->lexema == "("))
			{
				cout << "Error in " << i + 2 << " lexema " << lexems[i + 1]->lexema << endl;
				throw exception();
			}
			if ((lexems[i]->isOperation() && lexems[i]->lexema != "~") && !(lexems[i + 1]->isConst() || lexems[i + 1]->isVariable() || lexems[i + 1]->lexema == "~" || lexems[i + 1]->lexema == "("))
			{
				cout << "Error in " << i + 2 << " lexema " << lexems[i + 1]->lexema << endl;
				throw exception();
			}
			if ((lexems[i]->lexema == "(") && !(lexems[i + 1]->lexema == "~" || lexems[i + 1]->isConst() || lexems[i + 1]->isVariable() || lexems[i + 1]->lexema == "("))
			{
				cout << "Error in " << i + 2 << " lexema " << lexems[i + 1]->lexema << endl;
				throw exception();
			}
			if ((lexems[i]->lexema == ")") && !((lexems[i + 1]->isOperation() && lexems[i + 1]->lexema != "~") || lexems[i + 1]->lexema == ")"))
			{
				cout << "Error in " << i + 2 << " lexema " << lexems[i + 1]->lexema << endl;
				throw exception();
			}
		}
		e_counter = 0;
		if (lexems[i]->isConst())
			for (size_t j = 0; j < lexems[i]->lexema.length() - 1; j++)
			{
				if (lexems[i]->lexema[j] == '.' && (lexems[i]->lexema[j + 1] == '.' || lexems[i]->lexema[j + 1] == 'e'))
				{
					cout << "Error in " << i + 1 << " lexema " << lexems[i]->lexema << " in " << j + 2 << " index" << endl;
					throw exception();
				}
				if (lexems[i]->lexema[j] == 'e')
				{
					e_counter++;
					if (!(lexems[i]->lexema[j + 1] == '+' || lexems[i]->lexema[j + 1] == '-' ||
						(lexems[i]->lexema[j + 1] >= '0' && lexems[i]->lexema[j + 1] <= '9') || lexems[i]->lexema[j + 1] == '.'))
					{
						cout << "Error in " << i + 1 << " lexema " << lexems[i]->lexema << " in " << j + 2 << " index" << endl;
						throw exception();
					}
				}
				if (e_counter > 1)
				{
					cout << "Error in " << i + 1 << " lexema - too many 'e'" << endl;
					throw exception();
				}
			}
	}
	void ArithmeticExpression::Parse()
	{
		Lexema tmp;
		for (size_t i = 0; i < infix.size(); i++)
		{
			if ((infix[i] >= '0' && infix[i] <= '9') || infix[i] == '.')
			{
				while ((infix[i] >= '0' && infix[i] <= '9') || infix[i] == '.' || infix[i] == 'e' && i < infix.size())
				{
					if (infix[i] == 'e')
					{
						tmp.lexema.push_back(infix[i]);
						i++;
					}
					tmp.lexema.push_back(infix[i]);
					i++;
				}
				lexems.push_back(new Lexema(tmp));
				if (i == infix.size())
					break;
			}
			lexems.push_back(new Lexema(infix[i]));
			tmp.lexema = "";
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
			s_postfix.append(postfix[i].lexema);
			s_postfix.append("|");
		}
		return s_postfix;
	}
	vector<Lexema> ArithmeticExpression::GetOperands() const
	{
		vector<Lexema> op;
		for (const auto& item : operands)
			if (item.first.lexema >= "a" && item.first.lexema <= "z")
				op.push_back(item.first);
		return op;
	}
	double ArithmeticExpression::Calculate(const map<Lexema, double>& values)
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
			if (postfix[i].lexema == "+")
			{
				rightOperand = st.top();
				st.pop();
				leftOperand = st.top();
				st.pop();
				st.push(leftOperand + rightOperand);
			}
			else if (postfix[i].lexema == "-")
			{
				rightOperand = st.top();
				st.pop();
				leftOperand = st.top();
				st.pop();
				st.push(leftOperand - rightOperand);
			}
			else if (postfix[i].lexema == "*")
			{
				rightOperand = st.top();
				st.pop();
				leftOperand = st.top();
				st.pop();
				st.push(leftOperand * rightOperand);
			}
			else if (postfix[i].lexema == "/")
			{
				rightOperand = st.top();
				st.pop();
				leftOperand = st.top();
				st.pop();
				if (rightOperand == 0)
					throw exception("Can't divide by zero");
				st.push(leftOperand / rightOperand);
			}
			else if (postfix[i].lexema == "~")
			{
				leftOperand = st.top();
				st.pop();
				st.push(0 - leftOperand);
			}
			else
				st.push(operands[postfix[i].lexema]);
		}
		return st.top();
	}