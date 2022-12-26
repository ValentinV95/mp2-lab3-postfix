// реализация функций и классов для вычисления арифметических выражений

#include <iostream>
#include "arithmetic.h"

using namespace std;


double _STOD(string str)
{
	double Res = 0.0;
	int _size = str.size();
	int s1 = 1;
	double multiplier = 10.0;

	for ( int i = 0; i < _size; i++)
	{
		if (s1 == 1 && str[i] != '.')
		{
			Res = Res * multiplier;
			Res  += (int(str[i]) - 48);
		}
		if (str[i] == '.')
		{
			s1 = 0;
			multiplier = 0.1;
		}
		if (s1 == 0 && str[i] != '.')
		{
			Res += (int(str[i]) - 48) * multiplier;
			multiplier /= 10.0;
		}
	}
	return Res;
}



Operation::Operation() { _type = "operation"; }

Operation::Operation(char op)
{

	_type = "operation";
	_lexem_m.push_back(op);
	Operation_name = op;
	switch (op)
	{
	case '+':
		Operation_name = '+';
		Priority = 1;
		break;
	case '-':
		Operation_name = '-';
		Priority = 1;
		break;
	case '*':
		Operation_name = '*';
		Priority = 2;
		break;
	case '/':
		Operation_name = '/';
		Priority = 2;
		break;
	case '(':
		Operation_name = '(';
		_type = "open_bracket";
		Priority = 0;
		break;
	case ')':
		Operation_name = ')';
		_type = "close_bracket";
		Priority = 0;
		break;
	default:
		break;
	}

}



_Constant::_Constant(TStack<char>& a, int znak)
{
	_type = "constant";
	int numsize = a.size();\

	char* strnum = new char[numsize];

	string str;
	for (int i = numsize-1; i >= 0; i--)
	{
		strnum[i] = a.pop();
	}
	for (int i = 0; i < numsize; i++)
	{
		str.push_back(strnum[i]);
	}
	Value = _STOD(str);
	Value *= znak;
	if(znak<0)
	_lexem_m.push_back('-');
	_lexem_m += str;
}


bool is_Var(char c)
{
	return (c >= 'a' && c <= 'z');
}
bool is_Oper(char c)
{
	return (c == '+' || c == '-' || c == '*' || c == '/');
}

bool is_Digit(char c)
{
	
	return(c >= '0' && c <= '9');
}

int isPrioritychar(char a)
{
	if (a == '-' || a == '+')return 1;
	if (a == '*' || a == '/')return 2;
	if (a == '(' || a == ')')return 0;

}


string Lexema::show() { string temp = _lexem_m; return temp; }

_Constant::_Constant() { _type = "constant"; }

_Variable::_Variable() { _type = "variable"; _Var = '$'; }

_Variable::_Variable(char var, int sgn) {
	_type = "variable";
	_lexem_m.push_back(var);
	_Var = var;
	sign = sgn;
}



