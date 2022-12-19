// тесты для вычисления арифметических выражений
#include <gtest.h>
#include"arithmetic.h"


TEST(TPostfix, can_create_correct_expression)
{
	string expr("a+b");
	ASSERT_NO_THROW(TPostfix arifm(expr));
}

TEST(TPostfix, cant_create_uncorrect_expression)
{
	string expr("a++b");
	ASSERT_ANY_THROW(TPostfix arifm(expr));
}

TEST(TPostfix, cant_create_expression_with_only_brackets)
{
	string expr("()");
	ASSERT_ANY_THROW(TPostfix arifm(expr));
}

TEST(TPostfix, cant_create_expression_with_only_operation)
{
	string expr("+");
	ASSERT_ANY_THROW(TPostfix arifm(expr));
}

TEST(TPostfix, cant_calculate_expression_with_only_operation)
{
	string expr("sin()");
	TPostfix arifm(expr);
	ASSERT_ANY_THROW(arifm.calculate());
}

TEST(TPostfix, can_create_expression_with_exponential_constant)
{
	string expr("a+3.123e-10");
	ASSERT_NO_THROW(TPostfix arifm(expr));
}

TEST(TPostfix, cant_create_expression_with_uncorrect_exponential_constant)
{
	string expr("a+3.123e-");
	ASSERT_ANY_THROW(TPostfix arifm(expr));
}

TEST(TPostfix, cant_create_expression_with_uncorrect_brackets)
{
	string expr("a+b)");
	ASSERT_ANY_THROW(TPostfix arifm(expr));
	string expr1("(a+b");
	ASSERT_ANY_THROW(TPostfix arifm(expr1));
	string expr2("(a+b))");
	ASSERT_ANY_THROW(TPostfix arifm(expr2));
	string expr3("((a+b)");
	ASSERT_ANY_THROW(TPostfix arifm(expr3));
	string expr4("a+b+()");
	ASSERT_ANY_THROW(TPostfix arifm(expr4));
}

TEST(TPostfix, can_create_expression_with_function)
{
	string expr("sin(a)+b");
	ASSERT_NO_THROW(TPostfix arifm(expr));
}

TEST(TPostfix, cant_create_expression_with_uncorrect_function)
{
	string expr("sxin(a)+b");
	ASSERT_ANY_THROW(TPostfix arifm(expr));
}

TEST(TPostfix, can_translate_in_RPN)
{
	string expr("a+b");
	TPostfix arifm(expr);
	string exp_expr("ab+");
	EXPECT_EQ(exp_expr, arifm.getPostfixStr());
}

TEST(TPostfix, translate_saves_priority )
{
	string expr("a+b*c");
	TPostfix arifm(expr);
	string exp_expr("abc*+");
	EXPECT_EQ(exp_expr, arifm.getPostfixStr());
}

TEST(TPostfix, RPN_havent_brackets )
{
	string expr("(a+b)*c");
	TPostfix arifm(expr);
	string exp_expr("ab+c*");
	EXPECT_EQ(exp_expr, arifm.getPostfixStr());
}

TEST(TPostfix, correctly_apply_operations)
{
	string expr("2+2*2");
	TPostfix arifm(expr);
	EXPECT_EQ(arifm.calculate(), 6.0);
}

TEST(TPostfix, correctly_handles_minus)
{
	string expr("3---1");
	TPostfix arifm(expr);
	EXPECT_EQ(arifm.calculate(), 2.0);
}

TEST(TPostfix, can_use_function)
{
	string expr("sin(0)/2");
	TPostfix arifm(expr);
	EXPECT_EQ(arifm.calculate(), 0.0);
}

TEST(TPostfix, can_use_function_in_function)
{
	string expr("cos(sin(0))/2");
	TPostfix arifm(expr);
	EXPECT_EQ(arifm.calculate(), 0.5);
}

TEST(TPostfix, correcty_handle_priorities)
{
	string expr("-10^2");
	TPostfix arifm(expr);
	EXPECT_EQ(arifm.calculate(), -100.0);
	string expr1("(-10)^2");
	TPostfix arifm1(expr1);
	EXPECT_EQ(arifm1.calculate(), 100.0);
}

TEST(TPostfix, correcty_handle_exp_form_of_num)
{
	string expr("5e-5");
	TPostfix arifm(expr);
	EXPECT_EQ(arifm.calculate(), 0.00005);
}