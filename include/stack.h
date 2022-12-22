template <typename T>// объявление и реализация шаблонного стека
class Tstack {
private:
	size_t top;
	size_t cap;
	T* mas;
public:
	Tstack(int len = 10) :cap(len), top(0), mas(new T[len]())
	{
		if (len <= 0) throw std::invalid_argument("Tstack(int len)");
	}
	virtual ~Tstack()
	{
		delete[] mas;
	}
    Tstack( Tstack& r) : top(0), cap(r.cap), mas(new T[r.cap]()) // Копирование стека затирает исходный стек
	{
		Tstack tmp(cap);
		while (!r.isEmpty())
		{
			tmp.push(r.pop());
		}
		while (!tmp.isEmpty())
		{
			push(tmp.pop());
		}
	}

    Tstack& operator= ( Tstack& r)
	{
		if (this != &r) 
		{
			delete[] mas;
			mas = new T[r.cap]();
			top = 0;
			cap = r.cap;
			Tstack tmp(cap);
			while (!r.isEmpty()) 
			{
				tmp.push(r.pop());
			}
			while (!tmp.isEmpty())
			{
				push(tmp.pop());
			}
		}
		return *this;
	}

	void push(T el) // - вставка элемента, 
	{
		if (isFull())
		{
			Tstack tmp(cap * 2);
			while (!isEmpty()) {
				tmp.push(pop());
			}
			*this = tmp;
		}
		mas[++top - 1] = el;

	}

	T pop() // - извлечение элемента, 
	{
		if (isEmpty())
		{
			throw std::out_of_range("underflow stack");
		}

		return mas[top-- - 1];

	}

	T peek() // - просмотр верхнего элемента (без удаления)
	{
		if (isEmpty())
		{
			throw std::out_of_range("underflow stack");
		}

		return mas[top - 1];
	}

	bool isEmpty() // - проверка на пустоту, 
	{
		return top == 0;
	}

	bool isFull() 
	{
		return top == cap -1 ;
	}

	bool operator ==(const Tstack& r) const
	{
		if (top == r.top) 
		{
			for (size_t i = 0; i < top; i++) {
				if (mas[i] != r.mas[i]) return false;
			}
			return true;
		}
		return false;
	}

	size_t size() { return cap; } // - получение количества элементов в стеке
	
	void clr() // - очистка стека
	{
		while (!isEmpty())
		{
			pop();
		}
	}
}; 
// при вставке в полный стек должна перевыделяться память

template <typename T>
class TQueue 
{
private:
	Tstack<T> s1;
	Tstack<T> s2;
public:
	TQueue(int len = 10) :s1(len), s2(len) {};
	~TQueue() 
	{
		delete s1;
		delete s2;
	}
	void push(T el) //добавление в начало очереди 
	{
		s1.push(el);
	}
	T pop(void) // взятие из конца очереди
	{
		if (s2.isEmpty()) 
		{
			while (!s1.isEmpty()) 
			{
				s2.push(s1.pop());
			}
		}
		return s2.pop();
	}
};