TPostfix::TPostfix(string infix)
{
	infix.erase(remove(infix.begin(), infix.end(), ' '), infix.end());
	Lexema** arr;
	int _size = infix.size();
	int _sign = 1;
	int pos = 0;
	int brackets = 0;
	arr = new Lexema * [_size];


	for (int i = 0; i < _size; i++)
	{

		if (infix[i] == '-' && (i == 0 || (i - 1 >= 0 && ((infix[i+1] >='0' && infix[i+1] <='9') || (infix[i + 1] >= 'a' && infix[i + 1] <= 'z')) && (infix[i - 1] == '(' || infix[i - 1] == '+' || infix[i - 1] == '-' || infix[i - 1] == '*' || infix[i - 1] == '/'))))
		{
			infix[i] = '~';
		}

	}


	//__________________CHECKING STRING____________________________//

	if (infix.size() <= 2) throw invalid_argument("invalid input, input is empty");
	if (infix[0] == ')' || is_Oper(infix[0])) throw invalid_argument("invalid input, first symbol is operation or )");
	if (infix[_size - 1] == '(' || is_Oper(infix[_size - 1])) throw invalid_argument("invalid input, first symbol is operation or )");
	for (int i = 0; i < _size; i++)
	{
		if (!is_Oper(infix[i]) && !is_Digit(infix[i]) && !is_Var(infix[i]) && infix[i]!= '(' && infix[i] != ')' && infix[i] != '.' && infix[i] != '~') throw invalid_argument("invalid input, unknown symbol");
		if(i != _size-1)
		{
			if (infix[i] == '(')brackets++;
			if (infix[i] == ')')brackets--;
			if (is_Oper(infix[i]) && is_Oper(infix[i + 1]))throw invalid_argument("invalid input. Two operations.");
			if ((is_Digit(infix[i]) && is_Var(infix[i + 1])) || (is_Var(infix[i]) && is_Digit(infix[i + 1]))) invalid_argument("Invalid input. Variable and constant is near");
			if ((infix[i] == ')') && (is_Digit(infix[i + 1]) || is_Var(infix[i + 1]))) throw invalid_argument("invalid input ) near to variable or constant. If you want to multiply, please write epression_1 * (expression_2)");
			if (infix[i] == '(' && infix[i + 1] == ')') throw invalid_argument("invalid argument. empty expression inside brackets");
		}
		if ((i > 0) && infix[i] == '(' && !is_Oper(infix[i - 1])) throw invalid_argument("invalid argument. variable or constant near to (. If you want to multiply, please write epression_1 * (expression_2)");
	}
	if (brackets != 0) throw invalid_argument("Too many / too few brackets");

	//__________________GETTING POSTFIX____________________________//

	for (int i = 0; i < _size; i++)
	{
		if (infix[i] == '~' && (is_Digit(infix[i+1]) || is_Var(infix[i+1])))
		{
				_sign *= -1;
				i++;
				//infix[i] = '~';
		}
		 if (is_Digit(infix[i]))
		{
			TStack<char> _stck;
			//if (_sign == -1) { _stck.push('-'); }
			while (is_Digit(infix[i]) || infix[i] == '.')
			{
				_stck.push(infix[i]);
				i++;
			}
			i--;
			_Constant* c = new _Constant(_stck, _sign);
			_sign = 1;
			arr[pos] = c;
			pos++;
		}
		 if (is_Var(infix[i]))
		{
			 _Variable* v = new _Variable(infix[i], _sign);
			 arr[pos] = v;
			 pos++;
		}


		  if (is_Oper(infix[i]))
		{
			Operation* op = new Operation(infix[i]);
			if ((i - 1 >= 0 && (is_Oper(infix[i - 1]) || infix[i - 1] == '-')) || is_Oper(infix[i + 1]) || infix[i + 1] == ')' || i == 0 || (i - 1 >= 0 && (infix[i - 1] == '('))) throw invalid_argument("Invalid input oper");
 			arr[pos] = op;
 			pos++;
		 }


		 if (infix[i] == '(')
		 {


		 	if ((i - 1 >= 0) && (is_Var(infix[i - 1]) || is_Digit(infix[i - 1])) || /*is_Oper(infix[i + 1])*/(infix[i+1] == '+' || infix[i + 1] == '*' || infix[i + 1] == '/') || i + 1 >= _size) throw invalid_argument("Invalid input");
		 	Operation* op = new Operation(infix[i]);
		 	arr[pos] = op;
		 	pos++;

		 }
		 if (infix[i] == ')')
		 {
		 	if ((i - 1 <= 0) && (is_Oper(infix[i - 1])) || is_Digit(infix[i + 1]) || is_Var(infix[i + 1]) || i - 1 <= 0) throw invalid_argument("Invalid input");

		 	Operation* op = new Operation(infix[i]);
		 	arr[pos] = op;
		 	pos++;
		 	//brackets--;

		 }



	}

	int _size1 = pos;

	Lexema** _LEXEMA = new  Lexema * [_size1];
	for (int i = 0; i < _size1; i++)
	{

		_LEXEMA[i] = arr[i];
		cout << _LEXEMA[i]->GetLexeme()<<"  ";
	}
	cout << endl;
	//for (int o = 0; o < _size1; o++)
	//{
	//	cout << _LEXEMA[o]->GetType()<< "  ";
	//}
	//cout << endl;

	_size1 = pos;

	string postfix_form;

	TStack<Lexema> lexms1;
	TStack<Lexema> lexms_topost;

	int indx = _size1;
	postfix_size = _size1;
	postfix = new Lexema*[indx];
	TStack<char> postfix_stck;
	int z = 0;
	int final_size = _size1;
	//for (int o = 0; o < indx; o++)
	//{
	//	if (_LEXEMA[o]->GetType() == "operation")cout << _LEXEMA[o]->GetPriority();
	//}

	for (int u = 0; u < indx; u++)
	{
		if (_LEXEMA[u]->GetType() == "constant" || _LEXEMA[u]->GetType() == "variable")
		{
			postfix[z++] = _LEXEMA[u];
		}
		else if (_LEXEMA[u]->GetType() == "open_bracket")
		{
			postfix_stck.push('(');
			final_size--;
		}
		else if (_LEXEMA[u]->GetType() == "close_bracket")
		{
			if (!postfix_stck.empty())
			{
				while (postfix_stck.top()!='(')
				{
					postfix[z++] = new Operation(postfix_stck.pop());
				}
				postfix_stck.pop();
				final_size--;
			}

		}
		if (_LEXEMA[u]->GetType() == "operation")
		{
			if (!postfix_stck.empty() && (_LEXEMA[u]->GetPriority() <= isPrioritychar(postfix_stck.top())))
			{
				while ((_LEXEMA[u]->GetPriority() <= isPrioritychar(postfix_stck.top())) && (!postfix_stck.empty()) && _LEXEMA[u]->GetType() == "operation")
				{
					postfix[z++] = new Operation(postfix_stck.pop());
				}
			}
			postfix_stck.push(_LEXEMA[u]->GetOperation());
		}

	
	}

	while (!postfix_stck.empty())
	{
		postfix[z++] = new Operation(postfix_stck.pop());
	}
	//cout << lexms_topost.size() << endl;
	//cout << "====================" << endl;

	for (int i = 0; i < final_size; i++)
	{
		postfix_form += postfix[i]->GetLexeme();
	}
	postfix_size = final_size;
	 
	_pstfx = postfix_form;

}

