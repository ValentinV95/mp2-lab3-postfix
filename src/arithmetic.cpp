#include "../include/arithmetic.h"






Operation::Operation()
{
	type = 3;
}

Operation::Operation(char a)
{

	type = 3;
	lexem_m.push_back(a);

	switch (a)
	{
	case '+':
		lexem_Op = '+';
		priority = 1;
		break;

	case '-':
		lexem_Op = '-';
		priority = 1;
		break;

	case '*':
		lexem_Op = '*';
		priority = 2;
		break;

	case '/':
		lexem_Op = '/';
		priority = 2;
		break;

	case '(':
		lexem_Op = '(';
		type = -1;
		break;

	case ')':
		lexem_Op = ')';
		type = -2;
		break;

	default:
		break;
	}

}



Const::Const(Tstack<char>& a, Tstack<char>& save_const, int znak)
{
	type = 1;
	int dblsize = a.size();
	for (int i = 0; i < a.size(); i++)
	{
		for (int j = 0; a.Top() != '.' && j < dblsize; j++)
		{
			lexem_const = lexem_const / 10 + (a.Pop() - 48);
		}

		if (a.Top() != '.')
		{
			lexem_const = lexem_const * pow(10, dblsize - 1);
		}
		else
		{
			lexem_const /= 10;
			a.Pop();
			int umn = 1;
			while (!a.isEmpty())
			{
				lexem_const = lexem_const + (a.Pop() - 48) * umn;
				umn *= 10;
			}
		}
	}

	lexem_const *= znak;

	char* num_str;
	int numsize = save_const.size();
	num_str = new char[numsize];
	if (znak == -1)
	{
		lexem_m.push_back('-');
	}
	for (int q = numsize - 1; q >= 0; q -= 1)
	{
		num_str[q] = save_const.Pop();
	}
	for (int y = 0; y < numsize; y++)
	{
		lexem_m.push_back(num_str[y]);
	}
	cout << endl << "string :  " << lexem_m << endl;
}

Const::Const()
{
	type = 1;
}



Var::Var()
{
	var_znak = 1;
	type = 2;
	lexem_var = '$';
}

Var::Var(char var, int znak)
{
	type = 2;

	if (znak == -1)
	{
		var_znak = -1;
		lexem_m.push_back('-');
	}

	lexem_m.push_back(var);
	lexem_var = var;

	
}



TPostfix::TPostfix(string infix)
{
	search(infix);


}



//------------------------------------------------|)


void Const::shop()
{
	cout << " " << lexem_m;
}

void Operation::shop()
{
	cout << " " << lexem_m;
}

string LEXEM::show()
{
	string tmp = lexem_m;
	return tmp;
}

void Var::shop()
{
	cout << " " << lexem_m;
}















//------------------------------------------------|)





