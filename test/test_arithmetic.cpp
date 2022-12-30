// тесты для вычисления арифметических выражений
#include "arithmetic.h"
#include <gtest.h>

TEST(arithmetic, one_number)
{
	EXPECT_EQ(1, TPostfix("1").calculate());
	EXPECT_EQ(2, TPostfix("2").calculate());
}

TEST(arithmetic, unar_sub)
{
	EXPECT_EQ(-1, TPostfix("-1").calculate());
}

TEST(arithmetic, sum)
{
	EXPECT_EQ(2.0, TPostfix("1+1").calculate());
}

TEST(arithmetic, sub)
{
	EXPECT_EQ(0.0, TPostfix("1-1").calculate());
}

TEST(arithmetic, mul)
{
	EXPECT_EQ(6, TPostfix("2*3").calculate());
}

TEST(arithmetic, div)
{
	EXPECT_EQ(2, TPostfix("4/2").calculate());
}
TEST(arithmetic, op_priority)
{
	EXPECT_EQ(7, TPostfix("1+2*3").calculate());
}

TEST(arithmetic, brackets)
{
	EXPECT_EQ(9, TPostfix("(1+2)*3").calculate());
}

TEST(arithmetic, mested_brackets)
{
	EXPECT_EQ(4, TPostfix("((1+2)/3)*4").calculate());
}

TEST(arithmetic, unary_sub_expression)
{
	EXPECT_EQ(-6, TPostfix("2*(-3)").calculate());
}

TEST(arithmetic, op_order)
{
	EXPECT_EQ(2, TPostfix("2*3-4").calculate());
}

TEST(arithmetic, variable)
{
	TPostfix expr("a");
	expr.set_variable('a', 1.2);
	EXPECT_EQ(1.2, expr.calculate());
}

TEST(arithmetic, multyple_variables)
{
	TPostfix expr("a+b");
	expr.set_variable('a', 1);
	expr.set_variable('b', 2);
	EXPECT_EQ(3, expr.calculate());
	EXPECT_EQ(2, expr.get_variable_names().size());
	EXPECT_EQ('a', expr.get_variable_names()[0]);
	EXPECT_EQ('b', expr.get_variable_names()[1]);
}

TEST(arithmetic, stupid_infix_form)
{
	;
	ASSERT_NO_THROW(TPostfix("1").calculate());
	ASSERT_ANY_THROW(TPostfix("-").calculate());
	ASSERT_ANY_THROW(TPostfix("1-").calculate());
	ASSERT_ANY_THROW(TPostfix("1-()").calculate());
	ASSERT_ANY_THROW(TPostfix("1()").calculate());
	ASSERT_ANY_THROW(TPostfix("1(2)").calculate());
	ASSERT_ANY_THROW(TPostfix("()").calculate());
}
	