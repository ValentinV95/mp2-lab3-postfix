template <typename T>// ���������� � ���������� ���������� �����
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
    Tstack( Tstack& r) : top(0), cap(r.cap), mas(new T[r.cap]()) // ����������� ����� �������� �������� ����
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

	void push(T el) // - ������� ��������, 
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

	T pop() // - ���������� ��������, 
	{
		if (isEmpty())
		{
			throw std::out_of_range("underflow stack");
		}

		return mas[top-- - 1];

	}

	T peek() // - �������� �������� �������� (��� ��������)
	{
		if (isEmpty())
		{
			throw std::out_of_range("underflow stack");
		}

		return mas[top - 1];
	}

	bool isEmpty() // - �������� �� �������, 
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

	size_t size() { return cap; } // - ��������� ���������� ��������� � �����
	
	void clr() // - ������� �����
	{
		while (!isEmpty())
		{
			pop();
		}
	}
}; 
// ��� ������� � ������ ���� ������ �������������� ������