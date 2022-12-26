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
	int ID = -1;
	int Razmer = 2;
	
	
	
//Открытый класс	
public:
	Stack()
	{
		data = new T[Razmer];
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
		if (++ID == Razmer)  
		{
			T* tmp = new T[Razmer * 2];
			for (Razmer i = 0; i < Razmer; i++)
				tmp[i] = data[i];
			delete[] data;
			data = tmp;
			Razmer *= 2;
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
