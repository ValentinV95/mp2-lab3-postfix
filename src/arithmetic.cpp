#include "../include/arithmetic.h"






Operation::Operation()
{
	alter_lexem_m = lexem_m;
	type = 3;
}

Operation::Operation(char a)
{
	alter_lexem_m = lexem_m;
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



Const::Const(Tstack<char>& a, Tstack<char>& save_const, int znak,bool alternative)
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
		alter_lexem_m.push_back(num_str[y]);
	}
	if(znak == -1)
	{
		alter_lexem_m.push_back(' ');
		alter_lexem_m.push_back(' ');
		alter_lexem_m.push_back('~');
	}

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

Var::Var(char var, int znak, bool alternative)
{
	type = 2;

	if (znak == -1)
	{
		var_znak = -1;
		lexem_m.push_back('-');
	}

	lexem_m.push_back(var);
	lexem_var = var;
	alter_lexem_m.push_back(var);
	if (znak == -1)
	{
		alter_lexem_m.push_back(' ');
		alter_lexem_m.push_back(' ');
		alter_lexem_m.push_back('~');
	}
	
}



TPostfix::TPostfix(string infix,bool alternative,bool test)
{
	if (infix.length() == 0)
	{
		throw exception("Literaly no input:  Empty infix");
	}
	search(infix,alternative,test);

}



//------------------------------------------------|)


void Const::shop(bool alternative)
{
	if (alternative)
	{
		cout << "  " << alter_lexem_m;
	}
	else
	{
		cout << "  " << lexem_m;
	}
}

void Operation::shop(bool alternative)
{
	cout << "  " << lexem_m;
}

string LEXEM::show()
{
	string tmp = lexem_m;
	return tmp;
}

void Var::shop(bool alternative)
{
	if (alternative)
	{
		cout << "  " << alter_lexem_m;
	}
	else
	{
		cout << "  " << lexem_m;
	}
}















//------------------------------------------------|)





