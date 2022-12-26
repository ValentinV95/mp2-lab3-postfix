// объ€вление функций и классов дл€ вычислени€ арифметических выражений
#ifndef __ARITHMETIC_H__
#define __ARITHMETIC_H__
#include <string>
#include "stack.h"

using namespace std;

class TPostfix
{
    string infix;
    string postfix;
public:
    TPostfix(string Value) 
    { 
        infix = Value;
    }
    TPostfix() 
    { 
        infix = "a + b";
    }
    int Priority(char val);
    size_t checkStringIsANumber(string inString);
    char getEndOfString();
    string GetInfix() 
    { 
        return infix;
    }
    string GetPostfix() 
    { 
        return postfix; 
    }
    string ToPostfix();
    double Calculate();
};

#endif