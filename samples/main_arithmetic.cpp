// реализация пользовательского приложения

#include <iostream>
#include "arithmetic.h"

using namespace std;

int main()
{
	string str;
	cout << "Programm accept only numbers (0-9) , brackets ( and ), variables (a-z in lower case)" << endl;
	cout << "operations + - * / and point" << endl;
	//cout<< "if you want to multiply , use only "
	cout << " enter arithmetic expression: ";
	getline(cin ,str);
	cout << endl;
	TPostfix post(str);
	double res = post.Calculate();
	cout << post._GetPostfix();
	cout << endl << res;

	return 0;
}