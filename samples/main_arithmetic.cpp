// реализация пользовательского приложения

#include "arithmetic.h"

int main()
{
	//Lexem** mas = new Lexem * [3];
	//Value a(33.234);
	//Operation b('/');
	//Var c("x1");
	//mas[0] = &a;
	//mas[1] = &b;
	//mas[2] = &c;
	//cout << mas[0]->show();
	//cout << mas[1]->show();
	//cout << mas[2]->show();
	string s;
	std::cin >> s;
	TPostfix arg(s);
	arg.to_postfix();
	arg.showP();
	cout << std::endl << "size: " << arg.get_size() << std::endl << arg.CALCULATE();
}
