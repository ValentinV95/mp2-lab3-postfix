// объявление и реализация шаблонного стека
// стек поддерживает операции: 
// - вставка элемента, 
// - извлечение элемента, 
// - просмотр верхнего элемента (без удаления)
// - проверка на пустоту, 
// - получение количества элементов в стеке
// - очистка стека
// при вставке в полный стек должна перевыделяться память

#include <iostream>

using namespace std;

template <typename T>
class TStack {
private:
	T* _Stack;
	int _size;
	int _top;
public:
	TStack()
	{
		_size = 1;
		_top = -1;
		_Stack = new T[_size];
	}

	~TStack()
	{
		delete[]_Stack;
	}

	bool empty()
	{
		return _top == -1;

	}
	int size()
	{
		return _top + 1;
	}
	T top() {
		T temp = _Stack[_top];
		return temp;
	}


	void push(T elem)
	{
		if (_top == _size - 1)
		{
			T* _Stack_temp = new T[_size * 2];
			for (int i = 0; i < _size; i++)
			{
				_Stack_temp[i] = _Stack[i];
			}
			delete[]_Stack;
			_Stack = _Stack_temp;
			_size = _size * 2;
		}
		_Stack[++_top] = elem;
	}
	T pop()
	{

		if (!empty()) { return _Stack[_top--]; }
	}


	T& TStack::operator[](const unsigned int indx)
	{
		return _Stack[indx];
	}

};