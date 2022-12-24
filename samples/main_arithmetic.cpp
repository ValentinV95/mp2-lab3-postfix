#include"arithmetic.h"

int main()
{

	cout << "                                                                                 " << endl;
	cout << "   > > > >-| What you need to know before using this programm |-< < < <          " << endl;
	cout << "                                                                                 " << endl;
	cout << "                                                                                 " << endl;
	cout << "  __________________________________________________________________________________________     " << endl;
	cout << " |                                                                                          |    " << endl;
	cout << " | 1. You can use binary operation ( - , + , * , / )                                        |    " << endl;
	cout << " |                                                                                          |    " << endl;
	cout << " | 2. You can use unary minus ( - ), one time before each operand                           |    " << endl;
	cout << " |                                                                                          |    " << endl;
	cout << " | 3. You can use brackets '(' ')' , at least one operand must be inside                    |    " << endl;
	cout << " |                                                                                          |    " << endl;
	cout << " | 4. You can input double as operand, without '.' or with                                  |    " << endl;
	cout << " |      - If you want double with '.' input numbers before and after '.'                    |    " << endl;
	cout << " |      Example what you can: ( 1 ),( 1826 ),( 1.0 ),( 123.53 )                             |    " << endl;
	cout << " |      Example what you can't : ( . ),( 1. ),( .32 )                                       |    " << endl;
	cout << " |                                                                                          |    " << endl;
	cout << " | 5. You can input variables as almost any english letter ( a - z )                        |    " << endl;
	cout << " |      - Unlike a double, you can input in variables whatever you want !                   |    " << endl;
	cout << " |      Example: ( -1 ),( 1.2 ),( 1. ),( .3 ),(-.2)  exception:( . )                        |    " << endl;
	cout << " |                                                                                          |    " << endl;
	cout << " | 6. You can put spaces anywhere and anytime                                               |    " << endl;
	cout << " |      Example (it will work) :  ( 1    .  2 +          12  -   -  x )                     |    " << endl;
	cout << " |                                                                                          |    " << endl;
	cout << " | 7. If you input two or more operands in a row they will multiply                         |    " << endl;
	cout << " |      Example: 1x2.3axs2   ->   1*x*2.3*a*x*s*2                                           |    " << endl;
	cout << " |                                                                                          |    " << endl;
	cout << " | 8. If you input operand before '(' or after ')' there will be operation '*' between them |    " << endl;
	cout << " |      Example: 2(1)2   ->   2*(1)*2                                                       |    " << endl;
	cout << " |__________________________________________________________________________________________|    " << endl;




		string infix;

		cout <<endl<<endl<<endl<< "Input :  ";
		getline(cin, infix);
		cout << endl << endl << "Your input without spaces :  ";
		infix = without_spaces(infix);
		cout << infix;
		try
		{
			cout << endl << endl;
			bool alternative;
			alternative = choice();
			int move_choice;
			
			TPostfix MainPart(infix, alternative,0);


			cout << endl << endl << endl << " Do you want to see more information about your infix form ?"<< endl << endl <<" (1) YES"<<endl<<" (else) NO" << endl << endl << " Answer: ";
			cin >> move_choice;
			cout << endl;


			if (move_choice == 1)
			{
				MainPart.checked_infix(alternative);
			}
			cout << endl;


			MainPart.to_postfix_form(alternative,0);
			cout << endl << endl << endl;
			double resultat= MainPart.calculation(0);
			cout << endl << endl;
			cout <<"__________________________________________"<< endl;
			cout <<"                                          " << endl;
			cout << "     Resultat : " << resultat << endl;
			cout <<"__________________________________________" << endl;
			cout << endl << endl << endl;


			cout << endl << endl << endl << " Do you want to see full information about postfix form ? " << endl << endl <<" (1) YES"<<endl<<" (else) NO"<<endl<<endl<< " Answer: ";
			cin >> move_choice;
			cout << endl;
			if (move_choice == 1)
			{
				MainPart.get_full_information(alternative);
			}
		
		}
		catch (const exception& e)
		{
			cout << e.what()<<endl;
		}


  return 0;
}
