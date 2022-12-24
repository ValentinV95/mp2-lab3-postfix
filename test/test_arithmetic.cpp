// тесты для вычисления арифметических выражений
#include "arithmetic.h"
#include <gtest.h>

TEST(arithmetic, can_solve_correctly)
{
	double d;
	TPostfix a("1");//works
	EXPECT_EQ(a.CALCULATE(),1.0);

	a.set_infix("-1");//works unar sub
	EXPECT_EQ(a.CALCULATE(), -1.0);

	a.set_infix("1+1");////works add
	EXPECT_EQ(a.CALCULATE(), 2.0);

	a.set_infix("1-1");//works sub
	EXPECT_EQ(!(fabs(a.CALCULATE())< 10.e-16), 0);

	a.set_infix("1*3");//works mul
	EXPECT_EQ(a.CALCULATE(), 3.0);

	a.set_infix("1/3");//works div
	EXPECT_EQ(a.CALCULATE(), 1.0/3.0);

	a.set_infix("1--1");//works sub unar sub
	EXPECT_EQ(a.CALCULATE(), 2.0);

	a.set_infix("1---1");//works any times unar sub
	EXPECT_EQ(a.CALCULATE(), 0.0);

	a.set_infix("1+-1");//works add unar sub
	EXPECT_EQ(a.CALCULATE(), 0.0);

	a.set_infix("1*-3");//works mul unar sub
	EXPECT_EQ(a.CALCULATE(), -3.0);

	a.set_infix("1/-3");//works div unar sub
	EXPECT_EQ(a.CALCULATE(), -1.0 / 3.0);

	a.set_infix("-1-2+3*4/5");//works combination of unar,add,sub,mul and div (operations)
	EXPECT_EQ(fabs(a.CALCULATE()+0.6)<10.e-16, 1);

	a.set_infix("9/3/3");//solve from left to right priority
	EXPECT_EQ(fabs(a.CALCULATE() - 1) < 10.e-16, 1);

	a.set_infix("(1)");//works with bracket
	EXPECT_EQ(a.CALCULATE(), 1.0);

	a.set_infix("(-1)");//works with bracket unar sub
	EXPECT_EQ(a.CALCULATE(), -1.0);

	a.set_infix("(--1)");//works with bracket unar unar sub
	EXPECT_EQ(a.CALCULATE(), 1.0);

	a.set_infix("1-(1)");//works operations with bracket
	EXPECT_EQ(a.CALCULATE(), 0.0);

	a.set_infix("1-(-1)");//works operations with bracket with unar sub
	EXPECT_EQ(a.CALCULATE(), 2.0);

	a.set_infix("1-(--1)");//works operations with bracket with unar unar sub
	EXPECT_EQ(a.CALCULATE(), 0.0);

	a.set_infix("(1-1)");//works in bracket
	EXPECT_EQ(a.CALCULATE(), 0.0);

	a.set_infix("2*(1-2)");//works priority with bracket
	EXPECT_EQ(a.CALCULATE(), -2.0);

	a.set_infix("1-((((1))))");//works with any times bracket
	EXPECT_EQ(a.CALCULATE(), 0.0);

	a.set_infix("-(1+(2*3/4-(--8*3)))-1");//works with any operations with bracket
	d = -(1.0+(2.0*3.0/4.0-(8.0*3)))-1.0;
	EXPECT_EQ((fabs(a.CALCULATE()-d) < 10.e-16), 1);

	a.set_infix("957823.0");//works with any const before 6 digits in easy form
	EXPECT_EQ((fabs(a.CALCULATE() - 957823.0) < 10.e-16), 1);

	//Because the getline function or the cin function
	//automatically converts a constant to the normal double form
	//if it has more than 6 digits

	a.set_infix("6.2349e+46");//works with any const in normal form
	EXPECT_EQ((fabs(a.CALCULATE() - 6.2349e+46) < 10.e-16), 1);

	a.set_infix("72.1e+3--2.3*(7.e-3/2.13e-5+.3)-1.");//It works correctly in any case if there are no logical errors in the tokens
	d = 72.1e+3+2.3 * (7.e-3 / 2.13e-5 + .3) - 1.;
	EXPECT_EQ((fabs(a.CALCULATE() - d) < 10.e-16), 1);
}
TEST(arithmetic, can_CALCULATE_any_times)
{
	TPostfix a("1+2*((3/4))");
	double check = 0;
	ASSERT_NO_THROW(check = a.CALCULATE() + a.CALCULATE() + a.CALCULATE() + a.CALCULATE() + a.CALCULATE() + a.CALCULATE() + a.CALCULATE() + a.CALCULATE());
}
TEST(arithmetic, can_ShowPostfix_any_times)
{
	TPostfix a("1+2*((3/4))");
	string check;
	ASSERT_NO_THROW(check = a.showP() + a.showP() + a.showP() + a.showP() + a.showP() + a.showP() + a.showP() + a.showP());
}
TEST(arithmetic, correct_size_of_lexems)
{
	string s = "1";
	TPostfix a(s);
	int check = 1;
	for (size_t i = 0, j = 1; i < 20; i++, j += 2)
	{
		EXPECT_EQ(a.get_size(), j);
		s += "+1";
		a.set_infix(s);
	}
}
TEST(arithmetic, throw_exception_if_bad_infix_form)
{
	TPostfix a("1");
	ASSERT_NO_THROW(a.CALCULATE());

	a.set_infix("-");
	ASSERT_ANY_THROW(a.CALCULATE());

	a.set_infix("1-");
	ASSERT_ANY_THROW(a.CALCULATE());

	a.set_infix("1-()");
	ASSERT_ANY_THROW(a.CALCULATE());

	a.set_infix("1()");
	ASSERT_ANY_THROW(a.CALCULATE());

	a.set_infix("1(2)");
	ASSERT_ANY_THROW(a.CALCULATE());

	a.set_infix("()");
	ASSERT_ANY_THROW(a.CALCULATE());

	a.set_infix("()3");
	ASSERT_ANY_THROW(a.CALCULATE());

	a.set_infix("()3-");
	ASSERT_ANY_THROW(a.CALCULATE());

	a.set_infix("(-)");
	ASSERT_ANY_THROW(a.CALCULATE());

	a.set_infix("/(-)*");
	ASSERT_ANY_THROW(a.CALCULATE());

	a.set_infix("(");
	ASSERT_ANY_THROW(a.CALCULATE());

	a.set_infix(")");
	ASSERT_ANY_THROW(a.CALCULATE());

	a.set_infix("((");
	ASSERT_ANY_THROW(a.CALCULATE());

	a.set_infix("))");
	ASSERT_ANY_THROW(a.CALCULATE());

	a.set_infix("(()");
	ASSERT_ANY_THROW(a.CALCULATE());

	a.set_infix("())");
	ASSERT_ANY_THROW(a.CALCULATE());

	a.set_infix(")(");
	ASSERT_ANY_THROW(a.CALCULATE());

	a.set_infix("()())(");
	ASSERT_ANY_THROW(a.CALCULATE());

	a.set_infix("");
	ASSERT_ANY_THROW(a.CALCULATE());

	a.set_infix("A+B");
	ASSERT_ANY_THROW(a.CALCULATE());

	a.set_infix("*/(+-AB( _ )BB-");
	ASSERT_ANY_THROW(a.CALCULATE());

	a.set_infix(" ");
	ASSERT_ANY_THROW(a.CALCULATE());
}
