// тесты для вычисления арифметических выражений

#include <gtest.h>
#include "arithmetic.h"

TEST(Operation, can_create_operation)
{
	ASSERT_NO_THROW(Operation op('+', 1, 1));
}

TEST(Operation, can_check_that_operation_is_not_operand)
{
	Operation op('+', 1, 1);
	EXPECT_EQ(op.isOperand(), false);
}

TEST(Operation, can_check_operation_priority)
{
	Operation op1('~', 1, 1);
	EXPECT_EQ(op1.getPriority(), 3);
	Operation op2('+', 2, 2);
	EXPECT_EQ(op2.getPriority(), 1);
	Operation op3('/', 3, 3);
	EXPECT_EQ(op3.getPriority(), 2);
}

TEST(Operation, can_show_operation)
{
	Operation op('+', 1, 1);
	ASSERT_NO_THROW(op.show());
}

TEST(Var, can_create_variable)
{
	map<char, double> mp;
	mp['a'] = 3.0;
	ASSERT_NO_THROW(Var variable('a', mp, 1, 1));
}

TEST(Var, can_check_that_variable_is_operand)
{
	map<char, double> mp;
	mp['a'] = 5.3;
	Var variable('a', mp, 1, 1);
	EXPECT_EQ(variable.isOperand(), true);
}

TEST(Var, can_get_value_of_a_variable)
{
	map<char, double> mp;
	mp['a'] = 8.8;
	Var variable('a', mp, 1, 1);
	EXPECT_EQ(variable.getValue(), 8.8);
}

TEST(Var, can_show_variable)
{
	map<char, double> mp;
	mp['a'] = 3.1;
	Var variable('a', mp, 1, 1);
	ASSERT_NO_THROW(variable.show());
}

TEST(Const, can_create_const)
{
	ASSERT_NO_THROW(Const con("pi", 3.14, 1, 1));
}

TEST(Const, can_check_that_const_is_operand)
{
	Const con("pi", 3.14, 1, 1);
	EXPECT_EQ(con.isOperand(), true);
}

TEST(Const, can_get_value_of_a_const)
{
	Const con("pi", 3.14, 1, 1);
	EXPECT_EQ(con.getValue(), 3.14);
}

TEST(Const, can_show_const)
{
	Const con("pi", 3.14, 1, 1);
	ASSERT_NO_THROW(con.show());
}

TEST(Postfix, can_create_postfix)
{
	ASSERT_NO_THROW(Postfix post("a+b"));
}

TEST(Postfix, can_create_exponential_num)
{
	Postfix expr("1.0e-5");
	expr.convertToPostfix();
	EXPECT_EQ(0.00001, expr.getRes());
}

TEST(Postfix, cant_create_only_operation)
{
	ASSERT_ANY_THROW(Postfix post("+"));
}

TEST(Postfix, cant_create_operation_after_operation)
{
	ASSERT_ANY_THROW(Postfix post("a+*b"));
}

TEST(Postfix, cant_create_operand_after_operand)
{
	ASSERT_ANY_THROW(Postfix post("a+b3.14"));
}

TEST(Postfix, cant_create_only_brackets)
{
	ASSERT_ANY_THROW(Postfix post("()"));
}

TEST(Postfix, cant_create_uncorrect_floating_point_number)
{
	ASSERT_ANY_THROW(Postfix post("1.0.5"));
}

TEST(Postfix, cant_create_with_uncorrect_brackets)
{
	ASSERT_ANY_THROW(Postfix post("(a+b))"));
	ASSERT_ANY_THROW(Postfix post("((a+b)"));
	ASSERT_ANY_THROW(Postfix post(")(a+b)"));
	ASSERT_ANY_THROW(Postfix post("(a+b)("));
}

TEST(Postfix, can_check_that_convert_to_postfix_has_no_exceptions)
{
	Postfix post("a+b");
	ASSERT_NO_THROW(post.convertToPostfix());
}

TEST(Postfix, can_correctly_translate_to_postfix)
{
	Postfix post("a+b");
	post.convertToPostfix();
	string expPost("ab+");
	EXPECT_EQ(expPost, post.getPostfix());
}

TEST(Postfix, can_correctly_translate_to_postfix_with_brackets)
{
	Postfix post("(a+b)/c");
	post.convertToPostfix();
	string expPost("ab+c/");
	EXPECT_EQ(expPost, post.getPostfix());
}

TEST(Postfix, can_correctly_calculate_operation_with_unary_minus)
{
	Postfix post("3-----1");
	post.convertToPostfix();
	EXPECT_EQ(2.0, post.getRes());
}

TEST(Postfix, can_correctly_calculate_operation_with_brakets)
{
	Postfix post("(3.0+(-5.5))*4");
	post.convertToPostfix();
	EXPECT_EQ(-10, post.getRes());
}

TEST(Postfix, can_correctly_calculate_operation_with_exponential_number)
{
	Postfix post("1.0e+5*1.0e-5");
	post.convertToPostfix();
	EXPECT_EQ(1.0, post.getRes());
}

TEST(Postfix, can_correctly_calculate_test1)
{
	Postfix post("(-(-10))");
	post.convertToPostfix();
	EXPECT_EQ(10, post.getRes());
}

TEST(Postfix, can_correctly_calculate_test2)
{
	Postfix post("2+4e-3*(5e+2-(-8))");
	post.convertToPostfix();
	EXPECT_EQ(4.032, post.getRes());
}

TEST(Postfix, can_correctly_calculate_test3)
{
	Postfix post(".8+8.");
	post.convertToPostfix();
	EXPECT_EQ(8.8, post.getRes());
}