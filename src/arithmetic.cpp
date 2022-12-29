#include "arithmetic.h"

void TPostfix::Get_Using_Operands() {
	if (infix.find('x') != string::npos) operands.push_back('x');
	if (infix.find('y') != string::npos) operands.push_back('y');
	if (infix.find('z') != string::npos) operands.push_back('z');
}


bool TPostfix::isDigit(const char& a) {

	if ('0' <= a && a <= '9') return true;

	else return false;
}


bool TPostfix::isOperand(const char& a) {

	return (operands.find(a) != string::npos);
}


bool TPostfix::isOperation(const char& a) {

	return (operations.find(a) != string::npos);

}


TPostfix::TPostfix(string& _str) : infix(_str) {
	size = _str.size();
	SetOfLexems = new string[size]();

	operations = "+-*/";
	priority = { {"(", 0}, {")", 0}, {"+", 1}, {"-", 1}, {"*", 2}, {"/", 2}, {"~", 4} };

	Get_Using_Operands();

	CheckInfix();

	ToPostfix();
}

TPostfix::~TPostfix() {
	delete[] SetOfLexems;
}

string TPostfix::GetOperands() { return operands; }

string TPostfix::GetInfix() { return infix; }

string TPostfix::GetPostfix() { return postfix; }


void TPostfix::Parser() {

	size_t number = 0;

	for (size_t i = 0; i < size; i++) {

		if (infix[i] == '-') {

			if (i == 0 || infix[i - 1] == '(' || isOperation(infix[i - 1])) SetOfLexems[number++] = '~';

			else if (infix[i - 1] == 'e') SetOfLexems[number] += infix[i];

			else SetOfLexems[number++] = infix[i];
		}

		else if (isDigit(infix[i])) {

			if (i + 1 == size || (infix[i + 1] < '0' && infix[i + 1] != '.')) SetOfLexems[number++] += infix[i];

			else SetOfLexems[number] += infix[i];

		}

		else if (infix[i] == 'e' || infix[i] == '.') SetOfLexems[number] += infix[i];

		else SetOfLexems[number++] = infix[i];

	}

	sizesol = number;

}


void TPostfix::ToPostfix() {

	Parser();

	string* postfixmas = new string[sizesol];
	size_t number = 0;

	DStack<string> st;

	string tmp;
	for (size_t i = 0; i < sizesol; i++) {

		if (SetOfLexems[i] == "(") st.Push(SetOfLexems[i]);

		else if (SetOfLexems[i] == ")") {

			while (st.Top() != "(") {

				postfixmas[number++] = st.Pop();

			}
			st.Pop();
		}

		else if (SetOfLexems[i] == "~" || (SetOfLexems[i].size() == 1 && operations.find(SetOfLexems[i]) != string::npos)) {

			while (!st.IsEmpty()) {
				tmp = st.Pop();

				if (priority[SetOfLexems[i]] <= priority[tmp]) {
					postfixmas[number++] = tmp;
				}
				else {
					st.Push(tmp);
					break;
				}
			}

			st.Push(SetOfLexems[i]);
		}

		else postfixmas[number++] = SetOfLexems[i];

	}
	while (!st.IsEmpty()) postfixmas[number++] = st.Pop();

	sizesol = number;

	for (size_t i = 0; i < number; i++) {
		postfix += postfixmas[i];
		SetOfLexems[i] = postfixmas[i];
	}

	delete[] postfixmas;

}


double TPostfix::toNumber(string str) {
	double number = 0.0, sign = 1.0;


	if (str.find('.') != string::npos && str.find('e') == string::npos) {

		double beforepoint = 0.0, afterpoint = 0.0;
		string beforepoints, afterpoints;
		size_t quantity_of_point = 1;

		int p = str.find('.');

		for (int i = 0; i < p; i++) { beforepoints += str[i]; }
		for (int i = p + 1; i < str.size(); i++) { afterpoints += str[i]; }

		beforepoint = toNumber(beforepoints);
		afterpoint = toNumber(afterpoints);

		for (int i = 0; i < afterpoints.size(); i++) { afterpoint /= 10; }

		number = beforepoint + afterpoint;

	}

	else if (str.find('e') != string::npos) {

		double beforeE = 0.0, afterE = 0.0;
		string beforeEs, afterEs;

		int p = str.find('e');

		for (int i = 0; i < p; i++) { beforeEs += str[i]; }
		for (int i = p + 1; i < str.size(); i++) { afterEs += str[i]; }

		beforeE = toNumber(beforeEs);
		afterE = toNumber(afterEs);

		number = beforeE * pow(10.0, afterE);
	}

	else {

		if (str[0] == '~') {

			for (size_t i = 1; i < str.size(); i++) {
				number = number * 10.0 + static_cast<double>(str[i] - '0');
			}
			number *= -1.0;
		}

		else {

			for (size_t i = 0; i < str.size(); i++) {
				number = number * 10.0 + static_cast<double>(str[i] - '0');
			}
		}
	}

	return number;
}


