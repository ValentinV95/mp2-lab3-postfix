// реализация функций и классов для вычисления арифметических выражений

#include "arithmetic.h"

TPostfix::TPostfix() : infix(""), size(0), postfix(""), result(0.0), errornumber(-1), errorstring(infix)
{
	data = new string[size]();
}

TPostfix::TPostfix(string _infix) : infix(_infix), size(_infix.size()), postfix(""), result(0.0), errornumber(-1), errorstring(infix)
{
	data = new string[size]();

	toLexem();
} // Create string arithmetic expression

TPostfix::~TPostfix() // Destructor clears data memory
{
	delete[] data;
}

void TPostfix::setTPostfix(string _infix) // Set some string
{
	delete[] data;

	infix = _infix;
	size = _infix.size();
	postfix = "";
	result = 0.0;
	errornumber = -1;
	errorstring = infix;
	data = new string[size]();

	toLexem();
}

void TPostfix::toLexem() // Converting an expression into lexem array
{
	int brackets = 0;
	size_t lexemnumber = 0;

	for (size_t i = 0; i < size; i++)
	{
		switch (infix[i]) {
		case '(':
		{
			if (i + 1 == size || i != 0 && (infix[i - 1] > '0' || infix[i - 1] == ')'))
			{
				errornumber = i;
				throw "Opening bracket was installed in wrong position";
			}

			brackets++;
			data[lexemnumber++] = infix[i];
			break;
		}
		case ')':
		{
			if (i == 0 || (infix[i - 1] < '0' && infix[i - 1] != ')'))
			{
				errornumber = i;
				throw "Closing bracket was installed in wrong position";
			}

			brackets--;
			data[lexemnumber++] = infix[i];
			break;
		}
		case '+': case '*': case '/':
		{
			if (i == 0 || (i + 1) == size || (infix[i - 1] < '0' && infix[i - 1] != ')'))
			{
				errornumber = i;
				throw "Operation was installed in wrong position";
			}

			data[lexemnumber++] = infix[i];
			break;
		}
		case '-':
		{
			if ((i + 1) == size)
			{
				errornumber = i;
				throw "Operation was installed in wrong position";
			}

			if (i == 0 || (infix[i - 1] < '0' && infix[i - 1] != ')')) data[lexemnumber++] = '~';

			else if (infix[i - 1] == 'E') data[lexemnumber] += '~';

			else data[lexemnumber++] = infix[i];

			break;
		}
		default:
		{
			if (i != 0 && infix[i - 1] == ')')
			{
				errornumber = i - 1;
				throw "Closing bracket was installed in wrong position";
			}

			if (infix[i] >= 'a' && infix[i] <= 'z')
			{
				if (i != 0 && infix[i - 1] >= '0' || i + 1 != size && infix[i + 1] == '.')
				{
					errornumber = i;
					throw "Variables must be latin lowercase letter";
				}

				data[lexemnumber++] = infix[i];
			}

			else if (infix[i] >= '0' && infix[i] <= '9' || infix[i] == 'E')
			{
				if (infix[i] == 'E')
				{
					if ((i + 1) == size
						|| i == 0
						|| infix[i - 1] < '0' && infix[i - 1] != '.'
						|| infix[i + 1] < '0' && infix[i + 1] != '-')
					{
						if (i + 1 == size || i == 0 || infix[i - 1] < '0') errornumber = i;
						else errornumber = i + 1;

						throw "Wrong exponentional notation";
					}

					else data[lexemnumber] += infix[i];
				}

				else if (i != 0 && infix[i - 1] >= 'a' && infix[i - 1] <= 'z')
				{
					errornumber = i;
					throw "You forgot operation";
				}

				else if (i + 1 == size || (infix[i + 1] < '0' && infix[i + 1] != '.')) data[lexemnumber++] += infix[i];

				else data[lexemnumber] += infix[i];
			}

			else if (infix[i] == '.')
			{
				if (i == 0
					|| infix[i - 1] < '0'
					|| infix[i - 1] > '9'
					|| (i + 1) == size
					|| infix[i + 1] < '0'
					|| infix[i + 1] > '9' && infix[i + 1] != 'E')
				{
					errornumber = i;
					throw "Number must be in math form";
				}

				data[lexemnumber] += infix[i];
			}

			else
			{
				errornumber = i;
				throw "Incorrect symbol";
			}

			break;
		}
		}
	}

	if (brackets != 0)
	{
		errornumber = size;
		throw "Opening bracket and closing one must be equal number";
	}

	size = lexemnumber;
}

void TPostfix::stringCheck(string it) // Checking operand input correctness
{
	size_t tsize = it.size();
	for (size_t i = 0; i < tsize; i++)
	{
		if (it[i] >= '0' && it[i] <= '9'
			|| it[i] == 'E'
			|| it[i] == '.'
			|| it[i] == '-')
		{
			if (it[i] == '-' && tsize == 1)
			{
				errorstring = it;
				errornumber = i;
				throw "it isn't number";
			}

			if (it[i] == 'E')
			{
				if (i == 0
					|| it[i - 1] < '0' && it[i - 1] != '.'
					|| it[i - 1] > '9'
					|| (i + 1) == size
					|| it[i + 1] < '0' && it[i + 1] != '-'
					|| it[i + 1] > '9')
				{
					errorstring = it;
					errornumber = i;
					throw "Wrong exponational notation";
				}
			}

			if (it[i] == '.')
			{
				if (i == 0
					|| it[i - 1] < '0'
					|| it[i - 1] > '9'
					|| (i + 1) == tsize
					|| it[i + 1] < '0'
					|| it[i + 1] > '9' && it[i + 1] != 'E')
				{
					errorstring = it;
					errornumber = i;
					throw "Wrong math form";
				}
			}
		}

		else
		{
			errorstring = it;
			errornumber = i;
			throw "Wrong symbol";
		}
	}
}

