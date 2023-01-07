// объ€вление функций и классов дл€ вычислени€ арифметических выражений

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <exception>
#include <sstream>

using namespace std;


class Lexem {

public:
	string value;
	virtual string show() = 0;
};

class Operand :public Lexem {};

class Variable :public Operand {

public:
	Variable(char str) {
		value = str;
	}
	string show() {
		return value;
	}
};

class Value :public Operand {

public:
	Value(string dbl) {
		value = dbl;
	}
	string show() {
		return value;
	}
};

class Operation :public Lexem {
public:
	Operation(char c) {
		value = c;
	}

	int order();

	string show() override {
		return value;
	}
};

class TPostfix {
public:
	TPostfix(string str);
	void set_variable(char name, double value);
	vector<char> get_variable_names();
	string show_postfix();
	double calculate();

private:
	void parse();
	void add_variable(char name, double value);

	string m_infix;
	std::vector<Lexem*> m_postfix;
	map<char, double> m_variables;
};
