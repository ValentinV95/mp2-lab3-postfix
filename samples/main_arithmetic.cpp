// реализация пользовательского приложения
#include "arithmetic.h"
using namespace std;
#include "stack.h"

int main()
{
	string expr;
	TStack <double> st;
	cin >> expr;
	Arithmetic_expression exp(expr);
	exp.show();
	exp.show_postfix();
	map<char, double> values;
	exp.Input();
	double res = exp.Calculate();
	cout << res;
	exp.Checking_Correct();
}
