#include"arithmetic.h"

int main()
{


		string infix;

		cout <<endl<< "Input :  ";
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
			cout << endl << endl << "Resultat : " << resultat;
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
