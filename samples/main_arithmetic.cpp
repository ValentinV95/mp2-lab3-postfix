// реализация пользовательского приложения

#include "arithmetic.h"
#include <string.h>
using namespace std;



int main()
{
	string input = "Start";

	cout << "Solve algebraic infix equations by postfix method" << endl << endl;

	cout << "1. Dont input  spaces." << endl;
	cout << "2. Available algebraic operations:'+','-','/','*', '(',')'" << endl;
	cout << "4)You can input '-' any times, anythere without end of the string." << endl;
	cout << "5)You have operands:'a'-'z'." << endl;

	TPostfix data(input);
		cout << endl << "Input equation or if you want to stop input 'STOP': " << endl;
		cin >> input;
		data.setInfix(input);
		try
		{
			cout << "Postfix form: " << data.showPostfix() << endl << "answer: " << data.CALCULATE();
		}
		catch (const exception& e)
		{
			cout << "exception:" << e.what() << endl;
		}
	


}