void TPostfix::search(string infix)
{
	int problem_flag = -1;

	int pos = 0;
	mas = new LEXEM * [infix.length()];

	int znak = 1;
	int oznak = 1;


	int count_c = 0;
	int c_k1 = 0;
	int c_k2 = 0;



	for (int i = 0; i < infix.length(); i++)
	{

		//=============================[ Операнд - константа ] 

		if (infix[i] == '-' && infix[i + 1] >= '0' && infix[i + 1] <= '9')
		{
			if (i - 1 >= 0 && (infix[i - 1] < '0' || infix[i - 1] > '9') && infix[i - 1] != '.' && infix[i - 1] != ')' && !(infix[i - 1] >= 97 && infix[i - 1] <= 122)) //[no operand / not ')']  " - " [operand constanta] 
			{
				znak = -1;
				i++;
			}
			else if (i == 0)  //             [empty]  " - " [operand constanta] 
			{
				znak = -1;
				i++;
			}

		}
		if (infix[i] >= '0' && infix[i] <= '9')
		{

			int stop = 0;
			Tstack<char> number1, number2;
			while ((infix[i] >= '0' && infix[i] <= '9') || infix[i] == '.')
			{
				if (infix[i] == '.')
				{
					stop++;
					if (stop == 2)
					{
						cout << endl << endl << "There is a problem in " << problem_flag << " and " << i << " symbols !" << endl << "Two points in one operand" << endl << endl;
						exit(0);
					}
					problem_flag = i;
				}
				number1.Push(infix[i]);
				number2.Push(infix[i]);
				i++;
			}
			problem_flag = -1;
			i--;
			mas[pos] = new Const(number1, number2, znak);
			cout << "number :  " << mas[pos]->get_double() << endl;

			pos++;

			znak = 1;
		}

		//=============================[ operand - variable ]


		else if (infix[i] == '-' && infix[i + 1] >= 97 && infix[i + 1] <= 122)
		{
			if (i - 1 >= 0 && (infix[i - 1] == '+' || infix[i - 1] == '-' || infix[i - 1] == '*' || infix[i - 1] == '/' || infix[i - 1] == '(')) //[no operand / not ')']  " - " [operand constanta] 
			{
				oznak = -1;
			}
			else if (i == 0)  //             [empty]  " - " [operand constanta] 
			{
				oznak = -1;
			}

		}
		else if (infix[i] >= 97 && infix[i] <= 122)
		{
			if (i - 1 >= 0 && infix[i - 1] == ')')
			{
				cout << endl << endl << "There is a problem in symbol: " << i << " and " << i + 1 << endl << "Wrong input: Missing operation between ')' and '" << infix[i] << "'" << endl << endl;
				exit(0);
			}



			if (pos > 0 && (mas[pos - 1]->get_type() == 1 || mas[pos - 1]->get_type() == 2))
			{
				cout << endl << endl << "There is a problem in symbol: " << i << " and " << i + 1 << endl << "Wrong input: Two operands" << endl << endl;
				exit(0);
			}

			vars[infix[i]] = 0.0;
			mas[pos] = new Var(infix[i], oznak);
			pos++;

			oznak = 1;
		}

		//=============================[ operation (without " () " ]

		else if (infix[i] == '+' || infix[i] == '-' || infix[i] == '*' || infix[i] == '/')
		{
			if (i == 0)
			{
				cout << endl << endl << "There is a problem in first symbol" << endl << "Wrong input: Operation at the begining" << endl << endl;
				exit(0);
			}
			if (i + 1 == infix.length())
			{
				cout << endl << endl << "There is a problem in last symbol" << endl << "Wrong input: Operation at the end" << endl << endl;
				exit(0);

			}
			if (mas[pos - 1]->get_type() == 3 && infix[i - 1] != ')')
			{
				cout << endl << endl << "There is a problem in symbol: " << i << " and " << i + 1 << endl << "Wrong input: Operation before operation" << endl << endl;
				exit(0);
			}
			if (infix[i + 1] == ')')
			{
				cout << endl << endl << "There is a problem in symbol: " << i + 1 << endl << "Wrong input: Operation have no operand next to him" << endl << endl;
				exit(0);
			}
			mas[pos] = new Operation(infix[i]);
			pos++;
		}


		//=============================[ operation - () ]

		else if (infix[i] == '(' || infix[i] == ')')
		{
			if (infix[i] == '(' && (i - 1 >= 0 && infix[i - 1] != '+' && infix[i - 1] != '-' && infix[i - 1] != '*' && infix[i - 1] != '/' && infix[i - 1] != '('))
			{
				cout << endl << endl << "There is a problem in symbol: " << i << " and " << i + 1 << endl << "Wrong input: Missing operation between '" << infix[i - 1] << "' and '('" << endl << endl;
				exit(0);
			}
			if (infix[i] == ')' && ((pos > 0 && !(mas[pos - 1]->get_type() == 1 || mas[pos - 1]->get_type() == 2)) || (i > 0 && infix[i - 1] == '(')) && (i > 0 && infix[i - 1] != ')'))
			{
				cout << endl << endl << "There is a problem after symbol '(' and before symbol ')'  which placed before " << i + 1 << " symbol" << endl << "Wrong input: operand must be under parentheses" << endl << endl;
				exit(0);
			}

			if (infix[i] == '(')
			{
				count_c++;
				c_k1++;
			}
			if (infix[i] == ')')
			{
				count_c--;
				c_k2++;
			}

			if (count_c < 0)
			{
				cout << endl << endl << "There is a problem in symbol: " << i + 1 << endl << "Wrong input: Operation ')' is incorrect" << endl << endl;
				exit(0);
			}

			mas[pos] = new Operation(infix[i]);
			pos++;
		}

		//=============================[ Thing what has not been included (trash) ]

		else
		{
			cout << endl << endl << "There is a problem in " << i + 1 << " symbol !" << endl << " wrong input" << endl << endl;
			exit(0);
		}

	}

	cout << endl << endl;

	if (count_c != 0)
	{
		cout << endl << endl << "There is a problem in the whole input !" << endl << " wrong input: We have " << c_k1 << "'('  but  " << c_k2 << "')'" << endl << endl;
		exit(0);
	}
	L_Size = pos;


	//))))))))))))))))))))))))))))))))))))))))))))))))
	LEXEM** tmp;
	tmp = new LEXEM * [L_Size];
	for (int l_r = 0; l_r < L_Size; l_r++)
	{
		tmp[l_r] = mas[l_r];
	}
	delete[] mas;
	mas = tmp;
	//))))))))))))))))))))))))))))))))))))))))))))))))


	infix_len = infix.length();
	true_size = L_Size - c_k1 - c_k2;
}




