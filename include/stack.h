// объявление и реализация шаблонного стека
// стек поддерживает операции: 
// - вставка элемента, 
// - извлечение элемента, 
// - просмотр верхнего элемента (без удаления)
// - проверка на пустоту, 
// - получение количества элементов в стеке
// - очистка стека
// при вставке в полный стек должна перевыделяться память
#pragma once
using namespace std;

template <typename T>
class TStack {
private:
	int top;
	size_t MemSize;
	T* pMem;
public:
	TStack(size_t _memsize = 10) :top(-1), MemSize(_memsize) {
	if (_memsize <= 0)
		throw exception("stack size can't be zero or negative");
	else
		pMem = new T[MemSize];
	}

	~TStack() { 
		delete[]pMem;
	}

	size_t size()const { 
		return top + 1; 
	}

	bool IsEmpty() const {
		return top == -1; 
	}

	bool IsFull() const {
		return top == MemSize - 1;
	}
	
	T& TopElem() {
		if (IsEmpty())
			throw exception("Empty stack");
		return pMem[top];
	}

	void clear() {
		top = -1;
	}

	T& Pop() {
		if (IsEmpty())
			throw exception("Empty stack");
		return pMem[top--];
	}

	void Push(const T& val) {
		if (IsFull()) {
			T* tmpMem = new T[MemSize * 2];
			for (size_t i = 0; i < MemSize; i++) {
				tmpMem[i] = pMem[i];
			}
			delete[] pMem;
			pMem = tmpMem;
			MemSize = MemSize * 2;
		}
		pMem[++top] = val;
	}
};

//#pragma once
//
//template <class T>
//class TStack {
//private:
//	T* data;
//	size_t size;
//	int index = -1;
//public:
//	TStack(size_t sz = 1) : size(sz)
//	{
//		if (sz <= 0)
//			throw std::exception("uncorrect length");
//		data = new T[size]();
//	}
//
//	TStack(const TStack<T>& a)
//	{
//		index = a.index;
//		size = a.size;
//		data = new T[size]();
//		for (size_t i = 0; i <= a.index; i++)
//			data[i] = a.data[i];
//	}
//
//	bool IsFull() noexcept			
//	{
//		return index == size - 1;
//	}
//
//	bool IsEmpty() noexcept			
//	{
//		return index == -1;
//	}
//
//	void Push(T Elem)				
//	{
//		if (IsFull())
//		{
//			TStack<T> tmp(*this);
//			delete[] data;
//			size *= 2;
//			data = new T[size]();
//			for (size_t i = 0; i <= index; i++)
//				data[i] = tmp.data[i];
//		}
//		data[++index] = Elem;
//	}
//
//	T& Pop()					  
//	{
//		if (this->IsEmpty())
//			throw std::exception("isEmpty: stack_is_empty");
//		return data[index--];
//	}
//
//	T& TopElem()              
//	{
//		if (this->IsEmpty())
//			throw std::exception("view_top: stack_is_empty");
//		return data[index];
//	}
//
//	size_t GetLength()         
//	{
//		return index + 1;
//	}
//
//	void clear()                
//	{
//		index = -1;
//	}
//
//	~TStack() { delete[] data; }
//};