void TPostfix::search(string infix,bool alternative,bool test)
{


	
	int problem_flag = -1;

	int pos = 0;
	mas = new LEXEM * [infix.length()];

	int znak = 1;
	int oznak = 1;


	int count_c = 0;
	c_k1 = 0;
	c_k2 = 0;



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
			if (pos > 0)
			{
				if (mas[pos-1]->get_type()==2)
				{
					if(!test) cout << endl << endl << "There is a problem in symbol: " << i << " and " << i + 1 << endl;
					throw exception("Wrong input: Two operands in a row");
				}	
			}

			int stop = 0;
			Tstack<char> number1, number2;
			while ((infix[i] >= '0' && infix[i] <= '9') || infix[i] == '.')
			{
				if (infix[i] == '.')
				{
					stop++;
					if (stop == 2)
					{
						if (!test) cout << endl << endl << "There is a problem in " << problem_flag << " and " << i << " symbols !" << endl ;
						throw exception("Two points in one operand");
					}
					problem_flag = i;
				}
				number1.Push(infix[i]);
				number2.Push(infix[i]);
				i++;
			}
			problem_flag = -1;
			i--;
			mas[pos] = new Const(number1, number2, znak,alternative);

			pos++;

			znak = 1;
		}

		//=============================[ operand - variable ]


		if (infix[i] == '-' && infix[i + 1] >= 97 && infix[i + 1] <= 122)
		{
			if (i - 1 >= 0 && (infix[i - 1] == '+' || infix[i - 1] == '-' || infix[i - 1] == '*' || infix[i - 1] == '/' || infix[i - 1] == '(')) //[no operand / not ')']  " - " [operand constanta] 
			{
				oznak = -1;
				i++;
			}
			else if (i == 0)  //             [empty]  " - " [operand constanta] 
			{
				oznak = -1;
				i++;
			}

		}
		if (infix[i] >= 97 && infix[i] <= 122)
		{
			if (i - 1 >= 0 && infix[i - 1] == ')')
			{
				if (!test) cout << endl << endl << "There is a problem in symbol: " << i << " and " << i + 1 << endl << " Missing operation between ')' and '" << infix[i] << "'" << endl << endl;
				throw exception("Wrong input: can't find operation");
			}



			if (pos > 0 && (mas[pos - 1]->get_type() == 1 || mas[pos - 1]->get_type() == 2))
			{
				if (!test) cout << endl << endl << "There is a problem in symbol: " << i << " and " << i + 1 << endl;
				throw exception("Wrong input: Two operands in a row");
			}

			vars[infix[i]] = 0.0;
			mas[pos] = new Var(infix[i], oznak, alternative);
			pos++;

			oznak = 1;
		}

		//=============================[ operation (without " () " ]

		 if (infix[i] == '+' || infix[i] == '-' || infix[i] == '*' || infix[i] == '/')
		{
			if (i == 0)
			{
				if (!test) cout << endl << endl << "There is a problem in first symbol" << endl ;
				throw exception("Wrong input: Operation at the begining");
			}
			if (i + 1 == infix.length())
			{
				if (!test) cout << endl << endl << "There is a problem in last symbol" << endl ;
				throw exception("Wrong input: Operation at the end");

			}
			if (mas[pos - 1]->get_type() == 3 && infix[i - 1] != ')')
			{
				if (!test) cout << endl << endl << "There is a problem in symbol: " << i << " and " << i + 1 << endl ;
				throw exception("Wrong input: Operation before operation");
			}
			if (infix[i + 1] == ')')
			{
				if (!test) cout << endl << endl << "There is a problem in symbol: " << i + 1 << endl ;
				throw exception("Wrong input: Operation have no operand next to him");
			}
			mas[pos] = new Operation(infix[i]);
			pos++;
		}


		//=============================[ operation - () ]

		  if (infix[i] == '(' || infix[i] == ')')
		{
			if (infix[i] == '(' && (i - 1 >= 0 && infix[i - 1] != '+' && infix[i - 1] != '-' && infix[i - 1] != '*' && infix[i - 1] != '/' && infix[i - 1] != '('))
			{
				if (!test) cout << endl << endl << "There is a problem in symbol: " << i << " and " << i + 1 << endl << " Missing operation between '" << infix[i - 1] << "' and '('" << endl << endl;
				throw exception("Wrong input : can't find operation");
			}
			if (infix[i] == ')' && ((pos > 0 && !(mas[pos - 1]->get_type() == 1 || mas[pos - 1]->get_type() == 2)) || (i > 0 && infix[i - 1] == '(')) && (i > 0 && infix[i - 1] != ')'))
			{
				if (!test) cout << endl << endl << "There is a problem after symbol '(' and before symbol ')'  which placed before " << i + 1 << " symbol" << endl ;
				throw exception("Wrong input: operand must be under parentheses");
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
				if (!test) cout << endl << endl << "There is a problem in symbol: " << i + 1 << endl ;
				throw exception("Wrong input: Operation ')' is incorrect");
			}

			mas[pos] = new Operation(infix[i]);
			pos++;
		}

		//=============================[ Thing what has not been included (trash) ]

		 if((infix[i]!='+' && infix[i] != '-' && infix[i] != '*' && infix[i] != '/' && infix[i] != '(' && infix[i] != ')') && (infix[i]<97 || infix[i]>122)&&(infix[i] <'0'||infix[i]>'9' ))
		{
			 if (!test) cout << endl << endl << "There is a problem in " << i + 1 << " symbol !" << endl ;
			throw exception(" Wrong input");
		}
		
	}

	if (!test)cout << endl << endl;

	if (count_c != 0)
	{
		if (!test) cout << endl << endl << "There is a problem in the whole input !" << endl << " We have " << c_k1 << "'('  but  " << c_k2 << "')'" << endl ;
		throw exception(" Wrong input: wrong number of parentheses");
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




void TPostfix::to_postfix_form(bool alternative,bool test)
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
					if (!test)cout << postfix_mas[j - 1]->get_lexem_m() << endl;
				}
				postfixStack.Pop();
			}
		}

		if (mas[i]->get_type() == 3)
		{
			if (mas[i]->get_priority()<= get_priority_outside(postfixStack.Top()))
			{
				while (!postfixStack.isEmpty()    &&    (mas[i]->get_type()==3)   &&   (mas[i]->get_priority() <= get_priority_outside(postfixStack.Top())))
				{
					postfix_mas[j++] = new Operation(postfixStack.Pop());
				}
			}
				postfixStack.Push(mas[i]->get_char_op());
			
		}

	}

	while (!postfixStack.isEmpty())
	{
		postfix_mas[j++] = new Operation(postfixStack.Pop());

	}



	if (!test)
	{
		cout << endl << " Postfix :   ";


		for (int i = 0; i < true_size; i++)
		{
			postfix_mas[i]->shop(alternative);
		}

	}
	
}




