// Объявление функций и классов для вычисления арифметических выражений


//Объявление начальных библиотек


using namespace std;
#pragma once
#include <iostream>
#include <iomanip>
#include "stack.h"
#include <string>




//Начало работы класса

class TPostfix
{
// Используваемые   класса для работы программы (Закрытые)
private:
	size_t size;
	string infix, postfix;
	string* data;
	Stack<string> operations;
	Stack<double> numbers;
	double result;
	int errornumber;
	string errorstring;



// Используваемые  класса для работы программы (Открытые)

public:

	TPostfix();

	TPostfix(string _infix); 

	~TPostfix(); 
	void setTPostfix(string _infix); 

	void toLexem();

	void stringCheck(string it); 

	void toVariable(); 

	size_t operation_priority(string operation); 

	void toPostfix(); 

	double toNumber(string number); 

	void toCalculate(); 

	string getPostfix(); 

	double getResult(); 

	string getInfix(); /

	string getLexem(int n); 

	void getError(); 

};