double TPostfix::Calculate()
{
	TStack<double> _constants;
	map<char, double> variables;
	TStack <char> vars;
	TStack<double> vbs;
	for (int i = 0; i < postfix_size; i++)
	{
		if (postfix[i]->GetType() == "variable")
		{
			if (!vars.empty())
			{
				for (int j = 0; j < vars.size(); i++)
				{
					if (vars[j] == postfix[i]->GetOperation())
					{
						break;
					}
					vars[j] = postfix[i]->GetOperation();
				}
			}
			else
			{
				vars.push( postfix[i]->GetOperation());
			}
		}
	}
	if (!vars.empty())
	{
		cout << "Input variable's values: " << endl;
		for (int j = 0; j < vars.size(); j++)
		{
			double value;
			cin >> value;
			vbs.push( value);
			cout << vars[j] <<"="<<vbs[j] << endl;
		}
	}
	for (int i = 0; i < postfix_size; i++)
	{
		if (postfix[i]->GetType() == "constant")
		{
			//cout << postfix[i]->GetValue();
			_constants.push(postfix[i]->GetValue());
		}
		if (!vars.empty())
		{
			if (postfix[i]->GetType() == "variable")
			{
				for (int h = 0; h < vars.size(); h++)
				{
					if (postfix[i]->GetOperation() == vars[h])
					{
						_constants.push(vbs[h]);
					}
				}
			}
		}
		if(postfix[i]->GetType() == "operation")
		{
			if (postfix[i]->GetOperation() == '+')
			{
				double left = _constants.pop();
				double right = _constants.pop();
				_constants.push(right + left);
			}
			if (postfix[i]->GetOperation() == '-')
			{
				double left = _constants.pop();
				double right = _constants.pop();
				_constants.push(right - left);

			}
			if (postfix[i]->GetOperation() == '*')
			{
				double left = _constants.pop();
				double right = _constants.pop();
				_constants.push(right * left);
			}
			if (postfix[i]->GetOperation() == '/')
			{
			
				double left = _constants.pop();
				double right = _constants.pop();
				if (left <= 0.00000001 && left >= -0.00000001)  throw invalid_argument("invalid input");
				_constants.push(right / left);
			}
		}
	}

	double res = _constants.pop();
	return res;

}