
//Объявление билиотек
#include<Arithmetic.h>
#include<string>
#include<iostream>



//Menu rule:
//1)Allowed operation: +, -, *, /,
//2)Input your expression without spaces
//3)Variables must be latin
//4)You can use parentheses
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
