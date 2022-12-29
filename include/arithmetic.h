// ���������� ������� � ������� ��� ���������� �������������� ���������

#pragma once

#include <iostream>
#include <iomanip>
#include "stack.h"
#include <string>

using namespace std;

class TPostfix
{
private:
	size_t size; //������ ������� ������
	string inf, postf; //��� � ����� ����� � ���� ������
	string* data; //������ ������ 
	Stack<string> operations; //��������� ����� �����
	Stack<double> numbers;
	double result;
	int numberror;
	string stringerror;

public:
	TPostfix(); // �������� ������� ������� ������

	TPostfix(string _infix); // �������� ����� ��������� � ������

	~TPostfix(); // ����������

	void toVariable(); // ���� ����������

	void setTPostfix(string _infix);

	void toLexem(); // ������������� ��������� � ������ ������

	void stringCheck(string it); // �������� ������������ ����� ��������

	void toPostfix(); // �������������� ��� ����� � �����

	string getPostfix();

	string getInfix();

	size_t operation_priority(string operation);

	double toNumber(string number); //������������� ������ � double

	double getResult(); //��������� ���������� � double

	void toCalculate(); //����������

	string getLexem(int n); // ����� �������

	void getError();
};