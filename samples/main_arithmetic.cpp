// реализация пользовательского приложения
#include <iostream>
#include <string>
#include "arithmetic.h"
#include <locale>
#include <conio.h>
#include<Windows.h>

using namespace std;

int main()
{
	string expression;
	double res;

	SetConsoleOutputCP(65001);
	cout << "Введите арифметическое выражение: ";
	cin >> expression;
	cout << expression << endl;
	TPostfix postfix(expression);
	cout << "Арифметическое выражение: " << postfix.GetInfix() << endl;
	postfix.ToPostfix();
	cout << "Постфиксная форма: " << postfix.GetPostfix() << endl;
	cout << "Результат выражения: " << postfix.Calculate() << endl;

	return 0;
}