// реализация функций и классов для вычисления арифметических выражений
#include "arithmetic.h"

Operation::Operation(char opn)
{
	lex = opn;
	switch (opn)
	{
	case ')':
	case '(':
		priority = 0;
		break;
	case '+':
	case '-':
		priority = 1;
		break;
	case '*':
	case '/':
		priority = 2;
		break;
	case '~':
		priority = 3;                      
		break;                             
	}
};

char Operation::show()
{
	return lex;
};

size_t Operation::getPrior()
{
	return priority;
};

bool Operation::isOperation()
{
	return true;
};

Operation::Operation(const Operation& op)
{
	this->lex = op.lex;
	this->priority = op.priority;
};

Operand::Operand()
{
};

Operand::Operand(char opd)
{
	lex = opd;
};

bool Operand::isOperation()
{
	return false;
}
char Operand::show()
{
	return 0;
};

Variable::Variable(char var)
{
	lex = var;
};

char Variable::show()
{
	return lex;
};


bool Variable::isVar()
{
	return true;
};

Const::Const(char num)                      
{
	lex = num;
	value = num - '0';
};

char Const::show()
{
	return lex;
}
 
bool Const::isVar()
{
	return false;
};

double Const::getValue()
{
	return value;
};

Arithmetic::Arithmetic(string expr) : expression(expr)
{
	this->parse();
};

void Arithmetic::parse()
{
	if (expression[0] == '+' || expression[0] == '*' || expression[0] == '/' || expression[0] == ')')
		throw exception("Wrong expression");
	int count_brackets = 0;
	for (size_t i = 0; i < expression.size(); i++)
	{
		if (expression[i] >= '0' && expression[i] <= '9')
		{
			infix.push_back(new Const(expression[i]));
		}
		switch (expression[i])
		{
		case 'a':
		case 'b':
		case 'c':
		case 'd':
			infix.push_back(new Variable(expression[i]));
			break;
		case '+':
		case '*':
		case '/':
			infix.push_back(new Operation(expression[i]));
			break;
		case '(':
			infix.push_back(new Operation(expression[i]));
			count_brackets++;
			break;
		case ')':
			if (infix[i - 1]->isOperation() && (infix[i - 1]->show() != ')'))
				throw exception("Wrong expression");
			infix.push_back(new Operation(expression[i]));
			count_brackets--;
			break;
		case '-':
			if (i == 0 || (infix[i - 1]->isOperation() && infix[i - 1]->show() != ')'))   
				infix.push_back(new Operation('~'));
			else
			{
				infix.push_back(new Operation('-'));
			}
			break;
		}
		if (count_brackets < 0)
			throw exception("Wrong expression");
	}
	if (count_brackets!=0)
		throw exception("Wrong expression");
};

void Arithmetic::toPostfix()
{
	Stack<Operation*> stack;                                   
	for (size_t i = 0; i < infix.size(); i++)
	{
		if (infix[i]->isOperation())
		{
			if (infix[i]->show() == ')')
			{
				while (stack.checkTop()->show() != '(')
					postfix.push_back(stack.pop());
				stack.pop();
			}
			if (infix[i]->show() == '(')
			{
				Operation* op = (Operation*)infix[i];               
				stack.push(op);
			}
			if (infix[i]->show() != '(' && infix[i]->show() != ')')
			{
				Operation* op = (Operation*)infix[i];
				while (!stack.isEmpty() && (stack.checkTop()->getPrior() >= op->getPrior()))            // если просто > то не корректно a - b - c
					postfix.push_back(stack.pop());
				stack.push(op);
			}
		}
		else
			postfix.push_back(infix[i]);
	}
	while (!stack.isEmpty())
		postfix.push_back(stack.pop());
}

void Arithmetic::setVarValues()
{
	double val = 0.0;
	for (size_t i = 0; i < infix.size(); i++)
	{	
		if (val_map.count(infix[i]->show()) == 0)
		{
			Operand* op = (Operand*)infix[i];
			if (!infix[i]->isOperation() && op->isVar())
			{
				cout << infix[i]->show() << " = ";
				cin >> val;
			}
			val_map[infix[i]->show()] = val;
		}
	}
};

double Arithmetic::calculate()
{
	this->setVarValues();
	Stack<double> stack;

	for (size_t i = 0; i < postfix.size(); i++)                      
	{
		Operand* op = (Operand*)postfix[i];
		Const* c = (Const*)postfix[i];
		double tmp;
		double right;
		double left;
		if (!postfix[i]->isOperation())
			if (op->isVar())
				stack.push(val_map[postfix[i]->show()]);
			else
				stack.push(c->getValue());
		else
			switch (postfix[i]->show())
			{                                                                 
			case '~':
				tmp = -stack.pop();
				stack.push(tmp);
				break;
			case '+':
				right = stack.pop();
				left = stack.pop();
				stack.push(left + right);
				break;
			case '-':
				right = stack.pop();
				left = stack.pop();
				stack.push(left - right);
				break;
			case '*':
				right = stack.pop();
				left = stack.pop();
				stack.push(left * right);
				break;
			case '/':
				right = stack.pop();
				left = stack.pop();
				stack.push(left / right);
				break;
			}
	}

	return stack.checkTop();
};

void Arithmetic::showPostfix()
{
	for (size_t i = 0; i < postfix.size(); i++)
		cout <<postfix[i]->show();
	cout << endl;
};

string Arithmetic::get_origin_expression()
{
	return expression;
};

string Arithmetic::getPostfix()
{
	string tmp;
	for (size_t i = 0; i < postfix.size(); i++)
	{
		tmp.push_back(postfix[i]->show());
	}
	return tmp;
};

void Arithmetic::setVarValues_for_test(double a, double b, double c, double d)
{
	val_map['a'] = a;
	val_map['b'] = b;
	val_map['c'] = c;
	val_map['d'] = d;
};