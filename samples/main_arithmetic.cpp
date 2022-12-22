#include "../src/arithmetic.cpp"// реализация пользовательского приложения

int main()
{
	TPostfix a("3+5*4+(-2)");
	std::cout << a;
  return 0;
}
