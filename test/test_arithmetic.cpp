// тесты для вычисления арифметических выражений

#include <gtest.h>
#include <arithmetic.h>


TEST(TArithmetic, support_all_correct_form_number)
{
	std::string infix1 = "1";
	ASSERT_NO_THROW(Arithmetic try1(infix1));
	std::string infix2 = "1.";
	ASSERT_NO_THROW(Arithmetic try2(infix2));
	std::string infix3 = "1.1";
	ASSERT_NO_THROW(Arithmetic try3(infix3));
	std::string infix4 = ".1";
	ASSERT_NO_THROW(Arithmetic try4(infix4));
	std::string infix5 = "1E1";
	ASSERT_NO_THROW(Arithmetic try5(infix5));
	std::string infix6 = "1E+1";
	ASSERT_NO_THROW(Arithmetic try6(infix6));
	std::string infix7 = "1E-1";
	ASSERT_NO_THROW(Arithmetic try7(infix7));
	std::string infix8 = "1.E1";
	ASSERT_NO_THROW(Arithmetic try8(infix8));
	std::string infix9 = "1.E+1";
	ASSERT_NO_THROW(Arithmetic try9(infix9));
	std::string infix10 = "1.E-1";
	ASSERT_NO_THROW(Arithmetic try10(infix10));
	std::string infix11 = ".1E1";
	ASSERT_NO_THROW(Arithmetic try11(infix11));
	std::string infix12 = ".1E+1";
	ASSERT_NO_THROW(Arithmetic try12(infix12));
	std::string infix13 = ".1E-1";
	ASSERT_NO_THROW(Arithmetic try13(infix13));
}

TEST(TArithmetic, throw_when_incorrect_number)
{
	std::string infix1 = ".";
	ASSERT_ANY_THROW(Arithmetic try1(infix1));
	std::string infix2 = "1E";
	ASSERT_ANY_THROW(Arithmetic try2(infix2));
	std::string infix3 = "1E+";
	ASSERT_ANY_THROW(Arithmetic try3(infix3));
	std::string infix4 = "1E-";
	ASSERT_ANY_THROW(Arithmetic try4(infix4));
	std::string infix5 = "1.E";
	ASSERT_ANY_THROW(Arithmetic try5(infix5));
	std::string infix6 = "1.E+";
	ASSERT_ANY_THROW(Arithmetic try6(infix6));
	std::string infix7 = "1.E-";
	ASSERT_ANY_THROW(Arithmetic try7(infix7));
	std::string infix8 = "1.1E";
	ASSERT_ANY_THROW(Arithmetic try8(infix8));
	std::string infix9 = "1.1E+";
	ASSERT_ANY_THROW(Arithmetic try9(infix9));
	std::string infix10 = "1.1E-";
	ASSERT_ANY_THROW(Arithmetic try10(infix10));
	std::string infix11 = ".1E";
	ASSERT_ANY_THROW(Arithmetic try11(infix11));
	std::string infix12 = ".1E+";
	ASSERT_ANY_THROW(Arithmetic try12(infix12));
	std::string infix13 = ".1E-";
	ASSERT_ANY_THROW(Arithmetic try13(infix13));
}

TEST(TArithmetic, support_variable)
{
	std::string infix1 = "a";
	ASSERT_NO_THROW(Arithmetic try1(infix1));
	std::string infix2 = "abc";
	ASSERT_NO_THROW(Arithmetic try2(infix2));
}

TEST(TArithmetic, throw_when_incorrect_symbol)
{
	std::string infix1 = "#";
	ASSERT_ANY_THROW(Arithmetic try1(infix1));
	std::string infix2 = "&";
	ASSERT_ANY_THROW(Arithmetic try2(infix2));
}


TEST(TArithmetic, support_add)
{
	std::string infix1 = "1+1";
	ASSERT_NO_THROW(Arithmetic try1(infix1));
	std::string infix2 = "1+1+1";
	ASSERT_NO_THROW(Arithmetic try2(infix2));
}

TEST(TArithmetic, support_substract)
{
	std::string infix1 = "1-1";
	ASSERT_NO_THROW(Arithmetic try1(infix1));
	std::string infix2 = "1-1-1";
	ASSERT_NO_THROW(Arithmetic try2(infix2));
}

TEST(TArithmetic, support_multiply)
{
	std::string infix1 = "1*1";
	ASSERT_NO_THROW(Arithmetic try1(infix1));
	std::string infix2 = "1*1*1";
	ASSERT_NO_THROW(Arithmetic try2(infix2));
}

TEST(TArithmetic, support_division)
{
	std::string infix1 = "1/1";
	ASSERT_NO_THROW(Arithmetic try1(infix1));
	std::string infix2 = "1/1/1";
	ASSERT_NO_THROW(Arithmetic try2(infix2));
}

TEST(TArithmetic, support_brackets)
{
	std::string infix1 = "(1+1)";
	ASSERT_NO_THROW(Arithmetic try1(infix1));
	std::string infix2 = "(1*1*1)";
	ASSERT_NO_THROW(Arithmetic try2(infix2));
}

TEST(TArithmetic, can_calculate_correct_infix1)
{
	std::string infix1 = "1+2/2+3E+1";
	Arithmetic try1(infix1);
	ASSERT_NO_THROW(try1.Calculate());
	EXPECT_EQ(try1.Calculate(), 32);
}


TEST(TArithmetic, can_calculate_correct_infix)
{
	std::string infix1 = "14+(1+3)/(2-1)";
	Arithmetic try1(infix1);
	double res = try1.Calculate();
	EXPECT_EQ(res, 18);
}


TEST(TArithmetic, throw_when_incorrect_infix2)
{
	std::string infix1 = "+";
	ASSERT_ANY_THROW(Arithmetic try1(infix1));
	std::string infix2 = "-";
	ASSERT_ANY_THROW(Arithmetic try2(infix2));
	std::string infix3 = "-1)";
	ASSERT_ANY_THROW(Arithmetic try3(infix3));
	std::string infix4 = "(";
	ASSERT_ANY_THROW(Arithmetic try4(infix4));
	std::string infix5 = "()";
	ASSERT_ANY_THROW(Arithmetic try5(infix5));
	std::string infix6 = "(*1)";
	ASSERT_ANY_THROW(Arithmetic try6(infix6));
	std::string infix7 = "a1";
	ASSERT_ANY_THROW(Arithmetic try7(infix7));
	std::string infix8 = "17+";
	ASSERT_ANY_THROW(Arithmetic try8(infix8));
	std::string infix9 = "1/";
	ASSERT_ANY_THROW(Arithmetic try9(infix9));
	std::string infix10 = "(1+1)(2+2)";
	ASSERT_ANY_THROW(Arithmetic try10(infix10));
	std::string infix11 = "7-p(1+1)";
	ASSERT_ANY_THROW(Arithmetic try11(infix11));
	std::string infix12 = "+-14";
	ASSERT_ANY_THROW(Arithmetic try12(infix12));
	std::string infix13 = "1+*2";
	ASSERT_ANY_THROW(Arithmetic try13(infix13));
}

TEST(TArithmetic, throw_when_zero_devision)
{
	std::string infix1 = "1+(2/(1-1))";
	Arithmetic try1(infix1);
	ASSERT_ANY_THROW(try1.Calculate());
}

