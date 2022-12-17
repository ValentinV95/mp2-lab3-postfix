// тесты для вычисления арифметических выражений

#include "arithmetic.h"
#include <gtest.h>

TEST(TArithmetic, can_create_postfix_from_correct_infix)
{
	string infix = "x+5";
	ASSERT_NO_THROW(TArithmetic post(infix));
}

TEST(TArithmetic, can_create_postfix_from_one_size_correct_infix)
{
	string infix = "x";
	ASSERT_NO_THROW(TArithmetic post_1(infix));
	infix = "1";
	ASSERT_NO_THROW(TArithmetic post_2(infix));
}

TEST(TArithmetic, throws_when_use_space)
{
	string infix = "x +5";
	ASSERT_ANY_THROW(TArithmetic post_1(infix));
	infix = "x+ 5";
	ASSERT_ANY_THROW(TArithmetic post_2(infix));
	infix = " x+5";
	ASSERT_ANY_THROW(TArithmetic post_3(infix));
	infix = "x+5 ";
	ASSERT_ANY_THROW(TArithmetic post_4(infix));
	infix = "(x+y) +1";
	ASSERT_ANY_THROW(TArithmetic post_5(infix));
	infix = "1+ (x+y)";
	ASSERT_ANY_THROW(TArithmetic post_6(infix));
}

TEST(TArithmetic, can_use_brackets)
{
	string infix = "(x+5)";
	ASSERT_NO_THROW(TArithmetic post_1(infix));
	infix = "-(x+5)*2";
	ASSERT_NO_THROW(TArithmetic post_2(infix));
	infix = "-((x+5)*2)-1";
	ASSERT_NO_THROW(TArithmetic post_3(infix));
}

TEST(TArithmetic, throws_when_number_of_opening_and_closing_brackets_does_not_match)
{
	string infix = "(x+1";
	ASSERT_ANY_THROW(TArithmetic post_1(infix));
	infix = "x+1)";
	ASSERT_ANY_THROW(TArithmetic post_2(infix));
	infix = "((x+1)";
	ASSERT_ANY_THROW(TArithmetic post_3(infix));
	infix = "(x+1))";
	ASSERT_ANY_THROW(TArithmetic post_4(infix));
}

TEST(TArithmetic, can_use_exponential_form_without_sign)
{
	string infix = "x+1e1";
	ASSERT_NO_THROW(TArithmetic post(infix));
}

TEST(TArithmetic, can_use_exponential_form_with_plus)
{
	string infix = "x+1e+1";
	ASSERT_NO_THROW(TArithmetic post(infix));
}

TEST(TArithmetic, can_use_exponential_form_with_minus)
{
	string infix = "x+1e-1";
	ASSERT_NO_THROW(TArithmetic post(infix));
}

TEST(TArithmetic, throws_when_use_e_in_variable_name)
{
	string infix = "x+e";
	ASSERT_ANY_THROW(TArithmetic post_1(infix));
	infix = "x+xex";
	ASSERT_ANY_THROW(TArithmetic post_2(infix));
}

TEST(TArithmetic, throws_when_lexem_before_e_is_wrong)
{
	string infix = "x+e-1";
	ASSERT_ANY_THROW(TArithmetic post(infix));
}

TEST(TArithmetic, throws_when_lexem_after_e_is_wrong)
{
	string infix = "x+1e*1";
	ASSERT_ANY_THROW(TArithmetic post_1(infix));
	infix = "x+1ea1";
	ASSERT_ANY_THROW(TArithmetic post_2(infix));
	infix = "x+1e#1";
	ASSERT_ANY_THROW(TArithmetic post_3(infix));
	infix = "x+1e 1";
	ASSERT_ANY_THROW(TArithmetic post_4(infix));
}

TEST(TArithmetic, throws_when_first_lexem_is_wrong)
{
	string infix = "*x";
	ASSERT_ANY_THROW(TArithmetic post_1(infix));
	infix = "&x";
	ASSERT_ANY_THROW(TArithmetic post_2(infix));
	infix = ")x";
	ASSERT_ANY_THROW(TArithmetic post_3(infix));
	infix = "e5";
	ASSERT_ANY_THROW(TArithmetic post_4(infix));
	infix = ".3";
	ASSERT_ANY_THROW(TArithmetic post_5(infix));
}

TEST(TArithmetic, can_create_postfix_with_correct_first_lexem)
{
	string infix = "10";
	ASSERT_NO_THROW(TArithmetic post_1(infix));
	infix = "abc";
	ASSERT_NO_THROW(TArithmetic post_2(infix));
	infix = "-x";
	ASSERT_NO_THROW(TArithmetic post_3(infix));
	infix = "(x+1)";
	ASSERT_NO_THROW(TArithmetic post_4(infix));
}

