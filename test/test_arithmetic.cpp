// тесты для вычисления арифметических выражений

#include <gtest.h>
#include "arithmetic.h"

TEST(Arithmetic_expression, can_create_correct_expression) {
	ASSERT_NO_THROW(Arithmetic_expression expr("x*y"));
}

TEST(Arithmetic_expression, can_create_postfix_form) {
	Arithmetic_expression expr("3*3+2");
	EXPECT_EQ(11, expr.Calculate());
}

TEST(Arithmetic_expression, correct_brackets) {
	ASSERT_ANY_THROW(Arithmetic_expression expr("((a+c)"));
	ASSERT_ANY_THROW(Arithmetic_expression expr("(a+c))"));
	ASSERT_ANY_THROW(Arithmetic_expression expr(")a+c)"));
	ASSERT_ANY_THROW(Arithmetic_expression expr("a+)-c("));
}

TEST(Arithmetic_expression, correct_calculation) {
	Arithmetic_expression expr("(4+5)*(8/4)+3");
	double res;
	res = expr.Calculate();
	EXPECT_EQ(true, abs(res - 21.0) < 0.00001);
};