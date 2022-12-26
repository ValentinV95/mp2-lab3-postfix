#ifndef __STACK_H__
#define __STACK_H__
#include <iostream>
using namespace std;



template <class T>
class TStack
{
private:
	int top;
	int size;
	T* pMem;
public:
	TStack(int _size)  
	{ 
		if (_size > 0) {
			top = -1;
			size = _size;
			pMem = new T[size];
		}
		else {
			throw exception("wrong stack size");
		}
	}

	const bool IsEmpty()
	{
		if (top != -1) {
			return 0;
		}
		return 1;
	}

	const bool IsFull()
	{
		if (top != size - 1) {
			return 0;
		}
		return 1;
	}

	void clean()
	{
		top = -1;
	}

	int Size()
	{
		return top + 1;
	}

	T get_top()
	{
		if (!IsEmpty()) {
			return pMem[top];
		}
		else {
			throw exception("stack is empty");
		}
	}


	T pop()
	{
		if (!IsEmpty()) {
			return pMem[top--];
		}
		else {
			throw exception("stack is empty");
		}
	}

	void push(const T& element)
	{
		if (top == size - 1) {
			T* tmpMem = new T[size * 2];
			copy(pMem, pMem + size, tmpMem);
			delete[] pMem;
			pMem = tmpMem;
			size *= 2;
		}
		pMem[++top] = element;
	}

	~TStack()
	{
		delete[] pMem;
	}
};
#endif  
