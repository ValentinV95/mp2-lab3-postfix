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


	const auto variables = data.get_variable_names();
	if (!variables.empty())
	{
		cout << "Input variables values:" << endl;
		for (const auto& variable : variables)
		{
			cout << variable << ": ";
			double value;
			cin >> value;
			data.set_variable(variable, value);
		}
	}

	try
	{
		cout << "answer: " << data.calculate() << endl;
		cout << "Postfix form: " << data.show_postfix() << endl;
	}
	catch (const exception& e)
	{
		cout << "Invalid expression:\n" << e.what() << endl;
	}
	


}

//for (auto i = m_variables.begin(); i != m_variables.end(); ++i) {
//	cout << "Input " << i->first << " value: " << std::endl;
//	std::cin >> varTemp;
//	m_variables[i->first] = varTemp;
//}