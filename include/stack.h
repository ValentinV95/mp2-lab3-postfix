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
	T* data;
	int Index = -1;
	int r_size = 2;
public:
	Stack()
	{
		data = new T[r_size];
	}

	void Clear() 
	{
		Index = -1;
	}

	bool IsEmpty()  
	{
		return Index < 0;
	}

	void Push(T elem) 
	{
		if (++Index == r_size)  
		{
			T* tmp = new T[r_size * 2];
			for (size_t i = 0; i < r_size; i++)
				tmp[i] = data[i];
			delete[] data;
			data = tmp;
			r_size *= 2;
		}
		data[Index] = elem;
	}

	T Pop() 
	{
		if (IsEmpty())
			throw std::exception("Stack is empty.");
		return data[Index--];
	}

	int GetSize() 
	{
		return Index + 1;
	}

	T Top() 
	{
		if (IsEmpty())
			throw std::exception("Stack is empty.");
		return data[Index];
	}
	~Stack()
	{
		delete[] data;
	}
};