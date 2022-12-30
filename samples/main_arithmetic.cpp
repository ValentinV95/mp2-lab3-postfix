// реализация пользовательского приложения
#include "arithmetic.h"
using namespace std;
#include "stack.h"

int main()
{
	string expr;
	cin >> expr;
	try {
		Arithmetic_expression exp(expr);
		exp.Checking_Correct();	
		exp.show();
		exp.show_postfix();
		exp.Input();
		double res = exp.Calculate();
		cout << res;	
	}
	catch (const std::exception& ex) {
		cout << ex.what() << endl;
	}
	
}
