#include <iomanip>
#include "arithmetic.h"
#include <locale.h>

using std::cout;
using std::endl;

int main()
{
	setlocale(LC_ALL, "Russian");
	cout << "The program supports:" << endl;
	cout << "- Unary minus and binary operations like '*','+', '/', '-'" << endl;
	cout << "- Brackets" << endl;
	cout << "- Integer and constants" << endl;
	cout << "- Variable names of any length using only lowercase Latin characters, excluding 'e'" << endl;
	cout << "- Separation by dot" << endl;
	cout << "- Exponential form" << endl;
	

	string term;
	cout << endl << "Enter an expression (no spaces): ";
	std::getline(std::cin, term);
	try
	{
		Arithmetic expression(term);
		cout << endl << "Postfix form: " << expression.GetPostfix() << endl;
		cout << endl << "Expression value: " << expression.Calculate() << endl;
	}
	catch (const string message)
	{
		cout << endl << message << endl;
	}

	return 0;
}