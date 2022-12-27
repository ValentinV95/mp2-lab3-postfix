// объявление и реализация шаблонного стека
// стек поддерживает операции: 
// - вставка элемента, 
// - извлечение элемента, 
// - просмотр верхнего элемента (без удаления)
// - проверка на пустоту, 
// - получение количества элементов в стеке
// - очистка стека
// при вставке в полный стек должна перевыделяться память
template <typename T>
class TStack {
private:
	int top;
	size_t MemSize;
	T* pMem;
public:
	TStack(size_t _memsize = 10) :top(-1); MemSize(_memsize) {
	if (_memsize <= 0)
		throw exception("stack size can't be zero or negative");
	else
		pMem = new T[MemSize];
	}

	~TStack() { 
		delete[]pMem
	}

	size_t size()const { 
		return top + 1; 
	}

	bool IsEmpty() const {
		return top == -1; 
	}

	bool TopElem() const {
		return top == MemSize - 1;
	}
	
	void clear() {
		top = -1;
	}

	T Pop() {
		if (IsEmpty())
			throw exception("Empty stack");
		return pMem[top--];
	}

	void Push(const T& val) {
		if (TopElem) {
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