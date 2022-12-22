// объ€вление функций и классов дл€ вычислени€ арифметических выражений

// #include <stack.h>
#include <string>



class BaseLexem
{
protected:
	std::string name;
	std::string lexem;
	double double_performance;
	int priority;
	int pos_start;
	int pos_end;

public:

	std::string LexemType();
	std::string GetLexem();
	double Value();
	virtual void SetPriority(char operation) = 0;
	int GetSatrtPos();
	int GetEndPos();
	int GetPriority();
};


class BinaryOperation : public BaseLexem //  + - * /
{
protected:
	void SetPriority(char operation) override;
public:
	BinaryOperation(char data, int pos1, int pos2);
};

class UnaryOperation : public BaseLexem // ~
{
protected:
	void SetPriority(char operation) override;
public:
	UnaryOperation(char data, int pos_start, int pos_end);
};

class Brackets : public BaseLexem // '(' ')' 
{
protected:
	void SetPriority(char operation) override;
public:
	Brackets(char data, int pos_start, int pos_end);
};

class Operand : public BaseLexem
{
protected:
	double ConvertNumber(std::string strlex);
public:
	virtual void SetPriority(char operation);
};

class Number : public Operand
{
public:
	Number(std::string lexem, int pos_start, int pos_end);
	Number(double value, int pos_start, int pos_end);
	Number();
private:
};

class Var : public Operand
{
public:
	Var(std::string lexem, int pos_start, int pos_end);
private:
};



class Arithmetic
{
private:
	std::string infix;
	BaseLexem** lexems = nullptr;
	BaseLexem** postfix = nullptr;
	int size;
	int last = -1;
	int postfix_size;

	bool IsBinaryOperation(const char& ch);
	bool IsUnaryOperation(const char& ch);
	bool IsNumber(const char& ch);
	bool IsNumber(std::string num);
	bool IsVar(const char& ch);
	bool IsVar(std::string num);
	bool IsBrackets(const char& ch);

	void resize();
	std::string ShowError(int index, std::string text);
	std::string ShowError(int index1, int index2, std::string text);


	void FindIncorrectSymbols();
	void CheckLexemOrder();
	void InputVarValue();

	void Postfix();
	void Parser();


public:
	Arithmetic(const std::string& arifmetic);
	double Calculate();
	~Arithmetic();

};