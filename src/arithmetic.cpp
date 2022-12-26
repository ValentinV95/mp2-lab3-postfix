// реализация функций и классов для вычисления арифметических выражений

#include "arithmetic.h"

int Postfix::isOperator(char priority)
{
    switch (priority)
    {
    case '(':
        return 1;
    case ')':
        return 1;
    case'+':
        return 2;
    case '-':
        return 2;
    case '*':
        return 3;
    case '/':
        return 3;
    case '~':
        return 4;
    }
    return false;
}
void Postfix::checkBrackets(const std::string& s)const
{
    int leftBrackets = 0;
    int rightBrackets = 0;
    for (int i = 0; i < s.length(); i++) 
    {
        if (s[i] == '(')
        {
            leftBrackets++;
        }
        if (s[i] == ')')
        {
            rightBrackets++;
        }
    }
    if (leftBrackets != rightBrackets)
    {
        throw myExcp("Incorrect line.");
    }
}

int Postfix::checkingLine(const std::string& s) const
{
    if (s.length() == 0)
    {
        return true;
    }
    Postfix p;
    if (s.length() == 1)
    {
        if (p.isOperator(s[0]))
        {
            return true;
        }
    }
    if (p.isOperator(s[0]) > 1)
    {
        return true;
    }
    for (size_t i = 0, j = 1; j < s.length(); j++) 
    {
        if (s[j] == ' ')
        {
            continue;
        }
        if ((s[i] == '(') && ((s[j] == '+') || (s[j] == '*') || (s[j] == '/') || (s[j] == '~') || (s[j] == '-')))
        {
            return true;
        }
        if ((s[j] == ')') && ((s[i] == '-') || (s[i] == '+') || (s[i] == '*') || (s[i] == '/') || (s[i] == '~')))
        {
            return true;
        }
        if ((s[i] == ')') && (s[j] == '('))
        {
            return true;
        }
        if ((s[i] == s[j]) && (s[i] == '('))
        {
            continue;
        }
        if ((s[i] == s[j]) && (s[i] == ')'))
        {
            continue;
        }
        if ((s[i] == '*') && ((s[j] == '+') || (s[j] == '-') || (s[j] == '/') ||  (s[j] == '+') || (s[j] == '~') || (s[j] == ')')))
        {
            return true;
        }
        if ((s[i] == '/') && ((s[j] == '+') || (s[j] == '-') || (s[j] == '*') || (s[j] == '+') || (s[j] == '~') || (s[j] == '/') || (s[j] == ')')))
        {
            return true;
        }
        if ((s[i] == '+') && ((s[j] == '*') || (s[j] == '-') || (s[j] == '/') || (s[j] == '~') || (s[j] == '+') || (s[j] == ')')))
        {
            return true;
        }
        if ((s[i] == '-') && ((s[j] == '+') || (s[j] == '-') || (s[j] == '/') || (s[j] == '~') || (s[j] == '+') || (s[j] == ')')))
        {
            return true;
        }
        if ((s[j] == ')') && ((s[i] == '+') || (s[i] == '-') || (s[i] == '*') || (s[i] == '/')))
        {
            return true;
        }
        if ((s[i] == '~') && ((s[j] == '+') || (s[j] == '-') || (s[j] == '/') || (s[j] == ')')))
        {
            return true;
        }
        i++;
    }
    return false;
}

std::string Postfix::ToPostfix(const std::string& infixString)const
{

    if (!infixString.length()) 
    {
        throw myExcp("String is empty.");
    }

    checkBrackets(infixString);

    std::map <char, int> operations;
    operations['~'] = 4; 
    operations['*'] = 3; 
    operations['/'] = 3;
    operations['+'] = 2; 
    operations['-'] = 2;
    operations['('] = 1;

    TStack<char> result;
    TStack<char> operationsStack;

    for (size_t i = 0; i < infixString.length(); i++) 
    {
        if (infixString[i] == ' ')
        {
            continue;
        }

        if (operations.count(infixString[i]))
        {
            if ((!operationsStack.isEmpty()) && (operations[infixString[i]] <= operations[operationsStack.peek()]) && (infixString[i] != '('))
            {
                while ((!operationsStack.isEmpty()) && (operations[infixString[i]] <= operations[operationsStack.peek()]))
                {
                    result.push(operationsStack.pop());
                }
            }
            operationsStack.push(infixString[i]);
            continue;
        }

        if ((infixString[i] >= 'a') && (infixString[i] <= 'z'))
        {
            result.push(infixString[i]);
            continue;
        }

        if (infixString[i] == ')')
        {
            char t = '0';
            while ((!operationsStack.isEmpty()) && (t != '(')) 
            {
                t = operationsStack.pop();
                result.push(t);
            }
            if (t == '(')
            {
                result.pop();
            }
            continue;
        }
        throw myExcp("Incorrect symbol.");
    }

    while (!operationsStack.isEmpty()) 
    {
        result.push(operationsStack.pop());
    }

    if (result.isEmpty())
    {
        throw myExcp("Line doesn't contain an expression.");
    }
    std::string resultString = "";

    while (!result.isEmpty())
    {
        operationsStack.push(result.pop());
    }
    while (!operationsStack.isEmpty()) 
    {
        resultString += operationsStack.pop();
    }
    return resultString;
}

double Postfix::calculate(const std::string& postfixString, std::map<char, double>& values)
{
    if (postfixString == "")
    {
        throw myExcp("String is empty.");
    }
    TStack<double> result;
    char tmp;
    double leftOperand;
    double rightOperand;

    for (size_t i = 0; i < postfixString.length(); i++) 
    {
        tmp = postfixString[i];

        if ((tmp >= 'a') && (tmp <= 'z')) 
        {
            if (!values.count(tmp)) 
            {
                std::cout << "Enter the " << tmp << ": ";
                std::cin >> values[tmp];
            }
            result.push(values[tmp]);
            continue;
        }

        if (result.isEmpty())
        {
            throw myExcp("Error.");
        }

        switch (tmp) 
        {
        case '+':
            rightOperand = result.pop();
            leftOperand = result.pop();
            result.push(leftOperand + rightOperand);
            break;
        case '-':
            rightOperand = result.pop();
            leftOperand = result.pop();
            result.push(leftOperand - rightOperand);
            break;
        case '*':
            rightOperand = result.pop();
            leftOperand = result.pop();
            result.push(leftOperand * rightOperand);
            break;
        case '/':
            if (rightOperand == 0)
            {
                throw myExcp("Division by zero.");
            }
            rightOperand = result.pop();
            leftOperand = result.pop();
            result.push(leftOperand / rightOperand);
            break;
        case '~':
            rightOperand = result.pop();
            result.push(-rightOperand);
            break;
        }
    }

    double res = result.pop();
    if (!result.isEmpty())
    {
        throw myExcp("Incorrect line.");
    }
    return res;
}
