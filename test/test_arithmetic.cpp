// тесты для вычисления арифметических выражений

#include <arithmetic.h>
#include <gtest.h>

TEST(Postfix, operation_plus)
{
	std::string str = "a+b+c";
	std::string str1 = "ab+c+";
	Postfix p;

	EXPECT_EQ(str1, p.ToPostfix(str));
}

TEST(Postfix, operation_sub)
{
	std::string str = "a-b-c";
	std::string str1 = "ab-c-";
	Postfix p;

	EXPECT_EQ(str1, p.ToPostfix(str));
}

TEST(Postfix, operation_mul_and_div)
{
	std::string str = "a*b/c";
	std::string str1 = "ab*c/";
	Postfix p;

	EXPECT_EQ(str1, p.ToPostfix(str));
}

TEST(Postfix, operation_unary_minus)
{
	std::string str = "~~a";
	std::string str1 = "~a~";
	Postfix p;

	EXPECT_EQ(str1, p.ToPostfix(str));
}

TEST(Postfix, expression_1)
{
	std::string str = "(a+b-~a)*a";
	std::string str1 = "ab+a~-a*";
	Postfix p;

	EXPECT_EQ(str1, p.ToPostfix(str));
}

TEST(Postfix, expression_2)
{
	std::string str = "~a+(a*a)/a-a";
	std::string str1 = "a~aa*a/+a-";
	Postfix p;

	EXPECT_EQ(str1, p.ToPostfix(str));
}

TEST(Postfix, calculate_operation_plus) 
{
	Postfix p;
	std::string str = "a+b+c";

	std::map<char, double> m;

	m['a'] = 1;
	m['b'] = 2;
	m['c'] = 3;

	EXPECT_EQ(6, p.calculate(p.ToPostfix(str), m));
}

TEST(Postfix, calculate_operation_sub)
{
	Postfix p;
	std::string str = "a-b-c";

	std::map<char, double> m;

	m['a'] = 1;
	m['b'] = 2;
	m['c'] = 3;

	EXPECT_EQ(-4, p.calculate(p.ToPostfix(str), m));
}

TEST(Postfix, calculate_operation_mul_and_div)
{
	Postfix p;
	std::string str = "a*b*c/a";

	std::map<char, double> m;

	m['a'] = 1;
	m['b'] = 2;
	m['c'] = 3;

	EXPECT_EQ(6, p.calculate(p.ToPostfix(str), m));
}

TEST(Postfix, calculate_operation_unary_minus)
{
	Postfix p;
	std::string str = "~a";

	std::map<char, double> m;

	m['a'] = 5;

	EXPECT_EQ(-5, p.calculate(p.ToPostfix(str), m));
}

TEST(Postfix, calculate_expression_1)
{
	Postfix p;
	std::string str = "(a+b-~a)*a";

	std::map<char, double> m;

	m['a'] = 6;
	m['b'] = 3;

	EXPECT_EQ(90, p.calculate(p.ToPostfix(str), m));
}

TEST(Postfix, calculate_expression_2)
{
	Postfix p;
	std::string str = "~a+(a*a)/a-a";

	std::map<char, double> m;

	m['a'] = 5;

	EXPECT_EQ(-5, p.calculate(p.ToPostfix(str), m));
}
