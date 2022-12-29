#pragma once

#include "stack.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;



class TPostfix {

private:
	string infix, postfix;
	string operations, operands;

	int size, sizesol;

	vector<char> lexems;
	map<string, int> priority;

	string* SetOfLexems;

	void Get_Using_Operands();
	
	bool isDigit(const char& a);

	bool isOperand(const char& a);

	bool isOperation(const char& a);
	


public:

	TPostfix(string& _str);

	~TPostfix();

	string GetOperands();

	string GetInfix();

	string GetPostfix();

	void Parser();

	void ToPostfix();

	double toNumber(string str);

	double Calculate(map<char, double>& values);

	void CheckInfix();

};