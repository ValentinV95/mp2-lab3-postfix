// тесты для вычисления арифметических выражений

#include "arithmetic.h"
#include <gtest.h>


TEST(ArithmeticExpression, can_create_an_expression_from_a_correct_string)
{
	string infix = "a+b";
	EXPECT_NO_THROW(ArithmeticExpression expression(infix));
}

TEST(ArithmeticExpression, throws_when_create_an_expression_from_a_incorrect_string)
{
	string infix = "a++b";
	EXPECT_ANY_THROW(ArithmeticExpression expression(infix));
}

TEST(ArithmeticExpression, throws_when_number_of_opening_and_closing_brackets_does_not_match)
{
	string infix = "(a+1";
	ASSERT_ANY_THROW(ArithmeticExpression expression1(infix));
	infix = "a+1)";
	ASSERT_ANY_THROW(ArithmeticExpression expression2(infix));
	infix = "((a+1)";
	ASSERT_ANY_THROW(ArithmeticExpression expression3(infix));
	infix = "(a+1))";
	ASSERT_ANY_THROW(ArithmeticExpression expression4(infix));
}

TEST(ArithmeticExpression, can_get_the_infix_form_of_the_expression)
{
	ArithmeticExpression expression("a+b");
	EXPECT_EQ(expression.GetInfix(), "a+b");
}

TEST(ArithmeticExpression, can_use_exponential_form_without_sign)
{
	string infix = "a+1e1";
	ASSERT_NO_THROW(ArithmeticExpression expression(infix));
}

TEST(ArithmeticExpression, can_use_exponential_form_with_plus)
{
	string infix = "a+1e+1";
	ASSERT_NO_THROW(ArithmeticExpression expression(infix));
}

TEST(ArithmeticExpression, can_use_exponential_form_with_minus)
{
	string infix = "a+1e-1";
	ASSERT_NO_THROW(ArithmeticExpression expression(infix));
}

TEST(ArithmeticExpression, throws_when_lexem_after_e_is_wrong)
{
	string infix = "a+1e*1";
	ASSERT_ANY_THROW(ArithmeticExpression expression_1(infix));
	infix = "a+1ea1";
	ASSERT_ANY_THROW(ArithmeticExpression expression_2(infix));
	infix = "a+1e#1";
	ASSERT_ANY_THROW(ArithmeticExpression expression_3(infix));
	infix = "a+1e 1";
	ASSERT_ANY_THROW(ArithmeticExpression expression_4(infix));
}

TEST(ArithmeticExpression, throws_when_first_lexem_is_wrong)
{
	string infix = "*a";
	ASSERT_ANY_THROW(ArithmeticExpression expression_1(infix));
	infix = "&a";
	ASSERT_ANY_THROW(ArithmeticExpression expression_2(infix));
	infix = ")a";
	ASSERT_ANY_THROW(ArithmeticExpression expression_3(infix));
	infix = "e5";
	ASSERT_ANY_THROW(ArithmeticExpression expression_4(infix));
}

TEST(ArithmeticExpression, can_create_expression_with_correct_first_lexem)
{
	string infix = "10";
	ASSERT_NO_THROW(ArithmeticExpression expression_1(infix));
	infix = "a+b+c";
	ASSERT_NO_THROW(ArithmeticExpression expression_2(infix));
	infix = "-a";
	ASSERT_NO_THROW(ArithmeticExpression expression_3(infix));
	infix = "(a+1)";
	ASSERT_NO_THROW(ArithmeticExpression expression_4(infix));
}

TEST(ArithmeticExpression, can_create_expression_with_correct_last_lexem)
{
	string infix = "10";
	ASSERT_NO_THROW(ArithmeticExpression expression_1(infix));
	infix = "a+b+c";
	ASSERT_NO_THROW(ArithmeticExpression expression_2(infix));
	infix = "(a+1)";
	ASSERT_NO_THROW(ArithmeticExpression expression_3(infix));
}

TEST(ArithmeticExpression, throws_when_last_lexem_is_wrong)
{
	string infix = "10+";
	ASSERT_ANY_THROW(ArithmeticExpression expression_1(infix));
	infix = "10(";
	ASSERT_ANY_THROW(ArithmeticExpression expression_2(infix));
	infix = "10e";
	ASSERT_ANY_THROW(ArithmeticExpression expression_3(infix));
	infix = "10.";
	ASSERT_ANY_THROW(ArithmeticExpression expression_4(infix));
	infix = "10#";
	ASSERT_ANY_THROW(ArithmeticExpression expression_5(infix));
}

TEST(ArithmeticExpression, can_create_expression_with_correct_next_lexem_after_opening_brackets)
{
	string infix = "(-10)";
	ASSERT_NO_THROW(ArithmeticExpression expression_1(infix));
	infix = "(a+1)";
	ASSERT_NO_THROW(ArithmeticExpression expression_2(infix));
	infix = "(1+a)";
	ASSERT_NO_THROW(ArithmeticExpression expression_3(infix));
	infix = "((1+a)+1)";
	ASSERT_NO_THROW(ArithmeticExpression expression_3(infix));
}

TEST(ArithmeticExpression, throws_when_next_lexem_after_opening_brackets_is_wrong)
{
	string infix = "(*10)";
	ASSERT_ANY_THROW(ArithmeticExpression expression_1(infix));
	infix = "()";
	ASSERT_ANY_THROW(ArithmeticExpression expression_3(infix));
	infix = "(#+9)";
	ASSERT_ANY_THROW(ArithmeticExpression expression_4(infix));
}

