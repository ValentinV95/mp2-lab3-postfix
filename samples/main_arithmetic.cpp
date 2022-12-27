// реализация пользовательского приложения
#include <stdio.h>
#include <iostream>
#include "arithmetic.h"

int main()
{
	char choise = 'N';
	string eq = "";

	TPostfix postfix("1");
	TPostfix::ShowInfo();
	while (eq != ";")
	{
		try
		{
			if (eq != "")
			{
				cout << "Repeat the calculation of this expression? Y/N: ";
				cin >> choise;
			}

			if (choise == 'Y' || choise == 'y')
			{
				cout << "Result: " << postfix.Calculate() << "\n" << "\n";
			}
			else if (choise == 'N' || choise == 'n' || eq == "")
			{
				cout << "For end enter ;\n";
				cout << "Enter the expression: ";
				cin >> eq;
				if (eq != ";")
				{
					postfix.SetInfix(eq);
					cout << "Result: " << postfix.Calculate() << "\n" << "\n";
				}
			}
			else
			{
				throw exception("Uncnown choise");
			}
		}
		catch (TPostfixException& exc)
		{
			std::cout << "\n" << exc.what()<<"\n";
		}
		catch (exception& exc)
		{
			std::cout << "\n" << exc.what() << "\n";
		}
	}
}
