// реализация пользовательского приложения
#include "arithmetic.h"
using namespace std;
#include "stack.h"

int main()
{
	//string expr;
	//cin >> expr;
	Arithmetic_expression exp("x/(x+3/1,23)");
	exp.show();
	exp.show_postfix();


	//try {
	//	TStack <double> st(0);
	//}
	//catch(string * msg){
	//	cout << msg;
	//}
	//cout << "empty stack";
}
