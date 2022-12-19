// объ€вление функций и классов дл€ вычислени€ арифметических выражений
#include<map>
#include"stack.h"
#include <cctype>
#include <algorithm>


 class LEXEM
{
public:
	virtual char get_char_op()=0;
	virtual bool isOperation()=0;
	virtual bool isOperand()=0;
	virtual double get_double() = 0;
	virtual int get_priority()=0;

	int size_for_postfix = 0;
	int postfix_size = 0;

	int type; // 1-константа, 2-переменна€, 3-операци€ , type -1 "("  , type -2 ")"
	string lexem_m;

	virtual void shop() = 0;

	string show()
	{
		string tmp = lexem_m;
		return tmp;
	}
	
	string get_lexem_m() { return lexem_m; }

	 int get_type() { return type; }


	 int get_size_for_postfix() { return size_for_postfix; }
	 int get_postfix_size() { return postfix_size; }


	 char get_char() {return '@';}

};



 class Operation : public LEXEM
 {
 public:
	 bool isOperation() { return 1; };
	 bool isOperand() {return 0;}

	 char lexem_Op;
	 int priority=10;
	 
	
	 Operation()
	 {
		 type = 3;
	 }


	 Operation(char a)
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


	 void shop()
	 {
		 cout << " " << lexem_m;
	 }
	
	 int get_priority() { return priority; }

	 char get_char_op() { return lexem_Op; }

	 double get_double() { return 0.0; }
 };



 class Operand : public LEXEM
 {
 public:

	 bool isOperation() { return 0; };
	 bool isOperand() { return 1; }



	 
	 
 };



 class Const : public Operand
 {
 public:
	 double lexem_const=0;

	 Const()
	 {
		 type = 1;
	 }

	 Const(Tstack<char> a, Tstack<char> save_const, int znak)
	 {
		 type = 1;
		 int dblsize = a.size();
		 for (int i = 0; i < a.size(); i++)
		 {
			 for (int j=0;a.Top() != '.' && j< dblsize;j++)
			 {
				 lexem_const = lexem_const / 10 + (a.Pop()-48);
			 }
			 
			 if (a.Top() != '.')
			 {
				 lexem_const = lexem_const * pow(10, dblsize-1); 
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
		 for (int q = numsize -1; q >= 0; q-=1)
		 {
			 num_str[q]=save_const.Pop();
		 }
		 for (int y = 0; y < numsize; y++)
		 {
			 lexem_m.push_back(num_str[y]);
		 }
		 cout <<endl << "string :  " << lexem_m<<endl;
	 }


	 int  get_priority() { return 0; }


	 char get_char_op() { return '0'; }


	 void shop()
	 {
		 cout << " " << lexem_m;
	 }

	 double get_double() { return lexem_const; }

 };



 class Var : public Operand
 {
 public:
	 char lexem_var;

	 Var()
	 {
		 type = 2;
		 lexem_var = '$';
	 }


	 Var(char var)
	 {
		 type = 2;

		 lexem_m.push_back(var);
		 lexem_var = var;
	 }



	 int get_priority() { return 0; }
	 char get_char_op() 
	 { 
		 type = 2;
		 return lexem_var; 
	 }


	 void shop()
	 {	 
		 cout << " " << lexem_m;
	 }

	 double get_double() { return 0.0; }
 };








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

 


































template <typename T> class TPostfix
{

public:
	LEXEM** mas;
	int L_Size=0;
	int true_size = 0;
	map<char, double> vars;


	TPostfix(string infix) 
	{
		search(infix);
		
		
	}

	void search(string infix)
	{
		int problem_flag = -1;

		LEXEM** mas;
		int pos = 0;
		mas = new LEXEM * [infix.length()];

		int znak = 1;


		int count_c = 0;
		int c_k1 = 0;
		int c_k2 = 0;



		for (int i = 0; i < infix.length(); i++)
		{

			//=============================[ ќперанд - константа ] 

			if (infix[i] == '-' && infix[i + 1] >= '0' && infix[i + 1] <= '9')
			{
				if (i - 1 >= 0 && (infix[i - 1] < '0' || infix[i - 1] > '9') && infix[i - 1] != '.' && infix[i - 1] != ')' && !(infix[i-1] >= 97 && infix[i-1] <= 122)) //[не операнд / не ')']  " - " [операнд константа] 
				{
					znak = -1;
					i++;
				}
				else if (i == 0)  //             [пусто]  " - " [операнд константа] 
				{
					znak = -1;
					i++;
				}

			}
			if (infix[i] >= '0' && infix[i] <= '9')
			{

				int stop = 0;
				Tstack<char> number;
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
					number.Push(infix[i]);
					i++;
				}
				problem_flag = -1;
				i--;
				Const* constanta = new Const(number, number, znak);
				cout << "number :  " << constanta->lexem_const << endl;

				mas[pos] = constanta;
				pos++;

				znak = 1;
			}

			//=============================[ ќпераци€ (без скобок) ]

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
				Operation* operation = new Operation(infix[i]);

				mas[pos] = operation;
				pos++;
			}

			//=============================[ ќперанд - переменна€ ]

			else if (infix[i] >=97 && infix[i] <=122 )
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
				Var* variable = new Var(infix[i]);
				mas[pos] = variable;
				pos++;
			}

			//=============================[ ќпераци€ - скобки ]

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

				Operation* operation = new Operation(infix[i]);

				mas[pos] = operation;
				pos++;
			}

			//=============================[ Ёлементы не вход€щие в формулу ]

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
		/*LEXEM** tmp;
		tmp = new LEXEM * [L_Size];
		for (int l_r = 0; l_r < L_Size; l_r++)
		{
			tmp[l_r] = mas[l_r];
		}
		delete[] mas;
		mas = tmp;
		*/
		cout << "Checked Infix : ";
		for (int l_r = 0; l_r < L_Size; l_r++)
		{
			cout << mas[l_r]->show();
		}

		cout << endl << endl << "Amount of Chars :  " << infix.length() << endl;
		cout << endl << "Amount of Lexems :  " << L_Size << endl;

		true_size = L_Size-c_k1-c_k2;
	



		cout << endl << endl << " Size is: " << L_Size;
		cout << endl << " But postfix size is: " << true_size;



		


		LEXEM** postfix_mas;
		postfix_mas = new LEXEM*[true_size];
		int j = 0;

		Tstack<char> postfixStack;

		

		for (int i = 0; i < L_Size; i++)
		{
			
			if (mas[i]->isOperand())
			{
				
					postfix_mas[j++]= mas[i];
				
				
			}

			if (mas[i]->get_type() == -1)
			{
				postfixStack.Push('(');
			}

			if (mas[i]->lexem_m==")")
			{
				if (!postfixStack.isEmpty())
				{
					while (postfixStack.Top() != '(')
					{
						Operation* n = new Operation(postfixStack.Pop());
						postfix_mas[j++] = n;
					}
					postfixStack.Pop();
				}
			}

			if (mas[i]->get_type() == 3)
			{
					if (((mas[i]->get_lexem_m() =="+" || mas[i]->get_lexem_m() == "-")&& (postfixStack.Top() == '*' || postfixStack.Top() == '/')) || ((mas[i]->get_lexem_m() == "+" || mas[i]->get_lexem_m() == "-")&& (postfixStack.Top() == '+' || postfixStack.Top() == '-')))
					{
						Operation* n = new Operation(postfixStack.Pop());
						postfix_mas[j++] = n;
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
			Operation* n = new Operation(postfixStack.Pop());
			postfix_mas[j++] = n;
		}



		cout << endl << " Postfix :   ";

		for (int i = 0; i < true_size; i++)
		{
			postfix_mas[i]->shop();
		}




		double res=0;

		double one, two;

		Tstack<double> calc;

		cout << endl<<endl << "Input variables :" << endl << endl;

		
		 j = 0;
		

		double ss;

		cout << "Before start calculate." << std::endl;
		

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
				cout << "     const :" << postfix_mas[i]->get_double() ;
			}
			else if (postfix_mas[i]->isOperand() )
			{
				calc.Push(vars[postfix_mas[i]->get_char_op()]);
				cout << "     var :" << vars[postfix_mas[i]->get_char_op()] ;

			}


			else if (postfix_mas[i]->isOperation() && postfix_mas[i]->get_type() == 3)
			{
				if (postfix_mas[i]->get_char_op() == '+')
				{
					two = calc.Pop();
					 one= calc.Pop();
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
					calc.Push(one / two);
					

				}

			}

			

		}

		res = calc.Pop();
		cout << endl << endl << "Resultat : " << res;
	}


};