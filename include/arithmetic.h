// объявление функций и классов для вычисления арифметических выражений

#ifndef _ARIFMETIC_H_
#define _ARIFMETIC_H_

#include <iostream>
#include <stdexcept>
#include "string"
#include "stack.h"
#include "map"

class Postfix 
{
protected:
	int operationPriority(char);
	void checkBrackets(const std::string&)const;
	bool isDigit(const char&);
	int checkingLine(std::string&);
public:
	std::string ToPostfix(std::string);
	double calculate(const std::string&, std::map<char, double>&);
};

class myExcp : public std::exception
{
private:
	std::string error;
public:
	myExcp(std::string s)
	{ 
		error = s; 
	}
	const char* what() const noexcept
	{
		return error.c_str();
	}
};

#endif
