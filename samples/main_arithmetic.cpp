//Объявление билиотек
#include<Arithmetic.h>
#include<string>
#include<iostream>
#include <math.h>
#include <locale>
#include <map>
#include <ostream>



//Меню пользователья
int main()//Пользовательское приложение
{
	std::string str;
	std::cout << "Send Infix form"<<'\n';
	std::cin >> str;
	std::cout <<"Infix form" <<'\n'<< str;
	try
	{
		Arithmetic ar(str);
		double res = ar.Calculate();
		std::cout <<"\n\n"<<"Result:"<<'\n' << res;
	}
	catch (const std::string& error)
	{
		std::cout << Wrong record of an arithmetic expression or something else;
	}


}
