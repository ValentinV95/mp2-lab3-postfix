// реализация пользовательского приложения
#include "arithmetic.h"
using namespace std;
#include "stack.h"

int main()
{
	//string expr;
	//cin >> expr;
	Arithmetic_expression exp("10/(-10)");
	exp.show();
	exp.show_postfix();
	map<char, double> values;

	//try {
	//	TStack <double> st(0);
	//}
	//catch(string * msg){
	//	cout << msg;
	//}
	//cout << "empty stack";
}
