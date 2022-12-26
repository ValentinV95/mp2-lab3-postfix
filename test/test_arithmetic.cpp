// тесты для вычисления арифметических выражений

#include <gtest.h>
#include "arithmetic.h"


TEST(TPostfix, can_create_postfix)
{
	string expression = "2+2";
	ASSERT_NO_THROW(TPostfix p(expression));
}


