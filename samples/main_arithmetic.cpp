// реализация пользовательского приложения

#include <iostream>
#include "../include/arithmetic.h"
#include <locale.h>

int main()
{
	setlocale(LC_ALL, "Russian");
	std::cout << "-----------------SOLVING EXPRESSIONS-----------------\n" << "enter your expressions:" << std::endl;
	std::string Eq;
	std::cin >> Eq;
	try
	{
		TPostfix Equation(Eq);
		Equation.infix_show();
		Equation.postfix_show();
		std::cout << "result:  " << Equation.resolve();
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what();
	}
	catch (const lexException& e)
	{
		std::cout << e.what();
	}
}
