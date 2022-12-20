// реализация пользовательского приложения

#include <iostream>
#include "../include/arithmetic.h"
#include <locale.h>

int main()
{
	setlocale(LC_ALL, "Russian");
	std::string Eq = "(a+b*c/d-e)*(f+g*h)";
	try
	{
		TPostfix Equation(Eq);
		Equation.infix_show();
		Equation.postfix_show();
		std::cout << Equation.resolve();
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
