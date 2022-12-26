// ���������� � ���������� ���������� �����
// ���� ������������ ��������: 
// - ������� ��������, 
// - ���������� ��������, 
// - �������� �������� �������� (��� ��������)
// - �������� �� �������, 
// - ��������� ���������� ��������� � �����
// - ������� �����
// ��� ������� � ������ ���� ������ �������������� ������
template <typename T>
class TStack {
private:
	int top;
	size_t MemSize;
	T* pMem;
public:
	TStack(_memsize = 10) :top(-1); MemSize(_memsize), pMem(new T[MemSize]) {}

	~TStack() { delete[]pMem }

	size_t size()const { return top + 1; }

	bool IsEmpty() const { return top == -1; }

	bool TopElem() const { return top == MemSize - 1; }

	T Pop() { return pMem[top--]; }

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