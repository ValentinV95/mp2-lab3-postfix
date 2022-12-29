// реализация пользовательского приложения
#include "arithmetic.h"
#include "clocale"

int main()
{
	setlocale(LC_ALL, "Russian");
	string expression;
	double res;
	cout << "Arithmetic expression can contain variables \"a\" \"b\" \"c\" \"d\" " << endl;
	cout << "constants \"0\" \"1\" \"2\" \"3\" \"4\" \"5\" \"6\" \"7\" \"8\" \"9\" and " << endl;
	cout << "also operations \"+\" \"*\" \"/\" \"(\" \")\" \"-\" (unary and binary)." << endl;
	cout << "The expression must not contain spaces or other symbols than those mentioned above." << endl;
	cout << "For example (a+b)*-(b/c)" << endl;

	cin >> expression;
	Arithmetic expr(expression);
	expr.toPostfix();
	expr.showPostfix();

	cout << endl;
	cout << "enter values (any double)" << endl;
	res = expr.calculate();
    cout << expression << " = " << res << endl;
  return 0;
}
