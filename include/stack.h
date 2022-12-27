#pragma once
// объявление и реализация шаблонного стека

using namespace std;
template<typename T>
class Stack
{
	int data_size;
	int size=0;
	int top;

	T* data;
public:
	Stack(int size = 1)
	{
		if (!size || size < 0)
			throw exception("size may not be greater than  zero or equal to zero");

		this->data_size = size;
		top = -1;
		data = new T[data_size];
	}

	Stack(const Stack& other)
	{
		data_size = other.data_size;
		size = other.size;
		top = other.top;

		data = new T[data_size];
		copy(other.data, other.data + data_size, data);
	}

	void push(T item)
	{
		if (data_size == (top + 1))
		{
			T* tmp = data;
			data = new T[data_size * 2];

			for (int i = 0; i < data_size; i++)
				data[i] = tmp[i];

			data_size *= 2;
			delete[] tmp;
		}

		data[++top] = item;
		size++;
	}

	T pop()
	{
		if (!isEmpty())
			return data[top--];
		throw exception("stack is empty there is nothing to return");
	}

	T head() const
	{
		if (isEmpty())
			throw exception("stack is empty and have no haed element");

		return data[top];
	}

	bool isEmpty() const { return !(top + 1); }

	int getSize() const noexcept 
	{ 
		return size; 
	}

	void clear() { top = -1; size = 0; }

	~Stack() { delete[] data; }
};