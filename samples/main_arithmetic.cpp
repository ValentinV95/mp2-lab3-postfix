// реализация пользовательского приложения

#include <iostream>
#include "../include/arithmetic.h"
#include <locale.h>

int main()
{
	setlocale(LC_ALL, "Russian");
	std::cout << "-----------------SOLVING EXPRESSIONS-----------------\n" << "RULES:" << std::endl;
	std::cout << "1)DON'T use space\n2)Arithmetic operation: *,/,+,-\n3)Variables should be named with one letter" << std::endl;
	std::cout << "Enter your expressions:  ";
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