TEST(TArithmetic, can_create_postfix_with_correct_last_lexem)
{
	string infix = "10";
	ASSERT_NO_THROW(TArithmetic post_1(infix));
	infix = "abc";
	ASSERT_NO_THROW(TArithmetic post_2(infix));
	infix = "(x+1)";
	ASSERT_NO_THROW(TArithmetic post_3(infix));
}

TEST(TArithmetic, throws_when_last_lexem_is_wrong)
{
	string infix = "10+";
	ASSERT_ANY_THROW(TArithmetic post_1(infix));
	infix = "10(";
	ASSERT_ANY_THROW(TArithmetic post_2(infix));
	infix = "10e";
	ASSERT_ANY_THROW(TArithmetic post_3(infix));
	infix = "10.";
	ASSERT_ANY_THROW(TArithmetic post_4(infix));
	infix = "10#";
	ASSERT_ANY_THROW(TArithmetic post_5(infix));
}

TEST(TArithmetic, can_create_postfix_with_correct_next_lexem_after_opening_brackets)
{
	string infix = "(-10)";
	ASSERT_NO_THROW(TArithmetic post_1(infix));
	infix = "(a+1)";
	ASSERT_NO_THROW(TArithmetic post_2(infix));
	infix = "(1+a)";
	ASSERT_NO_THROW(TArithmetic post_3(infix));
	infix = "((1+a)+1)";
	ASSERT_NO_THROW(TArithmetic post_3(infix));
}

TEST(TArithmetic, throws_when_next_lexem_after_opening_brackets_is_wrong)
{
	string infix = "(*10)";
	ASSERT_ANY_THROW(TArithmetic post_1(infix));
	infix = "(e-1)";
	ASSERT_ANY_THROW(TArithmetic post_2(infix));
	infix = "()";
	ASSERT_ANY_THROW(TArithmetic post_3(infix));
	infix = "(#+9)";
	ASSERT_ANY_THROW(TArithmetic post_4(infix));
}

TEST(TArithmetic, can_create_postfix_with_correct_next_lexem_after_closing_brackets)
{
	string infix = "(-10)*x";
	ASSERT_NO_THROW(TArithmetic post_1(infix));
	infix = "(-(-10))";
	ASSERT_NO_THROW(TArithmetic post_2(infix));
}

TEST(TArithmetic, throws_when_next_lexem_after_closing_brackets_is_wrong)
{
	string infix = "(-10)(-10)";
	ASSERT_ANY_THROW(TArithmetic post_1(infix));
	infix = "(-1)x";
	ASSERT_ANY_THROW(TArithmetic post_2(infix));
	infix = "(-1)1";
	ASSERT_ANY_THROW(TArithmetic post_3(infix));
	infix = "(-1)e-1";
	ASSERT_ANY_THROW(TArithmetic post_4(infix));
	infix = "(-1)#";
	ASSERT_ANY_THROW(TArithmetic post_5(infix));
}

TEST(TArithmetic, can_create_postfix_with_correct_next_lexem_after_operation)
{
	string infix = "x/y";
	ASSERT_NO_THROW(TArithmetic post_1(infix));
	infix = "x+-y";
	ASSERT_NO_THROW(TArithmetic post_2(infix));
	infix = "x-1";
	ASSERT_NO_THROW(TArithmetic post_3(infix));
	infix = "x*(-y)";
	ASSERT_NO_THROW(TArithmetic post_4(infix));
}

TEST(TArithmetic, throws_when_next_lexem_after_operation_is_wrong)
{
	string infix = "x+*y";
	ASSERT_ANY_THROW(TArithmetic post_1(infix));
	infix = "x/e-1";
	ASSERT_ANY_THROW(TArithmetic post_2(infix));
	infix = "x*)";
	ASSERT_ANY_THROW(TArithmetic post_3(infix));
	infix = "x-#";
	ASSERT_ANY_THROW(TArithmetic post_4(infix));
}

TEST(TArithmetic, can_create_postfix_with_correct_next_lexem_after_latin_character)
{
	string infix = "x/y";
	ASSERT_NO_THROW(TArithmetic post_1(infix));
	infix = "xy";
	ASSERT_NO_THROW(TArithmetic post_2(infix));
	infix = "(-x)";
	ASSERT_NO_THROW(TArithmetic post_3(infix));
}

TEST(TArithmetic, throws_when_next_lexem_after_latin_character_is_wrong)
{
	string infix = "xe-1";
	ASSERT_ANY_THROW(TArithmetic post_1(infix));
	infix = "x(-1)";
	ASSERT_ANY_THROW(TArithmetic post_2(infix));
	infix = "x1";
	ASSERT_ANY_THROW(TArithmetic post_3(infix));
	infix = "x#";
	ASSERT_ANY_THROW(TArithmetic post_4(infix));
}

