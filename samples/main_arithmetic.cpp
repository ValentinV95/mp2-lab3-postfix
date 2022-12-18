// реализация пользовательского приложения
#include "arithmetic.h"
#include <locale>
#include<string>
#include <iomanip>

int main()
{
	cout << "Main rules: " << endl;
	cout << "1) Input your expression without spaces" << endl;
	cout << "2) Allowed operation: +, -, *, /, unary minus. Also you can use parentheses" << endl;
	cout << "3) Floating point number must be with dot (For example: 2.2, 453.3)" << endl;
	cout << "4) Number must be in math form (For example: can't 5. or .5 only 5.0 or 0.5)" << endl;;
	cout <<	"5) Variables must be latin lowercase letter(For example : a, b, ..., z)" << endl;
	cout << "6) Exponentional notation with E (without +) (For example: 2.E5, 2.E-5)" << endl;
	cout << "7) New operation will be added in future" << endl;

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
			std::cout << "<- " << msg << std::endl;
		}
	}
}
