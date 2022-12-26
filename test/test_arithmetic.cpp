// тесты для вычисления арифметических выражени
#include <gtest.h>
#include <arithmetic.h>

TEST(Arithmetic, support_all_correct_form_number)
{
	std::string example = "1";
	ASSERT_NO_THROW(Arithmetic try1(example));//assert no throw
//	ASSERT_ANY_THROW();//Кинется ошибка
//	EXPECT_EQ();//Принимает 2 параметра, должны быть одинаковыми
//	EXPECT_NE();//Принимает 2 параметра, должны быть не равны
}
TEST(Arithmetic, throw_when_zero_devision)
{
	std::string example = "1+(4/(1-1))";
	Arithmetic try1(example);
	ASSERT_ANY_THROW(try1.Calculate());
}
TEST(Arithmetic, support_brackets)
{
	std::string example = "(8+1)";
	ASSERT_NO_THROW(Arithmetic try1(example));
	std::string example2 = "(1*2*3)";
	ASSERT_NO_THROW(Arithmetic try2(example2));
}
TEST(Arithmetic, can_calculate)
{
	std::string example = "7+3+8/8-1";
	Arithmetic try1(example);
	double res = try1.Calculate();
	EXPECT_EQ(res, 10);
}


TEST(Arithmetic, throw_when_number_before_open_bracket)
{
	std::string example = "2(1+4)";
	ASSERT_ANY_THROW(Arithmetic case1(example));
}
TEST(Arithmetic, throw_when_var_before_open_bracket)
{
	std::string example = "a(1+4)";
	ASSERT_ANY_THROW(Arithmetic case1(example));
}
TEST(Arithmetic, throw_when_close_bracket_before_open_bracket)
{
	std::string example = ")(1+4)";
	ASSERT_ANY_THROW(Arithmetic case1(example));
}
TEST(Arithmetic, throw_when_digit_before_unary)
{
	std::string example = "2~1";
	ASSERT_ANY_THROW(Arithmetic case1(example));
}
TEST(Arithmetic, throw_when_Var_before_unary)
{
	std::string example = "a~1";
	ASSERT_ANY_THROW(Arithmetic case1(example));
}
TEST(Arithmetic, throw_when_close_bracket_before_unary)
{
	std::string example = "(~";
	ASSERT_ANY_THROW(Arithmetic case1(example));
}
TEST(Arithmetic, throw_when_close_bracket_before_digit)
{
	std::string example = ")4+6";
	ASSERT_ANY_THROW(Arithmetic case1(example));
}
TEST(Arithmetic, throw_when_close_bracket_before_var)
{
	std::string example = ")a+6";
	ASSERT_ANY_THROW(Arithmetic case1(example));
}
TEST(Arithmetic, throw_when_digit_before_binary)
{
	std::string example = "+4-5";
	ASSERT_ANY_THROW(Arithmetic case1(example));
}
TEST(Arithmetic, throw_when_close_bracket_before_binary)
{
	std::string example = "+)-5";
	ASSERT_ANY_THROW(Arithmetic case1(example));
}
TEST(Arithmetic, throw_when_digit_before_close_bracket)
{
	std::string example = "4)+4";
	ASSERT_ANY_THROW(Arithmetic case1(example));
}
TEST(Arithmetic, throw_when_var_before_close_bracket)
{
	std::string example = "ab)+4";
	ASSERT_ANY_THROW(Arithmetic case1(example));
}
TEST(Arithmetic, throw_when_close_bracket_before_close_bracket)
{
	std::string example = "))+4";
	ASSERT_ANY_THROW(Arithmetic case1(example));
}
TEST(Arithmetic, throw_when_start_with_close_bracket)
{
	std::string example = ")";
	ASSERT_ANY_THROW(Arithmetic case1(example));
}
TEST(Arithmetic, throw_when_start_with_binary)
{
	std::string example = "+5";
	ASSERT_ANY_THROW(Arithmetic case1(example));
}
TEST(Arithmetic, throw_when_penultimate_symbol_is_open_bracket)
{
	std::string example = "1+(3";
	ASSERT_ANY_THROW(Arithmetic case1(example));
}
TEST(Arithmetic, throw_when_penultimate_symbol_is_binary)
{
	std::string example = "1+*3";
	ASSERT_ANY_THROW(Arithmetic case1(example));
}
TEST(Arithmetic, throw_when_penultimate_symbol_is_unary)
{
	std::string example = "1~3";
	ASSERT_ANY_THROW(Arithmetic case1(example));
}
TEST(Arithmetic, throw_when_incorrect_symbol)
{
	std::string example = "%";
	ASSERT_ANY_THROW(Arithmetic case1(example));
}
TEST(Arithmetic, throw_when_incorrect_form)
{
	std::string example = "+#*@";
	ASSERT_ANY_THROW(Arithmetic case1(example));
}