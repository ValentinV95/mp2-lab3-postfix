// объявление и реализация шаблонного стека
// стек поддерживает операции: 
// - вставка элемента, 
// - извлечение элемента, 
// - просмотр верхнего элемента (без удаления)
// - проверка на пустоту, 
// - получение количества элементов в стеке
// - очистка стека
// при вставке в полный стек должна перевыделяться память

#include <exception>

template<typename T>
class TStack {
private:
	T* m_pMem;
	int m_top;
	size_t m_memSize;

public:
	TStack() {
		m_top = -1;
		m_memSize = 1;
		m_pMem = new T();
	}

	void push(T value) {
		if (IsFull()) {
			T* temp = new T[m_memSize * 2];
			for (size_t i = 0; i < m_memSize; ++i) {
				temp[i] = m_pMem[i];
			}
			delete[]m_pMem;
			m_pMem = temp; 
			m_memSize *= 2;
		}
		m_pMem[++m_top] = value;
	}

	T pop() {
		if (IsEmpty()) throw std::exception("Stack is empty");
		return m_pMem[m_top--];
	}

	T showTop() {
		return m_pMem[m_top];
	}

	bool IsEmpty() {
		return m_top == -1;
	}

	bool IsFull() {
		return m_top == (m_memSize - 1);
	}

	size_t size() {
		return m_top + 1;
	}

	~TStack() {
		delete[]m_pMem;
	}
};
