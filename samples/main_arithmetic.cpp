#include "../src/arithmetic.cpp"// реализация пользовательского приложения

int main()
{
	std::setlocale(LC_ALL,"Russian");
	std::cout << "The program supports next operation:" <<
		std::endl << "Basic arithmetic operation:" <<
		std::endl << "add(+),sub(-),mult(*),div(/),square root(sqrt),exp(^),logarithm(log)" <<
		std::endl <<
		std::endl << "Trigonomethric function:" <<
		std::endl << "sin,cos" << std::endl << std::endl;
	std::cout << "Enter an expression:" << std::endl;
	string s;
	getline(std::cin, s);
	try {
		TPostfix a(s);
		std::cout <<"Result ="<< a;
	}
	catch (MyException e)
	{
		std::cout << e.what();
	}
  return 0;
}
