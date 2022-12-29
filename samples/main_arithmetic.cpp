#include "arithmetic.h"

int main()
{
	cout << "Welcome welcome to the expression calculator" << "\n" << endl;
	cout << "Input your expression without spaces, please" << endl;
	cout << "Available operands: x, y, z" << endl;
	cout << "Available operations: +, -(binary), *, /, -(unary) " << endl;
	cout << "Also, you can use exponential number notation with letter 'e'" << endl;
	cout << "Floating number should be separated with point" << "\n" << endl;


	string infix;
	cout << "Input your expression:" << endl;
	cin >> infix;

	map<char, double> values;
	double val;

	

    try {
		TPostfix str(infix);

		for (char c : str.GetOperands()) {
		cout << "Input value of operand " << c << ":";
		cin >> val;
		values[c] = val;
		}

		cout << str.Calculate(values);
	}
	catch (const string error){
		cout << "Wrong expression:" << endl << error << endl;
	}
}
