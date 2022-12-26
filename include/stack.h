// ���������� � ���������� ���������� �����
// ���� ������������ ��������: 
// - ������� ��������, 
// - ���������� ��������, 
// - �������� �������� �������� (��� ��������)
// - �������� �� �������, 
// - ��������� ���������� ��������� � �����
// - ������� �����
// ��� ������� � ������ ���� ������ �������������� ������


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
	~Stack() // - ������� ����� (��������)
	{
		delete[] data;
	}

	void Clear()
	{
		index = -1;
	}

	bool IsEmpty()  // - �������� �� �������
	{
		return index < 0;
	}

	void Push(T elem) // - ������� ��������
	{
		if (++index == real_size)  // ��� ������� � ������ ���� ������ �������������� ������
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

	T Pop() // - ���������� ��������
	{
		if (IsEmpty())
			throw std::exception("Stack is empty!");
		return data[index--];
	}

	int GetSize() // - ��������� ���������� ��������� � �����
	{
		return index + 1;
	}

	T Top() // - �������� �������� �������� (��� ��������)
	{
		if (IsEmpty())
			throw std::exception("Stack is empty!");
		return data[index];
	}
};