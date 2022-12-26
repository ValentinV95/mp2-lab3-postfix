#pragma once

#include <iostream>
#include <map>
#include <cmath>
#include <string>
#include "stack.h"

class lexException : 
public std::exception 
{
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

class Lexem 
{
public:
	Lexem();
	virtual std::string whatis() = 0;
	virtual size_t prioritet() = 0;
	virtual void ToDo(Stack<double>& S) = 0;
	virtual std::string show() = 0;
	virtual ~Lexem();
};

class Operator : 
	public Lexems 
    {
    private:
	std::string lex;
	size_t priority;
    public:
	Operator(char _lex);
	size_t prioritet() override;
	std::string whatis() override;
	void ToDo(Stack<double>& S) override;
	std::string show() override;
	~Operator();
    };

class Operand : 
	public Lexems {
    private:
	std::string lex;
    public:
	Operand(std::string _lex);
	size_t prioritet();
	std::string whatis() override;
	void ToDo(Stack<double>& S) override;
	std::string show() override;
	~Operand();
    };

class Var : 
	public Lexems 
    {
    private:
	std::string lex;
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
	std::string get_infixLexem();
	std::string get_postfixLexem();
	~TPostfix();
};

	
bool isOperand(const char& lexema) noexcept;
bool isOperator(const char& lexema) noexcept;
bool isVar(const char& lexema) noexcept;

double convert(std::string lexema);