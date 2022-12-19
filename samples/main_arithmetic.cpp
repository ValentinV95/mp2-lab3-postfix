// реализация пользовательского приложения

#include "arithmetic.h"

int main()
{
	string exprStr;
	cout << "Enter expression : ";
	cin >> exprStr;
	ArithmeticExpression expr(exprStr);
	cout << expr.GetInfix() << endl;
	cout << expr.GetPostfix() << endl;
	vector<Lexema> operands = expr.GetOperands();
	map<Lexema, double> values;
	double val;
	for (const auto& op : operands)
	{
		cout << "Enter value of " << op.lexema << ": ";
		cin >> val;
		values[op] = val;
	}
	cout << expr.Calculate(values) << endl;
}