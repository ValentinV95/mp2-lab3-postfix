// объявление и реализация шаблонного стека
// стек поддерживает операции: 
// - вставка элемента, 
// - извлечение элемента, 
// - просмотр верхнего элемента (без удаления)
// - проверка на пустоту, 
// - получение количества элементов в стеке
// - очистка стека
// при вставке в полный стек должна перевыделяться память
#pragma once

template<class T>
class Stack
{
private:
	int index = -1;
	size_t dataSize;
	T* data;
public:
	Stack()
	{
		dataSize = 5;
		data = new T[dataSize];
	}

	Stack(const Stack& temp) // Copy constructor
	{
		this->index = temp.index;
		this->dataSize = temp.dataSize;
		this->data = new T[this->dataSize];

		for (int i = 0; i < this->dataSize; i++)
			this->data[i] = temp.data[i];
	}

	~Stack()
	{
		delete[] data;
	}

	bool isEmpty() // Empty check
	{
		return index == -1;
	}

	void push(T temp) // Add element on stack top
	{
		if ((index + 1) == dataSize)
		{
			size_t tempSize = this->dataSize;
			T* temp = new T[tempSize];
			for (size_t i = 0; i < tempSize; i++)
				temp[i] = this->data[i];

			delete[] this->data;

			dataSize *= 2;
			this->data = new T[dataSize];
			for (int i = 0; i < tempSize; i++)
				data[i] = temp[i];

			delete[] temp;
		}

		data[++index] = temp;
	}

	T pop() // Get top element with delete one in stack
	{
		if (!isEmpty())
			return data[index--];
		throw std::out_of_range("Stack is empty");
	}

	T top() // Get top element without delete one in stack
	{
		if (!isEmpty())
			return data[index];
		throw std::out_of_range("Stack is empty");
	}

	int size() // Get number of elements
	{
		return index + 1;
	}

	void clear() //Delete all elements in stack without change his data size
	{
		index = -1;
	}

};