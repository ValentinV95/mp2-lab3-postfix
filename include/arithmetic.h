// объявление функций и классов для вычисления арифметических выражений
#pragma once

#include <iostream>
#include <iomanip>
#include "stack.h"
#include <string>

using namespace std;

class TPostfix
{
private:
	size_t size;
	string infix, postfix;
	string* data;
	Stack<string> operations;
	Stack<double> numbers;
	double result;
	int errornumber;
	string errorstring;

public:

	TPostfix(); // Create empty class object

	TPostfix(string _infix); // Create string arithmetic expression

	~TPostfix(); // Destructor clears data memory

	void setTPostfix(string _infix); // Set some string

	void toLexem(); // Converting an expression into lexem array

	void stringCheck(string it); // Checking operand input correctness

	void toVariable(); // Enter variable

	size_t operation_priority(string operation); // Get operation priority in size_t

	void toPostfix(); // Converting infix form  into postfix one

	double toNumber(string number); // Converting string into double

	void toCalculate(); // Calculating

	string getPostfix(); // Get postfix form in string

	double getResult(); // Get result of calculating in double

	string getInfix(); // Get infix form in string

	string getLexem(int n); // Output lexem

	void getError(); // Output all symbols to symbol with error

};