class Stack {
private:
	T* data;
	size_T size;
	int index = -1;
public:
	Stack(size_T sz = 1) : size(sz)
	{
		if (sz <= 0)
			throw std::exception("Uncorrected length");
		data = new T[size]();
	}

	Stack(const Stack<T>& a)
	{
		index = a.index;
		size = a.size;
		data = new T[size]();
		for (size_T i = 0; i <= a.index; i++)
			data[i] = a.data[i];
	}

	bool Full() noexcept
	{
		return index == size - 1;
	}

	bool Empty() noexcept
	{
		return index == -1;
	}

	void push(T Elem)
	{
		if (Full())
		{
			Stack<T> tmp(*this);
			delete[] data;
			size *= 2;
			data = new T[size]();
			for (size_T i = 0; i <= index; i++)
				data[i] = tmp.data[i];
		}
		data[++index] = Elem;
	}

	T& pop()
	{
		if (this->Empty())
			throw std::exception("Empty: stack_is_empty");
		return data[index--];
	}

	T& view_top()
	{
		if (this->Empty())
			throw std::exception("view_top: stack_is_empty");
		return data[index];
	}

	size_T GetLength()
	{
		return index + 1;
	}

	void Clear()
	{
		index = -1;
	}

	~Stack() { delete[] data; }
};
