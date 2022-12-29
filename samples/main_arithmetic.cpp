// реализация пользовательского приложения

#include "arithmetic.h"


int main()
{
	
	cout << "Basic rules of working with the application: " << endl;
	cout << "1) Enter the expression without spaces" << endl;
	cout << "2) Enter variables in Latin letters (For example: a, b, ..., z)" << endl;
	cout << "3) Available operations: +, -, *, /, unary minus" << endl;
	cout << "4) The floating point number must be separated by a dot" << endl;;
	cout << "5) Denote exponential numbers with the letter E (without +)" << endl;

	string infix;
	TPostfix expression;

	while (1)
	{
		for (size_t i = 0; i < 116; i++)
			cout << "_";
		cout << endl;
		cout << "Enter an arithmetic expression: ";
		cin >> infix;

		try
		{
			expression.setTPostfix(infix);
			cout << "Infix form: " << expression.getInfix() << endl;
			expression.toPostfix();
			cout << "Postfix form: " << expression.getPostfix() << endl;
			expression.toCalculate();
			cout << setprecision(10) << "Result: " << expression.getResult() << endl;
		}
		catch (const char* msg)
		{
			expression.getError();
			//cout << "<- " << msg << endl;
			cout << msg << endl;
		}
	}
}