double TPostfix::Calculate(map<char, double>& values) {

	DStack<double> st;
	double leftOp, rightOp;

	for (size_t i = 0; i < sizesol; i++) {

		if (SetOfLexems[i] == "~") {

			rightOp = st.Pop();
			st.Push(-1.0 * rightOp);

		}
		else if (SetOfLexems[i] == "+") {

			rightOp = st.Pop();
			leftOp = st.Pop();
			st.Push(leftOp + rightOp);

		}
		else if (SetOfLexems[i] == "-") {

			rightOp = st.Pop();
			leftOp = st.Pop();
			st.Push(leftOp - rightOp);

		}
		else if (SetOfLexems[i] == "*") {

			rightOp = st.Pop();
			leftOp = st.Pop();
			st.Push(leftOp * rightOp);

		}
		else if (SetOfLexems[i] == "/") {

			rightOp = st.Pop();
			leftOp = st.Pop();
			st.Push(leftOp / rightOp);
		}
		else if (operands.find(SetOfLexems[i]) != string::npos) {

			if (SetOfLexems[i] == "x") st.Push(values['x']);
			if (SetOfLexems[i] == "y") st.Push(values['y']);
			if (SetOfLexems[i] == "z") st.Push(values['z']);

		}
	
		else { st.Push(toNumber(SetOfLexems[i])); }
	}
	return st.Pop();
}


void TPostfix::CheckInfix() {

	string error = "Unexpected element: ";
	string arrow = "<-";
	int open = 0, close = 0;

	error += infix[0];

	if (infix[0] != '(' && (!isDigit(infix[0])) && (!isOperand(infix[0])) && infix[0] != '-') {
		error += arrow;
		throw (error);
	}

	for (size_t i = 0; i < size - 1; i++) {

		if (i != 0) {
			error += infix[i];
		}

		if (isDigit(infix[i])){

			if (infix[i + 1] == '(' || isOperand(infix[i + 1])) {

				error += infix[i + 1] + arrow;
				throw (error);
			}
		}

		else if (infix[i] == 'e') {

			if (infix[i + 1] != '-' && (!isDigit(infix[i + 1]))) {

				error += infix[i + 1] + arrow;
				throw (error);
			}
		}

		else if (isOperand(infix[i]) || infix[i] == ')'){

			if ((!isOperation(infix[i + 1])) && infix[i + 1] != ')') {

				error += infix[i + 1] + arrow;
				throw (error);
			}
			
		}

		else if(isOperation(infix[i])){

			if (!isOperand(infix[i + 1]) && (!isDigit(infix[i + 1])) && infix[i + 1] != '(' && infix[i + 1] != '-') {

				error += infix[i + 1] + arrow;
				throw (error);
			}
		}

		else if (infix[i] == '(') {

			if (infix[i + 1] != '-' && infix[i + 1] != '(' && !isDigit(infix[i+1]) && !isOperand(infix[i + 1])) {
				error += infix[i + 1] + arrow;
				throw (error);
			}
		}

		else if (infix[i] == '.') {

			if (!isDigit(infix[i + 1])) {
				error += infix[i + 1] + arrow;
				throw (error);
			}
		}

		if (i + 2 == size) {
			if (!isDigit(infix[i + 1]) && !isOperand(infix[i + 1]) && infix[i + 1] != ')') {
				error += infix[i + 1] + arrow;
				throw (error);
			}
		}
		
	}

	for (size_t i = 0; i < size; i++) {
		if (infix[i] == '(') open++;
		if (infix[i] == ')') close++;
	}


	if (open != close) {
		string error_brackets = "wrong number of brackets";
		throw (error_brackets);
	}
	
}