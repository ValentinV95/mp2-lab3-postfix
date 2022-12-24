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
	int index;
	int Size;
	T* Data;
	void OverHeaven()
	{
		T* tmpData = new T[Size * 2];
		std::copy(Data, Data + Size, tmpData);
		delete[] Data;
		this->Data = tmpData;
		Size *= 2;
	}
public:
	Stack(size_t sz = 1) : Size(sz), index(-1)
	{
		if (sz <= 0) {
			throw std::exception("Stack size is zero");
		}
		else {
			Data = new T[Size];
		}
	}
	~Stack() 
	{
		delete[] Data;
	}

	void Clear() 
	{
		index = -1;
	}

	void Push(T element)
	{
		if (IsFull()) OverHeaven();
		Data[++index] = element;
	}

	bool IsEmpty()  
	{
		return index < 0;
	}

	bool IsFull() const
	{
		return index == Size - 1;
	}

	T Pop()
	{
		if (IsEmpty())
			throw std::exception("Empty stack");
		return Data[index--];
	}

	T Top()
	{
		if (IsEmpty())
			throw std::exception("Empty stack");
		return Data[index];
	}

	int GetSize() 
	{
		return index + 1;
	}

	
};