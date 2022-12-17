// реализация пользовательского приложения
#include <iomanip>
#include "arithmetic.h"

using std::cout;
using std::endl;

int main()
{
	cout << "The program supports:" << endl;
	cout << "- Unary ('-') and binary ('+', '-', '*', '/') operations" << endl;
	cout << "- Brackets" << endl;
	cout << "- Integer and real constants" << endl;
	cout << "- Decimal separator only as a point: '.'" << endl;
	cout << "- Exponential form of any signed ('-' or '+') or unsigned numbers" << endl;
	cout << "- Variable names of any length using only lowercase Latin characters, excluding 'e'" << endl;
	cout << "- Prohibition of spaces" << endl;

	string source;
	cout << endl << "Infix form: ";
	std::getline(std::cin, source);  // space-controlled input
	try
	{
		TArithmetic expression(source);
		cout << endl << "Postfix form: " << expression.GetPostfix() << endl;
		cout << endl << "Expression value: " << expression.Calculate() << endl;
	}
	catch (const string message)
	{
		cout << endl << message << endl;
	}

	return 0;
}
