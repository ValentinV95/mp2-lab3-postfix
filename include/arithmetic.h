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
	size_t size; //размер массива лексем
	string inf, postf; //инф и постф формы в виде строки
	string* data; //массив лексем 
	Stack<string> operations; //обработка постф формы
	Stack<double> numbers;
	double result;
	int numberror;
	string stringerror;

public:
	TPostfix(); // Создание пустого объекта класса

	TPostfix(string _infix); // Создание арифм выражения в строку

	~TPostfix(); // Деструктор

	void toVariable(); // Ввод переменной

	void setTPostfix(string _infix);

	void toLexem(); // Преобразовать выражение в массив лексем

	void stringCheck(string it); // Проверка правильности ввода операнда

	void toPostfix(); // Преобразование инф формы в постф

	string getPostfix();

	string getInfix();

	size_t operation_priority(string operation);

	double toNumber(string number); //Преобразовать строку в double

	double getResult(); //Результат вычисления в double

	void toCalculate(); //Вычисление

	string getLexem(int n); // Вывод лексемы

	void getError();
};