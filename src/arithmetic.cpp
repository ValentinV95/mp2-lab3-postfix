// реализация функций и классов для вычисления арифметических выражений

#include "arithmetic.h"

TPostfix::~TPostfix() 
{
	delete[] data;
}

TPostfix::TPostfix() : inf(""), size(0), postf(""), result(0.0), numberror(-1), stringerror(inf)
{
	data = new string[size]();
}

TPostfix::TPostfix(string _infix) : inf(_infix), size(_infix.size()), postf(""), result(0.0), numberror(-1), stringerror(inf)
{
	data = new string[size]();

	toLexem();
}

void TPostfix::toVariable() // Ввод переменной
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

void TPostfix::setTPostfix(string _infix)
{
	delete[] data;

	inf = _infix;
	size = _infix.size();
	postf = "";
	result = 0.0;
	numberror = -1;
	stringerror = inf;
	data = new string[size]();

	toLexem();
}

void TPostfix::toLexem() // обработка входной строки в массив лексем и вывод ошибок о неправильной постф записи
{
	int brackets = 0;
	size_t lexemnumber = 0;

	for (size_t i = 0; i < size; i++)
	{
		switch (inf[i]) {
		case '(':
		{
			if (i + 1 == size || i != 0 && (inf[i - 1] > '0' || inf[i - 1] == ')'))
			{
				numberror = i;
				throw "Opening bracket was installed in wrong position";
			}

			brackets++;
			data[lexemnumber++] = inf[i];
			break;
		}
		case ')':
		{
			if (i == 0 || (inf[i - 1] < '0' && inf[i - 1] != ')'))
			{
				numberror = i;
				throw "Closing bracket was installed in wrong position";
			}

			brackets--;
			data[lexemnumber++] = inf[i];
			break;
		}
		case '+': case '*': case '/':
		{
			if (i == 0 || (i + 1) == size || (inf[i - 1] < '0' && inf[i - 1] != ')'))
			{
				numberror = i;
				throw "Operation was installed in wrong position";
			}

			data[lexemnumber++] = inf[i];
			break;
		}
		case '-':
		{
			if ((i + 1) == size)
			{
				numberror = i;
				throw "Operation was installed in wrong position";
			}

			if (i == 0 || (inf[i - 1] < '0' && inf[i - 1] != ')')) data[lexemnumber++] = '~';

			else if (inf[i - 1] == 'E') data[lexemnumber] += '~';

			else data[lexemnumber++] = inf[i];

			break;
		}
		default:
		{
			if (i != 0 && inf[i - 1] == ')')
			{
				numberror = i - 1;
				throw "Closing bracket was installed in wrong position";
			}

			if (inf[i] >= 'a' && inf[i] <= 'z')
			{
				if (i != 0 && inf[i - 1] >= '0' || i + 1 != size && inf[i + 1] == '.')
				{
					numberror = i;
					throw "Variables should be written in Latin lowercase letters";
				}

				data[lexemnumber++] = inf[i];
			}

			else if (inf[i] >= '0' && inf[i] <= '9' || inf[i] == 'E')
			{
				if (inf[i] == 'E')
				{
					if ((i + 1) == size
						|| i == 0
						|| inf[i - 1] < '0' && inf[i - 1] != '.'
						|| inf[i + 1] < '0' && inf[i + 1] != '-')
					{
						if (i + 1 == size || i == 0 || inf[i - 1] < '0') numberror = i;
						else numberror = i + 1;

						throw "Wrong exponentional notation";
					}

					else data[lexemnumber] += inf[i];
				}

				else if (i != 0 && inf[i - 1] >= 'a' && inf[i - 1] <= 'z')
				{
					numberror = i;
					throw "You forgot operation";
				}

				else if (i + 1 == size || (inf[i + 1] < '0' && inf[i + 1] != '.')) data[lexemnumber++] += inf[i];

				else data[lexemnumber] += inf[i];
			}

			else if (inf[i] == '.')
			{
				if (i == 0
					|| inf[i - 1] < '0'
					|| inf[i - 1] > '9'
					|| (i + 1) == size
					|| inf[i + 1] < '0'
					|| inf[i + 1] > '9' && inf[i + 1] != 'E')
				{
					numberror = i;
					throw "Number must be in math form";
				}

				data[lexemnumber] += inf[i];
			}

			else
			{
				numberror = i;
				throw "Incorrect symbol";
			}

			break;
		}
		}
	}

	if (brackets != 0)
	{
		numberror = size;
		throw "Opening bracket and closing one must be equal number";
	}

	size = lexemnumber;
}

void TPostfix::stringCheck(string it) // Проверка введенного пользователем значения переменной
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
				stringerror = it;
				numberror = i;
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
					stringerror = it;
					numberror = i;
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
					stringerror = it;
					numberror = i;
					throw "Wrong math form";
				}
			}
		}

		else
		{
			stringerror = it;
			numberror = i;
			throw "Wrong symbol";
		}
	}
}

void TPostfix::toPostfix() // перевод в постф форму
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
		postf += postfixform[i];
	}

	delete[] postfixform;
}

string TPostfix::getPostfix() 
{
	return postf;
}

string TPostfix::getInfix() 
{
	return inf;
}

size_t TPostfix::operation_priority(string operation) 
{
	if (operation == "+" || operation == "-") return 1;
	if (operation == "*" || operation == "/") return 2;
	if (operation == "~") return 3;
	else return 0;
}

double TPostfix::toNumber(string number) // преобразовать строку в double
{
	double double_number = 0.0, sign = 1.0, e_double = 0.0;
	int flag = 0, k = 0, dot = 0;
	string e_num;

	for (int i = 0; i < number.size(); i++)
	{
		if (dot > 1)
		{
			stringerror = number;
			numberror = i - 1;
			throw "More than 1 dot";
		}

		if (number[i] == '-' || number[i] == '~')
		{
			if (i != 0)
			{
				stringerror = number;
				numberror = i;
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
					stringerror = number;
					numberror = j;
					throw "Exponentional notation can be only integer number and cann't have other symbol";
				}
			}

			e_double = toNumber(e_num);

			break;
		}

		if ((number[i] < '0') || (number[i] > '9'))
		{
			stringerror = number;
			numberror = i;
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

double TPostfix::getResult() // результат вычисления в double
{
	return result;
}

void TPostfix::toCalculate() // Вычисление
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
				stringerror = "";
				for (size_t j = 0; j < size; j++)
				{
					if (i == j) numberror = stringerror.size();
					stringerror += data[j];
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

string TPostfix::getLexem(int n) // вывод лексемы
{
	if (n < 0 || n >= this->size) throw out_of_range("Out of range");
	return data[n];
}

void TPostfix::getError() 
{
	cout << stringerror << endl;
	for (size_t i = 0; i < numberror; i++)
		cout << " ";
	cout << "^" << endl;
}
