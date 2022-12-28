// реализация пользовательского приложения
#include "arithmetic.h"

int main()
{
	Arithmetic_expression exp("5-x*9");
	exp.show();
	exp.show_postfix();
}
