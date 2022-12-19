// объявление и реализация шаблонного стека
// стек поддерживает операции: 
// - вставка элемента, 
// - извлечение элемента, 
// - просмотр верхнего элемента (без удаления)
// - проверка на пустоту, 
// - получение количества элементов в стеке
// - очистка стека
// при вставке в полный стек должна перевыделяться память
#include<iostream>
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

	TStack(TStack&& other) noexcept
	{
		sz = other.sz;
		ind = other.ind;
		pMem = other.pMem;
		other.pMem = nullptr;
	}

	TStack& operator=(TStack& other)
	{
		if (this == &other)
			return *this;
		T* tmp = new T[other.sz];
		copy(other.pMem, other.pMem + other.sz, tmp);
		delete[] pMem;
		sz = other.sz;
		ind = other.ind;
		pMem = tmp;
		return *this;
	}

	TStack& operator=(TStack&& other) noexcept
	{
		delete[] pMem;
		sz = other.sz;
		ind = other.ind;
		pMem = other.pMem;
		other.pMem = nullptr;
		return *this;
	}

	~TStack() { delete[] pMem; }

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
			throw exception("Try to pop from empty stack!");
		ind--;
	}

	T& top() const
	{
		if (isEmpty())
			throw exception("Try to get top element from empty stack!");
		return pMem[ind - 1];
	}

	bool isEmpty() const noexcept { return !static_cast<bool>(ind); }

	size_t size() const noexcept { return ind; }

	void clear()
	{
		ind = 0;
	}
};