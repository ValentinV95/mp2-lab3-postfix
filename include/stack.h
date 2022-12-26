//Объявление билиотек
#include <string>
#include <iostream>
#include <math.h>
#include <locale>
#include <map>
#include <ostream>





template <class T>
class Stack
{

//Приватный класс
private:
	T* data;
	int Index = -1;
	int r_size = 2;
	
	
	
//Открытый класс	
public:
	Stack()
	{
		data = new T[r_size];
	}
	void Clear() 
	{
		ID = -1;
	}
	bool IsEmpty()  
	{
		return ID < 0;
	}
	void Push(T elem) 
	{
		if (++ID == r_size)  
		{
			T* tmp = new T[r_size * 2];
			for (size_t i = 0; i < r_size; i++)
				tmp[i] = data[i];
			delete[] data;
			data = tmp;
			r_size *= 2;
		}
		data[ID] = elem;
	}
	T Pop() 
	{
		if (IsEmpty())
			throw std::exception("Nothing on the stack");
		return data[ID--];
	}
	
	//Возвращение индекса
	
	int GetSize() 
	{
		return ID + 1;
	}
	T Top() 
	{
		if (IsEmpty())
			throw std::exception("Nothing on the stack");
		return data[ID];
	}
	~Stack()
	//Очистка
	{
		delete[] data;
	}
};
