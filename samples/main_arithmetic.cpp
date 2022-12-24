// реализация пользовательского приложения
#include"arithmetic.h"

int main()
{
	try
	{
		cout << "When entering an expression, constants, variables (from a to z), parentheses,"<<endl;
		cout << "as well as operations + , -, / , * and unary minus can be used" << endl;
		string exp;
		cout << "Enter an expression: " << exp << endl;
		getline(cin,exp);
		exp.erase(remove_if(exp.begin(), exp.end(), isspace), exp.end());
		Postfix arifm(exp);
		arifm.convertToPostfix();
		cout << "Result = " << arifm.getRes() << endl;
	}
	catch (exception& ex)
	{
		cout << ex.what() << endl;
	}
	return 0;
}