void TPostfix::toVariable() // Enter variable
{
	string operand, tmp;

	for (size_t i = 0; i < size; i++)
	{
		if (data[i] >= "a" && data[i] <= "z")
		{
			tmp = data[i];
			cout << endl << "Enter " << tmp << " operand: ";
			cin >> operand;

			stringCheck(operand);

			for (size_t j = i; j < size; j++)
				if (this->data[j] == tmp)
					this->data[j] = operand;
		}
	}
}

size_t TPostfix::operation_priority(string operation) // Get operation priority in size_t
{
	if (operation == "+" || operation == "-") return 1;
	if (operation == "*" || operation == "/") return 2;
	if (operation == "~") return 3;
	else return 0;
}

void TPostfix::toPostfix() // Converting infix form  into postfix one
{
	size_t postfixsize = 0;
	string* postfixform = new string[size];

	for (size_t i = 0; i < size; i++)
	{
		if (data[i] < "0" || data[i] == "~")
		{
			if (data[i] == "(") operations.push(data[i]);

			else if (data[i] == ")")
			{
				while ((operations.top() != "("))
					postfixform[postfixsize++] = operations.pop();

				operations.pop();
			}

			else
			{
				if (!operations.isEmpty()
					&& !(operations.top() == "~" && data[i] == "~")
					&& (operation_priority(operations.top()) >= operation_priority(data[i])))
				{
					while ((!operations.isEmpty())
						&& (operation_priority(operations.top()) >= operation_priority(data[i])))
						postfixform[postfixsize++] = operations.pop();
				}

				operations.push(data[i]);
			}
		}

		else postfixform[postfixsize++] = data[i];
	}

	while (!operations.isEmpty())
		postfixform[postfixsize++] = operations.pop();

	size = postfixsize;

	for (size_t i = 0; i < size; i++)
	{
		data[i] = postfixform[i];
		postfix += postfixform[i];
	}

	delete[] postfixform;
}

double TPostfix::toNumber(string number) // Converting string into double
{
	double double_number = 0.0, sign = 1.0, e_double = 0.0;
	int flag = 0, k = 0, dot = 0;
	string e_num;

	for (int i = 0; i < number.size(); i++)
	{
		if (dot > 1)
		{
			errorstring = number;
			errornumber = i - 1;
			throw "More than 1 dot";
		}

		if (number[i] == '-' || number[i] == '~')
		{
			if (i != 0)
			{
				errorstring = number;
				errornumber = i;
				throw "Minus can't stay in this place";
			}

			sign = -1.0;
			continue;
		}

		if (number[i] == '.')
		{
			flag = 1;
			dot++;
			continue;
		}

		if (number[i] == 'E')
		{
			for (int j = i + 1; j < number.size(); j++)
			{
				if ((number[j] >= '0' && number[j] <= '9') || number[j] == '~' || number[j] == '-')
					e_num += number[j];
				else
				{
					errorstring = number;
					errornumber = j;
					throw "Exponentional notation can be only integer number and cann't have other symbol";
				}
			}

			e_double = toNumber(e_num);

			break;
		}

		if ((number[i] < '0') || (number[i] > '9'))
		{
			errorstring = number;
			errornumber = i;
			throw "inccorect symbol";
		}

		if (flag) k++;

		double_number = double_number * 10.0 + static_cast<double>(number[i] - '0');
	}

	for (int i = 0; i < k; i++)
		double_number /= 10.0;

	if (sign < 0) double_number *= sign;

	double_number *= pow(10.0, e_double);
	return double_number;
}

void TPostfix::toCalculate() // Calculating
{
	toVariable();

	double temp;

	for (size_t i = 0; i < size; i++)
	{
		if (data[i] == "+")
		{
			temp = numbers.pop();
			temp += numbers.pop();
			numbers.push(temp);
		}

		else if (data[i] == "-")
		{
			temp = numbers.pop();
			temp = numbers.pop() - temp;
			numbers.push(temp);
		}

		else if (data[i] == "*")
		{
			temp = numbers.pop();
			temp *= numbers.pop();
			numbers.push(temp);
		}

		else if (data[i] == "/")
		{
			if (fabs(numbers.top()) < 1e-15)
			{
				errorstring = "";
				for (size_t j = 0; j < size; j++)
				{
					if (i == j) errornumber = errorstring.size();
					errorstring += data[j];
				}

				throw "Division by zero";
			}

			temp = numbers.pop();
			temp = numbers.pop() / temp;
			numbers.push(temp);
		}

		else if (data[i] == "~")
		{
			temp = numbers.pop();
			numbers.push(-temp);
		}

		else
		{
			numbers.push(toNumber(data[i]));
		}
	}

	result = numbers.pop();
}

string TPostfix::getPostfix() // Get postfix form in string
{
	return postfix;
}

double TPostfix::getResult() // Get result of calculating in double
{
	return result;
}

string TPostfix::getInfix() // Get infix form in string
{
	return infix;
}

string TPostfix::getLexem(int n) // Output lexem for test
{
	if (n < 0 || n >= this->size) throw out_of_range("Out of range");
	return data[n];
}

void TPostfix::getError() // Output all symbols to symbol with error
{
	cout << errorstring << endl;
	for (size_t i = 0; i < errornumber; i++)
		cout << " ";
	cout << "^" << endl;
}