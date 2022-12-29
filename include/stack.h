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
	size_t realSize;
	T* data;
public:
	Stack()
	{
		realSize = 5;
		data = new T[realSize];
	}

	Stack(const Stack& temp) // Конструктор копирования
	{
		this->index = temp.index;
		this->realSize = temp.realSize;
		this->data = new T[this->realSize];

		for (int i = 0; i < this->realSize; i++)
			this->data[i] = temp.data[i];
	}

	void push(T temp) // вставка элемента
	{
		if ((index + 1) == realSize) //при вставке в полный стек должна перевыделяться память
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

	~Stack() //очистка стека
	{
		delete[] data;
	}

	bool isEmpty() // проверка на пустоту
	{
		return index == -1;
	}


	T pop() // Извлечение элемента
	{
		if (!isEmpty())
			return data[index--];
		throw std::out_of_range("Empty stack");
	}

	T top() // просмотр верхнего элемента
	{
		if (!isEmpty())
			return data[index];
		throw std::out_of_range("Empty stack");
	}

	int size() // получение количества элементов в стеке
	{
		return index + 1;
	}

	void clear() 
	{
		index = -1;
	}

};