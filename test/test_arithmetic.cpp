// тесты для вычисления арифметических выражений
#include "arithmetic.h"
#include <gtest.h>

TEST(arithmetic, one_number)
{
	EXPECT_EQ(1, TPostfix("1").CALCULATE());
	EXPECT_EQ(2, TPostfix("2").CALCULATE());
}

TEST(arithmetic, unar_sub)
{
	EXPECT_EQ(-1, TPostfix("-1").CALCULATE());
}

TEST(arithmetic, sum)
{
	EXPECT_EQ(2.0, TPostfix("1+1").CALCULATE());
}

TEST(arithmetic, sub)
{
	EXPECT_EQ(0.0, TPostfix("1-1").CALCULATE());
}

TEST(arithmetic, mul)
{
	EXPECT_EQ(6, TPostfix("2*3").CALCULATE());
}

TEST(arithmetic, div)
{
	EXPECT_EQ(2, TPostfix("4/2").CALCULATE());
}
TEST(arithmetic, op_priority)
{
	EXPECT_EQ(7, TPostfix("1+2*3").CALCULATE());
}

TEST(arithmetic, brackets)
{
	EXPECT_EQ(9, TPostfix("(1+2)*3").CALCULATE());
}

TEST(arithmetic, mested_brackets)
{
	EXPECT_EQ(4, TPostfix("((1+2)/3)*4").CALCULATE());
}

TEST(arithmetic, unary_sub_expression)
{
	EXPECT_EQ(-6, TPostfix("2*(-3)").CALCULATE());
}

TEST(arithmetic, op_order)
{
	EXPECT_EQ(2, TPostfix("2*3-4").CALCULATE());
}

TEST(arithmetic, variable)
{
	TPostfix expr("a");
	expr.add_variable('a', 1.2);
	EXPECT_EQ(1.2, expr.CALCULATE());
}

TEST(arithmetic, stupid_infix_form)
{
	TPostfix a("1");
	ASSERT_NO_THROW(a.CALCULATE());

	a.setInfix("-");
	ASSERT_ANY_THROW(a.CALCULATE());

	a.setInfix("1-");
	ASSERT_ANY_THROW(a.CALCULATE());

	a.setInfix("1-()");
	ASSERT_ANY_THROW(a.CALCULATE());

	a.setInfix("1()");
	ASSERT_ANY_THROW(a.CALCULATE());

	a.setInfix("1(2)");
	ASSERT_ANY_THROW(a.CALCULATE());

	a.setInfix("()");
	ASSERT_ANY_THROW(a.CALCULATE());
}
	