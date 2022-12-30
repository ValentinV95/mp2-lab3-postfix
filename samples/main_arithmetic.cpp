// реализация пользовательского приложения

#include "../include/arithmetic.h"
#include <string.h>
using namespace std;



int main()
{
	cout << "Solve algebraic infix equations by postfix method" << endl << endl;

	cout << "1. Dont input  spaces." << endl;
	cout << "2. Available algebraic operations:'+','-','/','*', '(',')'" << endl;
	cout << "3. You can use variables: 'a'-'z'." << endl << endl;

	cout << "Input equation" << endl;
	string equation;
	cin >> equation;
	TPostfix data(equation);


	cout << "Input variables values:" << endl;
	for (const auto& variable : data.get_variable_names())
	{
		cout << variable << ": ";
		double value;
		cin >> value;
		data.set_variable(variable, value);
	}

	try
	{
		cout << "Postfix form: " << data.show_postfix() << endl;
		cout << "answer: " << data.calculate();
	}
	catch (const exception& e)
	{
		cout << "exception:" << e.what() << endl;
	}
	


}

//for (auto i = m_variables.begin(); i != m_variables.end(); ++i) {
//	cout << "Input " << i->first << " value: " << std::endl;
//	std::cin >> varTemp;
//	m_variables[i->first] = varTemp;
//}