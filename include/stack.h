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
class TStack
{
private:

	T* mas;
	int it;
	size_t maxsize;

public:

	TStack()
	{
		it = -1;
		maxsize = 1;
		mas = new T();
	}

	void push_back(T value)
	{
		if (IsFull())
		{
			T* tmp = new T[maxsize*2];
			for (size_t i = 0; i < maxsize; i++)
			{
				tmp[i] = mas[i];
			}
			delete[]mas;
			mas = tmp;

			maxsize *= 2;
		}
		mas[++it] = value;
	}

	T pop()
	{
		if (IsEmpty()) throw std::exception("No elements in Stack!");
		return mas[it--];
	}

	T show()
	{
		return mas[it];
	}

	bool IsEmpty()
	{
		return it == -1;
	}

	bool IsFull()
	{
		return it == (maxsize-1);
	}

	size_t size()
	{
		return it + 1;
	}

	~TStack()
	{
		delete[]mas;
	}

};