// тесты для вычисления арифметических выражений

#include "../gtest/gtest.h"
#include "../include/arithmetic.h"
#include "../src/arithmetic.cpp"

TEST(arithmetic, cant_solve_empty_expression_1)
{
	TPostfix a("");
	ASSERT_ANY_THROW(solve(a));
}

TEST(arithmetic, cant_solve_empty_expression_2)
{
	TPostfix a("()");
	ASSERT_ANY_THROW(solve(a));
}

TEST(arithmetic, can_convert_positive_int_number)
{
	TPostfix a("2");
	EXPECT_DOUBLE_EQ(2.0,solve(a));
}

TEST(arithmetic, can_convert_negative_int_number)
{
	TPostfix a("-2");
	EXPECT_DOUBLE_EQ(-2.0, solve(a));
}

TEST(arithmetic, can_convert_double)
{
	TPostfix a("5.7");
	EXPECT_DOUBLE_EQ(5.7, solve(a));
}

TEST(arithmetic, can_convert_double_in_science_format_1)
{
	TPostfix a("5.7E4");
	EXPECT_DOUBLE_EQ(57000.0, solve(a));
}

TEST(arithmetic, can_convert_double_in_science_format_2)
{
	TPostfix a("5.7e-1");
	EXPECT_DOUBLE_EQ(0.57, solve(a));
}

TEST(arithmetic, cant_convert_double_with_extra_sign)
{
	ASSERT_ANY_THROW(TPostfix a("5.7.4"));
}

TEST(arithmetic, cant_convert_double_in_science_format_with_extra_sign_)
{
	ASSERT_ANY_THROW(TPostfix a("5.7E2E3"));
}

TEST(arithmetic, can_perform_arifmetic_operation_1)
{
	TPostfix a("2+5-3*12/6");
	EXPECT_DOUBLE_EQ(2 + 5 - 3 * 12 / 6, solve(a));
}

TEST(arithmetic, can_perform_arifmetic_operation_2)
{
	TPostfix a("log(4^sqrt(2))");
	EXPECT_DOUBLE_EQ(log(pow(4,sqrt(2))), solve(a));
}

TEST(arithmetic, brackets_change_queue_of_operation)
{
	TPostfix a("2*(4+(-1))");
	EXPECT_DOUBLE_EQ(2*(4+(-1)), solve(a));
}

TEST(arithmetic, can_perform_trigonometric_function)
{
	TPostfix a("sin(cos(-2))");
	EXPECT_DOUBLE_EQ(sin(cos(-2)), solve(a));
}

TEST(arithmetic, twice_negative_is_equal_to_source_one)
{
	TPostfix a("-(-2)");
	EXPECT_DOUBLE_EQ(2, solve(a));
}

TEST(arithmetic, wronge_open_brackets_throw_exception_1)
{
	ASSERT_ANY_THROW({ TPostfix a("3-()"); solve(a); });
}

TEST(arithmetic, wronge_open_brackets_throw_exception_2)
{
	ASSERT_ANY_THROW({ TPostfix a("3-()"); solve(a); });
}

TEST(arithmetic, wronge_close_brackets_throw_exception_1)
{
	ASSERT_ANY_THROW({ TPostfix a("3-()"); solve(a); });
}

TEST(arithmetic, wronge_close_brackets_throw_exception_2)
{
	ASSERT_ANY_THROW({ TPostfix a("3-()"); solve(a); });
}

TEST(arithmetic, operation_with_wronge_brackets_throw_exception)
{
	ASSERT_ANY_THROW({ TPostfix a("3-()"); solve(a); });
}

TEST(arithmetic, operation_with_not_enough_operand_throw_exception_1)
{
	ASSERT_ANY_THROW({ TPostfix a("3-()"); solve(a); });
}

TEST(arithmetic, operation_with_not_enough_operand_throw_exception_2)
{
	ASSERT_ANY_THROW({ TPostfix a("3-()"); solve(a); });
}

TEST(arithmetic, operation_with_not_enough_operand_throw_exception_3)
{
	ASSERT_ANY_THROW({ TPostfix a("3-()"); solve(a); });
}

TEST(arithmetic, can_perform_one_variable)
{
	variables.emplace("x", 5.0);
	TPostfix a("x-x^2");
	ASSERT_DOUBLE_EQ(5.0 - pow(5.0,2),solve(a));
}

TEST(arithmetic, can_perform_many_variable)
{
	variables.emplace("x1", 5.0);
	variables.emplace("x2", 25.0);
	variables.emplace("x3", 53.0);
	TPostfix a("x3-x1^2/x2");
	ASSERT_DOUBLE_EQ(53.0 - pow(5.0, 2)/25, solve(a));
}

TEST(arithmetic, undefined_operation_throw_exception)
{
	ASSERT_ANY_THROW({ TPostfix a("3?5"); solve(a); });
}