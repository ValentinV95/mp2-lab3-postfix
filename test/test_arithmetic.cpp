// тесты для вычисления арифметических выражений

#include "arithmetic.h"
#include <gtest.h>

TEST(TPostfix, throw_when_invalid_symbol_in_expression)
{
	ASSERT_ANY_THROW(TPostfix("3#9"));
}

//Operations
TEST(TPostfix, throw_when_expression_starts_by_binary_operation)
{
	ASSERT_ANY_THROW(TPostfix("+3+9"));
	ASSERT_ANY_THROW(TPostfix("/3+9"));
	ASSERT_ANY_THROW(TPostfix("*3+9"));
}

TEST(TPostfix, throw_when_expression_ends_by_binary_operation)
{
	ASSERT_ANY_THROW(TPostfix("3+9+"));
	ASSERT_ANY_THROW(TPostfix("3+9/"));
	ASSERT_ANY_THROW(TPostfix("3+9*"));
	ASSERT_ANY_THROW(TPostfix("3+9-"));
}

TEST(TPostfix, throw_when_two_binary_operation_in_a_row)
{
	ASSERT_ANY_THROW(TPostfix("3+/9"));
	ASSERT_ANY_THROW(TPostfix("3+*9"));
	ASSERT_ANY_THROW(TPostfix("3++9"));
}

TEST(TPostfix, throw_when_after_close_bracket_no_operation_or_end_of_expression)
{
	ASSERT_ANY_THROW(TPostfix("(3+9)2"));
}

//Brackets
TEST(TPostfix, throw_when_empty_brackets_in_expression)
{
	ASSERT_ANY_THROW(TPostfix("1+()+2"));
	ASSERT_ANY_THROW(TPostfix("sin()+2"));
}

TEST(TPostfix, throw_when_after_function_name_not_open_bracket)
{
	ASSERT_ANY_THROW(TPostfix("(sin)+2"));
}

TEST(TPostfix, throw_when_open_bracket_and_close_braket_count_is_not_equal)
{
	ASSERT_ANY_THROW(TPostfix("(9*2))+2"));
	ASSERT_ANY_THROW(TPostfix("((9*2)+2"));
}

//Wrong number format
TEST(TPostfix, throw_when_double_dot_in_number)
{
	ASSERT_ANY_THROW(TPostfix("9..3"));
}

TEST(TPostfix, throw_when_double_dot_in_number_in_function)
{
	ASSERT_ANY_THROW(TPostfix("sin(9..3)"));
	ASSERT_ANY_THROW(TPostfix("17.8+9..3"));
}

TEST(TPostfix, throw_when_double_dot_in_number_in_exponential_form)
{
	ASSERT_ANY_THROW(TPostfix("17e+9..3"));
	ASSERT_ANY_THROW(TPostfix("17..8e+9.3"));
}

//Wrong number format
TEST(TPostfix, throw_when_two_e_in_number)
{
	ASSERT_ANY_THROW(TPostfix("9ee-3"));
	ASSERT_ANY_THROW(TPostfix("sin(9ee-3)"));
	ASSERT_ANY_THROW(TPostfix("17.8+9ee+3"));
}

TEST(TPostfix, throw_when_no_plus_or_minus_after_e)
{
	ASSERT_ANY_THROW(TPostfix("9e*3"));
	ASSERT_ANY_THROW(TPostfix("sin(9e*3)"));
	ASSERT_ANY_THROW(TPostfix("17.8+9e/3"));
}

//Polish notation
TEST(TPostfix, no_throw_when_simple_expression_is_correct)
{
	ASSERT_NO_THROW(TPostfix("9*3"));
	ASSERT_NO_THROW(TPostfix("17.8+9e-3"));
}

TEST(TPostfix, no_throw_when_simple_expression_with_function_is_correct)
{
	ASSERT_NO_THROW(TPostfix("sin(9*3)"));
}

TEST(TPostfix, no_throw_when_simple_expression_with_exponential_form_is_correct)
{
	ASSERT_NO_THROW(TPostfix("17.8+9e-3"));
	ASSERT_NO_THROW(TPostfix("17.8+9e-3e+1"));
}

//Calculation chek
TEST(TPostfix, minus_exponential_form_chek)
{
	TPostfix p1("9e-2");
	EXPECT_EQ(p1.Calculate(),0.09);
}