void TPostfix::to_postfix_form()
{


	//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

	//                   [    Here  we  get  our  postfix    ]

	//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 


	postfix_mas = new LEXEM * [true_size];
	int j = 0;

	Tstack<char> postfixStack;



	for (int i = 0; i < L_Size; i++)
	{

		if (mas[i]->isOperand())
		{

			postfix_mas[j++] = mas[i];


		}

		if (mas[i]->get_type() == -1)
		{
			postfixStack.Push('(');
		}

		if (mas[i]->lexem_m == ")")
		{
			if (!postfixStack.isEmpty())
			{
				while (postfixStack.Top() != '(')
				{
					postfix_mas[j++] = new Operation(postfixStack.Pop());

				}
				postfixStack.Pop();
			}
		}

		if (mas[i]->get_type() == 3)
		{
			if (((mas[i]->get_lexem_m() == "+" || mas[i]->get_lexem_m() == "-") && (postfixStack.Top() == '*' || postfixStack.Top() == '/')) || ((mas[i]->get_lexem_m() == "+" || mas[i]->get_lexem_m() == "-") && (postfixStack.Top() == '+' || postfixStack.Top() == '-')))
			{
				postfix_mas[j++] = new Operation(postfixStack.Pop());
				postfixStack.Push(mas[i]->get_char_op());
			}
			else
			{
				postfixStack.Push(mas[i]->get_char_op());
			}

		}


	}

	while (!postfixStack.isEmpty())
	{
		postfix_mas[j++] = new Operation(postfixStack.Pop());

	}



	cout << endl << " Postfix :   ";

	for (int i = 0; i < true_size; i++)
	{
		postfix_mas[i]->shop();
	}

}




void TPostfix::calculation()
{

	//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

	//                   [    Here  we  calculate using our  postfix    ]

	//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

	double res = 0;

	double one, two;

	Tstack<double> calc;




	int j = 0;


	double ss;

	cout << endl << "Before start calculate." << std::endl;

	cout << endl << endl << "Input variables :" << endl << endl;

	for (auto i = vars.begin(); i != vars.end(); i++)
	{
		cout << "Input " << i->first << " value: " << std::endl;
		std::cin >> ss;
		vars[i->first] = ss;
	}

	cout << endl << "Operands in postfix form :" << endl;

	for (int i = 0; i < true_size; i++)
	{
		if (postfix_mas[i]->get_type() == 1)
		{
			calc.Push(postfix_mas[i]->get_double());
			cout << "     const :" << postfix_mas[i]->get_double();
		}
		else if (postfix_mas[i]->isOperand())
		{
			double znak_k = postfix_mas[i]->get_double();
			vars[postfix_mas[i]->get_char_op()] *= znak_k;
			calc.Push(vars[postfix_mas[i]->get_char_op()]);
			cout << "     var :" << vars[postfix_mas[i]->get_char_op()];

		}


		else if (postfix_mas[i]->isOperation() && postfix_mas[i]->get_type() == 3)
		{
			if (postfix_mas[i]->get_char_op() == '+')
			{
				two = calc.Pop();
				one = calc.Pop();
				calc.Push(one + two);


			}
			else if (postfix_mas[i]->get_char_op() == '-')
			{
				two = calc.Pop();
				one = calc.Pop();
				calc.Push(one - two);


			}
			else if (postfix_mas[i]->get_char_op() == '*')
			{
				two = calc.Pop();
				one = calc.Pop();
				calc.Push(one * two);


			}
			else if (postfix_mas[i]->get_char_op() == '/')
			{
				two = calc.Pop();
				one = calc.Pop();
				if (two < 0.00000000000001)
				{
					cout << endl << endl << "There is a problem in the whole input !" << endl << " wrong input: We have division by zero |  " << one << "/0  |" << endl << endl;
					exit(0);
				}
				calc.Push(one / two);


			}

		}



	}

	res = calc.Pop();
	cout << endl << endl << "Resultat : " << res;

}







void TPostfix::checked_infix()
{

	cout << "Checked Infix : ";
	for (int l_r = 0; l_r < L_Size; l_r++)
	{
		cout << mas[l_r]->show();
	}

	cout << endl << endl << "Amount of Chars :  " << infix_len << endl;
	cout << endl << "Amount of Lexems :  " << L_Size << endl;



	cout << endl << endl << " Size is: " << L_Size;
	cout << endl << " But postfix size is: " << true_size;



}





//------------------------------------------------|)


string without_spaces(string infix)
{
	infix.erase(remove_if(infix.begin(), infix.end(), ::isspace), infix.end());
	cout << infix;
	return infix;
}

int get_priority_outside(char a)
{
	switch (a)
	{
	case '+': case '-':
		return 1;
		break;

	case '*': case '/':
		return 2;
		break;

	default:
		break;
	}

}