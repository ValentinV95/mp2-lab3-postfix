#include<stdlib.h>
#include<math.h>
#include<iostream>
#include<string>



using namespace std;

// объявление и реализация шаблонного стека
// стек поддерживает операции: 
// - вставка элемента, 
// - извлечение элемента, 
// - просмотр верхнего элемента (без удаления)
// - проверка на пустоту, 
// - получение количества элементов в стеке
// - очистка стека
// при вставке в полный стек должна перевыделяться память


template <typename T> class Tstack
{
private:

	int top;
	size_t memSize;
	T* pMem;

public:

	Tstack(T* p, size_t in_size) : top(-1), memSize(in_size), pMem(p) {}

	Tstack(size_t in_size) : top(-1), memSize(in_size)
	{
		pMem = new T[memSize];
	}

	Tstack(void) : top(-1), memSize(1)
	{
		pMem = new T[memSize];
	}

	/*	~Tstack()
		{
			//-|написать здесь что-то|--|написать здесь что-то|--|написать здесь что-то|--|написать здесь что-то|-
		}
	*/

	~Tstack() = default;
	//-|сделать свой деструктор|-

	bool isEmpty() { return top == -1; }
	bool isFull() { return top == memSize - 1; }

	T Top() { return pMem[top]; }
	size_t size() { return top + 1; }

	void Push(T a)
	{
		if (isFull())
		{
			T* tmp = new T[memSize * 2];
			for (size_t i = 0; i < memSize; i++)
			{
				tmp[i] = pMem[i];
			}
			delete[]pMem;
			pMem = tmp;
			memSize *= 2;
			
		}		
			pMem[++top] = a;
		
	}

	T Pop()
	{
		if (!isEmpty()) { return pMem[top--]; }

	}








};