TEST(TArithmetic, can_create_postfix_with_correct_next_lexem_after_digit)
{
	string infix = "1/5";
	ASSERT_NO_THROW(TArithmetic post_1(infix));
	infix = "(-1)";
	ASSERT_NO_THROW(TArithmetic post_2(infix));
	infix = "15";
	ASSERT_NO_THROW(TArithmetic post_3(infix));
	infix = "1e-1";
	ASSERT_NO_THROW(TArithmetic post_4(infix));
}

TEST(TArithmetic, throws_when_next_lexem_after_digit_is_wrong)
{
	string infix = "1(-1)";
	ASSERT_ANY_THROW(TArithmetic post_1(infix));
	infix = "1x";
	ASSERT_ANY_THROW(TArithmetic post_2(infix));
	infix = "1#";
	ASSERT_ANY_THROW(TArithmetic post_3(infix));
}

TEST(TArithmetic, can_create_postfix_with_correct_next_lexem_after_point)
{
	string infix = "1.5";
	ASSERT_NO_THROW(TArithmetic post(infix));
}

TEST(TArithmetic, throws_when_next_lexem_after_point_is_wrong)
{
	string infix = "1.x";
	ASSERT_ANY_THROW(TArithmetic post_1(infix));
	infix = "1.e-1";
	ASSERT_ANY_THROW(TArithmetic post_2(infix));
	infix = "1.-1";
	ASSERT_ANY_THROW(TArithmetic post_3(infix));
	infix = "1.#";
	ASSERT_ANY_THROW(TArithmetic post_4(infix));
	infix = "1.(";
	ASSERT_ANY_THROW(TArithmetic post_5(infix));
	infix = "1.)";
	ASSERT_ANY_THROW(TArithmetic post_6(infix));
}

TEST(TArithmetic, can_get_postfix)
{
	string infix = "1+5";
	TArithmetic post(infix);
	EXPECT_EQ("1 5 +", post.GetPostfix());
}

TEST(TArithmetic, can_create_correct_postfix_with_many_unary_minuses)
{
	string infix = "1---5";
	TArithmetic post(infix);
	EXPECT_EQ("1 5 - - -", post.GetPostfix());
}

TEST(TArithmetic, can_create_correct_postfix_with_brackets)
{
	string infix = "1/(1+5)";
	TArithmetic post(infix);
	EXPECT_EQ("1 1 5 + /", post.GetPostfix());
}

TEST(TArithmetic, can_create_correct_postfix_with_many_brackets)
{
	string infix = "-(1/(1+5))";
	TArithmetic post(infix);
	EXPECT_EQ("1 1 5 + / -", post.GetPostfix());
}

TEST(TArithmetic, can_create_correct_postfix_with_exponential_form_constant)
{
	string infix = "1e+10+1e-10";
	TArithmetic post(infix);
	EXPECT_EQ("1e+10 1e-10 +", post.GetPostfix());
}

TEST(TArithmetic, can_create_correct_postfix_with_increasing_priority)
{
	string infix = "1+5*6";
	TArithmetic post(infix);
	EXPECT_EQ("1 5 6 * +", post.GetPostfix());
}

TEST(TArithmetic, can_create_correct_postfix_with_decreasing_priority)
{
	string infix = "1*5-6";
	TArithmetic post(infix);
	EXPECT_EQ("1 5 * 6 -", post.GetPostfix());
}

TEST(TArithmetic, can_create_correct_postfix_with_same_priority)
{
	string infix = "1-5+6";
	TArithmetic post(infix);
	EXPECT_EQ("1 5 - 6 +", post.GetPostfix());
}

TEST(TArithmetic, can_calculate_postfix)
{
	string infix = "1-5+6";
	TArithmetic post(infix);
	EXPECT_EQ(true, abs(2.0 - post.Calculate()) < 0.000000001);
}

TEST(TArithmetic, can_calculate_postfix_with_real_constants)
{
	string infix = "1.2-0.1";
	TArithmetic post(infix);
	EXPECT_EQ(true, abs(1.1 - post.Calculate()) < 0.000000001);
}

TEST(TArithmetic, can_calculate_postfix_with_exponential_form_of_constants)
{
	string infix = "0.2e1+1e-1";
	TArithmetic post(infix);
	EXPECT_EQ(true, abs(2.1 - post.Calculate()) < 0.000000001);
}

TEST(TArithmetic, throws_when_there_is_division_by_zero)
{
	string infix = "1/0";
	TArithmetic post_1(infix);
	ASSERT_ANY_THROW(post_1.Calculate());
	infix = "1/(1-1)";
	TArithmetic post_2(infix);
	ASSERT_ANY_THROW(post_2.Calculate());
}
