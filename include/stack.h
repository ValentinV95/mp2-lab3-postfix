// объявление и реализация шаблонного стека
// стек поддерживает операции: 
// - вставка элемента, 
// - извлечение элемента, 
// - просмотр верхнего элемента (без удаления)
// - проверка на пустоту, 
// - получение количества элементов в стеке
// - очистка стека
// при вставке в полный стек должна перевыделяться память


using namespace std;

template<class T>
class Stack
{
private:
	T* data;
	int size;
	int index;
public:
	Stack(int sz = 1) : size(sz), index(-1)
	{
		if (sz <= 0)
		{
			throw exception("Stack size should be greater than zero");
		}
		data = new T[size];
	}
	~Stack()
	{
		delete[] data;
	}
	bool isFull()
	{
		return index == size - 1;
	}
	bool isEmpty()
	{
		return index == -1;
	}
	void push(const T& a)
	{
		if (isFull())
		{
			T* tmp = new T[size * 2];
			std::copy(data, data + size, tmp);
			size *= 2;
			delete[] data;
			data = tmp;
		}
		data[++index] = a;
	}
	void pop()
	{
		if (!isEmpty())
		{
			index--;
		}
	}
	T top()
	{
		if (!isEmpty())
		{
			return data[index];
		}
		return 0;
	}
	int getCount()
	{
		int tmp = index;
		return ++tmp;
	}
	void clear()
	{
		index = -1;
	}
};