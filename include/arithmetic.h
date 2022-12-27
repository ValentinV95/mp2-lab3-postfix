#include <string>
#include "../include/stack.h"
#include <map>

class lexException : public std::exception {
private:
	std::string error_message;
public:
	lexException(std::string err_msg, std::string eq, size_T err_id) : error_message(err_msg)
	{
		error_message += '\n' + eq + '\n';
		for (size_T i = 0; i < err_id; i++)
			error_message += " ";
		error_message += '^';
	}

	const char* what() const noexcept
	{
		return error_message.c_str();
	}
};

class Lexems {
public:
	Lexems();
	virtual std::string what_is() = 0;
	virtual size_T prioritet() = 0;
	virtual void ToDo(Stack<double>& S) = 0;
	virtual std::string show() = 0;
	virtual ~Lexems();
};

class Operator : public Lexems {
private:
	std::string lex;
	size_T priority;
public:
	Operator(char _lex);
	size_T prioritet() override;
	std::string what_is() override;
	void ToDo(Stack<double>& S) override;
	std::string show() override;
	~Operator();
};

class Operand : public Lexems {
private:
	std::string lex;
public:
	Operand(std::string _lex);
	size_T prioritet() override;
	std::string what_is() override;
	void ToDo(Stack<double>& S) override;
	std::string show() override;
	~Operand();
};

class Var : public Lexems {
private:
	std::string lex;
public:
	Var(char _lex);
	size_T prioritet() override;
	std::string what_is() override;
	void ToDo(Stack<double>& S) override;
	std::string show() override;
	~Var();
};


class TPostfix
{
private:
	std::string start_eq;
	std::map<std::string, std::string> nameValue_var;
	Lexems** infix_form;
	Lexems** postfix_form;
	size_T infix_size;
	size_T postfix_size;
public:
	TPostfix(std::string eq);
	void init_infix();
	void init_postfix();
	void correctChecker(const size_T& i, const size_T index);
	double resolve();
	std::string get_infixLexem();
	std::string get_postfixLexem();
	~TPostfix();
};

bool isOperand(const char& lexema) noexcept;
bool isOperator(const char& lexema) noexcept;
bool isVar(const char& lexema) noexcept;

double convert(std::string lexema);