// объ€вление и реализаци€ шаблонного стека
// стек поддерживает операции: 
// - вставка элемента, 
// - извлечение элемента, 
// - просмотр верхнего элемента (без удалени€)
// - проверка на пустоту, 
// - получение количества элементов в стеке
// - очистка стека
// при вставке в полный стек должна перевыдел€тьс€ пам€ть


template <class T>
class Stack
{
private:
	T* data = nullptr;
	int index = -1;
	int real_size = 2;
public:
	Stack()
	{
		data = new T[real_size];
	}
	~Stack() // - очистка стека (удаление)
	{
		delete[] data;
	}

	void Clear() // - только очистка стека
	{
		index = -1;
	}

	bool IsEmpty()  // - проверка на пустоту
	{
		return index < 0;
	}

	void Push(T elem) // - вставка элемента
	{
		if (++index == real_size)  // при вставке в полный стек должна перевыдел€тьс€ пам€ть
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

	T Top() // - просмотр верхнего элемента (без удалени€)
	{
		if (IsEmpty())
			throw std::exception("Stack is empty!");
		return data[index];
	}
};