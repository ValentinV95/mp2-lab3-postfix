#include "arithmetic.h"
#include <string.h>



int main()
{
	string s = "Start";

	cout << "Solve infix equations by postfix solve method." << endl << endl;

	cout << "1)Dont input one equation with spaces." << endl;
	cout << "2)If you want to solve more then one equation by one string, input equations with splitting them by space." << endl;
	cout << "3)You have operations:'+','-','/','*' and you can use brackets '(',')'." << endl;
	cout << "4)You can input '-' any times, anythere without end of the string." << endl;
	cout << "5)You have operands:'a'-'z'." << endl;
	cout << "6)Can multiplicate vars without '*'(Example: ab = a*b)." << endl;
	cout << "7)If we think that '1.' it`s '1.0' and '.1' it`s '0.1' then my programm can think that '.' it`s '0.0'" << endl;
	cout << "8)If you input not logical equation the programm will write exception(empty brackets isn`t logical)." << endl << endl;

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
		catch (const exception& e)
		{
			cout << "exception:" << e.what() << endl;
		}
	}
	cout << "The programm stopped." << endl;
}
