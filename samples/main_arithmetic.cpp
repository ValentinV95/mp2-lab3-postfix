//Объявление начальных библиотек
#include "arithmetic.h"















// Реализация пользовательского приложения
//Правила ввода арифмитического выражения
int main()
{
	cout << "Rule for entering your arithmetic expression: " << endl;
	cout << "|Possible operations  +, -, *, / . You can use parentheses for simplicity. When entering the entered numbers used points instead of a comma(0.0, 1.0, 4.2)|" << endl;
	cout << "|Please , enter your arithmetic expression (no spaces). Use latin to enter your users|" << endl;
	cout << "|Possible operations  +, -, *, / . You can use parentheses for simplicity. When entering the entered numbers used points instead of a comma|" << endl;

	string infix;
	TPostfix expression;


	//Ввод арифмитического выражанеия
	while (1)
	{
		for (size_t i = 0; i < 116; i++)
			cout << "_";
		cout << endl;
		cout << "|Please , enter your arithmetic expression (no spaces)|: ";
		cin >> infix;

		try
		{
      expression.toPostfix();
			cout << "Postfix form: " << expression.getPostfix() << endl;
			expression.setTPostfix(infix);
			cout << "Infix form: " << expression.getInfix() << endl;
			
			expression.toCalculate();
			cout << setprecision(10) << "Output result: " << expression.getResult() << endl;
		}
		catch (const char* msg)
		{
			expression.getError();
			cout << msg << endl;
		}
	}
}
