// ���������� � ���������� ���������� �����
// ���� ������������ ��������: 
// - ������� ��������, 
// - ���������� ��������, 
// - �������� �������� �������� (��� ��������)
// - �������� �� �������, 
// - ��������� ���������� ��������� � �����
// - ������� �����
// ��� ������� � ������ ���� ������ �������������� ������

#pragma once

template<class T>
class Stack
{
private:
	int index = -1;
	size_t realSize;
	T* data;
public:
	Stack()
	{
		realSize = 5;
		data = new T[realSize];
	}

	Stack(const Stack& temp) // ����������� �����������
	{
		this->index = temp.index;
		this->realSize = temp.realSize;
		this->data = new T[this->realSize];

		for (int i = 0; i < this->realSize; i++)
			this->data[i] = temp.data[i];
	}

	void push(T temp) // ������� ��������
	{
		if ((index + 1) == realSize) //��� ������� � ������ ���� ������ �������������� ������
		{
			size_t tempSize = this->realSize;
			T* temp = new T[tempSize];
			for (size_t i = 0; i < tempSize; i++)
				temp[i] = this->data[i];

			delete[] this->data;

			realSize *= 2;
			this->data = new T[realSize];
			for (int i = 0; i < tempSize; i++)
				data[i] = temp[i];

			delete[] temp;
		}

		data[++index] = temp;
	}

	~Stack() //������� �����
	{
		delete[] data;
	}

	bool isEmpty() // �������� �� �������
	{
		return index == -1;
	}


	T pop() // ���������� ��������
	{
		if (!isEmpty())
			return data[index--];
		throw std::out_of_range("Empty stack");
	}

	T top() // �������� �������� ��������
	{
		if (!isEmpty())
			return data[index];
		throw std::out_of_range("Empty stack");
	}

	int size() // ��������� ���������� ��������� � �����
	{
		return index + 1;
	}

	void clear() 
	{
		index = -1;
	}

};