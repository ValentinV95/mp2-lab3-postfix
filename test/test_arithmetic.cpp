// тесты для вычисления арифметических выражений

#include <gtest.h>
#include"arithmetic.h"


TEST(Arithmetic, can_rerurn_original_entry)
{
	Arithmetic expr("(a+b)*-(b/c)");
	EXPECT_EQ("(a+b)*-(b/c)", expr.get_origin_expression());
};

TEST(Arithmetic, can_make_postfix_form)
{
	Arithmetic expr("(a+b)*-(b/c)+3");
	expr.toPostfix();
	EXPECT_EQ("ab+bc/~*3+", expr.getPostfix());
};

TEST(Arithmetic, can_calculate)
{
	Arithmetic expr("(a+b)*-(b/c)+3");
	double res;
	expr.toPostfix();
	expr.setVarValues_for_test(0.001, 13, -33.3, 0);
	res = expr.calculate();
	EXPECT_EQ(true, abs(res - 8.07547) < 0.00001);
};

TEST(Arithmetic, check_bracket_order_wrong)
{
	ASSERT_ANY_THROW(Arithmetic expr1("a+b)*c("));  // нарушен порядок скобок

};


TEST(Arithmetic, check_is_correct_brackets)
{
	ASSERT_ANY_THROW(Arithmetic expr3("a+((b+c)")); // разное колличество откр и закр скобок 
	ASSERT_ANY_THROW(Arithmetic expr6(")a+b/c"));   // ) в начале выражения
	ASSERT_ANY_THROW(Arithmetic expr8("(a+b-)+c")); // операция перед ) (кроме такой же ) )
};


TEST(Arithmetic, check_is_binary_operation_at_the_beginning_of_an_expression)
{
	ASSERT_ANY_THROW(Arithmetic expr5("*a+b/c"));   // бинарная операция в начале выражения
};