TEST(ArithmeticExpression, can_create_expression_with_correct_next_lexem_after_closing_brackets)
{
	string infix = "(-10)*a";
	ASSERT_NO_THROW(ArithmeticExpression expression_1(infix));
	infix = "(-(-10))";
	ASSERT_NO_THROW(ArithmeticExpression expression_2(infix));
}

TEST(ArithmeticExpression, throws_when_next_lexem_after_closing_brackets_is_wrong)
{
	string infix = "(-10)(-10)";
	ASSERT_ANY_THROW(ArithmeticExpression expression_1(infix));
	infix = "(-1)a";
	ASSERT_ANY_THROW(ArithmeticExpression expression_2(infix));
	infix = "(-1)1";
	ASSERT_ANY_THROW(ArithmeticExpression expression_3(infix));
	infix = "(-1)e-1";
	ASSERT_ANY_THROW(ArithmeticExpression expression_4(infix));
	infix = "(-1)#";
	ASSERT_ANY_THROW(ArithmeticExpression expression_5(infix));
}

TEST(ArithmeticExpression, can_create_expression_with_correct_next_lexem_after_operation)
{
	string infix = "a/b";
	ASSERT_NO_THROW(ArithmeticExpression expression_1(infix));
	infix = "a+-b";
	ASSERT_NO_THROW(ArithmeticExpression expression_2(infix));
	infix = "a-1";
	ASSERT_NO_THROW(ArithmeticExpression expression_3(infix));
	infix = "a*(-b)";
	ASSERT_NO_THROW(ArithmeticExpression expression_4(infix));
}

TEST(ArithmeticExpression, throws_when_next_lexem_after_operation_is_wrong)
{
	string infix = "a+*b";
	ASSERT_ANY_THROW(ArithmeticExpression expression_1(infix));
	infix = "a*)";
	ASSERT_ANY_THROW(ArithmeticExpression expression_3(infix));
	infix = "b-#";
	ASSERT_ANY_THROW(ArithmeticExpression expression_4(infix));
}

TEST(ArithmeticExpression, can_create_expression_with_correct_next_lexem_after_point)
{
	string infix = "1.5";
	ASSERT_NO_THROW(ArithmeticExpression expression(infix));
}

TEST(ArithmeticExpression, throws_when_next_lexem_after_point_is_wrong)
{
	string infix = "1.a";
	ASSERT_ANY_THROW(ArithmeticExpression expression_1(infix));
	infix = "1.e-1";
	ASSERT_ANY_THROW(ArithmeticExpression expression_2(infix));
	infix = "1.#";
	ASSERT_ANY_THROW(ArithmeticExpression expression_4(infix));
	infix = "1.(";
	ASSERT_ANY_THROW(ArithmeticExpression expression_5(infix));
	infix = "1.)";
	ASSERT_ANY_THROW(ArithmeticExpression expression_6(infix));
}

TEST(ArithmeticExpression, can_get_the_postfix_form_of_the_correct_expression)
{
	ArithmeticExpression expression("a+b");
	EXPECT_EQ(expression.GetPostfix(), "|a|b|+|");
}

TEST(ArithmeticExpression, can_create_correct_postfix_form_with_many_unary_minuses)
{
	string infix = "1---5";
	ArithmeticExpression expression(infix);
	EXPECT_EQ("|1|5|~|~|-|", expression.GetPostfix());
}

TEST(ArithmeticExpression, can_create_correct_posfix_form_with_brackets_in_expression)
{
	string infix = "1/(1+5)";
	ArithmeticExpression expression(infix);
	EXPECT_EQ("|1|1|5|+|/|", expression.GetPostfix());
}

TEST(ArithmeticExpression, can_create_correct_postfix_form_with_many_brackets_in_expression)
{
	string infix = "-(1/(1+5))";
	ArithmeticExpression expression(infix);
	EXPECT_EQ("|1|1|5|+|/|~|", expression.GetPostfix());
}

TEST(ArithmeticExpression, can_create_correct_expression_with_exponential_form_constant)
{
	string infix = "1e+10+1e-10";
	ArithmeticExpression expression(infix);
	EXPECT_EQ("|1e+10|1e-10|+|", expression.GetPostfix());
}

TEST(ArithmeticExpression, can_create_correct_expression_with_same_priority)
{
	string infix = "1-5+6";
	ArithmeticExpression expression(infix);
	EXPECT_EQ("|1|5|-|6|+|", expression.GetPostfix());
}

TEST(ArithmeticExpression, can_get_operands_of_the_expression)
{
	ArithmeticExpression expression("a+b");
	EXPECT_EQ(expression.GetOperands()[0], "a");
	EXPECT_EQ(expression.GetOperands()[1], "b");
}

TEST(ArithmeticExpression, can_calculate_the_value_of_the_expression)
{
	ArithmeticExpression expression("a+b+5");
	map<string, double> values;
	values["a"] = 2;
	values["b"] = 3;
	EXPECT_EQ(10, expression.Calculate(values));
}

TEST(ArithmeticExpression, throws_when_there_is_division_by_zero)
{
	string infix = "1/0";
	ArithmeticExpression post_1(infix);
	map<string, double> values;
	ASSERT_ANY_THROW(post_1.Calculate(values));
}

TEST(ArithmeticExpression, can_calculate_the_value_of_the_expression_with_real_constants)
{
	string infix = "1.0-.5";
	ArithmeticExpression post(infix);
	map<string, double> values;
	EXPECT_EQ(true, abs(0.5 - post.Calculate(values)) < 0.000000001);
}

TEST(ArithmeticExpression, can_calculate_the_value_of_the_expression_with_exponential_form_of_constants)
{
	string infix = ".5e1+1e-1";
	ArithmeticExpression post(infix);
	map<string, double> values;
	EXPECT_EQ(true, abs(5.1 - post.Calculate(values)) < 0.000000001);
}