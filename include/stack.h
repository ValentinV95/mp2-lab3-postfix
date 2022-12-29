#pragma once

template<typename T>
class DStack {
private:
	int top;
	size_t Memsize;
	T* pMem;
public:
	DStack() : Memsize(1), top(-1), pMem(new T[Memsize]) { };

	size_t size() { return top + 1; }
	
	T Top() {
		if (IsEmpty()) throw std::exception("Stack is empty");
		return pMem[top]; 
	}

	T Pop() { 
		if (IsEmpty()) throw std::exception("Stack is empty");
		return pMem[top--]; 
	}

	

	bool IsEmpty() const { return top == -1; }

	void Push(const T& value) {

		if (top == Memsize - 1) {

			T* tmpmem = new T[Memsize * 2];
			std::copy(pMem, pMem + Memsize, tmpmem);
			delete[] pMem;
			pMem = tmpmem;
			Memsize *= 2;
		}
		pMem[++top] = value;
	}
	void clear() {
		top = -1;
	}

	~DStack() {
		delete[] pMem;
	}
};