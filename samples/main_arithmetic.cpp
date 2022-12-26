#include<Arithmetic.h>
#include<string>
#include<iostream>
int main()//Пользовательское приложение
{
	std::string str;
	std::cout << "Input Infix form"<<'\n';
	std::cin >> str;
	std::cout <<"This is your infix form" <<'\n'<< str;
	try
	{
		Arithmetic ar(str);
		double res = ar.Calculate();
		std::cout <<"\n\n"<<"This is your answer"<<'\n' << res;
	}
	catch (const std::string& error)
	{
		std::cout << error;
	}


}