double TPostfix::calculation(bool test)
{

	//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

	//                   [    Here  we  calculate using our  postfix    ]

	//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

	double res = 0;

	double one, two;

	Tstack<double> calc;




	int j = 0;


	double ss;

	if (!test) cout << endl << "Before start calculate." << std::endl;

	if (!test) cout << endl << endl << "Input variables :" << endl << endl;

	for (auto i = vars.begin(); i != vars.end(); i++)
	{
		if (!test)cout << "Input " << i->first << " value: " << std::endl;
		std::cin >> ss;
		vars[i->first] = ss;
		j++;
	}
	if (j == 0)
	{
		if (!test) cout << "   ( There are no variables )" << endl<<endl<<endl;
	}

	if (!test) cout << endl << "Operands in postfix form :" << endl;

	for (int i = 0; i < true_size; i++)
	{
		if (postfix_mas[i]->get_type() == 1)
		{
			calc.Push(postfix_mas[i]->get_double());
			if (!test) cout << "     const :" << postfix_mas[i]->get_double();
		}
		else if (postfix_mas[i]->isOperand())
		{
			double znak_k = postfix_mas[i]->get_double();
			vars[postfix_mas[i]->get_char_op()] *= znak_k;
			calc.Push(vars[postfix_mas[i]->get_char_op()]);
			if (!test) cout << "     var :" << vars[postfix_mas[i]->get_char_op()];

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
				if (abs(two) < 0.00000000000001)
				{
					if (!test) cout << endl << endl << "There is a problem in the whole input !" << endl << " We have division by zero |  " << one << "/0  |" << endl ;
					throw exception("wrong input : can't divide by zero");
				}
				calc.Push(one / two);


			}

		}



	}

	res = calc.Pop();
	return res;
	

}







void TPostfix::checked_infix(bool alternative)
{
	int minuses = 0;
	cout << "Checked Infix : ";
	for (int l_r = 0; l_r < L_Size; l_r++)
	{
		cout << mas[l_r]->show();
		if (alternative)
		{
			if (mas[l_r]->get_double() < 0)
			{
				minuses++;
			}
		}
	}

	cout << endl << endl << "Amount of Chars :  " << infix_len << endl;
	if (alternative)
	{
		cout << endl << "Amount of Lexems :  " << L_Size + minuses << endl;
	}
	else
	{
		cout << endl << "Amount of Lexems :  " << L_Size  << endl;
	}


	
	

	cout << endl << endl << " Size is: " << L_Size;
	cout << endl << " But postfix size is: " << true_size+ minuses;



}




