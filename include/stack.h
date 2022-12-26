#ifndef __STACK_H__
#define __STACK_H__
#include <cstddef>
#include <iostream>
const int MaxStackSize = 100;


template <class T>
class TStack
{
    T* pMem;
    int size;
    int top;
    int DataCount;
public:
    TStack(int _size) {
        size = _size;
        top = 0;
        if ((size < 1) || (size > MaxStackSize)) 
            throw size;
        DataCount = 0;
        pMem = new T[size];
    }

    ~TStack() 
    { 
        delete[] pMem; 
    }
    TStack& operator=(const TStack& tstack);
    int GetNextIndex(int index);
    int IsEmpty(void) const;
    int IsFull(void) const;
    void Put(const T& Val);
    virtual T Get(void);
    T Pop();
};


template<class T>
inline TStack<T>& TStack<T>::operator=(const TStack<T>& tstack) 
{
    if (this == &tstack) 
        return *this; 
    pMem = tstack.pMem;
    return *this;
}

template<class T>
inline int TStack<T>::GetNextIndex(int index) 
{
    return ++index; 
}

template<class T>
inline int TStack<T>::IsEmpty(void) const 
{ 
    return(DataCount == 0); 
}

template<class T>
inline int TStack<T>::IsFull(void) const 
{ 
    return (DataCount == size); 
}

template<class T>
inline void TStack<T>::Put(const T& Val) 
{
    if (IsFull()) 
        throw (DataCount);
    pMem[top] = Val;
    DataCount++;
    top++;
}

template<class T>
inline T TStack<T>::Pop() 
{
    if (this->IsEmpty())
        throw exception();
    top--;
    DataCount--;
    T tmp = pMem[top];
    pMem[top] = NULL;
    return tmp;
}

template<class T>
inline T TStack<T>::Get(void) 
{
    if (IsEmpty()) 
        throw (top);
    return pMem[top - 1];
}

#endif