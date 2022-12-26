// объявление функций и классов для вычисления арифметических выражений

#ifndef _ARIFMETIC_H_
#define _ARIFMETIC_H_

#include <iostream>
#include <stdexcept>
#include "string"
#include "stack.h"
#include "vector"
#include "map"

class Postfix 
{
protected:
	int isOperator(char);
	void checkBrackets(const std::string&)const;
	int checkingLine(const std::string&)const;
public:
	std::string ToPostfix(const std::string&)const;
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
