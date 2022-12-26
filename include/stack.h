//Объявление начальных библиотек
#pragma once





//Начало работы класса
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

	Stack(const Stack& temp)
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

	bool isEmpty() 
	{
		return index == -1;
	}

	void push(T temp) 
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



	//Просмотр верхнего элемента
	T pop() 
	{
		if (!isEmpty())
			return data[index--];
		throw std::out_of_range("Stack is empty");
	}

	T top() 
	{
		if (!isEmpty())
			return data[index];
		throw std::out_of_range("Stack is empty");
	}



	int size() 
	{
		return index + 1;
	}

	//Очистка стека
	void clear() 
	{
		index = -1;
	}

};
