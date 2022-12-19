#include"arithmetic.h"

int main()
{

	


		string infix;

		cout <<endl<< "Input :  ";
		getline(cin, infix);
		cout << endl << endl << "Your input without spaces :  ";
		infix = without_spaces(infix);
		

//------------------------------------------------------------------------



		

//------------------------------------------------------------------------


		cout << endl<<endl<<endl << "All operands in input";

		cout << endl;
		
		
		TPostfix<double> MainPart(infix);

		



		cout << endl << endl << endl;







/*                 [ Test zone 1 ]             For Ivan, Grigory and Anton

		Tstack<char> temp;

		temp.Push('1');
		temp.Push('2');
		temp.Push('3');
		temp.Push('4');
		temp.Push('.');
		temp.Push('5');
		temp.Push('6');

		Const tomp1(temp, temp, 1);
		Const tomp2(temp, temp, 1);
		Const tomp3(temp, temp, -1);
		Const tomp4(temp, temp, 1);
		Const tomp5(temp, temp, -1);

		LEXEM mas[5];

		mas[0] = tomp1;
		mas[1] = tomp2;
		mas[2] = tomp3;
		mas[3] = tomp4;
		mas[4] = tomp5;

		for (int i = 0; i < 5; i++)
		{
			cout << mas[i].show()<<endl;
		}

*/

















  return 0;
}