TEST(TPostfix, plus_exponential_form_chek)
{
	TPostfix p2("9e+2");
	EXPECT_EQ(p2.Calculate(), 900);
}

TEST(TPostfix,can_get_simple_integer_number)
{
	TPostfix p("1");
	EXPECT_EQ(p.Calculate(),1);
}

TEST(TPostfix, can_get_simple_floating_point_number_1)
{
	TPostfix p1("1.903");
	EXPECT_EQ(p1.Calculate(), 1.903);

}

TEST(TPostfix, can_get_simple_floating_point_number_2)
{
	TPostfix p2("0100.93");
	EXPECT_EQ(p2.Calculate(), 100.93);
}
TEST(TPostfix, double_exponential_form_chek)
{

	TPostfix p("1e-1e+1");
	EXPECT_EQ(p.Calculate(), 1 / pow(10, 10));
}

TEST(TPostfix, can_calculate_simple_correct_expression)
{
	TPostfix p("1.2+6");
	EXPECT_EQ(p.Calculate(),1.2 + 6);
}

TEST(TPostfix, can_calculate_simple_correct_expression_with_brackets)
{
	TPostfix p("(1.2+6)/(13.6-9)");
	EXPECT_EQ(p.Calculate(), (1.2 + 6) / (13.6 - 9));
}

TEST(TPostfix, can_calculate_simple_correct_expression_with_two_unary_minus_in_brackets)
{
	TPostfix p("1/(--2)");
	EXPECT_EQ(p.Calculate(), 0.5);
}

TEST(TPostfix, can_calculate_simple_correct_expression_with_few_unary_minus_in_a_row)
{
	TPostfix p2("---2");
	EXPECT_EQ(p2.Calculate(),-2.0);
}

TEST(TPostfix, can_calculate_simple_correct_expression_with_few_unary_minus_after_operation)
{
	TPostfix p1("1--2");
	EXPECT_EQ(p1.Calculate(), 3.0);
}

TEST(TPostfix, can_calculate_simple_correct_expression_with_double_unary_minus_in_start_of_row)
{
	TPostfix p("--2");
	EXPECT_EQ(p.Calculate(),2.0);
}

TEST(TPostfix, can_calculate_simple_correct_expression_with_unary_minus_after_division_operation)
{
	TPostfix p("1/-2");
	EXPECT_EQ(p.Calculate(), -0.5);
}

TEST(TPostfix, can_calculate_simple_correct_expression_with_unary_minus_in_start_of_row)
{
	TPostfix p("-2");
	EXPECT_EQ(p.Calculate(),-2);
}

TEST(TPostfix, can_calculate_hard_correct_expression_with_unary_minus)
{
	TPostfix p("10.0-(-10.0)");
	EXPECT_EQ(p.Calculate(),20.0);
}

TEST(TPostfix, can_calculate_simple_correct_expression_with_function)
{
	TPostfix p("sin(3)");
	EXPECT_EQ(p.Calculate(), sin(3));
}

TEST(TPostfix, can_calculate_simple_correct_expression_with_unary_minus_in_function)
{
	TPostfix p("sin(-3)");
	EXPECT_EQ(p.Calculate(), sin(-3));
}

TEST(TPostfix, can_calculate_simple_correct_expression_with_expression_in_function)
{
	TPostfix p("sin(3+11.9/2.01)");
	EXPECT_EQ(p.Calculate(), sin(3 + 11.9 / 2.01));
}


TEST(TPostfix, can_get_e_constant)
{
	TPostfix p("e");
	EXPECT_EQ(p.Calculate(), 2.7182818284);
}

TEST(TPostfix, can_get_pi_constant)
{
	TPostfix p("pi");
	EXPECT_EQ(p.Calculate(), 3.141592653589793);
}


TEST(TPostfix, can_calculate_simple_correct_expression_with_e_constant)
{
	TPostfix p("e*2");
	EXPECT_EQ(p.Calculate(), 2.7182818284*2);
}

TEST(TPostfix, can_calculate_simple_correct_expression_with_pi_constant)
{
	TPostfix p("pi+1");
	EXPECT_EQ(p.Calculate(), 3.141592653589793+1);
}
