// объявление функций и классов для вычисления арифметических выражений
#include <string>
#include "../include/stack.h"
#include <map>

class lexException : public std::exception {
private:
	std::string error_message;
public:
	lexException(std::string err_msg, std::string eq, size_t err_id) : error_message(err_msg)
	{
		error_message += '\n' + eq + '\n';
		for (size_t i = 0; i < err_id; i++)
			error_message += " ";
		error_message += '^';
	}

	const char* what() const noexcept
	{
		return error_message.c_str();
	}
};

class Lexems {
protected:
	std::string lex;
public:
	Lexems(std::string _lex);
	virtual std::string whatis() = 0;
	virtual size_t prioritet() = 0;
	virtual void ToDo(Stack<double>& S) = 0;
	virtual std::string show() = 0;
	virtual ~Lexems();
};

class Operator : public Lexems {
private:
	size_t priority;
public:
	Operator(char _lex);
	size_t prioritet() override;
	std::string whatis() override;
	void ToDo(Stack<double>& S) override;
	std::string show() override;
	~Operator();
};

class Operand : public Lexems {
public:
	Operand(std::string _lex);
	size_t prioritet();
	std::string whatis() override;
	void ToDo(Stack<double>& S) override;
	std::string show() override;
	~Operand();
};

class Var : public Lexems {
public:
	Var(char _lex);
	size_t prioritet();
	std::string whatis() override;
	void ToDo(Stack<double>& S) override;
	std::string show() override;
	~Var();
};


class TPostfix
{
public:
	std::string start_eq;
	std::map<std::string, std::string> nameValue_var;
	Lexems** infix_form;
	Lexems** postfix_form;
	size_t infix_size;
	size_t postfix_size;
public:
	TPostfix(std::string eq);
	void init_infix();
	void init_postfix();
	void correctChecker(const size_t& i, const size_t index);
	double resolve();
	void selectVar(size_t i);
	std::string get_infixLexem(const size_t id);
	std::string get_postfixLexem(const size_t id);
	void infix_show();
	void postfix_show();
	~TPostfix();
};

//функции для определения лексем:	
bool isOperand(const char& lexema) noexcept;
bool isOperator(const char& lexema) noexcept;
bool isVar(const char& lexema) noexcept;

double convert(std::string lexema);                                         //конвертирование операнда из строки в число
