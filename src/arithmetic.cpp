// реализация функций и классов для вычисления арифметических выражений

#include "arithmetic.h"

int Postfix::operationPriority(char priority)
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

bool Postfix::isDigit(const char& s)
{
    return (s >= '0' && s <= '9') || s == '.';
}

int Postfix::checkingLine(std::string& s)
{
    if (s.length() == 0)
    {
        return true;
    }
    Postfix p;
    if (s.length() == 1)
    {
        if (p.operationPriority(s[0]))
        {
            return true;
        }
    }
    if (p.operationPriority(s[0]) > 1)
    {
        return true;
    }
    
    for (size_t i = 0, j = 1; j < s.length(); j++) 
    {
        if (s[j] == ' ')
        {
            continue;
        }
        if ((s[i] == '(') && ((s[j] == '+') || (s[j] == '*') || (s[j] == '/')))
        {
            return true;
        }
        if ((s[j] == ')') && ((s[i] == '-') || (s[i] == '+') || (s[i] == '*') || (s[i] == '/')))
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
        if ((s[i] == '*') && ((s[j] == '+') || (s[j] == '-') || (s[j] == '/') || (s[j] == ')') ||  (s[j] == '*')))
        {
            return true;
        }
        if ((s[i] == '/') && ((s[j] == '+') || (s[j] == '-') || (s[j] == '*') || (s[j] == '+') || (s[j] == '/') || (s[j] == ')')))
        {
            return true;
        }
        if ((s[i] == '+') && ((s[j] == '*') || (s[j] == '-') || (s[j] == '/') || (s[j] == '+') || (s[j] == ')')))
        {
            return true;
        }
        if ((s[i] == '-') && ((s[j] == '+') || (s[j] == '-') || (s[j] == '/') || (s[j] == '*') || (s[j] == ')')))
        {
            return true;
        }
        if ((s[j] == ')') && ((s[i] == '+') || (s[i] == '-') || (s[i] == '*') || (s[i] == '/')))
        {
            return true;
        }
        i++;
    }
    return false;
}

double conversion(std::string s)
{
    double result = 0.0;
    double pow = 0;
    for (int i = s.length() - 1; i >= 0; i--, pow += 1)
    {
        result += (s[i] - '0') * std::pow(10.0, pow);
    }
    return result;
}

double NumConversion(std::string strlex)
{
    if (strlex.size() == 0)
    {
        throw myExcp("Incorrect digit form");
    }

    if (strlex[0] == '+')
    {
        return NumConversion(strlex.substr(1, strlex.size()));
    }

    if (strlex[0] == '-')
    {
        return -1. * NumConversion(strlex.substr(1, strlex.size()));
    }

    if (std::count(strlex.begin(), strlex.end(), '.') > 1)
    {
        throw myExcp("Incorrect digit form");
    }

    int dot_ind = strlex.find('.');
    double digit = 0.0;
    std::string left_of_dot;
    std::string right_of_dot;

    if (dot_ind == std::string::npos)
    {
        digit = conversion(strlex);
    }
    else
    {
        left_of_dot = strlex.substr(0, dot_ind);
        right_of_dot = strlex.substr(dot_ind + 1, strlex.size());
        if (left_of_dot.size() == 0 && right_of_dot.size() == 0)
        {
            throw myExcp("Incorrect digit form");
        }
        int pow = -1 * right_of_dot.size();
        digit = conversion(left_of_dot) + std::pow(10, pow) * conversion(right_of_dot);
    }
    return digit;
}

std::string Postfix::ToPostfix(std::string infixString)
{
    if (!infixString.length()) 
    {
        throw myExcp("String is empty.");
    }
    
    if (infixString[0] == '-')
    {
        infixString[0] = '~';
    }
    for (size_t i = 1; i < infixString.size(); i++)
    {
        if ((infixString[i - 1] == '~' || infixString[i - 1] == '-' || infixString[i - 1] == '*' || infixString[i - 1] == '/' || infixString[i - 1] == '+' || infixString[i - 1] == '(') && infixString[i] == '-')
        {
            infixString[i] = '~';
        }
    }
    if (checkingLine(infixString))
    {
        throw myExcp("Incorrect line. Error in arranging operations.");
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
                    result.push(' ');
                    result.push(operationsStack.pop());
                }
            }
            result.push(' ');
            operationsStack.push(infixString[i]);
            continue;
        }
        if ((infixString[i] >= 'a') && (infixString[i] <= 'z'))
        {
            result.push(infixString[i]);
            continue;
        }
        if ((infixString[i] >= 48) && (infixString[i] <= 57) || infixString[i] == '.')
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
                result.push(' ');
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
        result.push(' ');
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
    size_t i = 0;
    while(i < postfixString.length())
    {
        tmp = postfixString[i];
        if (tmp == ' ')
        {
            i++;
            continue;
        }
        if ((tmp >= 'a') && (tmp <= 'z')) 
        {
            if (!values.count(tmp)) 
            {
                std::cout << "Enter the " << tmp << ": ";
                std::cin >> values[tmp];
            }
            result.push(values[tmp]);
            i++;
            continue;
        }
        if (isDigit(tmp))
        {
            size_t j = i;
            for (; j < postfixString.length() && isDigit(postfixString[j]); j++)
            { }
            std::string num = postfixString.substr(i, j - i);
            double num_d = NumConversion(num);
            result.push(num_d);
            i = j;
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
            rightOperand = result.pop();
            leftOperand = result.pop();
            if (rightOperand == 0)
            {
                throw myExcp("Division by zero.");
            }
            result.push(leftOperand / rightOperand);
            break;
        case '~':
            rightOperand = result.pop();
            result.push(-rightOperand);
            break;
        }
        i++;
    }
    if (!result.isEmpty())
    {
        throw myExcp("Incorrect line.");
    }
    double res = result.pop();
    return res;
}
