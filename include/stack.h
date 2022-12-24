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

template <class T>
class TStack
{
private:
	T* pMem;
	size_t sz;
	size_t ind;
public:
	TStack() : sz(10), ind(0)
	{
		pMem = new T[sz]();
	}

	TStack(TStack& other)
	{
		sz = other.sz;
		ind = other.ind;
		pMem = new T[sz];
		copy(other.pMem, other.pMem + other.sz, pMem);
	}

	TStack& operator=(TStack& other)
	{
		if (this == &other)
		{
			return *this;
		}
		T* tmp = new T[other.sz];
		copy(other.pMem, other.pMem + other.sz, tmp);
		delete[] pMem;
		sz = other.sz;
		ind = other.ind;
		pMem = tmp;
		return *this;
	}

	~TStack() 
	{ 
		delete[] pMem; 
	}

	void push(T elem)
	{
		if (ind == sz)
		{
			T* tmp = new T[sz * 2];
			copy(pMem, pMem + sz, tmp);
			delete[] pMem;
			pMem = tmp;
			sz = sz * 2;
		}
		pMem[ind++] = elem;
	}

	void pop()
	{
		if (isEmpty())
		{
			throw exception("Can't pop the element because the stack is empty");
		}
		ind--;
	}

	T& top() const
	{
		if (isEmpty())
		{
			throw exception("Can't view the top element because the stack is empty");
		}
		return pMem[ind - 1];
	}

	bool isEmpty() const 
	{ 
		return !bool(ind); 
	}

	size_t size() const 
	{ 
		return ind; 
	}

	void clear()
	{
		delete[] pMem;
		sz = 10;
		ind = 0;
		pMem = new T[sz];
	}
};