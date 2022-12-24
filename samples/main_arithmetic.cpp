#include "arithmetic.h"
#include <string.h>



int main()
{
	string s = "Start";

	cout << "Solve infix equations by postfix solve method." << endl << endl;

	cout << "1)Dont input spaces." << endl;
	cout << "2)You have operations:'+','-','/','*' and you can use brackets '(',')'." << endl;
	cout << "3)You can input '-' any times, anythere without end of the string." << endl;
	cout << "4)You have operands:'a'-'z'." << endl;
	cout << "5)Can multiplicate vars without '*'(Example: ab = a*b)." << endl;
	cout << "5)If you input not logical equation the programm will write exception(empty brackets isn`t logical)." << endl << endl;

	TPostfix arg(s);

	while (true)
	{
		cout << endl << "Input equation or if you want to stop input 'STOP': " << endl;
		cin >> s;
		if (s == "STOP") break;
		arg.set_infix(s);
		try
		{
			cout << endl << "Postfix form: " << arg.showP() << endl << "size of  lexems: " << arg.get_size() << endl << "answer: " << arg.CALCULATE() << endl << endl;
		}
		catch (exception& e)
		{
			cout << "exception:" << e.what() << endl;
		}
	}
	cout << "The programm stopped." << endl;
}
