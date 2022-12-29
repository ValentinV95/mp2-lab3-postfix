// объ€вление и реализаци€ шаблонного стека
// стек поддерживает операции: 
// - вставка элемента, 
// - извлечение элемента, 
// - просмотр верхнего элемента (без удалени€)
// - проверка на пустоту, 
// - получение количества элементов в стеке
// - очистка стека
// при вставке в полный стек должна перевыдел€тьс€ пам€ть
#pragma once
using namespace std;

template <typename T>
class Stack
{
private:
	size_t size;
	int top;
	T* elemArr;
public:
	Stack(int size = 4)
	{
		top = -1;
		if (size < 0)
			throw out_of_range("size should be greater or equal than zero");
		this->size = size;                       
		elemArr = new T[size];
	};

	~Stack()
	{
		delete[] elemArr;
	}

	// - проверка на пустоту,
	bool isEmpty()
	{
		return top == -1;
	}

	//проверка на заполненость (дл€ перевыделени€ пам€ти)
	bool isFull()
	{
		return top == size - 1;
	}

	// - вставка элемента, 
	void push(T elem)
	{
		if (isFull())
		{
			T* tmp = new T[size*2];
			std::copy(elemArr, elemArr + size, tmp);
			delete[] elemArr;
			size *= 2;
			elemArr = tmp;
		}
		elemArr[++top] = elem;
	}

	// - извлечение элемента,
	T pop()
	{
		if (isEmpty())
			throw out_of_range("you cant get element, stack is empty");         
		return elemArr[top--];
	}

	// - просмотр верхнего элемента (без удалени€)
	T checkTop()
	{
		if (isEmpty())
		{
			throw out_of_range("you cant get element, stack is empty");          
		}                                 
		return elemArr[top];
	}

	// - получение количества элементов в стеке
	int get_size()
	{
		return top + 1;
	}

	// - очистка стека
	void clear()
	{
		top = -1;
	}
};