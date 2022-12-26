// реализация пользовательского приложения

#include <iostream>
#include "arithmetic.h"

using namespace std;

int main()
{
	string str;
	cin >> str;
	TPostfix post(str);
	double res = post.Calculate();
	cout << post._GetPostfix();
	cout << endl << res;

	return 0;
}