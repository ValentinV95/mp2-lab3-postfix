#include <iostream>
#include "arithmetic.h"

int main()
{	
	string infix;
	cout << "supported operations: +, -, *, /, (, )" << endl;
	cout << "Supports the introduction of variables and double" << endl;
	cout << "Enter infix form" << endl;
	cin >> infix;
	TPostfix f(infix);
}
