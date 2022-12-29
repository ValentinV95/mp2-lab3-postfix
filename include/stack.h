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
using namespace std;

template <typename T>
class Stack
{
private:
	size_t size;
	int top;
	T* elemArr;
public:
	Stack(int size = 4)
	{
		top = -1;
		if (size < 0)
			throw out_of_range("size should be greater or equal than zero");
		this->size = size;                       
		elemArr = new T[size];
	};

	~Stack()
	{
		delete[] elemArr;
	}

	// - �������� �� �������,
	bool isEmpty()
	{
		return top == -1;
	}

	//�������� �� ������������ (��� ������������� ������)
	bool isFull()
	{
		return top == size - 1;
	}

	// - ������� ��������, 
	void push(T elem)
	{
		if (isFull())
		{
			T* tmp = new T[size*2];
			std::copy(elemArr, elemArr + size, tmp);
			delete[] elemArr;
			size *= 2;
			elemArr = tmp;
		}
		elemArr[++top] = elem;
	}

	// - ���������� ��������,
	T pop()
	{
		if (isEmpty())
			throw out_of_range("you cant get element, stack is empty");         
		return elemArr[top--];
	}

	// - �������� �������� �������� (��� ��������)
	T checkTop()
	{
		if (isEmpty())
		{
			throw out_of_range("you cant get element, stack is empty");          
		}                                 
		return elemArr[top];
	}

	// - ��������� ���������� ��������� � �����
	int get_size()
	{
		return top + 1;
	}

	// - ������� �����
	void clear()
	{
		top = -1;
	}
};