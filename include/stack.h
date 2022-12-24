// объявление и реализация шаблонного стека
// стек поддерживает операции: 
// - вставка элемента, 
// - извлечение элемента, 
// - просмотр верхнего элемента (без удаления)
// - проверка на пустоту, 
// - получение количества элементов в стеке
// - очистка стека
// при вставке в полный стек должна перевыделяться память


template <class T>
class Stack
{
private:
	T* data = nullptr;
	int index = -1;
	int real_size = 10;
public:
	Stack()
	{
		data = new T[real_size];
	}
	~Stack() // - очистка стека (удаление)
	{
		delete[] data;
	}

	void Clear()
	{
		index = -1;
	}

	bool IsEmpty()  // - проверка на пустоту
	{
		return index < 0;
	}

	void Push(T elem) // - вставка элемента
	{
		if (++index == real_size)  // при вставке в полный стек должна перевыделяться память
		{
			T* tmp = new T[real_size * 2];
			for (size_t i = 0; i < real_size; i++)
				tmp[i] = data[i];
			delete[] data;
			data = tmp;
			real_size *= 2;
		}
		data[index] = elem;
	}

	T Pop() // - извлечение элемента
	{
		if (IsEmpty())
			throw std::exception("Stack is empty!");
		return data[index--];
	}

	int GetSize() // - получение количества элементов в стеке
	{
		return index + 1;
	}

	T Top() // - просмотр верхнего элемента (без удаления)
	{
		if (IsEmpty())
			throw std::exception("Stack is empty!");
		return data[index];
	}
};