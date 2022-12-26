//Объявление билиотек
#include<Arithmetic.h>
#include<string>
#include<iostream>



//Menu rule:

int main()
{
	std::string str;
	std::cout << "Enter an arithmetic expression"<<'\n';
	std::cin >> str;
	std::cout <<"Infix form:" <<'\n'<< str;
	try
	{
		Arithmetic ar(str);
		double res = ar.Calculate();
		std::cout <<"\n\n"<<"Result:"<<'\n' << res;
	}
	catch (const std::string& error)
	{
		std::cout << error;
	}


}