void TPostfix::get_full_information(bool alternative)
{
	cout << endl;
	cout << endl;
	cout <<"-------------------------------------------------------------------------"<< endl;
	cout << endl;
	cout <<"                [ Whole information about postfix form ]                 "<< endl;
	cout << endl;
	cout << "-------------------------------------------------------------------------" << endl;
	cout << endl;
	cout <<"- - - - - - -(| Amount of char in infix form: "<<infix_len<< endl;
	cout <<"- - - - - - -(| Amount of elements in infix form: "<< L_Size<< endl;
	cout <<"- - - - - - -(| Amount of elements in postfix form: "<< true_size<<"                ( whithout parentheses )"<< endl;
	
	int numbOfOperands = 0;
	int numbOfConst = 0;
	int numbOfVars = 0;
	int numbOfOperations = 0;

	for (int i = 0; i < true_size; i++)
	{
		numbOfOperands += postfix_mas[i]->isOperand();
		if (postfix_mas[i]->isOperand())
		{
			if (postfix_mas[i]->get_type() == 1)
			{
				numbOfConst++;
			}
			if (postfix_mas[i]->get_type() == 2)
			{
				numbOfVars++;
			}
		}
		numbOfOperations += postfix_mas[i]->isOperation();
	}

	cout << endl;
	cout << endl;
	cout << "- - - - - - -(| Amount of operands: "<< numbOfOperands << endl;
	cout << "-   -   -   -   -   -   -< amount of constants: "<< numbOfConst <<endl;
	cout << "-   -   -   -   -   -   -< amount of variables: "<< numbOfVars <<endl;
	cout << "- - - - - - -(| Amount of operations: " << numbOfOperations << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	TPostfix::get_quick_info(alternative);
	cout << endl;
	cout << endl;
}



void TPostfix::get_quick_info(bool alternative)
{
	for (int i = 0; i < true_size; i++)
	{
		string ans = "No";
		
		if (alternative && postfix_mas[i]->isOperand())
		{
			cout << endl << endl << endl << "     (" << i + 1 << ")  element: [ " << postfix_mas[i]->get_alter_lexem_m() << " ]" << endl;
		}
		else
		{
			cout << endl << endl << endl << "     (" << i + 1 << ")  element: [ " << postfix_mas[i]->get_lexem_m() << " ]" << endl;
		}
		

		if (postfix_mas[i]->isOperand())
		{
			if (postfix_mas[i]->get_double() < 0.0)
			{
				ans = "Yes";
			}
			cout <<endl<< "- - - -| Is there a unary minus ?     --->     Answer <" << ans <<">"<< endl;

			ans = "No";

			if (postfix_mas[i]->get_type() == 2) // x,y,z
			{
				cout << endl << "- - - -| Type of element:  [Operand] - (variable)" << endl;
				cout << endl << "- - - -| Double:      <  " << vars[postfix_mas[i]->get_char_op()] << "  >" << endl;
			}
			if (postfix_mas[i]->get_type() == 1)
			{
				cout << endl << "- - - -| Type of element:  [Operand] - (constant)" << endl;
				cout << endl << "- - - -| Double:      <  " << postfix_mas[i]->get_double() << "  >" << endl;
			}
		}
		if (postfix_mas[i]->isOperation())
		{
			cout << endl << "- - - -| Type of element:  [Operation]" << endl;
			cout << endl << "- - - -| Operation priority: " << postfix_mas[i]->get_priority();
		}
	}

}


//------------------------------------------------|)


string without_spaces(string infix)
{
	infix.erase(remove_if(infix.begin(), infix.end(), ::isspace), infix.end());
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

	case '(': case ')':
		return 0;
		break;

	default:
		break;
	}

}





bool choice()
{
	bool alternative;
	while (true)
	{
		int choice;
		cout << endl;
		cout << " How you want to see unary minus:" << endl;
		cout << " (1)  -x" << endl;
		cout << " (2)  x  ~                             (like two different lexems)" << endl;
		cout << endl;
		cout << "My choice: ";
		cin >> choice;
		if (choice == 1)
		{
			alternative = false;
			break;
		}
		else if (choice == 2)
		{
			alternative = true;
			break;
		}
		else
		{
			cout << " incorrect answer.  Try again" << endl;
		}
	}
	return alternative;
}